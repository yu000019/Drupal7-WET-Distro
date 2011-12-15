<?php
/**
 * @file template.php
 */

/**
 * Automatically rebuild the theme registry.
 * Uncomment to use during development.
 */
// drupal_theme_rebuild();

/**
 * Override or insert variables into all templates.
 */
function genesis_process(&$vars) {
  // Provide a variable to check if the page is in the overlay.
  if (module_exists('overlay')) {
    $vars['in_overlay'] = (overlay_get_mode() == 'child');
  }
  else {
    $vars['in_overlay'] = FALSE;
  }
}

/**
 * Override or insert variables into the html template.
 */
function genesis_preprocess_html(&$vars) {
  // Additional body classes to help out themers.
  if (!$vars['is_front']) {
    // Add unique class for each page.
    $path = drupal_get_path_alias($_GET['q']);
    // Add unique class for each website section.
    list($section, ) = explode('/', $path, 2);
    if (arg(0) == 'node') {
      if (arg(1) == 'add') {
        $section = 'page-node-add';
      }
      elseif (is_numeric(arg(1)) && (arg(2) == 'edit' || arg(2) == 'delete')) {
        $section = 'page-node-' . arg(2);
      }
    }
    $vars['classes_array'][] = drupal_html_class('section-' . $section);
  }
}

/**
 * Override or insert variables into the page template.
 */
function genesis_process_page(&$vars) {
  // Add a wrapper div using the title_prefix and title_suffix render elements.
  if (!empty($vars['title_suffix']['add_or_remove_shortcut']) ) {
    $vars['title_prefix']['shortcut_wrapper'] = array(
      '#markup' => '<div class="shortcut-wrapper clearfix">',
      '#weight' => 100,
    );
    $vars['title_suffix']['shortcut_wrapper'] = array(
      '#markup' => '</div>',
      '#weight' => -99,
    );
    // Make sure the shortcut link is the first item in title_suffix.
    $vars['title_suffix']['add_or_remove_shortcut']['#weight'] = -100;
  }
}

/**
 * Override or insert variables into page templates.
 */
function genesis_preprocess_page(&$vars) {
  $vars['logo_alt_text'] = check_plain(variable_get('site_name', '')) .' '. t('logo');
  $vars['logo_img'] = $vars['logo'] ? '<img src="'. check_url($vars['logo']) .'" alt="'. $vars['logo_alt_text'] .'"/>' : '';
  $vars['linked_site_logo'] = $vars['logo_img'] ? l($vars['logo_img'], '<front>', array(
    'attributes' => array(
      'rel' => 'home',
      'title' => t('Home page')
    ),
    'html' => TRUE,
    )
  ) : '';
  if (theme_get_setting('toggle_name') == FALSE) {
    $vars['visibility'] = 'element-invisible';
    $vars['hide_site_name'] = TRUE;
  }
  else {
    $vars['visibility'] = '';
    $vars['hide_site_name'] = FALSE;
  }
  $sitename = filter_xss_admin(variable_get('site_name', 'Drupal'));
  $vars['site_name'] = $sitename ? l($sitename, '<front>', array(
    'attributes' => array(
      'rel' => 'home',
      'title' => t('Home page')),
    )
  ) : '';
  // Set variables for the main menu and secondary links menu.
  $vars['main_menu_links'] = theme('links__system_main_menu',
    array(
      'links' => $vars['main_menu'],
      'attributes' => array(
      'id' => 'wet-boew-navigation',
        'class' => array(
          'links', 'clearfix', 'site-bar show-first rounded',
        )
      ), 
      'heading' => array(
        'text' => t('Main menu'),
        'level' => 'h2',
        'class' => array(
          'element-invisible',
        ),
      )
    )
  );
  $vars['secondary_menu_links'] = theme('links__system_secondary_menu',
    array(
      'links' => $vars['secondary_menu'],
      'attributes' => array(
        'id' => 'secondary-menu',
        'class' => array(
          'links', 'clearfix',
        ),
      ),
      'heading' => array(
        'text' => t('Secondary menu'),
        'level' => 'h2',
        'class' => array(
          'element-invisible',
        ),
      )
    )
  );
  // Work-around a stupid bug in Drupal 7...
  if (arg(0) == 'user' && arg(1) == 'login') {
    drupal_set_title(t('User login'));
  }
  if (arg(0) == 'user' && arg(1) == 'password') {
    drupal_set_title(t('Request new password'));
  }
  if (arg(0) == 'user' && arg(1) == 'register') {
    drupal_set_title(t('Create new account'));
  }
}

/**
 * Override or insert variables into the node templates.
 */
function genesis_preprocess_node(&$vars) {
  global $user;
  $node = $vars['node'];
  // Add to node classes.
  if ($node->uid && $node->uid == $user->uid) {
    // Node is authored by current user.
   $vars['classes_array'][] = 'node-mine';
  }
  $vars['title_attributes_array']['class'][] = 'node-title';
  $vars['content_attributes_array']['class'][] = 'node-content';
  if ($vars['page']) {
    // Node is displayed as teaser.
    $vars['classes_array'][] = 'node-view';
  }
  // rewrite submitted to use time, datetime and pubdate
  $vars['datetime'] = format_date($vars['created'], 'custom', 'c');
  if (variable_get('node_submitted_' . $vars['node']->type, TRUE)) {
    $vars['submitted'] = t('Submitted by !username on !datetime',
      array(
        '!username' => $vars['name'],
        '!datetime' => '<time datetime="' . $vars['datetime'] . '" pubdate="pubdate">' . $vars['date'] . '</time>',
      )
    );
  }
  else {
    $vars['submitted'] = '';
  }
  // Set variable for status.
  if (!$vars['status']) {
    $vars['unpublished'] = TRUE;
  }
  else {
    $vars['unpublished'] = FALSE;
  }
}

/**
 * Override or insert variables in comment templates.
 */
function genesis_preprocess_comment(&$vars) {
  // Add odd and even classes to comments
  $vars['classes_array'][] = $vars['zebra'];
  $vars['title_attributes_array']['class'][] = 'comment-title';
  $vars['content_attributes_array']['class'][] = 'comment-content';
  // inject a whole bunch of stuff into comments
  $uri = entity_uri('comment', $vars['comment']);
  $uri['options'] += array('attributes' => array('rel' => 'bookmark'));
  $vars['title'] = l($vars['comment']->subject, $uri['path'], $uri['options']);
  $vars['permalink'] = l(t('Permalink'), $uri['path'], $uri['options']);
  $vars['created'] = '<span class="date-time permalink">' . l($vars['created'], $uri['path'], $uri['options']) . '</span>';
  $vars['datetime'] = format_date($vars['comment']->created, 'custom', 'c');
}

/**
 * Override or insert variables into block templates.
 */
function genesis_preprocess_block(&$vars) {
  $block = $vars['block'];
  $vars['title'] = $block->subject;
  // Special classes for blocks
  $vars['classes_array'][] = 'block-' . $vars['block_zebra'];
  $vars['classes_array'][] = 'block-' . drupal_html_class($block->region);
  $vars['classes_array'][] = 'block-count-' . $vars['id'];
  $vars['title_attributes_array']['class'][] = 'block-title';
  $vars['content_attributes_array']['class'][] = 'block-content';
  $nav_blocks = array('navigation', 'main-menu', 'management', 'user-menu');
  if (in_array($vars['block']->delta, $nav_blocks)) {
    $vars['theme_hook_suggestions'][] = 'block__menu';
  }
  $nav_modules = array('superfish', 'nice_menus');
  if (in_array($vars['block']->module, $nav_modules)) {
    $vars['theme_hook_suggestions'][] = 'block__menu';
  }
}

/**
 * Changes the search form to use the "search" input element of HTML5 (from the Boron theme).
 */
function genesis_preprocess_search_block_form(&$vars) {
  $vars['search_form'] = str_replace('type="text"', 'type="search"', $vars['search_form']);
}

/**
 * hook_html_head_alter().
 */
function genesis_html_head_alter(&$head_elements) {
  $head_elements['system_meta_content_type']['#attributes'] = array(
    'charset' => 'utf-8',
  );
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function genesis_form_search_form_alter(&$form, $form_state) {
  if (isset($form['module']) && $form['module']['#value'] == 'node' && user_access('use advanced search')) {
    // Keyword boxes:
    $form['advanced'] = array(
      '#type' => 'fieldset',
      '#title' => t('Advanced search'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#attributes' => array('class' => array('search-advanced')),
    );
    $form['advanced']['keywords-fieldset'] = array(
      '#type' => 'fieldset',
      '#title' => t('Keywords'),
      '#collapsible' => FALSE,
    );
    $form['advanced']['keywords-fieldset']['keywords'] = array(
      '#prefix' => '<div class="criterion">',
      '#suffix' => '</div>',
    );
    $form['advanced']['keywords-fieldset']['keywords']['or'] = array(
      '#type' => 'textfield',
      '#title' => t('Containing any of the words'),
      '#size' => 30,
      '#maxlength' => 255,
    );
    $form['advanced']['keywords-fieldset']['keywords']['phrase'] = array(
      '#type' => 'textfield',
      '#title' => t('Containing the phrase'),
      '#size' => 30,
      '#maxlength' => 255,
    );
    $form['advanced']['keywords-fieldset']['keywords']['negative'] = array(
      '#type' => 'textfield',
      '#title' => t('Containing none of the words'),
      '#size' => 30,
      '#maxlength' => 255,
    );
    // Node types:
    $types = array_map('check_plain', node_type_get_names());
    $form['advanced']['types-fieldset'] = array(
      '#type' => 'fieldset',
      '#title' => t('Types'),
      '#collapsible' => FALSE,
    );
    $form['advanced']['types-fieldset']['type'] = array(
      '#type' => 'checkboxes',
      '#prefix' => '<div class="criterion">',
      '#suffix' => '</div>',
      '#options' => $types,
    );
    $form['advanced']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Advanced search'),
      '#prefix' => '<div class="action advanced-search-submit">',
      '#suffix' => '</div>',
      '#weight' => 99,
    );
    // Languages:
    $language_options = array();
    foreach (language_list('language') as $key => $entity) {
      $language_options[$key] = $entity->name;
    }
    if (count($language_options) > 1) {
      $form['advanced']['lang-fieldset'] = array(
        '#type' => 'fieldset',
        '#title' => t('Languages'),
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
      );
      $form['advanced']['lang-fieldset']['language'] = array(
        '#type' => 'checkboxes',
        '#prefix' => '<div class="criterion">',
        '#suffix' => '</div>',
        '#options' => $language_options,
      );
    }
    $form['#validate'][] = 'node_search_validate';
  }
}

/**
 * Set a class on the iframe body element for WYSIWYG editors. This allows you
 * to easily override the background for the iframe body element.
 * This only works for the WYSIWYG module: http://drupal.org/project/wysiwyg
 */
function genesis_wysiwyg_editor_settings_alter(&$settings, &$context) {
  $settings['bodyClass'] = 'wysiwygeditor';
}
