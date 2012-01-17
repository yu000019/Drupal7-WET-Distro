<?php

function _default_setup_form() {
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
      theme_enable(array($GLOBALS['$gov_theme_internet']));
      variable_set('theme_default', $GLOBALS['$gov_theme_internet']);
    }
    //If Government Site and Intranet Theme
    else {
      theme_disable(array('bartik'));
      theme_enable(array($GLOBALS['$gov_theme_intranet']));
      variable_set('theme_default', $GLOBALS['$gov_theme_intranet']);
    }
  }
  //If Non-Government Site
  else if (variable_get('radio_organization') == 'public') 
  {
    theme_disable(array('bartik'));
    theme_enable(array($GLOBALS['$public_theme_internet']));    
    variable_set('theme_default', $GLOBALS['$public_theme_internet']);
  }
  
  //Enable Dev Modules
  $module_list = array('devel','devel_generate','migrate','migrate_ui','migrate_extras','querypath','qpa');
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
  
  //Enable Features
  $module_list = array('wetkit_slider');
  module_enable($module_list, TRUE);

  $module_list = array('wetkit_ckeditor');
  module_enable($module_list, TRUE);

  $module_list = array('wetkit_styles');
  module_enable($module_list, TRUE);

  $module_list = array('wetkit_workflow_rules');
  module_enable($module_list, TRUE);
  
  $module_list = array('wetkit_migrate');    
  module_enable($module_list, TRUE);
       
  //Enable Government Specifications
  if (variable_get('radio_organization') == 'government')
  {
    //Kinda hackish but has to be run after first set
    $module_list = array($GLOBALS['$gov_web_usability']);
    module_enable($module_list, TRUE); 
  }
  //Enable Public Specifications
  else if (variable_get('radio_organization') == 'public')
  { 
    $module_list = array($GLOBALS['$public_web_usability']);    
    module_enable($module_list, TRUE);
  }
  
}

function _default_flush_vars() {
  //Remove Temporary Variables from variable table
  variable_del('radio_internet_intranet');
  variable_del('radio_organization');
}