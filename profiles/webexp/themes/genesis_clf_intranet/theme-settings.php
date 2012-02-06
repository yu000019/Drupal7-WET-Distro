<?php
/**
 * @file
 * theme-settings.php
 */

function genesis_clf_intranet_form_system_theme_settings_alter(&$form, &$form_state) {
  $form['Intranet'] = array(
    '#type' => 'fieldset',
    '#title' => t('Sub-site name'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['Intranet']['sub_site_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Intranet web site name'),
    '#description' => t('The display name for the Intranet web site'),
    '#default_value' => theme_get_setting('sub_site_name'),
  );
}