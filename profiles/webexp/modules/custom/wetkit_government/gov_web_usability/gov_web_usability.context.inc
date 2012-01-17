<?php
/**
 * @file
 * gov_web_usability.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function gov_web_usability_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'front_page_views';
  $context->description = 'Views for Front Page';
  $context->tag = 'views';
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
  t('Views for Front Page');
  t('views');
  $export['front_page_views'] = $context;

  return $export;
}
