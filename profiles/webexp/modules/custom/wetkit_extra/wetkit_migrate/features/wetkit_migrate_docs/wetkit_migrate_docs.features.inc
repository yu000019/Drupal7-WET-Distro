<?php
/**
 * @file
 * wetkit_migrate_docs.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function wetkit_migrate_docs_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}
