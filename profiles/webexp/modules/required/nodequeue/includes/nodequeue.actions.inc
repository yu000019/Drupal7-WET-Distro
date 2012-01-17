<?php

/**
 * @file nodequeue.actions.inc
 * Provides actions integration for nodequeues.
 */

/**
 * Implements hook_action_info().
 */
function nodequeue_action_info() {
  return array(
    'nodequeue_add_action' => array(
      'type' => 'node',
      'label' => t('Add to Nodequeues'),
      'configurable' => TRUE,
      'triggers' => array(
        'node_presave',
        'node_insert',
        'node_update',
      ),
    ),
    'nodequeue_remove_action' => array(
      'type' => 'node',
      'label' => t('Remove from Nodequeues'),
      'configurable' => TRUE,
      'triggers' => array(
        'node_delete',
      ),
    ),
  );
}

/**
 * Configuration form for Add to Nodequeues action.
 */
function nodequeue_add_action_form($context) {
  // Default values for form.
  if (!isset($context['queues'])) {
    $context['queues'] = '';
  }

  $queues = nodequeue_load_queues(nodequeue_get_all_queues(0, 0, TRUE), TRUE);
  foreach ($queues as $name => $queue) {
    $options[$name] = $queue->title;
  }
  $form = array();
  if (count($options)) {
    // Add form components.
    $form['queues'] = array(
      '#type' => 'select',
      '#title' => t("Queue"),
      '#default_value' => $context['queues'],
      '#multiple' => TRUE,
      '#options' => $options,
      '#required' => TRUE,
      '#description' => t('Specify the queues into which the node should be submitted. If the queue is a smartqueue, the node shall be placed into every subqueue for which it is eligible.')
    );
  }
  else {
    drupal_set_message(t('Please <a href="@url">create</a> a nodequeue first.', array('@url' => url('admin/structure/nodequeue'))));
  }
  return $form;
}

/**
 * Submit handler for Add to Nodequeues action configuration.
 */
function nodequeue_add_action_submit($form, &$form_state) {
  return array(
    'queues' => $form_state['values']['queues'],
  );
}

/**
 * Action to add a node to a queue.
 */
function nodequeue_add_action($node, $context) {
  $queues = nodequeue_load_queues($context['queues'], TRUE);
  // Filter out queues by node type. We choose not to use nodequeue_get_queues()
  // because it checks for access control which only matters if we administering
  // a queue.
  $eligible_queues = array();
  foreach ($queues as $queue) {
    if (in_array($node->type, $queue->types)) {
      $eligible_queues[$queue->name] = $queue;
    }
  }

  if (!empty($eligible_queues)) {
    // Remove the node from the eligible queues (if needed).
    nodequeue_remove_action($node, array('queues' => array_keys($eligible_queues)));

    // Use API to get the eligible subqueues
    $eligible_subqueues = nodequeue_get_subqueues_by_node($eligible_queues, $node);

    // Add node to each subqueue.
    foreach ($eligible_subqueues as $subqueue) {
      nodequeue_subqueue_add($queues[$subqueue->name], $subqueue, $node->nid);
    }
  }
}

/**
 * Old-style action to add a node to a queue.
 */
function action_nodequeue_add($op, $edit = array(), $node) {
  switch ($op) {
    case 'metadata':
      return array(
        'description' => t('Add to Nodequeues'),
        'type' => t('node'),
        'batchable' => TRUE,
        'configurable' => TRUE,
      );
      break;

    case 'do':
      $queues = nodequeue_load_queues($edit['queues'], TRUE);
      // Filter out queues by node type. We choose not to use
      // nodequeue_get_queues() because it checks for access control which only
      // matters if we administering a queue.
      $eligible_queues = array();
      foreach ($queues as $queue) {
        if (in_array($node->type, $queue->types)) {
          $eligible_queues[$queue->name] = $queue;
        }
      }

      if (!empty($eligible_queues)) {
        // Remove the node from the eligible queues (if needed).
        action_nodequeue_remove('do', array('queues' => array_keys($eligible_queues)), $node);

        // Use API to get the eligible subqueues
        $eligible_subqueues = nodequeue_get_subqueues_by_node($eligible_queues, $node);

        // Add node to each subqueue.
        foreach ($eligible_subqueues as $subqueue) {
          nodequeue_subqueue_add($queues[$subqueue->name], $subqueue, $node->nid);
        }
      }
      break;

      // return an HTML config form for the action
    case 'form':
      // default values for form
      if (!isset($edit['queues'])) {
        $edit['queues'] = '';
      }
      $queues = nodequeue_load_queues(nodequeue_get_all_queues(0, 0, TRUE), TRUE);
      foreach ($queues as $name => $queue) {
        $options[$name] = $queue->title;
      }
      $form = array();
      if (count($options)) {
        // add form components
        $form['queues'] = array(
          '#type' => 'select',
          '#title' => t("Queue"),
          '#default_value' => $edit['queues'],
          '#multiple' => TRUE,
          '#options' => $options,
          '#required' => TRUE,
          '#description' => t('Specify the queues into which the node should be submitted. If the queue is a smartqueue, the node shall be placed into every subqueue for which it is eligible.')
          );
      }
      else {
        drupal_set_message(t('Please <a href="@url">create</a> a nodequeue first.', array('@url' => url('admin/structure/nodequeue'))));
      }
      return $form;

      // validate the HTML form

      // process the HTML form to store configuration
    case 'submit':
      $params = array(
        'queues' => $edit['queues']
      );
      return $params;
      break;
  }
}

/**
 * Configuration form for Remove from Nodequeues action.
 */
function nodequeue_remove_action_form($context) {
  // Default values for form.
  if (!isset($context['queues'])) {
    $context['queues'] = array();
  }

  $queues = nodequeue_load_queues(nodequeue_get_all_queues(0, 0, TRUE), TRUE);
  foreach ($queues as $name => $queue) {
    $options[$name] = $queue->title;
  }

  // Add form components.
  $form['queues'] = array(
    '#type' => 'select',
    '#title' => t("Queues"),
    '#default_value' => $context['queues'],
    '#multiple' => TRUE,
    '#decription' => t('Specify the queues from which the node should be removed. If the queue is a smartqueue, the node shall be removed from all subqueues.'),
    '#required' => TRUE,
    '#options' => $options,
  );
  return $form;
}

/**
 * Submit handler for Remove from Nodequeues action configuration.
 */
function nodequeue_remove_action_submit($form, &$form_state) {
  return array(
    'queues' => $form_state['values']['queues'],
  );
}

function nodequeue_remove_action($node, $context) {
  $queues = $context['queues'];
  // If a node is being deleted, ensure it's also removed from any queues.
  $args = $queues;
  $result = db_select('nodequeue_nodes', 'n')
    ->fields('n')
    ->condition('nid', $node->nid)
    ->condition('name', $args)
    ->execute()
    ->fetchAll();

  foreach ($result as $obj) {
    // This removes by nid, not position, because if we happen to have a
    // node in a queue twice, the 2nd position would be wrong.
    nodequeue_subqueue_remove_node($obj->sqid, $node->nid);
  }
}

/**
 * Old-style action to remove a node from a queue.
 */
function action_nodequeue_remove($op, $edit = array(), $node) {
  switch ($op) {
    case 'metadata':
      return array(
        'description' => t('Remove from Nodequeues'),
        'type' => t('node'),
        'batchable' => TRUE,
        'configurable' => TRUE,
      );
      break;

    case 'do':
      $queues = $edit['queues'];
      // If a node is being deleted, ensure it's also removed from any queues.
      $args = $queues;
      $result = db_select('nodequeue_nodes', 'n')
        ->fields('n')
        ->condition('nid', $node->nid)
        ->condition('name', $args)
        ->execute()
        ->fetchAll();

      foreach ($result as $obj) {
        // This removes by nid, not position, because if we happen to have a
        // node in a queue twice, the 2nd position would be wrong.
        nodequeue_subqueue_remove_node($obj->sqid, $node->nid);
      }
      break;

      // return an HTML config form for the action
    case 'form':
      // default values for form
      if (!isset($edit['queues'])) {
        $edit['queues'] = array();
      }

      $queues = nodequeue_load_queues(nodequeue_get_all_queues(0, 0, TRUE), TRUE);
      foreach ($queues as $name => $queue) {
        $options[$name] = $queue->title;
      }

      // add form components
      $form['queues'] = array(
        '#type' => 'select',
        '#title' => t("Queues"),
        '#default_value' => $edit['queues'],
        '#multiple' => TRUE,
        '#decription' => t('Specify the queues from which the node should be removed. If the queue is a smartqueue, the node shall be removed from all subqueues.'),
        '#required' => TRUE,
        '#options' => $options,
      );
      return $form;
      break;

      // validate the HTML form

      // process the HTML form to store configuration
    case 'submit':
      $params = array(
        'queues' => $edit['queues']
      );
      return $params;
      break;
  }
}
