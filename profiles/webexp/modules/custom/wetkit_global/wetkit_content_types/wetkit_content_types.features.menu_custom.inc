<?php
/**
 * @file
 * wetkit_content_types.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function wetkit_content_types_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-documentation
  $menus['menu-documentation'] = array(
    'menu_name' => 'menu-documentation',
    'title' => 'Documentation',
    'description' => 'Documentation Menu Block',
    'language' => 'und',
    'i18n_mode' => '5',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Documentation');
  t('Documentation Menu Block');


  return $menus;
}
