<?php

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
        $translate['constraint_'. $key] = _password_policy_constraint_error($key, $value);
      }
    }
    // Set a custom form validate and submit handlers.
    $form['#validate'][] = 'webexp_password_validate';
    $form['#submit'][] = 'webexp_password_submit';  
  }
}

/**
 * implements hook_install_configure_form_alter().
 */
function webexp_form_install_configure_form_alter(&$form, &$form_state) {
  $form['site_information']['site_name']['#default_value'] = 'Web Experience Toolkit';
  $form['site_information']['site_mail']['#default_value'] = 'admin@'. $_SERVER['HTTP_HOST']; 
  $form['admin_account']['account']['name']['#default_value'] = 'admin';
  $form['admin_account']['account']['mail']['#default_value'] = 'admin@'. $_SERVER['HTTP_HOST']; 
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
      form_set_error('pass', st('Your password has not met the basic requirement(s):') .'<ul><li>'. implode('</li><li>', $error) .'</li></ul>');
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
  include_once 'webexp_custom_install.inc';
  include_once 'webexp_default_install.inc';
  
  $webexp_needs_batch_processing = variable_get('webexp_needs_batch_processing', TRUE);
  $tasks = array(
    'webexp_batch_processing' => array(
      'display_name' => st('Import Additional Language(s)'), 
      'display' => $webexp_needs_batch_processing, 
      'type' => 'batch', 
      'run' => $webexp_needs_batch_processing ? INSTALL_TASK_RUN_IF_NOT_COMPLETED : INSTALL_TASK_SKIP,
    ),
    'webexp_type_install_form' => array(
      'display_name' => st('Web Experience Toolkit: Installation Type'), 
      'type' => 'form',
    ), 
    'webexp_configuration_form' => array(
      'display_name' => st('Web Experience Toolkit: Further Configuration'), 
      'type' => 'form',
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
  //Get Locale Language
  global $install_state;
  $lang_val = isset($install_state['parameters']['locale']);
  
  //If using French Locale as default remove associated Install Task
  if ($lang_val == 'fr')
  {
    unset($tasks['webexp_batch_processing']);
  }
}

 