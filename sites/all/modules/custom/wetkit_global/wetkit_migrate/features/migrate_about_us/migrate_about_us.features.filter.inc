<?php
/**
 * @file
 * migrate_about_us.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function migrate_about_us_filter_default_formats() {
  $formats = array();

  // Exported format: Import HTML
  $formats['import_html'] = array(
    'format' => 'import_html',
    'name' => 'Import HTML',
    'cache' => '1',
    'status' => '1',
    'weight' => '0',
    'filters' => array(
      'filter_url' => array(
        'weight' => '0',
        'status' => '1',
        'settings' => array(
          'filter_url_length' => '72',
        ),
      ),
      'filter_htmlcorrector' => array(
        'weight' => '10',
        'status' => '1',
        'settings' => array(),
      ),
    ),
  );

  return $formats;
}
