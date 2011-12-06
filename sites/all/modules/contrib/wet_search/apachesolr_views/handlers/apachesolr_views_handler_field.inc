<?php

class apachesolr_views_handler_field extends views_handler_field {

  function get_value($values, $field = NULL) {
    $alias = isset($field) ? $this->aliases[$field] : $this->field_alias;
    if (isset($values->node->{$alias})) {
      return $values->node->{$alias};
    }
  }

}