<?php

//Global Theme + Web Usability Variables for Government
$GLOBALS['$gov_theme_internet'] = 'genesis_clf';
$GLOBALS['$gov_theme_intranet'] = 'genesis_clf_intranet';
$GLOBALS['$gov_web_usability'] = 'gov_web_usability';

//Global Theme + Web Usability Variables for Public
$GLOBALS['$public_theme_internet'] = 'genesis_public';
$GLOBALS['$public_theme_intranet'] = 'genesis_public_intranet';
$GLOBALS['$public_web_usability'] = 'public_web_usability';

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
function webexp_form_alter(&$form, $form_state, $form_id) {
  if ($form_id == 'install_configure_form') {
    $roles = array(DRUPAL_AUTHENTICATED_RID);
    $policy = _password_policy_load_active_policy($roles);

    $translate = array();
    if (!empty($policy['policy'])) {
      // Some policy constraints are active.
      password_policy_add_policy_js($policy, 1);
      foreach ($policy['policy'] as $key => $value) {
        $translate['constraint_' . $key] = _password_policy_constraint_error($key, $value);
      }
    }
    // Set a custom form validate and submit handlers.
    $form['#validate'][] = 'webexp_password_validate';
    $form['#submit'][] = 'webexp_password_submit';
  }
}

/**
 * Implements hook_install_configure_form_alter().
 */
function webexp_form_install_configure_form_alter(&$form, &$form_state) {
  $form['site_information']['site_name']['#default_value'] = 'Web Experience Toolkit';
  $form['site_information']['site_mail']['#default_value'] = 'admin@' . $_SERVER['HTTP_HOST'];
  $form['admin_account']['account']['name']['#default_value'] = 'admin';
  $form['admin_account']['account']['mail']['#default_value'] = 'admin@' . $_SERVER['HTTP_HOST'];
  $form['server_settings']['site_default_country']['#default_value'] = 'CA';
}

/**
 * Password save validate handler.
 */
function webexp_password_validate($form, &$form_state) {
  $values = $form_state['values'];
  $account = (object)array('uid' => 1);
  $account->roles = array(DRUPAL_AUTHENTICATED_RID => DRUPAL_AUTHENTICATED_RID);

  if (!empty($values['account']['pass'])) {
    $error = _password_policy_constraint_validate($values['account']['pass'], $account);
    if ($error) {
      form_set_error('pass', st('Your password has not met the basic requirement(s):') . '<ul><li>' . implode('</li><li>', $error) . '</li></ul>');
    }
  }
}

/**
 * Password save submit handler.
 */
function webexp_password_submit($form, &$form_state) {
  global $user;
  $values = $form_state['values'];
  $account = (object)array('uid' => 1);
  // Track the hashed password values which can then be used in the history constraint.
  if ($account->uid && !empty($values['account']['pass'])) {
    _password_policy_store_password($account->uid, $values['account']['pass']);
  }
}

/**
 * Trick to enforce page refresh when theme is changed from an overlay.
 */
function webexp_admin_paths_alter(&$paths) {
  $paths['admin/appearance/default*'] = FALSE;
}

/**
 * Implements hook_install_tasks().
 *
 * Allows the profile to setup and define tasks.
 */
function webexp_install_tasks() {
  //Add important .inc files needed for install once
  include_once 'webexp_install_tasks.inc';
  include_once 'webexp_default_install.inc';
  $webexp_needs_batch_processing = variable_get('webexp_needs_batch_processing', TRUE);
  $tasks = array(
    'webexp_configuration_form' => array(
      'display_name' => st('Web Experience Toolkit: Configuration'),
      'type' => 'form',
    ),
    'webexp_batch_processing' => array(
      'display_name' => st('Import Additional Language(s)'),
      'display' => $webexp_needs_batch_processing,
      'type' => 'batch',
      'run' => $webexp_needs_batch_processing ? INSTALL_TASK_RUN_IF_NOT_COMPLETED : INSTALL_TASK_SKIP,
    ),
    'webexp_final_setup' => array(
    ),
  );
  return $tasks;
}

/**
 * Implements hook_install_tasks_alter().
 *
 * Alters the profile that setups and defines tasks.
 */
function webexp_install_tasks_alter(&$tasks, $install_state) {
  //If using French Locale as default remove associated Install Task
  unset($tasks['install_import_locales']);
  unset($tasks['install_import_locales_remaining']);
}

/**
 * Implements hook_appstore_stores_info().
 */
function webexp_apps_servers_info() {
  $info =  drupal_parse_info_file(dirname(__file__) . '/webexp.info');
  return array(
    'webexp' => array(
      'title' => 'WebExp',
      'description' => "Apps for the Web Experience Toolkit Drupal distro",
      'manifest' => 'http://drupal.ircan.gc.ca/app/query',
      'profile' => 'webexp',
      'profile_version' => isset($info['version']) ? $info['version'] : '7.x-1.0',
      'server_name' => $_SERVER['SERVER_NAME'],
      'server_ip' => $_SERVER['SERVER_ADDR'],
      ),
    );
}