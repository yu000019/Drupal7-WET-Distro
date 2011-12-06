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

/**
 * Implements hook_views_api().
 */
function gov_web_usability_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function gov_web_usability_image_default_styles() {
  $styles = array();

  // Exported image style: slider
  $styles['slider'] = array(
    'name' => 'slider',
    'effects' => array(
      1 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '730',
          'height' => '250',
        ),
        'weight' => '1',
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function gov_web_usability_node_info() {
  $items = array(
    'main_slider' => array(
      'name' => t('Main Slider'),
      'base' => 'node_content',
      'description' => t('Main Slider for the Government of Canada'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
