<?php
/**
 * @file
 * wetkit_defaults.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function wetkit_defaults_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'sitewide_defaults';
  $context->description = 'Default Sitewide Blocks for WET Distro';
  $context->tag = 'Sitewide';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'locale-language_content' => array(
          'module' => 'locale',
          'delta' => 'language_content',
          'region' => 'sidebar_first',
          'weight' => '-25',
        ),
        'shortcut-shortcuts' => array(
          'module' => 'shortcut',
          'delta' => 'shortcuts',
          'region' => 'sidebar_first',
          'weight' => '-24',
        ),
        'system-navigation' => array(
          'module' => 'system',
          'delta' => 'navigation',
          'region' => 'sidebar_first',
          'weight' => '-23',
        ),
        'admin-account' => array(
          'module' => 'admin',
          'delta' => 'account',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
        'system-help' => array(
          'module' => 'system',
          'delta' => 'help',
          'region' => 'content',
          'weight' => '-10',
        ),
        'system-main' => array(
          'module' => 'system',
          'delta' => 'main',
          'region' => 'content',
          'weight' => '-9',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Default sitewide Blocks and Boxes for WET Distro');
  t('Sitewide');
  $export['sitewide_defaults'] = $context;

  return $export;
}
