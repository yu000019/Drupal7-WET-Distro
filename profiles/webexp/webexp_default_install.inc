<?php

function _default_setup_form() {
  //Start setting up the form
  $options_site = array('internet' => t('Internet'), 'intranet' => t('Intranet'));
  $options_branding = array('government' => t('Government'), 'public' => t('Public'));
    
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
  $form[] = array(
    '#type' => 'submit',
    '#value' => st('Save and continue'),
  );
  //Return the form back to parent
  return $form;
}

function _default_submit_form($form, &$form_state) {
  variable_set('radio_internet_intranet', $form_state['values']['webexp_site']);
  variable_set('radio_organization', $form_state['values']['webexp_govern']);
}

function _default_run_form() {  
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
  
  //Enable Sample Node Content
  include_once DRUPAL_ROOT . '/profiles/webexp/includes/webexp.node.inc';
  webexp_nodes();
  
  //Enable Dev Modules
  $module_list = array('devel','devel_generate','coder','coder_review','migrate','migrate_ui','migrate_extras','querypath','qpa');
  module_enable($module_list, TRUE);
  
  //Enable Workflow Modules
  $module_list = array('workbench','workbench_access','workbench_files','workbench_moderation');
  module_enable($module_list, TRUE);
  
  //Enable WYSIWYG Modules
  $module_list = array('ckeditor','ckeditor_link','imce');
  module_enable($module_list, TRUE);
  
  //Enable Skinr Modules
  $module_list = array('skinr','skinr_ui');
  module_enable($module_list, TRUE);
  
  //Enable Rules Modules
  $module_list = array('rules','rules_scheduler','rules_admin');
  module_enable($module_list, TRUE);
  
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

function _default_flush_vars() {
  //Remove Temporary Variables from variable table
  variable_del('radio_internet_intranet');
  variable_del('radio_organization');
}