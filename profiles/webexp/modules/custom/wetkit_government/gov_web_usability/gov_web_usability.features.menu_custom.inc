<?php
/**
 * @file
 * gov_web_usability.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function gov_web_usability_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: main-menu
  $menus['main-menu'] = array(
    'menu_name' => 'main-menu',
    'title' => 'WET: Mega Menu',
    'description' => 'The <em>Main</em> megamenu for Web Experience Toolkit',
    'language' => 'und',
    'i18n_mode' => '5',
  );
  // Exported menu: menu-wet-aboutus
  $menus['menu-wet-aboutus'] = array(
    'menu_name' => 'menu-wet-aboutus',
    'title' => 'WET: About Us',
    'description' => 'About Us Section for Web Experience Toolkit',
    'language' => 'und',
    'i18n_mode' => '5',
  );
  // Exported menu: menu-wet-stayconnected
  $menus['menu-wet-stayconnected'] = array(
    'menu_name' => 'menu-wet-stayconnected',
    'title' => 'WET: Stay Connected',
    'description' => 'Stay Connected Section for Web Experience Toolkit',
    'language' => 'und',
    'i18n_mode' => '5',
  );
  // Exported menu: menu-wet-contactus
  $menus['menu-wet-contactus'] = array(
    'menu_name' => 'menu-wet-contactus',
    'title' => 'WET: Contact Us',
    'description' => 'Contact Us Section for Web Experience Toolkit',
    'language' => 'und',
    'i18n_mode' => '5',
  );
  // Exported menu: menu-wet-footer
  $menus['menu-wet-footer'] = array(
    'menu_name' => 'menu-wet-footer',
    'title' => 'WET: Footer',
    'description' => 'Footer Section for Web Experience Toolkit',
    'language' => 'und',
    'i18n_mode' => '5',
  );
  // Exported menu: menu-wet-header
  $menus['menu-wet-header'] = array(
    'menu_name' => 'menu-wet-header',
    'title' => 'WET: Header',
    'description' => 'Header Section for Web Experience Toolkit',
    'language' => 'und',
    'i18n_mode' => '5',
  );
  // Exported menu: menu-wet-news
  $menus['menu-wet-news'] = array(
    'menu_name' => 'menu-wet-news',
    'title' => 'WET: News',
    'description' => 'News Section for Web Experience Toolkit',
    'language' => 'und',
    'i18n_mode' => '5',
  );
  // Exported menu: menu-wet-terms
  $menus['menu-wet-terms'] = array(
    'menu_name' => 'menu-wet-terms',
    'title' => 'WET: Terms',
    'description' => 'Terms Section for Web Experience Toolkit',
    'language' => 'und',
    'i18n_mode' => '5',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('WET: About Us');
  t('WET: Contact Us');
  t('WET: News');
  t('WET: Stay Connected');
  t('WET: Terms');
  t('WET: Footer');
  t('WET: Header');
  t('WET: Mega Menu');
  t('The <em>Main</em> megamenu for Web Experience Toolkit');
  t('About Us Section for Web Experience Toolkit');
  t('Stay Connected Section for Web Experience Toolkit');
  t('Contact Us Section for Web Experience Toolkit');
  t('Footer Section for Web Experience Toolkit');
  t('Header Section for Web Experience Toolkit');
  t('News Section for Web Experience Toolkit');
  t('Terms Section for Web Experience Toolkit');
  
  return $menus;
}
