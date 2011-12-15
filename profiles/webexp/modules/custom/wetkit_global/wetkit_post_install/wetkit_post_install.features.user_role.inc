<?php
/**
 * @file
 * wetkit_post_install.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function wetkit_post_install_user_default_roles() {
  $roles = array();

  // Exported role: administrator
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => '2',
  );

  // Exported role: author
  $roles['author'] = array(
    'name' => 'author',
    'weight' => '3',
  );

  // Exported role: information architect
  $roles['information architect'] = array(
    'name' => 'information architect',
    'weight' => '5',
  );

  // Exported role: information developer
  $roles['information developer'] = array(
    'name' => 'information developer',
    'weight' => '6',
  );

  // Exported role: module manager
  $roles['module manager'] = array(
    'name' => 'module manager',
    'weight' => '7',
  );

  // Exported role: stakeholder
  $roles['stakeholder'] = array(
    'name' => 'stakeholder',
    'weight' => '8',
  );

  return $roles;
}
