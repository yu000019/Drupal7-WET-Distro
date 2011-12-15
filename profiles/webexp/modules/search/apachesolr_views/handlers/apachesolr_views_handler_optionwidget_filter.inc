<?php

class apachesolr_views_handler_optionwidget_filter extends views_handler_filter {
  /**
   * override query
   */
  function query() {
    // TODO: Is this really always a array with only one value?
    if (property_exists($this, 'value') && !empty($this->value)) {
      $value = reset($this->value);
      $this->query->add_filter($this->real_field, $value);
    }
  }

  /**
   * Provide a simple textfield for equality
   */
  function value_form(&$form, &$form_state) {
    $options = module_invoke($this->definition['cck_field']['module'], 'allowed_values', $this->definition['cck_field']);
    $form['value'] = array(
      '#type' => 'select',
      '#title' => t($this->definition['title']),
      '#options' => $options,
      '#default_value' => $this->value,
    );
    xdebug_break();
  }
}