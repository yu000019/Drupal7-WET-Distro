<?php

/**
 * @file wurfl_cache.inc
 *  This files allow to override the default drupal cache in order to support theme switching based
 *  on device type and device group.
 *
 *  In order to enable this file, add the following to your settings.php file
 *  $conf['page_cache_fastpath'] = FALSE,
 *  $conf['cache_inc'] = './sites/all/modules/wurfl/wurfl_cache.inc',
 * );
 *
 */


/**
 * Return data from the persistent cache. Data may be stored as either plain text or as serialized data.
 * cache_get will automatically return unserialized objects and arrays.
 *
 * @param $cid
 *   The cache ID of the data to retrieve.
 * @param $this->bin
 *   The table $this->bin to store the data in. Valid core values are 'cache_filter',
 *   'cache_menu', 'cache_page', or 'cache' for the default cache.
 */

WurflCachImplementation implements DrupalCacheInterface {

  function __construct($bin) {
    $this->bin = $bin;
  }

  function get($cid) {
    global $user;
    if ($this->bin == 'cache_page') {
      cache_rewrite_cid($cid);
    }
    // Garbage collection necessary when enforcing a minimum cache lifetime
    $cache_flush = variable_get('cache_flush_' . $this->bin, 0);
    if ($cache_flush && ($cache_flush + variable_get('cache_lifetime', 0) <= REQUEST_TIME)) {
      // Reset the variable immediately to prevent a meltdown in heavy load situations.
      variable_set('cache_flush_' . $this->bin, 0);
      // Time to flush old cache data
      $delete = db_delete($this->bin);
      $delete->condition('expire', CACHE_PERMANENT, '!=')
        ->condition('expire', $cache_flush, '<=');
      $delete->execute();
    }

    $cache = db_fetch_object(db_query("SELECT data, created, headers, expire, serialized FROM {" . $this->bin . "} WHERE cid = '%s'", $cid));
    if (isset($cache->data)) {
      // If the data is permanent or we're not enforcing a minimum cache lifetime
      // always return the cached data.
      if ($cache->expire == CACHE_PERMANENT || !variable_get('cache_lifetime', 0)) {
        $cache->data = db_decode_blob($cache->data);
        if ($cache->serialized) {
          $cache->data = unserialize($cache->data);
        }
      }
      // If enforcing a minimum cache lifetime, validate that the data is
      // currently valid for this user before we return it by making sure the
      // cache entry was created before the timestamp in the current session's
      // cache timer. The cache variable is loaded into the $user object by
      // sess_read() in session.inc.
      else {
        if ($user->cache > $cache->created) {
          // This cache data is too old and thus not valid for us, ignore it.
          return 0;
        }
        else {
          $cache->data = db_decode_blob($cache->data);
          if ($cache->serialized) {
            $cache->data = unserialize($cache->data);
          }
        }
      }
      return $cache;
    }
    return 0;
  }

  /**
   * Store data in the persistent cache.
   *
   * The persistent cache is split up into four database
   * tables. Contributed modules can add additional tables.
   *
   * 'cache_page': This table stores generated pages for anonymous
   * users. This is the only table affected by the page cache setting on
   * the administrator panel.
   *
   * 'cache_menu': Stores the cachable part of the users' menus.
   *
   * 'cache_filter': Stores filtered pieces of content. This table is
   * periodically cleared of stale entries by cron.
   *
   * 'cache': Generic cache storage table.
   *
   * The reasons for having several tables are as follows:
   *
   * - smaller tables allow for faster selects and inserts
   * - we try to put fast changing cache items and rather static
   *   ones into different tables. The effect is that only the fast
   *   changing tables will need a lot of writes to disk. The more
   *   static tables will also be better cachable with MySQL's query cache
   *
   * @param $cid
   *   The cache ID of the data to store.
   * @param $data
   *   The data to store in the cache. Complex data types will be automatically serialized before insertion.
   *   Strings will be stored as plain text and not serialized.
   * @param $this->bin
   *   The table $this->bin to store the data in. Valid core values are 'cache_filter',
   *   'cache_menu', 'cache_page', or 'cache'.
   * @param $expire
   *   One of the following values:
   *   - CACHE_PERMANENT: Indicates that the item should never be removed unless
   *     explicitly told to using cache_clear_all() with a cache ID.
   *   - CACHE_TEMPORARY: Indicates that the item should be removed at the next
   *     general cache wipe.
   *   - A Unix timestamp: Indicates that the item should be kept at least until
   *     the given time, after which it behaves like CACHE_TEMPORARY.
   * @param $headers
   *   A string containing HTTP header information for cached pages.
   */
  function set($cid, $data, $expire = CACHE_PERMANENT, $headers = NULL) {
    if ($this->bin == 'cache_page') {
      cache_rewrite_cid($cid);
    }
    $serialized = 0;
    if (is_object($data) || is_array($data)) {
      $data = serialize($data);
      $serialized = 1;
    }
    $created = REQUEST_TIME;
    db_query("UPDATE {" . $this->bin . "} SET data = %b, created = %d, expire = %d, headers = '%s', serialized = %d WHERE cid = '%s'", $data, $created, $expire, $headers, $serialized, $cid);
    if (!db_affected_rows()) {
      @db_query("INSERT INTO {" . $this->bin . "} (cid, data, created, expire, headers, serialized) VALUES ('%s', %b, %d, %d, '%s', %d)", $cid, $data, $created, $expire, $headers, $serialized);
    }
  }

  /**
   *
   * Expire data from the cache. If called without arguments, expirable
   * entries will be cleared from the cache_page and cache_block tables.
   *
   * @param $cid
   *   If set, the cache ID to delete. Otherwise, all cache entries that can
   *   expire are deleted.
   *
   * @param $this->bin
   *   If set, the table $this->bin to delete from. Mandatory
   *   argument if $cid is set.
   *
   * @param $wildcard
   *   If $wildcard is TRUE, cache IDs starting with $cid are deleted in
   *   addition to the exact cache ID specified by $cid.  If $wildcard is
   *   TRUE and $cid is '*' then the entire table $this->bin is emptied.
   */
  function clear_all($cid = NULL, $wildcard = FALSE) {
    global $user;

    if (!isset($cid) && !isset($this->bin)) {
      // Clear the block cache first, so stale data will
      // not end up in the page cache.
      cache_clear_all(NULL, 'cache_block');
      cache_clear_all(NULL, 'cache_page');
      return;
    }

    if (empty($cid)) {
      if (variable_get('cache_lifetime', 0)) {
        // We store the time in the current user's $user->cache variable which
        // will be saved into the sessions table by sess_write(). We then
        // simulate that the cache was flushed for this user by not returning
        // cached data that was cached before the timestamp.
        $user->cache = REQUEST_TIME;

        $cache_flush = variable_get('cache_flush_' . $this->bin, 0);
        if ($cache_flush == 0) {
          // This is the first request to clear the cache, start a timer.
          variable_set('cache_flush_' . $this->bin, REQUEST_TIME);
        }
        elseif (REQUEST_TIME > ($cache_flush + variable_get('cache_lifetime', 0))) {
          // Clear the cache for everyone, cache_lifetime seconds have
          // passed since the first request to clear the cache.
          db_query("DELETE FROM {" . $this->bin . "} WHERE expire != %d AND expire < %d", CACHE_PERMANENT, REQUEST_TIME);
          variable_set('cache_flush_' . $this->bin, 0);
        }
      }
      else {
        // No minimum cache lifetime, flush all temporary cache entries now.
        db_query("DELETE FROM {" . $this->bin . "} WHERE expire != %d AND expire < %d", CACHE_PERMANENT, REQUEST_TIME);
      }
    }
    else {
      if ($wildcard) {
        if ($cid == '*') {
          db_query("TRUNCATE TABLE {" . $this->bin . "}");
        }
        else {
          db_query("DELETE FROM {" . $this->bin . "} WHERE cid LIKE '%s%%'", $cid);
        }
      }
      else {
        db_query("DELETE FROM {" . $this->bin . "} WHERE cid = '%s'", $cid);
      }
    }
  }

  /**
   *
   */
  function cache_rewrite_cid(&$cid) {
    if (empty($_SERVER['HTTP_USER_AGENT'])) {
      return;
    }
    global $wurflManager_ ;
    include_once 'sites/all/libraries/wurfl-php-1.1/WURFL/Application.php';
    $wurflConfigFile = 'sites/all/libraries/wurfl-php-1.1/resources/wurfl-config.xml';
    $wurflConfig = new WURFL_Configuration_XmlConfig($wurflConfigFile);
    $wurflManagerFactory = new WURFL_WURFLManagerFactory($wurflConfig);
    $wurflManager = $wurflManagerFactory->create();
    $requestingDevice =  $wurflManager->getDeviceForHttpRequest($_SERVER);
    $result['type'] = ($requestingDevice->getCapability("is_wireless_device") == 'true') ? 'mobile' : 'desktop'; // This is strange, return value is string, not boolean
    $width = $requestingDevice->getCapability('resolution_width');
    $height =  $requestingDevice->getCapability('resolution_height');
    $browser = $requestingDevice->getCapability('mobile_browser');
    if (!in_array($browser, array("Safari", "Android Webkit"))) {
      $result['group'] = 'low_end';
    }
    elseif (($height < 320 && $width < 480) || ($height < 480 && $width < 320)) {
      $result['group'] = 'low_end';
    }
    else {
      $result['group'] = 'high_end';
    }
    $query = $_GET;
    unset($query['q']);
    $seperator = count($query) ? '&' : '?';
    $cid =  $cid . $seperator . 'mobile_group=' . $result['group'] . '&device=' . $result['type'];
  }

}
