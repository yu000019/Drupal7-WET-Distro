<?php

function _custom_setup_form() {
  //Start setting up the form
  $options = array('1' => st('Enabled'), '0' => st('Disabled'));
  $options_site = array('internet' => st('Internet'), 'intranet' => st('Intranet'));
  $options_branding = array('government' => st('Government'), 'public' => st('Public'));
  
  $form = array();
  $form['webexp_govern'] = array(
    '#type' => 'radios',
    '#title' => st('Is this for Government or Public Use?'),
    '#default_value' =>  variable_get('radio_organization', 'government'),
    '#options' => $options_branding,
    '#description' => st('Please be certain that the wetkit module is included in the base install platform for this operation to succeed.'),
  );
  $form['webexp_site'] = array(
    '#type' => 'radios',
    '#title' => st('Site intended to be used for which of type of website?'),
    '#default_value' =>  variable_get('radio_internet_intranet', 'internet'),
    '#options' => $options_site,
    '#description' => st('This option will change the default theme that will be used based on the type of site.'),
  );
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
    '#default_value' =>  variable_get('radio_web_usability', 1),
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

function _custom_submit_form($form, &$form_state) {
  variable_set('radio_internet_intranet', $form_state['values']['webexp_site']);
  variable_set('radio_development', $form_state['values']['webexp_development']);
  variable_set('radio_workflow', $form_state['values']['webexp_workflow']);
  variable_set('radio_wysiwyg', $form_state['values']['webexp_wysiwyg']);
  variable_set('radio_skinr', $form_state['values']['webexp_skinr']);
  variable_set('radio_nodecontent', $form_state['values']['webexp_nodecontent']);
  variable_set('radio_web_usability', $form_state['values']['webexp_clf3']);
  variable_set('radio_rules', $form_state['values']['webexp_rules']);
  variable_set('radio_organization', $form_state['values']['webexp_govern']);
}

function _custom_run_form() {
  //If Government Site
  if (variable_get('radio_organization') == 'government')
  {
    //If Government Site and Internet Theme
    if (variable_get('radio_internet_intranet') == 'internet')
    {
      theme_disable(array('bartik'));
      theme_enable(array('genesis_clf'));
      variable_set('theme_default', 'genesis_clf');
    }
    //If Government Site and Intranet Theme
    else {
      theme_disable(array('bartik'));
      theme_enable(array('genesis_clf_intranet'));
      variable_set('theme_default', 'genesis_clf_intranet');
    }
  }
  //If Non-Government Site
  else if (variable_get('radio_organization') == 'public') 
  {
    theme_disable(array('bartik'));
    theme_enable(array('genesis_public'));
    variable_set('theme_default', 'genesis_public');
  }
  
  //Enable Dev Modules
  if (variable_get('radio_development', 0) == 1)
  {
    $module_list = array('devel','devel_generate','coder','coder_review','migrate','migrate_ui','migrate_extras','querypath','qpa');
    module_enable($module_list, TRUE);
  }
  
  //Enable Workflow Modules
  if (variable_get('radio_workflow', 0) == 1)
  {
    $module_list = array('workbench','workbench_access','workbench_files','workbench_moderation');
    module_enable($module_list, TRUE);
  }
  
  //Enable WYSIWYG Modules
  if (variable_get('radio_wysiwyg', 0) == 1)
  {
    $module_list = array('ckeditor','ckeditor_link','imce');
    module_enable($module_list, TRUE);
  }
  
  //Enable Skinr Modules
  if (variable_get('radio_skinr', 0) == 1)
  {
    $module_list = array('skinr','skinr_ui');
    module_enable($module_list, TRUE);
  }
  
  //Enable Rules Modules
  if (variable_get('radio_rules', 0) == 1)
  {
    $module_list = array('rules','rules_scheduler','rules_admin');
    module_enable($module_list, TRUE);
  }
  
  //Enable Features
  if (variable_get('radio_organization') == 'government')
  {
    $module_list = array('wetkit_migrate','wetkit_ckeditor','wetkit_styles','wetkit_slider','wetkit_workflow_rules','wetkit_workflow_rules');
    module_enable($module_list, TRUE);
    
    //Kinda hackish but has to be run after first set
    $module_list = array('gov_web_usability');
    module_enable($module_list, TRUE);
    
  }
  
  else if (variable_get('radio_organization') == 'public')
  {
    $module_list = array('wetkit_migrate','wetkit_ckeditor','wetkit_styles','wetkit_slider','wetkit_workflow_rules','wetkit_workflow_rules');
    module_enable($module_list, TRUE);
    
    //Kinda hackish but has to be run after first set
    $module_list = array('public_web_usability');
    module_enable($module_list, TRUE);
  }
  
}

function _custom_flush_vars() {
  //Remove Temporary Variables from variable table
  variable_del('radio_development');
  variable_del('radio_workflow');
  variable_del('radio_wysiwyg');
  variable_del('radio_skinr');
  variable_del('radio_nodecontent');
  variable_del('radio_web_usability');
  variable_del('radio_rules');
  variable_del('radio_internet_intranet');
  variable_del('radio_organization');
}