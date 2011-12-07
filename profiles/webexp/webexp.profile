<?php

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
function webexp_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the configuration form
  $form['site_information']['site_name']['#default_value'] = 'Web Experience Toolkit';
  $form['site_information']['site_mail']['#default_value'] = 'first.last@department.ca';
  $form['admin_account']['account']['name']['#default_value'] = 'admin';
  $form['admin_account']['account']['mail']['#default_value'] = 'first.last@department.ca';
  $form['server_settings']['site_default_country']['#default_value'] = 'CA';
}

/**
 * Implements hook_install_tasks().
 *
 * Allows the profile to install and defines the tasks.
 */
function webexp_install_tasks() {
  // Here, we define a variable to allow tasks to indicate that a particular,
  // processor-intensive batch process needs to be triggered later on in the
  // installation.
  $webexp_needs_batch_processing = variable_get('webexp_needs_batch_processing', TRUE);
  $tasks = array(
    'webexp_choices_form' => array(
      'display_name' => st('Web Experience Toolkit: Selection'), 
      'type' => 'form',
    ), 
    'webexp_setup_form' => array(
      'display_name' => st('Web Experience Toolkit: Configuration'), 
      'type' => 'form',
    ), 
    'webexp_batch_processing' => array(
      'display_name' => st('Import French Language'), 
      'display' => $webexp_needs_batch_processing, 
      'type' => 'batch', 
      'run' => $webexp_needs_batch_processing ? INSTALL_TASK_RUN_IF_NOT_COMPLETED : INSTALL_TASK_SKIP,
    ),
    'webexp_final_site_setup' => array(
    ),
  );
  return $tasks;
}

/**
 * Implements hook_choices_form().
 *
 * Allows the profile to implement the choices form.
 */
function webexp_choices_form() {
  
  //Continue configuration
  drupal_set_title(st('Web Experience Toolkit'));
  drupal_set_message('This area will assist in adding a more tailored user experience based on business requirements. Configuration will be will further differentiated based on the type of site and whether for governmental use.','status', FALSE);  
  
  $options = array('1' => t('Internet'), '0' => t('Intranet'));
  $options2 = array('1' => t('Yes'), '0' => t('No'));
   
  //Start setting up the form
  $form = array();
  $form['webexp_site'] = array(
    '#type' => 'radios',
    '#title' => st('Site intended to be used for which of type of website?'),
    '#default_value' =>  variable_get('radio_site', 1),
    '#options' => $options,
    '#description' => st('This option will change the default theme that will be used based on the type of site.'),
  );
  $form['webexp_govern'] = array(
    '#type' => 'radios',
    '#title' => st('Is this for Governmental Use?'),
    '#default_value' =>  variable_get('radio_govern', 1),
    '#options' => $options2,
    '#description' => st('Please be certain that the wetkit module is included in the base install platform for this operation to succeed.'),
  );
  $form[] = array(
    '#type' => 'submit',
    '#value' => st('Save and continue'),
  );
  //Return the form back to parent
  return $form;
}

/**
 * Implements hook_choices_form_submit().
 *
 * Allows the profile to create the form submit.
 */
function webexp_choices_form_submit($form, &$form_state) { 
  if (variable_get('webexp_site', 0) == 1)
  {
    theme_disable(array('bartik'));
    theme_enable(array('genesis_clf_intranet'));
    variable_set('theme_default', 'genesis_clf_intranet');
  }
  else {
    theme_disable(array('bartik'));
    theme_enable(array('genesis_clf'));
    variable_set('theme_default', 'genesis_clf');
  }
}

/**
 * Implements hook_setup_form().
 *
 * Allows the profile to create the setup form.
 */
function webexp_setup_form() {

  $options = array('1' => t('Enabled'), '0' => t('Disabled'));
  
  //Start setting up the form
  $form = array();
  $form['webexp_development'] = array(
    '#type' => 'radios',
    '#title' => st('Enable Development Module(s)?'),
    '#default_value' =>  variable_get('radio_development', 1),
    '#options' => $options,
    '#description' => st('Modules that will assist with Development for the Web Experience Toolkit based websites.'),
  );
  $form['webexp_workflow'] = array(
    '#type' => 'radios',
    '#title' => st('Enable Workflow Module(s)?'),
    '#default_value' =>  variable_get('radio_workflow', 1),
    '#options' => $options,
    '#description' => st('Modules that will assist with Workflows for the Web Experience Toolkit based websites.'),
  );
  $form['webexp_wysiwyg'] = array(
    '#type' => 'radios',
    '#title' => st('Enable CKEditor Module(s)?'),
    '#default_value' =>  variable_get('radio_wysiwyg', 1),
    '#options' => $options,
    '#description' => st('Modules that relate to a WYSIWYG Editor (CKEditor).'),
  );
  $form['webexp_skinr'] = array(
    '#type' => 'radios',
    '#title' => st('Enable Skinr Module(s)?'),
    '#default_value' =>  variable_get('radio_skinr', 1),
    '#options' => $options,
    '#description' => st('Modules that deal with Skinning Integration.'),
  );
  $form['webexp_nodecontent'] = array(
    '#type' => 'radios',
    '#title' => st('Add Default Node Content'),
    '#default_value' =>  variable_get('radio_nodecontent', 1),
    '#options' => $options,
    '#description' => st('Programmatically Created Node Content.'),
  );
  $form['webexp_clf3'] = array(
    '#type' => 'radios',
    '#title' => st('Enable CLF3 Prototype'),
    '#default_value' =>  variable_get('radio_clf3', 1),
    '#options' => $options,
    '#description' => st('CLF3 Prototype theme integrated with WET (80%).'),
  );
  $form['webexp_rules'] = array(
    '#type' => 'radios',
    '#title' => st('Enable Rules Functionality (Recommended)'),
    '#default_value' =>  variable_get('radio_rules', 1),
    '#options' => $options,
    '#description' => st('Enable the Rules Suite of Modules + Wet Features related to workflows.'),
  );
  $form[] = array(
    '#type' => 'submit',
    '#value' => st('Save and continue'),
  );
  //Return the form back to parent
  return $form;
  
}

/**
 * Implements hook_form_submit().
 *
 * Allows the profile to create the form submit.
 */
function webexp_setup_form_submit($form, &$form_state) {
    //Set variables in the drupal variable table
    variable_set('radio_development', $form_state['values']['webexp_development']);
    variable_set('radio_workflow', $form_state['values']['webexp_workflow']);
    variable_set('radio_wysiwyg', $form_state['values']['webexp_wysiwyg']);
    variable_set('radio_skinr', $form_state['values']['webexp_skinr']);
    variable_set('radio_nodecontent', $form_state['values']['webexp_nodecontent']);
    variable_set('radio_clf3', $form_state['values']['webexp_clf3']);
    variable_set('radio_rules', $form_state['values']['webexp_rules']);
    variable_set('views_headline', 1);
}

/**
 * Implements hook_batch_processing().
 *
 * Allows the profile to perform batch processing.
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
 * Implements hook_final_site_setup().
 *
 * Allows the profile to perform operations during the final install task.
 */
function webexp_final_site_setup() {
  //Based on selected configuration install modules
  webexp_addmodules();
  //Delete all of the variables inside the variables table
  variable_del('webexp_needs_batch_processing');
  variable_del('radio_development');
  variable_del('radio_workflow');
  variable_del('radio_wysiwyg');
  variable_del('radio_skinr');
  variable_del('radio_nodecontent');
  variable_del('radio_clf3');
  variable_del('radio_rules');
}

/**
 * Implements webexp_addmodules().
 *
 * Custom function to add ancilliary modules.
 */
function webexp_addmodules() {
  //Module Selection Screen
  if (variable_get('radio_development', 0) == 1)
  {
    $module_list = array('devel','devel_generate','coder','coder_review','migrate','migrate_ui','migrate_extras','querypath','qpa','wetkit_migrate');
    module_enable($module_list, TRUE);
  }
  if (variable_get('radio_workflow', 0) == 1)
  {
    $module_list = array('workbench','workbench_access','workbench_files','workbench_moderation');
    module_enable($module_list, TRUE);
  }
  if (variable_get('radio_wysiwyg', 0) == 1)
  {
    $module_list = array('ckeditor','ckeditor_link','imce','wetkit_ckeditor');
    module_enable($module_list, TRUE);
    //features_revert(array('wetkit_ckeditor' => array('ckeditor_profile')));
  }
  if (variable_get('radio_skinr', 0) == 1)
  {
    $module_list = array('skinr','skinr_ui','wetkit_styles');
    module_enable($module_list, TRUE);
  }
  if (variable_get('radio_nodecontent', 0) == 1)
  {
    include_once DRUPAL_ROOT . '/profiles/webexp/includes/webexp.node.inc';
    webexp_nodes();
  }
  if (variable_get('radio_clf3', 0) == 1)
  {
    $module_list = array('gov_web_usability','gov_clf2','admin_menu');
    module_enable($module_list, TRUE);
    drupal_add_css(drupal_get_path('module', 'webexp') . '/css/adminmenu.css', array('group' => CSS_THEME, 'every_page' => TRUE));

  }
  if (variable_get('radio_rules', 0) == 1)
  {
    $module_list = array('rules','rules_scheduler','rules_admin','wetkit_workflow_rules');
    module_enable($module_list, TRUE);
  }
}

/**
 * Implements hook_install_tasks_alter().
 *
 * Allows the profile to alter the install tasks.
 */
function webexp_install_tasks_alter(&$tasks, $install_state) {
  // Replace the "Install Finished" installation task provided by Drupal core
  //$tasks['install_finished']['function'] = 'webexp_locale_addition';
}
