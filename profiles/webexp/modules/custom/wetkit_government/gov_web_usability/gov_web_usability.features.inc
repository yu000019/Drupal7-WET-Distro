<?php
/**
 * @file
 * gov_web_usability.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function gov_web_usability_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
