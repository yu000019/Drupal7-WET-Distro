<?php
// $Id$
/**
 * @file
 * Administrative pages for configuring workflows.
 */

/**
 * Form builder. Create the form for adding/editing a workflow.
 *
 * @param $name
 *   Name of the workflow if editing.
 * @param $add
 *   Boolean, if true edit workflow name.
 *
 * @return
 *   HTML form.
 */
function workflow_add_form($form, &$form_state, $name = NULL) {
  $form = array();
  $form['wf_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Workflow Name'),
    '#maxlength' => '254',
    '#default_value' => $name,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add Workflow'),
  );
  return $form;
}

/**
 * Validate the workflow add form.
 *
 * @see workflow_add_form()
 */
function workflow_add_form_validate($form, &$form_state) {
  $workflow_name = $form_state['values']['wf_name'];
  $workflows = array_flip(workflow_get_all());
  // Make sure a nonblank workflow name is provided.
  if ($workflow_name == '') {
    form_set_error('wf_name', t('Please provide a nonblank name for the new workflow.'));
  }
  // Make sure workflow name is not a duplicate.
  if (array_key_exists($workflow_name, $workflows)) {
    form_set_error('wf_name', t('A workflow with the name %name already exists. Please enter another name for your new workflow.',
      array('%name' => $workflow_name)));
  }
}

/**
 * Submit handler for the workflow add form.
 *
 * @see workflow_add_form()
 */
function workflow_add_form_submit($form, &$form_state) {
  $workflow_name = $form_state['values']['wf_name'];
  $wid = workflow_create($workflow_name);
  watchdog('workflow', 'Created workflow %name', array('%name' => $workflow_name));
  drupal_set_message(t('The workflow %name was created. You should now add states to your workflow.',
    array('%name' => $workflow_name)), 'status');
  $form_state['wid'] = $wid;
  $form_state['redirect'] = 'admin/config/workflow/workflow/state/' . $wid;
}

/**
 * Form builder. Create form for confirmation of workflow deletion.
 *
 * @param $wid
 *   The ID of the workflow to delete.
 * @return
 *   Form definition array.
 *
 */
function workflow_delete_form($form, &$form_state, $wid, $sid = NULL) {
  if (isset($sid)) {
    return workflow_state_delete_form($wid, $sid);
  }
  $form['wid'] = array(
    '#type' => 'value',
    '#value' => $wid,
  );
  return confirm_form(
    $form,
    t('Are you sure you want to delete %title? All nodes that have a workflow state associated with this workflow will have those workflow states removed.', array('%title' => workflow_get_name($wid))),
    !empty($_GET['destination']) ? $_GET['destination'] : 'admin/config/workflow/workflow',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Submit handler for workflow deletion form.
 *
 * @see workflow_delete_form()
 */
function workflow_delete_form_submit($form, &$form_state) {
  if ($form_state['values']['confirm'] == 1) {
    $workflow_name = workflow_get_name($form_state['values']['wid']);
    workflow_deletewf($form_state['values']['wid']);
    watchdog('workflow', 'Deleted workflow %name with all its states', array('%name' => $workflow_name));
    drupal_set_message(t('The workflow %name with all its states was deleted.', array('%name' => $workflow_name)));
    $form_state['redirect'] = 'admin/config/workflow/workflow';
  }
}

/**
 * View workflow permissions by role
 *
 * @param $wid
 *   The ID of the workflow.
 */
function workflow_view_permissions($wid) {
  $name = workflow_get_name($wid);
  $all = array();
  $roles = array('author' => t('author')) + user_roles();
  foreach ($roles as $role => $value) {
    $all[$role]['name'] = $value;
  }
  $result = db_query(
    'SELECT t.roles, s1.state AS state_name, s2.state AS target_state_name ' .
    'FROM {workflow_transitions} t ' .
    'INNER JOIN {workflow_states} s1 ON s1.sid = t.sid ' .
    'INNER JOIN {workflow_states} s2 ON s2.sid = t.target_sid ' .
    'WHERE s1.wid = :wid ' .
    'ORDER BY s1.weight ASC , s1.state ASC , s2.weight ASC , s2.state ASC',
    array(':wid' => $wid));
  foreach ($result as $data) {
    foreach (explode(',', $data->roles) as $role) {
      $all[$role]['transitions'][] = array(check_plain(t($data->state_name)), WORKFLOW_ARROW, check_plain(t($data->target_state_name)));
    }
  }
  $header = array(t('From'), '', t('To'));
  $output = '';
  foreach ($all as $role => $value) {
    if (!empty($value['name'])) {
      $output .= '<h3>' . t("%role may do these transitions:", array('%role' => $value['name'])) . '</h3>';
    }
    if (!empty($value['transitions'])) {
      $output .= theme('table', array('header' => $header, 'rows' => $value['transitions'])) . '<p></p>';
    }
    else {
      $output .= '<table><tbody><tr class="odd"><td>' . t('None') . '</td><td></tr></tbody></table><p></p>';
    }
  }
  return theme('workflow_view_permissions', array('header' => $header, 'all' => $all));
}

/**
 * Theme the workflow permissions view.
 */
function theme_workflow_view_permissions($variables) {
  $header = $variables['header'];
  $all = $variables['all'];
  $output = '';
  foreach ($all as $role => $value) {
    if (!empty($value['name'])) {
      $output .= '<h3>' . t("%role may do these transitions:", array('%role' => $value['name'])) . '</h3>';
    }
    if (!empty($value['transitions'])) {
      $output .= theme('table', array('header' => $header, 'rows' => $value['transitions'])) . '<p></p>';
    }
    else {
      $output .= '<table><tbody><tr class="odd"><td>' . t('None') . '</td><td></tr></tbody></table><p></p>';
    }
  }
  return $output;
}

/**
 * Menu callback. Edit a workflow's properties.
 *
 * @param $wid
 *   The ID of the workflow.
 * @return
 *   HTML form and permissions table.
 */
function workflow_edit_form($form, $form_state, $workflow) {
  $form['wid'] = array(
    '#type' => 'value',
    '#value' => $workflow->wid,
  );
  $form['basic'] = array(
    '#type' => 'fieldset',
    '#title' => t('Workflow information'),
  );
  $form['basic']['wf_name'] = array(
    '#type' => 'textfield',
    '#default_value' => $workflow->name,
    '#title' => t('Workflow Name'),
    '#size' => '16',
    '#maxlength' => '254',
  );
  $form['basic']['name_as_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use the workflow name as the title of the workflow form.'),
    '#default_value' => isset($workflow->options['name_as_title']) ? $workflow->options['name_as_title'] : 0,
    '#description' => t('The workflow section of the editing form is in its own fieldset. Checking the box will add the workflow name as the title of workflow section of the editing form.'),
  );
  $form['comment'] = array(
    '#type' => 'fieldset',
    '#title' => t('Comment for Workflow Log'),
  );
  $form['comment']['comment_log_node'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show a comment field in the workflow section of the editing form.'),
    '#default_value' => $workflow->options['comment_log_node'],
    '#description' => t("On the node editing form, a Comment form can be shown so that the person making the state change can record reasons for doing so. The comment is then included in the node's workflow history."),
  );
  $form['comment']['comment_log_tab'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show a comment field in the workflow section of the workflow tab form.'),
    '#default_value' => $workflow->options['comment_log_tab'],
    '#description' => t("On the workflow tab, a Comment form can be shown so that the person making the state change can record reasons for doing so. The comment is then included in the node's workflow history."),
  );
  $form['tab'] = array(
    '#type' => 'fieldset',
    '#title' => t('Workflow tab permissions'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['tab']['tab_roles'] = array(
    '#type' => 'checkboxes',
    '#options' => workflow_get_roles(),
    '#default_value' => explode(',', $workflow->tab_roles),
    '#description' => t('Select any roles that should have access to the workflow tab on nodes that have a workflow.'),
  );
  $form['transitions'] = workflow_transition_grid_form($workflow->wid);
  $form['transitions']['#tree'] = TRUE;
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  $form['permissions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Permissions Summary'),
    '#collapsible' => TRUE,
  );
  $form['permissions']['summary'] = array(
    '#value' => '',
    '#suffix' => workflow_view_permissions($workflow->wid),
  );
  return $form;
}

/**
 * Theme the workflow editing form.
 *
 * @see workflow_edit_form()
 */
function theme_workflow_edit_form($variables) {
  $form = $variables['form'];
  $wid = $form['wid']['#value'];
  drupal_set_title(t('Edit workflow %name', array('%name' => workflow_get_name($wid))), PASS_THROUGH);
  $output = drupal_render($form['wf_name']);
  $states = workflow_get_states($wid);
  if ($states) {
    $roles = workflow_get_roles();
    $header = array(array('data' => t('From / To') . ' &nbsp;' . WORKFLOW_ARROW));
    $rows = array();
    foreach ($states as $state_id => $name) {
      // Don't allow transition TO (creation).
      if ($name != t('(creation)')) {
        $header[] = array('data' => check_plain(t($name)));
      }
      $row = array(array('data' => check_plain(t($name))));
      foreach ($states as $nested_state_id => $nested_name) {
        if ($nested_name == t('(creation)')) {
          // Don't allow transition TO (creation).
          continue;
        }
        if ($nested_state_id != $state_id) {
          // Need to render checkboxes for transition from $state to $nested_state.
          $from = $state_id;
          $to = $nested_state_id;
          $cell = '';
          foreach ($roles as $rid => $role_name) {
            $cell .= drupal_render($form['transitions'][$from][$to][$rid]);
          }
          $row[] = array('data' => $cell);
        }
        else {
          $row[] = array('data' => '');
        }
      }
      $rows[] = $row;
    }
    $output .= theme('table', array('header' => $header, 'rows' => $rows));
  }
  else {
    $output = t('There are no states defined for this workflow.');
  }
  $output .= drupal_render_children($form);
  return $output;
}

/**
 * Validate the workflow editing form.
 *
 * @see workflow_edit_form()
 */
function workflow_edit_form_validate($form_id, $form_state) {
  $wid = $form_state['values']['wid'];
  // Make sure workflow name is not a duplicate.
  if (array_key_exists('wf_name', $form_state['values']) && $form_state['values']['wf_name'] != '') {
    $workflow_name = $form_state['values']['wf_name'];
    $workflows = array_flip(workflow_get_all());
    if (array_key_exists($workflow_name, $workflows) && $wid != $workflows[$workflow_name]) {
      form_set_error('wf_name', t('A workflow with the name %name already exists. Please enter another name for this workflow.',
        array('%name' => $workflow_name)));
    }
  }
  else {
    // No workflow name was provided.
    form_set_error('wf_name', t('Please provide a nonblank name for this workflow.'));
  }

  // Make sure 'author' is checked for (creation) -> [something].
  $creation_id = _workflow_creation_state($wid);
  if (isset($form_state['values']['transitions'][$creation_id]) && is_array($form_state['values']['transitions'][$creation_id])) {
    foreach ($form_state['values']['transitions'][$creation_id] as $to => $roles) {
      if ($roles['author']) {
        $author_has_permission = TRUE;
        break;
      }
    }
  }
  $state_count = db_query("SELECT COUNT(sid) FROM {workflow_states} WHERE wid = :wid", array(':wid' => $wid))->fetchField();
  if (empty($author_has_permission) && $state_count > 1) {
    form_set_error('transitions', t('Please give the author permission to go from %creation to at least one state!',
      array('%creation' => '(creation)')));
  }
}

/**
 * Submit handler for the workflow editing form.
 *
 * @see workflow_edit_form()
 */
function workflow_edit_form_submit($form, &$form_state) {
  if (isset($form_state['values']['transitions'])) {
    workflow_update_transitions($form_state['values']['transitions']);
  }
  $options = array(
    'comment_log_node' => $form_state['values']['comment_log_node'],
    'comment_log_tab' => $form_state['values']['comment_log_tab'],
    'name_as_title' => $form_state['values']['name_as_title'],
  );
  workflow_update($form_state['values']['wid'], $form_state['values']['wf_name'], array_filter($form_state['values']['tab_roles']), $options);
  drupal_set_message(t('The workflow was updated.'));
  $form_state['redirect'] = 'admin/config/workflow/workflow';
}

/**
 * Menu callback and form builder. Create form to add a workflow state.
 *
 * @param $wid
 *   The ID of the workflow.
 * @return
 *   HTML form.
 */
function workflow_state_add_form($form, &$form_state, $wid, $sid = NULL) {
  $form['wid'] = array(
    '#type' => 'value',
    '#value' => $wid,
  );
  if (isset($sid)) {
    $state = workflow_get_state($sid);
    if (isset($state) && $state['status']) {
      drupal_set_title(t('Edit workflow state %state', array('%state' => $state['state'])), PASS_THROUGH);
      $form['sid'] = array(
        '#type' => 'value',
        '#value' => $sid,
      );
    }
  }
  // If we don't have a state or db_fetch_array() returned FALSE, load defaults.
  if (!isset($state) || $state === FALSE) {
    $state = array(
      'state' => '',
      'weight' => 0,
    );
    drupal_set_title(t('Add a new state to workflow %workflow', array('%workflow' => workflow_get_name($wid))), PASS_THROUGH);
  }
  $form['state'] = array(
    '#type' => 'textfield',
    '#title' => t('State name'),
    '#default_value' => $state['state'],
    '#size' => '16',
    '#maxlength' => '254',
    '#required' => TRUE,
    '#description' => t('Enter the name for a state in your workflow. For example, if you were doing a meal workflow it may include states like <em>shop</em>, <em>prepare</em>, <em>eat</em>, and <em>clean up</em>.'),
  );
  $form['weight'] = array(
    '#type' => 'weight',
    '#title' => t('Weight'),
    '#default_value' => $state['weight'],
    '#description' => t('In listings, the heavier states will sink and the lighter states will be positioned nearer the top.'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

/**
 * Validate the state addition form.
 *
 * @see workflow_state_add_form()
 */
function workflow_state_add_form_validate($form, &$form_state) {
  $state_name = $form_state['values']['state'];
  $wf_states = array_flip(workflow_get_states($form_state['values']['wid']));
  if (array_key_exists('sid', $form_state['values'])) {
    // Validate changes to existing state:
    // Make sure a nonblank state name is provided.
    if ($state_name == '') {
      form_set_error('state', t('Please provide a nonblank name for this state.'));
    }
    // Make sure changed state name is not a duplicate
    if (array_key_exists($state_name, $wf_states) && $form_state['values']['sid'] != $wf_states[$state_name]) {
      form_set_error('state', t('A state with the name %state already exists in this workflow. Please enter another name for this state.', array('%state' => $state_name)));
    }
  }
  else {
    // Validate new state:
    // Make sure a nonblank state name is provided
    if ($state_name == '') {
      form_set_error('state', t('Please provide a nonblank name for the new state.'));
    }
    // Make sure state name is not a duplicate
    if (array_key_exists($state_name, $wf_states)) {
      form_set_error('state', t('A state with the name %state already exists in this workflow. Please enter another name for your new state.', array('%state' => $state_name)));
    }
  }
}

/**
 * Submit handler for state addition form.
 *
 * @see workflow_state_add_form()
 */
function workflow_state_add_form_submit($form, &$form_state) {
  $form_state['sid'] = workflow_state_save($form_state['values']);
  if (array_key_exists('sid', $form_state['values'])) {
    drupal_set_message(t('The workflow state was updated.'));
  }
  else {
    watchdog('workflow', 'Created workflow state %name', array('%name' => $form_state['values']['state']));
    drupal_set_message(t('The workflow state %name was created.', array('%name' => $form_state['values']['state'])));
  }
  $form_state['redirect'] = 'admin/config/workflow/workflow';
}

/**
 * Form builder. Build the grid of transitions for defining a workflow.
 *
 * @param int $wid
 *   The ID of the workflow.
 */
function workflow_transition_grid_form($wid) {
  $form = array();

  $roles = workflow_get_roles();
  $states = workflow_get_states($wid);
  if (!$states) {
    $form = array(
      '#type' => 'markup',
      '#value' => t('There are no states defined for this workflow.'),
    );
    return $form;
  }
  foreach ($states as $state_id => $name) {
    foreach ($states as $nested_state_id => $nested_name) {
      if ($nested_name == t('(creation)')) {
        // Don't allow transition TO (creation).
        continue;
      }
      if ($nested_state_id != $state_id) {
        // Need to generate checkboxes for transition from $state to $nested_state.
        $from = $state_id;
        $to = $nested_state_id;
        foreach ($roles as $rid => $role_name) {
          $tid = workflow_get_transition_id($from, $to);
          $form[$from][$to][$rid] = array(
            '#type' => 'checkbox',
            '#title' => check_plain($role_name),
            '#default_value' => $tid ? workflow_transition_allowed($tid, $rid) : FALSE,
          );
        }
      }
    }
  }
  return $form;
}

/**
 * Menu callback. Create the main workflow page, which gives an overview
 * of workflows and workflow states.
 */
function workflow_overview() {
  $workflows = workflow_get_all();
  $row = array();
  foreach ($workflows as $wid => $name) {
    $links = array(
      'workflow_overview_add_state' => array(
        'title' => t('Add state'),
        'href' => "admin/config/workflow/workflow/state/$wid",
      ),
      'workflow_overview_actions' => array(
        'title' => t('Actions'),
        'href' => "admin/structure/trigger/workflow/$wid",
      ),
      'workflow_overview_edit' => array(
        'title' => t('Edit'),
        'href' => "admin/config/workflow/workflow/edit/$wid",
      ),
      'workflow_overview_delete' => array(
        'title' => t('Delete'),
        'href' => "admin/config/workflow/workflow/delete/$wid",
      ),
    );
    // Allow modules to insert their own workflow operations.
    $links = array_merge($links, module_invoke_all('workflow_operations', 'workflow', $wid));
    $states = workflow_get_states($wid);
    if (!module_exists('trigger') || count($states) < 2) {
      unset($links['workflow_overview_actions']);
    }
    $row[] = array(check_plain(t($name)), theme('links', array('links' => $links)));
    $subrows = array();
    foreach ($states as $sid => $state_name) {
      $state_links = array();
      if (!workflow_is_system_state(check_plain(t($state_name)))) {
        $state_links = array(
          'workflow_overview_edit_state' => array(
            'title' => t('Edit'),
            'href' => "admin/config/workflow/workflow/state/$wid/$sid",
          ),
          'workflow_overview_delete_state' => array(
            'title' => t('Delete'),
            'href' => "admin/config/workflow/workflow/state/delete/$wid/$sid",
          ),
        );
      }
      // Allow modules to insert state operations.
      $state_links = array_merge($state_links, module_invoke_all('workflow_operations', 'state', $wid, $sid));
      $subrows[] = array(check_plain(t($state_name)), theme('links', array('links' => $state_links)));
      unset($state_links);
    }
    $subheader_state      = array(
      'data' => t('State'),
      'style' => 'width: 30%',
    );
    $subheader_operations = array(
      'data' => t('Operations'),
      'style' => 'width: 70%',
    );
    $subheader_style      = array('style' => 'width: 100%; margin: 3px 20px 20px;');
    $subtable = theme('table', array('header' => array($subheader_state, $subheader_operations), 'rows' => $subrows, 'attributes' => $subheader_style));
    $row[] = array(array(
        'data' => $subtable,
        'colspan' => '2',
      ));
  }
  if ($row) {
    $output = theme('table', array('header' => array(t('Workflow'), t('Operations')), 'rows' => $row));
    $output .= drupal_render(drupal_get_form('workflow_types_form'));
  }
  else {
    $output = '<p>' . t('No workflows have been added. Would you like to <a href="@link">add a workflow</a>?', array('@link' => url('admin/config/workflow/workflow/add'))) . '</p>';
  }
  return $output;
}

/**
 * Form builder. Create form for confirmation of deleting a workflow state.
 *
 * @param $wid
 *   integer The ID of the workflow.
 * @param $sid
 *   The ID of the workflow state.
 * @return
 *   HTML form.
 */
function workflow_state_delete_form($form, $form_state, $wid, $sid) {
  $states = workflow_get_states($wid);
  $state_name = $states[$sid];
  // Will any nodes have no state if this state is deleted?
  if ($count = db_query("SELECT COUNT(nid) FROM {workflow_node} WHERE sid = :sid", array(':sid' => $sid))->fetchField()) {
    // Cannot assign a node to (creation) because that implies
    // that the node does not exist.
    $key = array_search(t('(creation)'), $states);
    unset($states[$key]);
    // Don't include the state to be deleted in our list of possible
    // states that can be assigned.
    unset($states[$sid]);
    if ($states) {
      $form['new_sid'] = array(
        '#type' => 'select',
        '#title' => t('State to be assigned to orphaned nodes'),
        '#description' => format_plural($count, 'Since you are deleting a workflow state, a node which is in that state will be orphaned, and must be reassigned to a new state. Please choose the new state.', 'Since you are deleting a workflow state, @count nodes which are in that state will be orphaned, and must be reassigned to a new state. Please choose the new state.'),
        '#options' => $states,
      );
    }
    else {
      $form['warning'] = array(
        '#value' => format_plural($count, 'Since you are deleting the last workflow state in this workflow, the one remaining node which is in that state will have its workflow state removed. ', 'Since you are deleting the last workflow state in this workflow, @count nodes which are in that state will have their workflow state removed. '),
      );
    }
  }
  $form['wid'] = array(
    '#type' => 'value',
    '#value' => $wid,
  );
  $form['sid'] = array(
    '#type' => 'value',
    '#value' => $sid,
  );
  return confirm_form(
    $form,
    t('Are you sure you want to delete %title (and all its transitions)?', array('%title' => $state_name)),
    !empty($_GET['destination']) ? $_GET['destination'] : 'admin/config/workflow/workflow',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Submit handler for workflow state deletion form.
 *
 * @see workflow_state_delete_form()
 */
function workflow_state_delete_form_submit($form, &$form_state) {
  $states = workflow_get_states($form_state['values']['wid']);
  $state_name = $states[$form_state['values']['sid']];
  if ($form_state['values']['confirm'] == 1) {
    $new_sid = isset($form_state['values']['new_sid']) ? $form_state['values']['new_sid'] : NULL;
    workflow_state_delete($form_state['values']['sid'], $new_sid);
    watchdog('workflow', 'Deleted workflow state %name', array('%name' => $state_name));
    drupal_set_message(t('The workflow state %name was deleted.', array('%name' => $state_name)));
  }
  $form_state['redirect'] = 'admin/config/workflow/workflow';
}

/**
 * Form builder. Allow administrator to map workflows to content types
 * and determine placement.
 */
function workflow_types_form($form) {
  $form = array();
  $workflows = array(t('None')) + workflow_get_all();
  if (count($workflows) == 0) {
    return $form;
  }
  $type_map = array();
  $result = db_query("SELECT wid, type FROM {workflow_type_map}");
  foreach ($result as $data) {
    $type_map[$data->type] = $data->wid;
  }
  $form['#theme'] = 'workflow_types_form';
  $form['#tree'] = TRUE;
  $form['help'] = array(
    '#type' => 'item',
    '#value' => t('Each content type may have a separate workflow. The form for changing workflow state can be displayed when editing a node, editing a comment for a node, or both.'),
  );
  foreach (node_type_get_names() as $type => $name) {
    $form[$type]['workflow'] = array(
      '#type' => 'select',
      '#title' => check_plain($name),
      '#options' => $workflows,
      '#default_value' => isset($type_map[$type]) ? $type_map[$type] : 0,
    );
    $form[$type]['placement'] = array(
      '#type' => 'checkboxes',
      '#options' => array(
        'node' => t('Post'),
        'comment' => t('Comment'),
      ),
      '#default_value' => variable_get('workflow_' . $type, array('node')),
    );
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save workflow mapping'),
  );
  return $form;
}

/**
 * Theme the workflow type mapping form.
 */
function theme_workflow_types_form($variables) {
  $form = $variables['form'];
  $header = array(t('Content Type'), t('Workflow'), t('Display Workflow Form for:'));
  $rows = array();
  foreach (node_type_get_names() as $type => $name) {
    $name = $form[$type]['workflow']['#title'];
    unset($form[$type]['workflow']['#title']);
    $rows[] = array($name, drupal_render($form[$type]['workflow']), drupal_render($form[$type]['placement']));
  }
  $output = drupal_render($form['help']);
  $output .= theme('table', array('header' => $header, 'rows' => $rows));
  return $output . drupal_render_children($form);
}

/**
 * Submit handler for workflow type mapping form.
 *
 * @see workflow_types_form()
 */
function workflow_types_form_submit($form, &$form_state) {
  workflow_types_save($form_state['values']);
  drupal_set_message(t('The workflow mapping was saved.'));
  menu_rebuild();
  $form_state['redirect'] = 'admin/config/workflow/workflow';
}