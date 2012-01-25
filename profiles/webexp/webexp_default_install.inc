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
    '#description' => st('This option will help to further assist between government and non-government branded solutions.'),
  );
  $form['webexp_site'] = array(
    '#type' => 'radios',
    '#title' => st('Site intended to be used for which of type of website?'),
    '#default_value' =>  variable_get('radio_internet_intranet', 'internet'),
    '#options' => $options_site,
    '#description' => st('This option will change the default theme based on the type of site.'),
  );
  $form['webexp_prefix_language_en'] = array(
    '#type' => 'textfield',
    '#title' => t('English Prefix'),
    '#required' => TRUE,
    '#default_value' => 'eng',
    '#description' => "Please enter the English Language Prefix for domains (Defaults if unsure)",
    '#size' => 20,
    '#maxlength' => 20,
  );
  $form['webexp_prefix_language_fr'] = array(
    '#type' => 'textfield',
    '#title' => t('French Prefix'),
    '#required' => TRUE,
    '#default_value' => 'fra',
    '#description' => "Please enter the French Language Prefix for domains (Defaults if unsure)",
    '#size' => 20,
    '#maxlength' => 20,
  );
  $form['webexp_domain_language_en'] = array(
    '#type' => 'textfield',
    '#title' => t('English Domain (Optional)'),
    '#required' => FALSE,
    '#default_value' => NULL,
    '#description' => "Please enter the English Language Domain (Leave Blank if unsure)",
    '#size' => 20,
    '#maxlength' => 20,
  );
  $form['webexp_domain_language_fr'] = array(
    '#type' => 'textfield',
    '#title' => t('French Domain (Optional)'),
    '#required' => FALSE,
    '#default_value' => NULL,
    '#description' => "Please enter the French Language Domain  (Leave Blank if unsure)",
    '#size' => 20,
    '#maxlength' => 20,
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
  variable_set('radio_prefix_domain_en', $form_state['values']['webexp_prefix_language_en']);
  variable_set('radio_prefix_domain_fr', $form_state['values']['webexp_prefix_language_fr']);
  variable_set('radio_language_domain_en', $form_state['values']['webexp_domain_language_en']);
  variable_set('radio_language_domain_fr', $form_state['values']['webexp_domain_language_fr']);
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
    
    //Kinda hackish but has to be run after first set
    $module_list = array($GLOBALS['$gov_web_usability']);
    module_enable($module_list, TRUE);
  }
  
  //If Non-Government Site
  else if (variable_get('radio_organization') == 'public') 
  {
    theme_disable(array('bartik'));
    theme_enable(array($GLOBALS['$public_theme_internet']));    
    variable_set('theme_default', $GLOBALS['$public_theme_internet']);
    
    $module_list = array($GLOBALS['$public_web_usability']);    
    module_enable($module_list, TRUE);
  }
}

function _default_flush_vars() {
  //Remove Temporary Variables from variable table
  variable_del('radio_internet_intranet');
  variable_del('radio_organization');
}