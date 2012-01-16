<?php
/**
* Implements hook_block_info().
*/
function gov_web_usability_block_info(){
  $blocks['videos_blocks'] = array(
    'info' => t('Videos Block'),
    'status' => TRUE,
    'region' => 'videos',
    'weight' => 0,
    'visibility' => BLOCK_VISIBILITY_NOTLISTED,
  );
  $blocks['videos_blocks2'] = array(
    'info' => t('Bloc Vidéos'),
    'status' => TRUE,
    'region' => 'videos',
    'weight' => 0,
    'visibility' => BLOCK_VISIBILITY_NOTLISTED,
  );
  $blocks['priorities_blocks'] = array(
    'info' => t('Priorities Block'),
    'status' => TRUE,
    'region' => 'priorities',
    'weight' => 0,
    'visibility' => BLOCK_VISIBILITY_NOTLISTED,
  );
  $blocks['priorities_blocks_fr'] = array(
    'info' => t('Bloc Priorités'),
    'status' => TRUE,
    'region' => 'priorities',
    'weight' => 0,
    'visibility' => BLOCK_VISIBILITY_NOTLISTED,
  );
  $blocks['minister_blocks'] = array(
    'info' => t('Minister Block'),
    'status' => TRUE,
    'region' => 'minister',
    'weight' => 0,
    'visibility' => BLOCK_VISIBILITY_NOTLISTED,
  );
  $blocks['minister_blocks_fr'] = array(
    'info' => t('Bloc Ministère'),
    'status' => TRUE,
    'region' => 'minister',
    'weight' => 0,
    'visibility' => BLOCK_VISIBILITY_NOTLISTED,
  );
  $blocks['connected_blocks'] = array(
    'info' => t('Connected Block'),
    'status' => TRUE,
    'region' => 'connected',
    'weight' => 0,
    'visibility' => BLOCK_VISIBILITY_NOTLISTED,
  );
  $blocks['connected_blocks_fr'] = array(
    'info' => t('Bloc Connectés'),
    'status' => TRUE,
    'region' => 'connected',
    'weight' => 0,
    'visibility' => BLOCK_VISIBILITY_NOTLISTED,
  );
  return $blocks;
}

/**
* Implements hook_block_view().
*/
function gov_web_usability_block_view($delta = '') {
  global $language;
  $block = array();
  switch ($delta) {
    case 'videos_blocks':
      $block['subject'] = t('Videos');
      $block['content'] = gov_web_usability_block_contents($delta);
      break;
    case 'videos_blocks2':
      $block['subject'] = t('Vidéos');
      $block['content'] = gov_web_usability_block_contents($delta);
      break;
    case 'priorities_blocks':
      $block['subject'] = t('Priorities');
      $block['content'] = gov_web_usability_block_contents($delta);
      break;
    case 'priorities_blocks_fr':
      $block['subject'] = t('Priorités');
      $block['content'] = gov_web_usability_block_contents($delta);
      break;
    case 'minister_blocks':
      $block['subject'] = t('Minister');
      $block['content'] = gov_web_usability_block_contents($delta);
      break;
    case 'minister_blocks_fr':
      $block['subject'] = t('Ministère');
      $block['content'] = gov_web_usability_block_contents($delta);
      break;
    case 'connected_blocks':
      $block['subject'] = t('Stay Connected');
      $block['content'] = gov_web_usability_block_contents($delta);
      break;
    case 'connected_blocks_fr':
      $block['subject'] = t('Restez connecté');
      $block['content'] = gov_web_usability_block_contents($delta);
      break;
  }
  return $block;
}

/**
* Implements hook_block_configure().
*/
function gov_web_usability_block_configure($delta) {
  $form = array();
  switch($delta) {
  case 'videos_blocks':
    $form['videos_blocks_content'] = array(
      '#type' => 'text_format',
      '#title' => t('Configure Video Block'),
      '#size' => 255,
      '#description' => t('Enter the appropriate markup for the Video Region.'),
      '#default_value' => variable_get('videos_block_content'),
      '#format' => 'full_html',
    );
    break;
  case 'videos_blocks2':
    $form['videos_blocks_content_fr'] = array(
      '#type' => 'text_format',
      '#title' => t('Configure Video Block'),
      '#size' => 255,
      '#description' => t('Enter the appropriate markup for the Video Region.'),
      '#default_value' => variable_get('videos_block_content_fr'),
      '#format' => 'full_html',
    );
    break;
  case 'priorities_blocks':
    $form['priorities_blocks_content'] = array(
      '#type' => 'text_format',
      '#title' => t('Configure Priorities Block'),
      '#size' => 255,
      '#description' => t('Enter the appropriate markup for the Priorities Region.'),
      '#default_value' => variable_get('priorities_block_content'),
      '#format' => 'full_html',
    );
    break;
  case 'priorities_blocks_fr':
    $form['priorities_blocks_content_fr'] = array(
      '#type' => 'text_format',
      '#title' => t('Configure Priorities Block'),
      '#size' => 255,
      '#description' => t('Enter the appropriate markup for the Priorities Region.'),
      '#default_value' => variable_get('priorities_block_content_fr'),
      '#format' => 'full_html',
    );
    break;
  case 'minister_blocks':
    $form['minister_blocks_content'] = array(
      '#type' => 'text_format',
      '#title' => t('Configure Minister Block'),
      '#size' => 255,
      '#description' => t('Enter the appropriate markup for the Minister Region.'),
      '#default_value' => variable_get('minister_block_content'),
      '#format' => 'full_html',
    );
    break;
  case 'minister_blocks_fr':
    $form['minister_blocks_content_fr'] = array(
      '#type' => 'text_format',
      '#title' => t('Configure Minister Block'),
      '#size' => 255,
      '#description' => t('Enter the appropriate markup for the Minister Region.'),
      '#default_value' => variable_get('minister_block_content_fr'),
      '#format' => 'full_html',
    );
    break;
  case 'connected_blocks':
    $form['connected_blocks_content'] = array(
      '#type' => 'text_format',
      '#title' => t('Configure Connected Block'),
      '#size' => 255,
      '#description' => t('Enter the appropriate markup for the Connected Region.'),
      '#default_value' => variable_get('connected_block_content'),
      '#format' => 'full_html',
    );
    break;
  case 'connected_blocks_fr':
    $form['connected_blocks_content_fr'] = array(
      '#type' => 'text_format',
      '#title' => t('Configure Connected Block'),
      '#size' => 255,
      '#description' => t('Enter the appropriate markup for the Connected Region.'),
      '#default_value' => variable_get('connected_block_content_fr'),
      '#format' => 'full_html',
    );
    break;
  }
  return $form;
}

/**
* Implements hook_block_save().
*/
function gov_web_usability_block_save($delta = '', $edit = array()) {
  //dpm($edit);
  switch($delta) {
    case 'videos_blocks':
      variable_set('videos_block_content', (string)$edit['videos_blocks_content']['value']);
      break;
    case 'videos_blocks2':
      variable_set('videos_block_content_fr', (string)$edit['videos_blocks_content_fr']['value']);
      break;
    case 'priorities_blocks':
      variable_set('priorities_block_content', (string)$edit['priorities_blocks_content']['value']);
      break;
    case 'priorities_blocks_fr':
      variable_set('priorities_block_content_fr', (string)$edit['priorities_blocks_content_fr']['value']);
      break;
    case 'minister_blocks':
      variable_set('minister_block_content', (string)$edit['minister_blocks_content']['value']);
      break;
    case 'minister_blocks_fr':
      variable_set('minister_block_content_fr', (string)$edit['minister_blocks_content_fr']['value']);
      break;
    case 'connected_blocks':
      variable_set('connected_block_content', (string)$edit['connected_blocks_content']['value']);
      break;
    case 'connected_blocks_fr':
      variable_set('connected_block_content_fr', (string)$edit['connected_blocks_content_fr']['value']);
      break;
  }
  return;
}

/**
* Implements hook_block_contents().
*/
function gov_web_usability_block_contents($delta) {
  $block = array();
  switch ($delta) {
    case 'videos_blocks':
      global $theme;
      if ($theme == 'genesis_clf' || $theme == 'genesis_clf_intranet') {
        $markup_video = variable_get('videos_block_content');
        return $markup_video;
      }
      break;
    case 'videos_blocks2':
      global $theme;
      if ($theme == 'genesis_clf' || $theme == 'genesis_clf_intranet') {
        $markup_video = variable_get('videos_block_content_fr');
        return $markup_video;
      }
      break;
    case 'priorities_blocks':
      global $theme;
      if ($theme == 'genesis_clf' || $theme == 'genesis_clf_intranet') {
        $markup_priorities = variable_get('priorities_block_content');
        return $markup_priorities;
      }
      break;
    case 'priorities_blocks_fr':
      global $theme;
      if ($theme == 'genesis_clf' || $theme == 'genesis_clf_intranet') {
        $markup_priorities = variable_get('priorities_block_content_fr');
        return $markup_priorities;
      }
      break;
    case 'minister_blocks':
      global $theme;
      if ($theme == 'genesis_clf' || $theme == 'genesis_clf_intranet') {
        $markup_minister = variable_get('minister_block_content');
        return $markup_minister;
      }
      break;
    case 'minister_blocks_fr':
      global $theme;
      if ($theme == 'genesis_clf' || $theme == 'genesis_clf_intranet') {
        $markup_minister = variable_get('minister_block_content_fr');
        return $markup_minister;
      }
      break;
    case 'connected_blocks':
      global $theme;
      if ($theme == 'genesis_clf' || $theme == 'genesis_clf_intranet') {
        $markup_connected = variable_get('connected_block_content');
        return $markup_connected;
      }
      break;
    case 'connected_blocks_fr':
      global $theme;
      if ($theme == 'genesis_clf' || $theme == 'genesis_clf_intranet') {
        $markup_connected = variable_get('connected_block_content_fr');
        return $markup_connected;
      }
      break;
  }
  return $block;
}