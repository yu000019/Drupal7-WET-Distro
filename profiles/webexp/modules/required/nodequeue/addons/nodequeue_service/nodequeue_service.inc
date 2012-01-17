<?php

/**
 * @file
 * Miscellaneous functions for Nodequeue Service.
 *
 * @author Greg Harvey - http://www.drupaler.co.uk
 */

/**
 * Returns an array of available nodequeue "channels" available.
 *
 * @return
 * array with key of nodequeue ids and all settings within
 */
function nodequeue_service_get_nodequeues() {
  if (module_exists('nodequeue')) {
    // Fetch all of the queues.
    $queues = nodequeue_load_queues(nodequeue_get_all_queues(0));
    if (empty($queues)) {
      return services_error(t('Nodequeue available, but no nodequeues exist.'));
    }
    else {
      $availablequeues = array();
      foreach ($queues as $queue) {
        $availablequeues[$queue->name]['name'] = $queue->name;
        $availablequeues[$queue->name]['title'] = $queue->title;
        $availablequeues[$queue->name]['subqueue_title'] = $queue->subqueue_title;
        $availablequeues[$queue->name]['size'] = $queue->size;
        $availablequeues[$queue->name]['link'] = $queue->link;
        $availablequeues[$queue->name]['link_remove'] = $queue->link_remove;
        $availablequeues[$queue->name]['owner'] = $queue->owner;
        $availablequeues[$queue->name]['show_in_ui'] = $queue->show_in_ui;
        $availablequeues[$queue->name]['show_in_tab'] = $queue->show_in_tab;
        $availablequeues[$queue->name]['show_in_links'] = $queue->show_in_links;
        $availablequeues[$queue->name]['reference'] = $queue->reference;
        $availablequeues[$queue->name]['reverse'] = $queue->reverse;
        $availablequeues[$queue->name]['subqueues'] = $queue->subqueues;
        $availablequeues[$queue->name]['types'] = $queue->types;
        $availablequeues[$queue->name]['roles'] = $queue->roles;
        $availablequeues[$queue->name]['count'] = $queue->count;
      }
    }
    return $availablequeues;
  }
  else {
    return services_error(t('Nodequeue module unavailable.'));
  }
}

/**
 * Returns an array of available subqueues by parent queue id.
 *
 * @param $name
 *   Name of the parent nodequeue.
 *
 * @return
 * array with key of subqueue ids and all settings within
 */
function nodequeue_service_get_subqueues($name) {
  if (module_exists('nodequeue')) {
    $subqueues = nodequeue_load_subqueues_by_queue($name);
    if (!empty($subqueues)) {
      foreach ($subqueues as $subqueue) {
        $availablequeues[$subqueue->sqid]['sqid'] = $subqueue->sqid;
        $availablequeues[$subqueue->sqid]['name'] = $name;
        $availablequeues[$subqueue->sqid]['reference'] = $subqueue->reference;
        $availablequeues[$subqueue->sqid]['title'] = check_plain($subqueue->title);
        $availablequeues[$subqueue->sqid]['count'] = $subqueue->count;
      }
      return $availablequeues;
    }
    else {
      return services_error(t('Specified nodequeue has no subqueues.'));
    }
  }
  else {
    return services_error(t('Nodequeue module unavailable.'));
  }
}

/**
 * Access callback function for the nodequeue service.
 */
function nodequeue_service_get_nodequeues_access() {
  if (user_access('get nodequeues')) {
    return TRUE;
  }
}
