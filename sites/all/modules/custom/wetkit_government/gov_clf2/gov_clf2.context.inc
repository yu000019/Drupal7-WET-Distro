<?php
/**
 * @file
 * gov_clf2.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function gov_clf2_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'clf_2';
  $context->description = 'Blocks related to the CLF 2.0 Theme';
  $context->tag = 'clf2';
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
        'search-form' => array(
          'module' => 'search',
          'delta' => 'form',
          'region' => 'solrsearch',
          'weight' => '-10',
        ),
        'locale-language' => array(
          'module' => 'locale',
          'delta' => 'language',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Blocks related to the CLF 2.0 Theme');
  t('clf2');
  $export['clf_2'] = $context;

  return $export;
}
