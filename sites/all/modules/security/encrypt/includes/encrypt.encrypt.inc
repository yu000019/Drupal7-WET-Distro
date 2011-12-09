<?php

/**
 * @file
 * This file holds the hook implementation for the encrypt modules
 *
 * @ingroup encrypt
 */

/**
 * Implementation of hook_encrypt_method_info().
 */
function encrypt_encrypt_method_info() {
  $methods = array();
  $default_method = (string) ENCRYPT_DEFAULT_METHOD;

  // Basic methods that dont need any extensions
  $methods[$default_method] = array(
    'title' => t('Basic'),
    'description' => t('This is the basic default encryption type that does not require any special extensions.'),
    'callback' => 'encrypt_encrypt_basic',
  );
  $methods['none'] = array(
    'title' => t('None'),
    'description' => t('This uses no encryption.  It is not suggested to use this.'),
    'callback' => 'encrypt_encrypt_none',
  );

  // Mcrypt method
  if (function_exists('mcrypt_get_iv_size') && function_exists('mcrypt_create_iv') && function_exists('mcrypt_encrypt')) {
    $methods['mcrypt_rij_256'] = array(
      'title' => t('Mcrypt AES 256'),
      'description' => t('This uses PHPs mcrypt extension and <a href="!url">AES-256</a>.', array('!url' => 'http://en.wikipedia.org/wiki/Advanced_Encryption_Standard')),
      'callback' => 'encrypt_encrypt_mcrypt_rij_256',
    );
  }

  return $methods;
}

/**
 * Callback for Encrypt implementation: none
 */
function encrypt_encrypt_none($op = 'encrypt', $text = '', $options = array()) {
  // Check op
  if ($op == 'decrypt') {
    // No encryption
    return $text;
  }
  else {
    // No encryption
    return $text;
  }
}

/**
 * Callback for Encrypt implementation: default
 *
 * This method uses a simple encryption method of character
 * replacement.
 */
function encrypt_encrypt_basic($op = 'encrypt', $text = '', $options = array()) {
  $processed_text = '';

  // Check for and assign key
  $key = !empty($options['key']) ? $options['key'] : variable_get('drupal_private_key', 'no_key');

  // Caching length operations to speed up for loops.
  $text_length = strlen($text);
  $key_length = strlen($key);

  // Loop through each character.
  for ($i = 0; $i < $text_length; $i++) {
    $char = substr($text, $i, 1);
    $keychar = substr($key, ($i % $key_length) - 1, 1);
    // Encrypt or decrypt the character.
    if ($op == 'decrypt') {
      $char = chr(ord($char) - ord($keychar));
    } else {
      $char = chr(ord($char) + ord($keychar));
    }
    $processed_text .= $char;
  }

  return $processed_text;
}

/**
 * Callback for Encrypt implementation: Mcrypt
 *
 * This method uses a PHPs mcrypt extension and AES-256
 */
function encrypt_encrypt_mcrypt_rij_256($op = 'encrypt', $text = '', $options = array()) {
  $processed_text = '';

  // Check for key
  if (!empty($options['key'])) {
    $key = $options['key'];
  }
  else {
    // Key cannot be too long for this encryption
    $key = drupal_substr(variable_get('drupal_private_key', 'no_key'), 0, 32);
  }

  // Define iv cipher
  $iv_size = mcrypt_get_iv_size(MCRYPT_RIJNDAEL_256, MCRYPT_MODE_ECB);
  $iv = mcrypt_create_iv($iv_size, MCRYPT_RAND);
  $use_base64 = array_key_exists('base64', $options) && $options['base64'] !== FALSE;

  // Check op
  if ($op == 'decrypt') {
    // Decrypt
    // Check if we are using base64 encoding
    if ($use_base64) {
      $text = base64_decode($text);
    }

    // Decrypt text
    $processed_text = mcrypt_decrypt(MCRYPT_RIJNDAEL_256, $key, $text, MCRYPT_MODE_ECB, $iv);
  }
  else {
    // Encrypt
    $processed_text = mcrypt_encrypt(MCRYPT_RIJNDAEL_256, $key, $text, MCRYPT_MODE_ECB, $iv);

    // Check if we are using base64 encoding
    if ($use_base64) {
      $processed_text = base64_encode($processed_text);
    }
  }

  return trim($processed_text);
}
