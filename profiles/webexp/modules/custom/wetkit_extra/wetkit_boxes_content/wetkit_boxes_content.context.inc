<?php
/**
 * @file
 * wetkit_boxes_content.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function wetkit_boxes_content_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'wetkit_default_boxes';
  $context->description = 'Default Multilingual Boxes for WET Distro';
  $context->tag = 'Boxes';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'boxes-videos_box' => array(
          'module' => 'boxes',
          'delta' => 'videos_box',
          'region' => 'videos',
          'weight' => '-10',
        ),
        'boxes-priorities_box' => array(
          'module' => 'boxes',
          'delta' => 'priorities_box',
          'region' => 'priorities',
          'weight' => '-10',
        ),
        'boxes-minister_box' => array(
          'module' => 'boxes',
          'delta' => 'minister_box',
          'region' => 'minister',
          'weight' => '-10',
        ),
        'boxes-connected_box' => array(
          'module' => 'boxes',
          'delta' => 'connected_box',
          'region' => 'connected',
          'weight' => '-10',
        ),
        'views-headlines_front_page-block' => array(
          'module' => 'views',
          'delta' => 'headlines_front_page-block',
          'region' => 'headlines',
          'weight' => '-10',
        ),
        'views-slider-block' => array(
          'module' => 'views',
          'delta' => 'slider-block',
          'region' => 'slideshow',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Boxes');
  t('Default Multilingual Boxes for Distro');
  $export['stayconnected_boxes'] = $context;

  return $export;
}
