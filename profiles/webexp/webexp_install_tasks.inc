<?php

/**
 * Implements hook_batch_processing().
 *
 * FIRST TASK: Allows the profile to install the french language.
 */
function webexp_batch_processing() {
  //Import the French po file and translate the interface;
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
 * Implements hook_choices_form().
 *
 * SECOND TASK: Allows the profile to implement the choices form.
 */
function webexp_type_install_form() {
  drupal_set_title(st('Web Experience Toolkit'));
  drupal_set_message('The following areas will assist in adding a more tailored user experience based on business requirements. Configuration will be will further differentiated based on the type of site and whether for governmental use.','status', FALSE);  

  $options_install = array('default' => t('Default'), 'custom' => t('Custom'));
  $options_branding = array('government' => t('Government'), 'public' => t('Public'));
  
  $form = array();
  $form['webexp_type_install'] = array(
    '#type' => 'radios',
    '#title' => st('What is the type of install you wish to use?'),
    '#default_value' =>  variable_get('radio_type_install', 'default'),
    '#options' => $options_install,
    '#description' => st('Please select your installation method. It is recommended to install the default package if you are not sure.'),
  );
  $form['webexp_govern'] = array(
    '#type' => 'radios',
    '#title' => st('Is this for Government or Public Use?'),
    '#default_value' =>  variable_get('radio_organization', 'government'),
    '#options' => $options_branding,
    '#description' => st('Please be certain that the wetkit module is included in the base install platform for this operation to succeed.'),
  );
  $form[] = array(
    '#type' => 'submit',
    '#value' => st('Save and continue'),
  );
  return $form; 
}

/**
 * Implements hook_choices_form_submit().
 *
 * SECOND TASK: Allows the profile to create the form submit.
 */
function webexp_type_install_form_submit($form, &$form_state) {
  //Assign Variables
  variable_set('radio_type_install', $form_state['values']['webexp_type_install']);
  variable_set('radio_organization', $form_state['values']['webexp_govern']);
}

/**
 * Implements hook_setup_form().
 *
 * THIRD TASK: Allows the profile to create the setup form.
 */
function webexp_configuration_form() {
  //Custom Installation
  if (variable_get('radio_type_install') == 'custom') {
    return _custom_setup_form();
  }
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
  //Custom Installation
  if (variable_get('radio_type_install') == 'custom') {
    return _custom_submit_form($form, &$form_state);
  }
  //Default Installation
  else if (variable_get('radio_type_install') == 'default') {
    return _default_submit_form($form, &$form_state);
  }
}

/**
 * Implements hook_final_site_setup().
 *
 * FINAL TASK: Allows the profile to perform final tasks based on gathered information.
 */
function webexp_final_setup() {
  //Custom Installation
  if (variable_get('radio_type_install') == 'custom') {
    _custom_run_form();
    _custom_flush_vars();
  }
  //Default Installation
  else if (variable_get('radio_type_install') == 'default') {
    _default_run_form();
    _default_flush_vars();
  }
  //Flush global variables
  _global_flush_vars();
}

function _global_flush_vars() {
  variable_del('webexp_needs_batch_processing');
  variable_del('radio_type_install');
  variable_del('radio_organization');
}