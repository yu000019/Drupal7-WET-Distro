<?php
/**
 * @file
 * wetkit_migrate_docs.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function wetkit_migrate_docs_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'migration_html_documentation';
  $context->description = 'Migration module placed block control';
  $context->tag = 'Migration';
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
        'menu-menu-documentation' => array(
          'module' => 'menu',
          'delta' => 'menu-documentation',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Migration module placed block control');
  t('migrate');
  $export['migration_html_documentation'] = $context;

  return $export;
}
