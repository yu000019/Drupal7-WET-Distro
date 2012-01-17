<?php
/**
 * @file
 * wetkit_post_install_ui.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function wetkit_post_install_ui_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer xmlsitemap
  $permissions['administer xmlsitemap'] = array(
    'name' => 'administer xmlsitemap',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'xmlsitemap',
  );

  return $permissions;
}
