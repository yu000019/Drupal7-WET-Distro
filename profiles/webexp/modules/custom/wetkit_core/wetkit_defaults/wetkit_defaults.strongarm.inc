<?php
/**
 * @file
 * wetkit_defaults.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function wetkit_defaults_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'features_ignored_orphans';
  $strongarm->value = array(
    'context_ui' => 'context_ui',
    'pathauto' => 'pathauto',
    'path' => 'path',
    'search' => 'search',
    'entity_token' => 'entity_token',
    'wetkit_ckeditor' => 'wetkit_ckeditor',
    'wetkit_wizard_default' => 'wetkit_wizard_default',
    'wetkit_wizard_default_dev' => 'wetkit_wizard_default_dev',
  );
  $export['features_ignored_orphans'] = $strongarm;

  return $export;
}
