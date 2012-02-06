<?php
/**
 * @file
 * template-overrides.php
 */

function genesis_public_menu_local_tasks(&$variables) {
  $output = '';
  if (!empty($variables['primary'])) {
    $variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Drupal Primary tabs') . '</h2>';
    $variables['primary']['#prefix'] .= '<ul class="drupaltabs primary">';
    $variables['primary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['primary']);
  }
  if (!empty($variables['secondary'])) {
    $variables['secondary']['#prefix'] = '<h2 class="element-invisible">' . t('Drupal Secondary tabs') . '</h2>';
    $variables['secondary']['#prefix'] .= '<ul class="drupaltabs secondary">';
    $variables['secondary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['secondary']);
  }
  return $output;
}

function genesis_public_theme_theme($existing, $type, $theme, $path) {

}

function genesis_public_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  $crumbs = '';
  if (!empty($breadcrumb)) {
    $crumbs = '<ol class="breadcrumbs">';
    foreach ($breadcrumb as $value) {
      $crumbs .= '<li>' . $value . '</li>';
    }
    $crumbs .= '</ol>';
  }
  return $crumbs;
}

function genesis_public_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == 'search_form') {
      $form['basic']['keys']['#id'] = 'cn-search';
      $form['basic']['submit']['#id'] = 'cn-search-submit';
  }
}

/**
 * Theme function for the form.
 */
function genesis_public_boxes_box($variables) {
  $block = $variables['block'];
  $output = "<div id='boxes-box-" . $block['delta'] . "' class='boxes-box" . (!empty($block['editing']) ? ' boxes-box-editing' : '') . "'>";
  $output .= '<div class="boxes-box-content">' . $block['content'] . '</div>';
  if (!empty($block['controls'])) {
    //$output .= '<div class="boxes-box-controls">';
    //$output .= $block['controls'];
    //$output .= '</div>';
  }
  if (!empty($block['editing'])) {
    $output .= '<div class="box-editor">' . drupal_render($block['editing']) . '</div>';
  }
  $output .= '</div>';
  return $output;
}