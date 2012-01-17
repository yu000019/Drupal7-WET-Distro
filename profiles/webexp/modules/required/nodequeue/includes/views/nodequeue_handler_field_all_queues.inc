<?php

/**
 * @file
 * Field handler for all queues.
 *
 * @ingroup views_field_handlers
 */
class nodequeue_handler_field_all_queues extends views_handler_field_prerender_list {
  /**
   * Provide meaningful defaults.
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['link_to_queue'] = array('default' => TRUE);
    $options['limit'] = array('default' => FALSE);
    $options['queues'] = array('default' => array());

    return $options;
  }

  /**
   * Provide "link to term" option.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['link_to_queue'] = array(
      '#title' => t('Link this field to queue arrange page'),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['link_to_queue']),
    );

    $form['limit'] = array(
      '#type' => 'checkbox',
      '#title' => t('Limit to queues'),
      '#default_value' => $this->options['limit'],
    );

    $options = array();
    $queues = nodequeue_load_queues(nodequeue_get_all_queues());
    foreach ($queues as $queue) {
      $options[$queue->name] = $queue->title;
    }

    $form['queues'] = array(
      '#prefix' => '<div><div id="edit-options-queues">',
      '#suffix' => '</div></div>',
      '#type' => 'checkboxes',
      '#title' => t('Queues'),
      '#options' => $options,
      '#default_value' => $this->options['queues'],
      '#dependency' => array('edit-options-limit' => array(TRUE)),
    );
  }

  function pre_render($values) {
    $nids = array();
    foreach ($values as $result) {
      $nids[] = $result->{$this->field_alias};
    }

    if ($nids) {
      $query = db_select('nodequeue_nodes', 'nn');
      $query->innerJoin('nodequeue_queue', 'nq', 'nn.name = nq.name');
      $query->fields('nn', array('nid', 'name'));
      $query->fields('nq', array('title'));
      $query->orderby('nq.title');
      $query->condition('nn.nid', $nids);
      $queues = array_filter($this->options['queues']);
      if (!empty($this->options['limit']) && !empty($queues)) {
        $query->condition('nn.name', $queues);
      }
      $result = $query->execute();

      foreach ($result as $queue) {
        $this->items[$queue->nid][$queue->name]['title'] = check_plain($queue->title);

        if (!empty($this->options['link_to_queue'])) {
          $this->items[$queue->nid][$queue->name]['make_link'] = TRUE;
          $this->items[$queue->nid][$queue->name]['path'] = 'admin/structure/nodequeue/' . $queue->name;
        }
      }
    }
  }

  function render_item($count, $item) {
    return $item['title'];
  }
}
