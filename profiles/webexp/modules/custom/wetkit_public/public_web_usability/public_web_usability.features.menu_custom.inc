<?php
/**
 * @file
 * public_web_usability.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function public_web_usability_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: main-menu
  $menus['main-menu'] = array(
    'menu_name' => 'main-menu',
    'title' => 'Main menu',
    'description' => 'The <em>Main</em> menu is used on many sites to show the major sections of the site, often in a top navigation bar.',
    'language' => 'und',
    'i18n_mode' => '5',
  );
  // Exported menu: menu-goc-about-us-bar
  $menus['menu-goc-about-us-bar'] = array(
    'menu_name' => 'menu-goc-about-us-bar',
    'title' => 'GoC About Us Bar',
    'description' => 'About Us Section for Web Experience Toolkit',
    'language' => 'und',
    'i18n_mode' => '5',
  );
  // Exported menu: menu-goc-connected-bar
  $menus['menu-goc-connected-bar'] = array(
    'menu_name' => 'menu-goc-connected-bar',
    'title' => 'GoC Stay Connected Bar',
    'description' => '',
    'language' => 'und',
    'i18n_mode' => '5',
  );
  // Exported menu: menu-goc-contact-bar
  $menus['menu-goc-contact-bar'] = array(
    'menu_name' => 'menu-goc-contact-bar',
    'title' => 'GoC Contact Us Bar',
    'description' => '',
    'language' => 'und',
    'i18n_mode' => '5',
  );
  // Exported menu: menu-goc-footer-bar
  $menus['menu-goc-footer-bar'] = array(
    'menu_name' => 'menu-goc-footer-bar',
    'title' => 'Goc Footer Bar',
    'description' => 'Government of Canada Footer Menu Area',
    'language' => 'und',
    'i18n_mode' => '5',
  );
  // Exported menu: menu-goc-nav-bar
  $menus['menu-goc-nav-bar'] = array(
    'menu_name' => 'menu-goc-nav-bar',
    'title' => 'Goc Nav Bar',
    'description' => '',
    'language' => 'und',
    'i18n_mode' => '5',
  );
  // Exported menu: menu-goc-news-bar
  $menus['menu-goc-news-bar'] = array(
    'menu_name' => 'menu-goc-news-bar',
    'title' => 'GoC News Bar',
    'description' => '',
    'language' => 'und',
    'i18n_mode' => '5',
  );
  // Exported menu: menu-goc-terms-bar
  $menus['menu-goc-terms-bar'] = array(
    'menu_name' => 'menu-goc-terms-bar',
    'title' => 'GoC Terms Bar',
    'description' => '',
    'language' => 'und',
    'i18n_mode' => '5',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('About Us Section for Web Experience Toolkit');
  t('GoC About Us Bar');
  t('GoC Contact Us Bar');
  t('GoC News Bar');
  t('GoC Stay Connected Bar');
  t('GoC Terms Bar');
  t('Goc Footer Bar');
  t('Goc Nav Bar');
  t('Government of Canada Footer Menu Area');
  t('Main menu');
  t('The <em>Main</em> menu is used on many sites to show the major sections of the site, often in a top navigation bar.');


  return $menus;
}
