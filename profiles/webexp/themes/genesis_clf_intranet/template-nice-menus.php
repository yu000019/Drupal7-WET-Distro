<?php
/**
 * @file
 * template-nice-menus.php
 */

function genesis_clf_intranet_nice_menus($variables) {
  $output = array(
    'content' => '',
    'subject' => '',
  );

  $id = $variables['id'];
  $menu_name = $variables['menu_name'];
  $mlid = $variables['mlid'];
  $direction = $variables['direction'];
  $depth = $variables['depth'];
  $menu = $variables['menu'];

  if ($menu_tree = theme('nice_menus_tree', array('menu_name' => $menu_name, 'mlid' => $mlid, 'depth' => $depth, 'menu' => $menu))) {
    if ($menu_tree['content']) {
      $output['content'] = '<ul class="wet-boew-menu wetd7-menu wetd7-menu-' . $direction . '" id="wetd7-menu-' . $id . '">' . $menu_tree['content'] . '</ul>' . "\n";
      $output['subject'] = $menu_tree['subject'];
    }
  }
  return $output;
}

function genesis_clf_intranet_nice_menus_build($variables) {
  $menu = $variables['menu'];
  $depth = $variables['depth'];
  $trail = $variables['trail'];
  $output = '';
  // Prepare to count the links so we can mark first, last, odd and even.
  $index = 0;
  $count = 0;
  foreach ($menu as $menu_count) {
    if ($menu_count['link']['hidden'] == 0) {
      $count++;
    }
  }
  // Get to building the menu.
  foreach ($menu as $menu_item) {
    $mlid = $menu_item['link']['mlid'];
    // Check to see if it is a visible menu item.
    if (!isset($menu_item['link']['hidden']) || $menu_item['link']['hidden'] == 0) {
      // Check our count and build first, last, odd/even classes.
      $index++;
      $first_class = $index == 1 ? ' first ' : '';
      $oddeven_class = $index % 2 == 0 ? ' even ' : ' odd ';
      $last_class = $index == $count ? ' last ' : '';
      // Build class name based on menu path
      // e.g. to give each menu item individual style.
      // Strip funny symbols.
      $clean_path = str_replace(array('http://', 'www', '<', '>', '&', '=', '?', ':', '.'), '', $menu_item['link']['href']);
      // Convert slashes to dashes.
      $clean_path = str_replace('/', '-', $clean_path);
      $class = 'menu-path-' . $clean_path;
      if ($trail && in_array($mlid, $trail)) {
        $class .= ' active-trail';
      }
      // If it has children build a nice little tree under it.
      if ((!empty($menu_item['link']['has_children'])) && (!empty($menu_item['below'])) && $depth != 0) {
        // Keep passing children into the function 'til we get them all.
        $children = theme('nice_menus_build', array('menu' => $menu_item['below'], 'depth' => $depth, 'trail' => $trail));
        // Set the class to parent only of children are displayed.
        $parent_class = ($children && ($menu_item['link']['depth'] <= $depth || $depth == -1)) ? 'menuparent ' : '';
        $element = array(
          '#below' => '',
          '#title' => $menu_item['link']['link_title'],
          '#href' =>  $menu_item['link']['href'],
          '#localized_options' => $menu_item['link']['localized_options'],
          '#attributes' => array(),
        );
        $variables['element'] = $element;
        if ($menu_item['link']['depth'] == 1) {
          $output .= '<li class="menu-' . $mlid . ' ' . $parent_class . $class . $first_class . $oddeven_class . $last_class . '"><section><h3>' . theme('nice_menus_menu_item_link', $variables) . '</h3>';
        }
        elseif ($menu_item['link']['depth'] == 2) {
          $output .= '<div class="menu-col">';
        }
        elseif ($menu_item['link']['depth'] == 3) {
          $output .= '<section><h4 class="col-head">' . theme('nice_menus_menu_item_link', $variables) . '</h4>';
        }
        else {
          $output .= '<li class="menu-' . $mlid . ' ' . $parent_class . $class . $first_class . $oddeven_class . $last_class . '">' . theme('nice_menus_menu_item_link', $variables);
        }
        // Check our depth parameters.
        if ($menu_item['link']['depth'] <= $depth || $depth == -1) {
          // Build the child UL only if children are displayed for the user.
          if ($children && ($menu_item['link']['depth'] == 1)) {
            $output .= '<div class="showcase">';
            $output .= $children;
            $output .= "</div>\n";
          }
          elseif ($children && ($menu_item['link']['depth'] == 2)) {
            $output .= $children;
          }
          elseif ($children && ($menu_item['link']['depth'] == 3)) {
            $output .= '<ul>';
            $output .= $children;
            $output .= "</ul>\n";
          }
        }
        if ($menu_item['link']['depth'] == 1) {
          $output .= "</section></li>\n";
        }
        elseif ($menu_item['link']['depth'] == 2) {
          $output .= '</div>';
        }
        elseif ($menu_item['link']['depth'] == 3) {
          $output .= '</section>';
        }
        else {
          $output .= "</li>\n";
        }
      }
      else {
        $element = array(
          '#below' => '',
          '#title' => $menu_item['link']['link_title'],
          '#href' =>  $menu_item['link']['href'],
          '#localized_options' => $menu_item['link']['localized_options'],
          '#attributes' => array(),
        );
        $variables['element'] = $element;
        $output .= '<li class="menu-' . $mlid . ' ' . $class . $first_class . $oddeven_class . $last_class . '">' . theme('nice_menus_menu_item_link', $variables) . "</li>\n";
      }
    }
  }
  return $output;
}

function genesis_clf_intranet_nice_menus_main_menu($variables) {
  $direction = $variables['direction'];
  $depth = $variables['depth'];
  $menu_name = variable_get('menu_main_links_source', 'main-menu');
  $output = theme('nice_menus', array('id' => 0, 'menu_name' => $menu_name, 'mlid' => 0, 'direction' => $direction, 'depth' => $depth));
  return $output['content'];
}

function genesis_clf_intranet_nice_menus_menu_item_link($variables) {
  if (empty($variables['element']['#localized_options'])) {
    $variables['element']['#localized_options'] = array();
  }
  return l($variables['element']['#title'], $variables['element']['#href'], $variables['element']['#localized_options']);
}
