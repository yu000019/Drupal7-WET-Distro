<?php

/**
 * @file
 * Password policy constraint callback to set a minimum delay between password changes.
 *
 * @link http://drupal.org/node/316765
 * @author David Kent Norman (http://deekayen.net/)
 */

//////////////////////////////////////////////////////////////////////////////
// Constraint API

/**
 * Description of the constraint.
 */
function password_policy_constraint_delay_description() {
  return array('name' => t('Delay'), 'description' => t('Minimum number of hours between password changes.'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_delay_error($constraint) {
  return format_plural($constraint, 'Password may only be changed in an hour from the last change.', 'Password may only be changed in @count hours from the last change.');
}

/**
 * Password validation.
 */
function password_policy_constraint_delay_validate($password, $constraint, $uid) {
  $result = db_query_range("SELECT MAX(created) as created FROM {password_policy_history} WHERE uid = :uid", 0, 1, array(':uid' => $uid));
  $last_change = $result->fetchField();
  if (!empty($last_change)) {
    // Constraint is set in hours, so it gets converted to seconds with *60*60.
    return time() - ($constraint*60*60) > $last_change;
  }
  return TRUE;
}

function password_policy_constraint_delay_js() {
  return '';
}
