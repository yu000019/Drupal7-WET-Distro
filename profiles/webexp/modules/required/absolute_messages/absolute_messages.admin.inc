<?php

/**
 * Implements hook_admin_settings().
 */
function absolute_messages_admin_settings_form() {
  $form = array();

  $form['general'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('General settings'),
  );
  $form['general']['absolute_messages_dismiss_all_count'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Show "Dismiss all messages" when number of messages is higher than'),
    '#default_value'  => variable_get('absolute_messages_dismiss_all_count', 2),
  );
  $form['general']['absolute_messages_display_lines'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Maximum number of message lines to display'),
    '#description'    => t('If set, only first n lines of each message will be displayed, expanding to full message after clicking on it. Useful for length messages. Leave empty for no limit.'),
    '#default_value'  => variable_get('absolute_messages_display_lines', ''),
  );

  $form['autodismiss'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Automatically dismiss messages'),
    '#description'  => t('Automatically dismiss all/some messages after a specific time.'),
  );
  foreach (_absolute_messages_message_types() as $message_type) {
    $form['autodismiss']['absolute_messages_dismiss_' . $message_type] = array(
      '#type'           => 'checkbox',
      '#title'          => t('Automatically dismiss %type messages', array('%type' => $message_type)),
      '#default_value'  => variable_get('absolute_messages_dismiss_' . $message_type, FALSE),
    );
    $form['autodismiss']['absolute_messages_dismiss_time_' . $message_type] = array(
      '#type'           => 'textfield',
      '#title'          => t('Automatically dismiss %type messages after', array('%type' => $message_type)),
      '#default_value'  => variable_get('absolute_messages_dismiss_time_' . $message_type, ''),
      '#field_suffix'   => t('seconds'),
      '#states'         => array(
        'visible'         => array(
          ':input[name="absolute_messages_dismiss_' . $message_type . '"]' => array('checked' => TRUE),
        ),
      ),
    );
  }

  $form['advanced'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Advanced settings'),
    '#collapsible'  => TRUE,
    '#collapsed'    => TRUE,
  );
    $form['advanced']['absolute_messages_no_js_check'] = array(
      '#type'           => 'checkbox',
      '#title'          => t('Do not check "has_js" cookie'),
      '#description'    => t('In PressFlow 6 "has_js" cookie was dropped, therefore there is no option to detect if JS is enabled without setting it back (which is not always desired). This option could skip "has_js" cookie check, and make the module work with default Pressflow 6 installations. The downside to this solution though is that the module will also try to work even for users which have JS really disabled, thus making them unable to see ANY system messages.'),
      '#default_value'  => variable_get('absolute_messages_no_js_check', FALSE),
    );

  return system_settings_form($form);
}
