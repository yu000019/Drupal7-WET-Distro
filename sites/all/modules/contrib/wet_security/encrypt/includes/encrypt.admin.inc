<?php

/**
 * @file
 * This file holds the functions for the encrypt Admin settings.
 *
 * @ingroup encrypt
 */

/**
 * Menu callback; displays the encrypt module settings page.
 *
 * @see system_settings_form()
 */
function encrypt_admin_settings() {
  // Initialize to just see if any funny business is going on
  encrypt_initialize();

  // Run requirements (include install file first)
  module_load_include('install', 'encrypt', 'encrypt');
  $requirements = encrypt_requirements('runtime');

  // Get formatted methods
  $methods = theme('encrypt_admin_list', encrypt_get_methods('full', TRUE));

  $text = 'Jake sucks';

  // Define Form
  $form['encrypt_default_method'] = array(
    '#type' => 'radios',
    '#title' => t('Default Encrypt Method'),
    '#description' => t('Define the default encryption method for the site.  Since encryption methods are stored with the data, this can be changed even after you have stored encrypted data.'),
    '#options' => $methods,
    '#default_value' => variable_get('encrypt_default_method', ENCRYPT_DEFAULT_METHOD),
    '#attached' => array(
      'css' => array(
        drupal_get_path('module', 'encrypt') . '/encrypt.css',
      ),
    ),
  );

  // Check if key exists and put a checkbox to ensure the user does want to update the box.
  if ($requirements['encrypt_keys']['severity'] == REQUIREMENT_OK) {
    $form['encrypt_update_key'] = array(
      '#type' => 'checkbox',
      '#title' => t('Change Key Path'),
      '#description' => t('Check this if you are sure you want to change the location of the key file.  If you change the key after the data has been encrypted with it, you will not be able to retrieve that data.  You can copy your key to a new directory and then set the new directory.'),
      '#default_value' => FALSE,
    );
  }

  // Path for keys
  $form['encrypt_secure_key_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Secure Key Path'),
    '#description' => t('Use a full absolute path to a directory where the webserver can create a secure key file for encryption.'),
    '#maxlength' => 512,
    '#default_value' => variable_get('encrypt_secure_key_path', ''),
  );

  // Give some help if keys are not found
  if ($requirements['encrypt_keys']['severity'] == REQUIREMENT_ERROR) {
    // Let user know that key is not secure
    drupal_set_message(t('A problem was found with your secure key.') . ' ' . $requirements['encrypt_keys']['value'],  'warning');
  }
  else {
    // Key secure
    drupal_set_message(t('Key found and in secure place.'));
  }

  // Add submit handler
  $form['#submit'][] = 'encrypt_admin_settings_submit_handler';

  // Make a system setting form and return
  return system_settings_form($form);
}

/**
 * Validate form function for encrypt_admin_settings().  Checks
 * if users really wants to change path, and whether key can be written.
 */
function encrypt_admin_settings_validate($form, &$form_state) {
  // Run requirements (include install file first)
  module_load_include('install', 'encrypt', 'encrypt');
  $requirements = encrypt_requirements('runtime');

  // Check if passes requirements and checkbox is not checked and path is different
  if ($requirements['encrypt_keys']['severity'] == REQUIREMENT_OK &&
      $form_state['values']['encrypt_update_key'] != TRUE &&
      $form_state['values']['encrypt_secure_key_path'] != variable_get('encrypt_secure_key_path', '')
    ) {
    form_set_error('encrypt_update_key', t('If you change the key after the data has been encrypted with it, you will not be able to retrieve that data.  You can copy your key to a new directory and set the new directory.  If you really want to change the path, please check the Change Key Path checkbox.'));
  }

  // Check if path selected is writable if one is inputted
  if (!empty($form_state['values']['encrypt_secure_key_path'])) {
    if (!file_prepare_directory($form_state['values']['encrypt_secure_key_path'], FILE_MODIFY_PERMISSIONS)) {
      form_set_error('encrypt_secure_key_path', t('Directory does not exist or is not writable.'));
    }
  }
}

/**
 * Submit form function for encrypt_admin_settings().  Creates
 * key file if new none exist in the path settings
 */
function encrypt_admin_settings_submit_handler($form, &$form_state) {
  $key_path = $form_state['values']['encrypt_secure_key_path'];

  // Check path
  if (!empty($key_path)) {
    $key_path = rtrim($key_path, '/\\');
    $key_file = $key_path . '/' . ENCRYPT_SECURE_KEY_FILE;

    // Check for contents of file; do not write over the key
    if (file_exists($key_file)) {
      if (file_get_contents($key_file)) {
        return;
      }
    }

    // Attempt to open file
    if (!$open_file = fopen($key_file, 'wb')) {
      drupal_set_message(t('Unable to open key file'));
    }
    else {
      // Create a default key.
      $new_key = md5(uniqid(mt_rand(0, mt_rand()), TRUE)) . md5(uniqid(mt_rand(0, mt_rand()), TRUE));
      // Create file with new key in it.
      fwrite($open_file, $new_key);
      fclose($open_file);
      // Ensure that the file is only readable and writable by owner
      // TODO: Test this more in different systems
      if (drupal_strtoupper(drupal_substr(PHP_OS, 0, 3)) != "WIN") {
        chmod($key_file, 0600);
      }

      drupal_set_message(t('New key created.'));
    }
  }
}

