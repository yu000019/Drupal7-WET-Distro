<?php
/**
 * @file
 * Code for the webexp_install_tasks.inc file.
 */

/**
 * Implements hook_batch_processing().
 *
 * FIRST TASK: Allows the profile to install the additional language (english or french).
 */
function webexp_batch_processing(&$install_state) {
  //Import the additonal language po file and translate the interface;
  //Require once is only added here because too early in the bootstrap
  require_once 'includes/locale.inc';
  require_once 'includes/form.inc';

  //Call funtion locale_add_language in locale.inc
  locale_add_language('fr');
  //Batch up the process + import existing po files
  $batch = locale_batch_by_language('fr');
  return $batch;

}

/**
 * Implements hook_setup_form().
 *
 * THIRD TASK: Allows the profile to create the setup form.
 */
function webexp_configuration_form() {
  //Override when install form disabled
  variable_set('radio_type_install', 'default');
  //Default Installation
  if (variable_get('radio_type_install') == 'default') {
    return _default_setup_form();
  }
}

/**
 * Implements hook_form_submit().
 *
 * THIRD TASK: Allows the profile to create the form submit.
 */
function webexp_configuration_form_submit($form, &$form_state) {
  //Default Installation
  if (variable_get('radio_type_install') == 'default') {
    return _default_submit_form($form, $form_state);
  }
}

/**
 * Implements hook_final_site_setup().
 *
 * FINAL TASK: Allows the profile to perform final tasks based on gathered information.
 */
function webexp_final_setup() {
  //Default Installation
  if (variable_get('radio_type_install') == 'default') {
    _default_run_form();
    _default_flush_vars();
  }
  //Flush global variables
  _global_flush_vars();
}

function _global_flush_vars() {
  variable_del('webexp_needs_batch_processing');
  variable_del('radio_type_install');
}