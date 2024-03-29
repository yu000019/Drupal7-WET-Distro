<?php

// TODO: Spellchecker field? What todo about spellchecker...

/**
 * Class for handling a view that gets its data not from the database, but from
 * a Solr server.
 */
class apachesolr_views_query extends views_plugin_query {

  /**
   * Array of parameters for Solr query.
   */
  protected $params;

  /**
   * Array of all encountered errors. Each of these is fatal, meaning that a
   * non-empty $errors property will result in an empty result being returned.
   *
   * @var array
   */
  protected $errors;

  /**
   * The names of all fields whose value is required by a handler. The format
   * follows the same as Search API field identifiers (parent:child).
   *
   * @var array
   */
  protected $fields;

  protected $apachesolr_results;

  public function build(&$view) {
    $view->init_pager();

    // Let the pager modify the query to add limits.
    $this->pager->query();

    // Set aliases of the fields.
    foreach ($view->field as $field_name => &$field) {
      $field->field_alias = $field_name;
      $field->aliases['entity_type'] = 'entity_type';
    }

    // Add fields to the query so they will be shown in solr document.
    $this->params['fl'] = array_keys($view->field);
  }

  /**
   * Executes the query and fills the associated view object with according
   * values.
   *
   * Values to set: $view->result, $view->total_rows, $view->execute_time,
   * $view->pager['current_page'].
   */
  public function execute(&$view) {
    try {
      $start = microtime(TRUE);

      // Execute the search.
      $params = array();
      if (isset($this->params['q'])) {
        $params['q'] =  $this->params['q'];
      }

      $params['rows'] = $this->pager->options['items_per_page'];
      $params['start'] = $this->pager->current_page * $this->pager->options['items_per_page'];

      // If we display all items without pager.
      if ($params['rows'] == 0) {
        $params['rows'] = 100000;
      }

      // Add fields.
      if (isset($this->params['fl'])) {
        $params['fl'] = implode(',', $this->params['fl']);
      }

      // Add filters to parameters.
      if (isset($this->params['filters'])) {
        $params['fq'] = $this->params['filters'];
      }

      // Add sorting.
      $solrsort = '';
      if (isset($this->params['sort'])) {
        $solrsort = implode(', ', $this->params['sort']);
      }

      // Get the Apache Solr "environment id".
      $env_id = NULL;
      if (strpos($view->base_table, 'apachesolr__') === 0) {
        $env_id = substr($view->base_table, 12);
      }

      // Load search query and execute it.
      // $solr = apachesolr_get_solr();
      $solr = apachesolr_get_solr($env_id);
      $query = new SolrBaseQuery('apachesolr', $solr, $params, $solrsort, '');

      $params = array(
        'fl' => array('id', 'entity_id', 'entity_type', 'bundle', 'bundle_name', 'label', 'is_comment_count', 'ds_created', 'ds_changed', 'score', 'path', 'url', 'is_uid', 'tos_name'),
      );
      if ($query) {
        $query->addParams($params);
      }

      apachesolr_search_add_boost_params($query);
      list($final_query, $response) = apachesolr_do_query($query, $this->pager->current_page);
      apachesolr_has_searched(TRUE);

      // This is needed for removing errors in standard field handler.
      // When we move to our custom field handlers this won't be needed.
      // @see views_handler_field_field.inc line 600.
      foreach (apachesolr_search_process_response($response, $final_query) as $result_item) {
        $view->result[] = (object) $result_item;
      }

      // Store apachesolr cached response.
      $this->apachesolr_response = $response;

      // Store the results.
      $this->pager->total_items = $view->total_rows = $this->apachesolr_response->response->numFound;
      $this->pager->update_page_info();


      // We shouldn't use $results['performance']['complete'] here, since
      // extracting the results probably takes considerable time as well.
      $view->execute_time = microtime(TRUE) - $start;
    }
    catch (Exception $e) {
      $this->errors[] = $e->getMessage();
    }

    if ($this->errors) {
      foreach ($this->errors as $msg) {
        drupal_set_message($msg, 'error');
      }
      $view->result = array();
      $view->total_rows = 0;
      $view->execute_time = 0;
      return;
    }
  }

  public function add_filter($type, $value, $exclude = FALSE) {
    $exclude_string = ($exclude) ? '-' : '';
    $this->params['filters'][] = $exclude_string . $type . ':' . $value;
  }

  public function add_filter_string($string) {
    $this->params['q.alt'][] = $string;
  }

  public function add_sort($field, $order) {
    $this->params['sort'][] = $field . ' ' . $order;
  }

  public function add_parameter($key, $value) {
    $this->params[$key] = $value;
  }

  public function add_field($table_alias, $field, $alias = '', $params = array()) {
    if (isset($table_alias[$field])) {
      return $table_alias[$field];
    }
  }

  public function ensure_table($table, $relationship) {
    if ($table == 'node') {
      return drupal_map_assoc(
        array('title', 'type',
            'path', 'path_alias', 'uid', 'name', 'created', 'changed',
            'last_comment_or_change', 'nid', 'status', 'promote', 'moderate',
            'sticky', 'tnid', 'translate', 'language', 'comment_count', 'tid',
            'vid', 'timestamp'
        ));
    }
  }

  public function get_params() {
    return $this->params;
  }
}
