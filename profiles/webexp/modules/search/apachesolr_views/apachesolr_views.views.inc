<?php

/*
 * Load files with base classes of the contained classes.
 */

/**
 * Implementation of hook_views_plugins().
 */
function apachesolr_views_views_plugins() {
  return array(
    'module' => 'apachesolr_views',
    'query' => array(
      'apachesolr_views_query' => array(
        'title' => t('Apache Solr Query'),
        'help' => t('Query that allows you to search with Apache Solr.'),
        'handler' => 'apachesolr_views_query',
        'parent' => 'views_query',
      ),
    ),
  );

}

/**
 * Implementation of hook_views_data().
 */
function apachesolr_views_views_data() {
  // Provide a Views base table for each Apache Solr "environment".
  foreach (apachesolr_load_all_environments() as $env_id => $environment) {
    $apachesolr_base_table = 'apachesolr__' . $environment['env_id'];
    $data[$apachesolr_base_table]['table'] = array(
      'group' => t('Apache Solr'),
      'base' => array(
        'query class' => 'apachesolr_views_query',
        'title' => t('Apache Solr @name', array('@name' => $environment['name'])),
        'help' => t('Searches the site with the Apache Solr search engine for @name', array('@name' => $environment['name'])),
        'field' => 'id',
        'entity type' => NULL,
        'apachesolr_environment' => $env_id,
      ),
    );

    // Fetch a list of fields from Solr.
    try {
      $solr = apachesolr_get_solr($env_id);
      $solr_fields = $solr->getFields(1);
    }
    catch (Exception $e) {
      watchdog('Apache Solr Views', nl2br(check_plain($e->getMessage())), NULL, WATCHDOG_ERROR);
      $solr_fields = array();
    }

    // Add fields to the base table.
    $sortable = array();
    foreach ($solr_fields as $solr_field_name => $solr_field) {
      // If this is not a sort field, add field and filter arguments.
      if (strpos($solr_field_name, 'sort_') !== 0) {
        // Title and label translation are handled by
        // apachesolr_views_field_names() and friends.
        $data[$apachesolr_base_table][$solr_field_name] = apachesolr_views_field_names($solr_field_name);
        $data[$apachesolr_base_table][$solr_field_name]['field'] = array(
          'handler' => 'apachesolr_views_handler_field',
          'click sortable' => TRUE,
        );
        $data[$apachesolr_base_table][$solr_field_name]['filter'] = array(
          'handler' => 'apachesolr_views_handler_filter',
        );
        $data[$apachesolr_base_table][$solr_field_name]['sort'] = array(
          'handler' => 'apachesolr_views_handler_sort',
        );
      }
      else {
        // Otherwise, track sort fields to improve sorting in the next step.
        $sortable[] = $solr_field_name;
      }
    }

    // If sort_* fields correspond with other fields, improve sorting.
    $excluded_fields = array('bundle_name');
    foreach ($sortable as $sort_field_name) {
      $pattern = '/^([a-z]+_)?' . preg_quote(substr($sort_field_name, 5), '/') . '$/';
      foreach ($solr_fields as $solr_field_name => $solr_field) {
        if ($sort_field_name != $solr_field_name && preg_match($pattern, $solr_field_name) && !in_array($solr_field_name, $excluded_fields)) {
          // Use the sort field for click sorting.
          $data[$apachesolr_base_table][$solr_field_name]['field']['click sortable'] = TRUE;
          $data[$apachesolr_base_table][$solr_field_name]['field']['click sort field'] = $sort_field_name;
          // And use the sort field for explicit sorts.
          $data[$apachesolr_base_table][$solr_field_name]['sort']['real_field'] = $sort_field_name;
        }
      }
    }
  }

  // Views of the default Apache Solr environment.
  foreach (module_invoke_all('apachesolr_entities') as $base_table => $definition) {
    $name = $definition['name'];
    $base_field = $definition['base_field'];
    $apachesolr_base_table = 'apachesolr_' . $base_table;
    $data[$apachesolr_base_table]['table']['group'] = t('Apache Solr');

    $data[$apachesolr_base_table]['table']['base'] = array(
      'query class' => 'apachesolr_views_query',
      'title' => t('Apache Solr @name', array('@name' => $name)),
      'help' => t('Searches the site with the Apache Solr search engine for @name', array('@name' => $name)),
      'field' => $base_field,
      'entity type' => 'node',
    );

//    $data[$apachesolr_base_table]['text'] = array(
//      'title' => t('Search'),
//      'help' => t('Searches the content with Solr'),
//      'filter' => array(
//        'handler' => 'apachesolr_views_handler_filter_search',
//      ),
//    );

//    $data[$apachesolr_base_table]['nid'] = array(
//      'title' => t('Nid'),
//      'help' => t('The node ID of the node.'),
//      'field' => array(
//        'handler' => 'views_handler_field_node',
//        'click sortable' => TRUE,
//      ),
//      'sort' => array(
//        'handler' => 'apachesolr_views_handler_sort',
//      ),
//    );

    // Get the list of the fields in idex directly from Solr.
    // $solr = apachesolr_get_solr();
    // $solr_fields = $solr->getFields(1);
    try {
      $solr = apachesolr_get_solr();
      $solr_fields = $solr->getFields(1);
    }
    catch (Exception $e) {
      $solr_fields = array();
      watchdog('Apache Solr Views', nl2br(check_plain($e->getMessage())), NULL, WATCHDOG_ERROR);
    }

    foreach ($solr_fields as $solr_field_name => $solr_field) {

      // We do not allow to display 'sort_*' fields.
      if (strpos($solr_field_name, 'sort_') === 0) {
        continue;
      }

      $field_type = $solr_field->type;

      $field_names = apachesolr_views_field_names($solr_field_name);

      $data[$apachesolr_base_table][$solr_field_name] = array(
        'title' => t($field_names['title']),
        'help' => t($field_names['help']),
        'field' => array(
          'handler' => 'apachesolr_views_handler_field',
          'click sortable' => TRUE,
        ),
        // Information for accepting a nid as an argument
//        'argument' => array(
//          'handler' => 'views_handler_argument_node_nid',
//          'name field' => 'title', // the field to display in the summary.
//          'numeric' => TRUE,
//          'validate type' => 'nid',
//        ),
        'filter' => array(
          'handler' => 'apachesolr_views_handler_filter',
        ),
        'sort' => array(
          'handler' => 'apachesolr_views_handler_sort',
        ),
      );
    }

  }

  return $data;
}
