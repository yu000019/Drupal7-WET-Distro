<?php

function genesis_clf_menu_local_tasks(&$variables) {
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

function genesis_clf_theme_theme($existing, $type, $theme, $path) {
  
}

function genesis_clf_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  $crumbs = '';
  if (!empty($breadcrumb)) {
      $crumbs = '<ol class="breadcrumbs">';

      foreach($breadcrumb as $value) {
           $crumbs .= '<li>'.$value.'</li>';
      }
      $crumbs .= '</ol>';
    }
      return $crumbs;
  }
  
function genesis_clf_form_alter(&$form, &$form_state, $form_id){
  if ($form_id == 'search_form'){
      $form['basic']['keys']['#id'] = 'cn-search';
      $form['basic']['submit']['#id'] = 'cn-search-submit';
  }
}
