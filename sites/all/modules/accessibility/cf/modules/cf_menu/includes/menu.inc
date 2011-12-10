<?php

/**
 * Displays the content accessibility menu page which presents links to content easement management pages.
 */
function cf_menu_accessibility_page() {
  $blocks = array();

  drupal_set_title(t("Content Accessibility"), PASS_THROUGH);

  $results = db_query("SELECT * FROM {menu_router} AS mr INNER JOIN {menu_links} AS ml ON mr.path = ml.router_path WHERE mr.path LIKE 'admin/content/accessibility/%' AND NOT mr.path LIKE 'admin/content/accessibility/%/%'", array(), array('fetch' => PDO::FETCH_ASSOC));

  if ($results){
    $available_paths = $results->fetchAll();

    foreach ($available_paths as $key => $value){
      _menu_link_translate($value);

      // The link description, either derived from 'description' in hook_menu()
      // or customized via menu module is used as title attribute.
      if (!empty($value['localized_options']['attributes']['title'])) {
        $value['description'] = $value['localized_options']['attributes']['title'];
        unset($value['localized_options']['attributes']['title']);
      }

      $block = $value;
      $block['title'] = l($value['link_title'], $value['router_path']);
      $block['content'] = '';

      $compact = system_admin_compact_mode();

      if (isset($value['description'])){
        $style='';

        if ($compact) {
          $style = " style='display: none;'";
        }

        $block['content'] .= '<div' . $style . '>' . filter_xss_admin($value['description']) . '</div>';
      }

      if (!empty($block['content'])) {
        $block['show'] = TRUE;
      }

      // Prepare for sorting as in function _menu_tree_check_access().
      // The weight is offset so it is always positive, with a uniform 5-digits.
      $blocks[(50000 + $value['weight']) . ' ' . $value['title'] . ' ' . $value['mlid']] = $block;
    }
  }

  if (empty($blocks)) {
    return t("There are no links available on this page.");
  }
  else {
    ksort($blocks);
    return theme('admin_page', array('blocks' => $blocks));
  }
}
