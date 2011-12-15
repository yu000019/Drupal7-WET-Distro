<?php
/**
 * @file
 * gov_clf2.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function gov_clf2_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}
