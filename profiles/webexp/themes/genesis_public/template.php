<?php

function genesis_public_theme_theme($existing, $type, $theme, $path) {
  
}

function genesis_public_preprocess_html(&$vars) {  
  $vars['layout_sidebars'] = 'none';
  $vars['layout_desc'] = '<!-- One column layout begins / Début de la mise en page d\'une colonne -->';
  $vars['layout_id'] = '<div id="cn-body-inner-1col">';

  if (!empty($vars['page']['sidebar_first'])) {
    $vars['layout_sidebars'] = 'first';
    $vars['layout_desc'] = '<!-- Two column layout begins / Début de la mise en page d\'une colonne -->';
    $vars['layout_id'] = '<div id="cn-body-inner-2col">';
  }
  if (!empty($vars['page']['sidebar_second'])) {
    $vars['layout_desc'] = '<!-- Two column layout begins / Début de la mise en page d\'une colonne -->';
    $vars['layout_sidebars'] = ($vars['layout_sidebars'] == 'first') ? 'both' : 'second';
    $vars['layout_id'] = '<div id="cn-body-inner-2col">';
  }
}

function genesis_public_preprocess_page(&$vars) { 
  if(module_exists('i18n_menu')) {
    $is_multilingual = 1;
  } 
  
  //Search Form
  $search_box = drupal_render(drupal_get_form('search_form'));
  $vars['search_box'] = $search_box;

  //Locale Language Block
  if(module_exists('i18n')) {
    $block = block_load('locale', 'language_content');
    $block_content = _block_render_blocks(array($block));
    $build = _block_get_renderable_array($block_content);
    $vars['language_switcher'] = $build['locale_language_content']['#markup'];
  } else {
    $vars['language_switcher'] = '';
  }

   
  //Panels
  if (module_exists('panels')) {
    $page = panels_get_current_page_display();
    if ($page) {
      $vars['theme_hook_suggestions'] = array();
      $vars['panels_enable'] = $page->layout;
      $vars['theme_hook_suggestions'][] = 'page__panels';
    }
    if (isset($page->panels['right']))
    {
      $vars['panels_right'] = 'right';
    }
    if (isset($page->panels['left']))
    {
      $vars['panels_left'] = 'left';
    }
  }
  
  //Nav Bar GoC + Language Switcher
  $menu = ($is_multilingual) ? i18n_menu_navigation_links('menu-wet-header') : menu_navigation_links('menu-wet-header');
  $goc_nav_bar_markup = theme('links__menu_goc_nav_bar', array(
    'links' => $menu,
    'attributes' => array(
        'id' => 'menu',
        'class' => array('links', 'clearfix'),
      ),
   )); 
  $goc_nav_bar_markup = strip_tags($goc_nav_bar_markup, '<li><a>');
  $language_link_markup = '<li id="cn-gcnb-lang" itemscope="itemscope" itemtype="http://schema.org/SiteNavigationElement">'. strip_tags($vars['language_switcher'],'<a><span>') . '</li>';
  $vars['menu_gov_bar'] = '<ul id="menu_goc_nav_bar" class="links">' . $goc_nav_bar_markup . $language_link_markup . '</ul>';
  
  //Footer Bar GoC + Language Switcher
  $menu = ($is_multilingual) ? i18n_menu_navigation_links('menu-wet-footer') : menu_navigation_links('menu-wet-footer');
  $goc_footer_bar_markup = theme('links__menu_goc_footer_bar', array(
    'links' => $menu,
    'attributes' => array(
        'id' => 'menu',
        'class' => array('links', 'clearfix'),
      ),
   )); 
  $vars['menu_gov_footer_bar'] = $goc_footer_bar_markup;
  
  //About Us Section
  $menu = ($is_multilingual) ? i18n_menu_navigation_links('menu-wet-aboutus') : menu_navigation_links('menu-wet-aboutus');
  $goc_footer_bar_markup = theme('links__menu_goc_sections', array(
    'links' => $menu,
    'attributes' => array(
        'id' => 'menu',
        'class' => array('links', 'clearfix'),
      ),
   )); 
  $vars['menu_gov_about_bar'] = $goc_footer_bar_markup;
  
  //News Bar
  $menu = ($is_multilingual) ? i18n_menu_navigation_links('menu-wet-news') : menu_navigation_links('menu-wet-news');
  $goc_news_bar_markup = theme('links__menu_goc_sections', array(
    'links' => $menu,
    'attributes' => array(
        'id' => 'menu',
        'class' => array('links', 'clearfix'),
      ),
   )); 
  $vars['menu_gov_news_bar'] = $goc_news_bar_markup;
  
  //Contact Us Bar
  $menu = ($is_multilingual) ? i18n_menu_navigation_links('menu-wet-contactus') : menu_navigation_links('menu-wet-contactus');
  $goc_contact_bar_markup = theme('links__menu_goc_sections', array(
    'links' => $menu,
    'attributes' => array(
        'id' => 'menu',
        'class' => array('links', 'clearfix'),
      ),
   )); 
  $vars['menu_gov_contact_bar'] = $goc_contact_bar_markup;
  
  //Stay Connected Bar
  $menu = ($is_multilingual) ? i18n_menu_navigation_links('menu-wet-stayconnected') : menu_navigation_links('menu-wet-stayconnected');
  $goc_connected_bar_markup = theme('links__menu_goc_sections', array(
    'links' => $menu,
    'attributes' => array(
        'id' => 'menu',
        'class' => array('links', 'clearfix'),
      ),
   )); 
  $vars['menu_gov_connected_bar'] = $goc_connected_bar_markup;
  
  //Terms Bar
  $menu = ($is_multilingual) ? i18n_menu_navigation_links('menu-wet-terms') : menu_navigation_links('menu-wet-terms');
  $goc_terms_bar_markup = theme('links__menu_goc_terms_bar', array(
    'links' => $menu,
    'attributes' => array(
        'id' => 'menu',
        'class' => array('links', 'clearfix'),
      ),
   )); 
  $vars['menu_gov_terms_bar'] = $goc_terms_bar_markup;  

  //Mega Menu
  if (module_exists('nice_menus')) {
    $vars['mega_menu'] = theme('nice_menus', array('id' => 0, 'direction' => 'down', 'depth' => 3, 'menu_name' => 'main-menu', 'menu' => NULL));
  }
  else {
    //Main Menu Bar
    $vars['mega_menu'] = theme('links__system_main_menu',
      array(
        'links' => $vars['main_menu'],
        'attributes' => array(
        'id' => 'wet-boew-navigation',
          'class' => array(
            'links', 'clearfix', 'wet-boew-megamenu wet-boew-menu site-bar show-first rounded',
          )
        ), 
        'heading' => array(
          'text' => t('Main menu'),
          'level' => 'h2',
          'class' => array(
            'element-invisible',
          ),
        )
      )
    );
  } 
}

function genesis_public_nice_menus($variables) {
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

function genesis_public_nice_menus_build($variables) {
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
        
        if($menu_item['link']['depth'] == 1) {
          $output .= '<li class="menu-' . $mlid . ' ' . $parent_class . $class . $first_class . $oddeven_class . $last_class . '"><section><h3>'. theme('nice_menus_menu_item_link', $variables) . '</h3>';
        }
        else if($menu_item['link']['depth'] == 2){
          $output .= '<div class="menu-col">';
        }
        else if($menu_item['link']['depth'] == 3){
          $output .= '<section><h4 class="col-head">'. theme('nice_menus_menu_item_link', $variables) . '</h4>';
        }
        else {
          $output .= '<li class="menu-' . $mlid . ' ' . $parent_class . $class . $first_class . $oddeven_class . $last_class . '">'. theme('nice_menus_menu_item_link', $variables);
        }
        
        // Check our depth parameters.
        if ($menu_item['link']['depth'] <= $depth || $depth == -1) {
          // Build the child UL only if children are displayed for the user.
          if ($children && ($menu_item['link']['depth'] == 1)) {
            $output .= '<div class="showcase">';
            $output .= $children;
            $output .= "</div>\n";
          }
          else if ($children && ($menu_item['link']['depth'] == 2)) {
            $output .= $children;
          }
          else if ($children && ($menu_item['link']['depth'] == 3)) {
            $output .= '<ul>';
            $output .= $children;
            $output .= "</ul>\n";
          }
        }
        if($menu_item['link']['depth'] == 1) {
          $output .= "</section></li>\n";
        }
        else if($menu_item['link']['depth'] == 2){
          $output .= '</div>';
        }
        else if($menu_item['link']['depth'] == 3){
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

function genesis_public_nice_menus_main_menu($variables) {
  $direction = $variables['direction'];
  $depth = $variables['depth'];
  $menu_name = variable_get('menu_main_links_source', 'main-menu');
  $output = theme('nice_menus', array('id' => 0, 'menu_name' => $menu_name, 'mlid' => 0, 'direction' => $direction, 'depth' => $depth));
  return $output['content'];
}

function genesis_public_nice_menus_menu_item_link($variables) {
  if (empty($variables['element']['#localized_options'])) {
    $variables['element']['#localized_options'] = array();
  }
  return l($variables['element']['#title'], $variables['element']['#href'], $variables['element']['#localized_options']);
}

function genesis_public_links__menu_goc_terms_bar($variables)  {
$links = $variables['links'];
  $attributes = $variables['attributes'];
  $heading = $variables['heading'];
  global $language_url;
  $output = '';

  if (count($links) > 0) {
    $output = '';

    // Treat the heading first if it is present to prepend it to the
    // list of links.
    if (!empty($heading)) {
      if (is_string($heading)) {
        // Prepare the array that will be used when the passed heading
        // is a string.
        $heading = array(
          'text' => $heading,
          // Set the default level of the heading. 
          'level' => 'h2',
        );
      }
      $output .= '<' . $heading['level'];
      if (!empty($heading['class'])) {
        $output .= drupal_attributes(array('class' => $heading['class']));
      }
      $output .= '>' . check_plain($heading['text']) . '</' . $heading['level'] . '>';
    }

    $output .= '<ul' . drupal_attributes($attributes) . '>';

    $num_links = count($links);
    $i = 1;

    foreach ($links as $key => $link) {
      $class = array($key);

      // Add first, last and active classes to the list of links to help out themers.
      if ($i == 1) {
        $class[] = 'first';
        $class[] = 'terms';
      }
      if ($i == $num_links) {
        $class[] = 'last';
        $class[] = 'trans';
      }
      if (isset($link['href']) && ($link['href'] == $_GET['q'] || ($link['href'] == '<front>' && drupal_is_front_page()))
           && (empty($link['language']) || $link['language']->language == $language_url->language)) {
        $class[] = 'active';
      }
      
      $output .= '<li' . drupal_attributes(array('class' => $class)) . '>';

      if (isset($link['href'])) {
        // Pass in $link as $options, they share the same keys.
        $output .= l($link['title'], $link['href'], $link);
      }
      elseif (!empty($link['title'])) {
        // Some links are actually not links, but we wrap these in <span> for adding title and class attributes.
        if (empty($link['html'])) {
          $link['title'] = check_plain($link['title']);
        }
        $span_attributes = '';
        if (isset($link['attributes'])) {
          $span_attributes = drupal_attributes($link['attributes']);
        }
        $output .= '<span' . $span_attributes . '>' . $link['title'] . '</span>';
      }

      $i++;
      $output .= "</li>\n";
    }

    $output .= '</ul>';
  }

  return $output;
}

function genesis_public_links__menu_goc_sections($variables)  {
  $links = $variables['links'];
  $attributes = $variables['attributes'];
  $heading = $variables['heading'];
  global $language_url;
  $output = '';

  if (count($links) > 0) {
    $output = '';

    // Treat the heading first if it is present to prepend it to the
    // list of links.
    if (!empty($heading)) {
      if (is_string($heading)) {
        // Prepare the array that will be used when the passed heading
        // is a string.
        $heading = array(
          'text' => $heading,
          // Set the default level of the heading. 
          'level' => 'h2',
        );
      }
      $output .= '<' . $heading['level'];
      if (!empty($heading['class'])) {
        $output .= drupal_attributes(array('class' => $heading['class']));
      }
      $output .= '>' . check_plain($heading['text']) . '</' . $heading['level'] . '>';
    }

    $output .= '<ul' . drupal_attributes($attributes) . '>';

    $num_links = count($links);
    $i = 1;

    foreach ($links as $key => $link) {
      $class = array($key);

      // Add first, last and active classes to the list of links to help out themers.
      if ($i == 1) {
        $class[] = 'first';
      }
      if ($i == $num_links) {
        $class[] = 'last';
      }
      if (isset($link['href']) && ($link['href'] == $_GET['q'] || ($link['href'] == '<front>' && drupal_is_front_page()))
           && (empty($link['language']) || $link['language']->language == $language_url->language)) {
        $class[] = 'active';
      }
      
      if ($i == 1){
        $output .= '<h4 class="col-head">';
      }
      else {
        $output .= '<li' . drupal_attributes(array('class' => $class)) . '>';
      }

      if (isset($link['href'])) {
        // Pass in $link as $options, they share the same keys.
        $output .= l($link['title'], $link['href'], $link);
      }
      elseif (!empty($link['title'])) {
        // Some links are actually not links, but we wrap these in <span> for adding title and class attributes.
        if (empty($link['html'])) {
          $link['title'] = check_plain($link['title']);
        }
        $span_attributes = '';
        if (isset($link['attributes'])) {
          $span_attributes = drupal_attributes($link['attributes']);
        }
        $output .= '<span' . $span_attributes . '>' . $link['title'] . '</span>';
      }

      if ($i == 1){
        $output .= "</h4>\n";
      }
      else {
        $output .= "</li>\n";
      }
      
      
      $i++;
    }

    $output .= '</ul>';
  }

  return $output;
}

function genesis_public_links__menu_goc_footer_bar($variables) {
  $links = $variables['links'];
  $attributes = $variables['attributes'];
  $heading = $variables['heading'];
  global $language_url;
  $output = '';

  if (count($links) > 0) {
    $output = '';

    // Treat the heading first if it is present to prepend it to the
    // list of links.
    if (!empty($heading)) {
      if (is_string($heading)) {
        // Prepare the array that will be used when the passed heading
        // is a string.
        $heading = array(
          'text' => $heading,
          // Set the default level of the heading. 
          'level' => 'h2',
        );
      }
      $output .= '<' . $heading['level'];
      if (!empty($heading['class'])) {
        $output .= drupal_attributes(array('class' => $heading['class']));
      }
      $output .= '>' . check_plain($heading['text']) . '</' . $heading['level'] . '>';
    }

    $output .= '<ul' . drupal_attributes($attributes) . '>';

    $num_links = count($links);
    $i = 1;

    foreach ($links as $key => $link) {
      $class = array($key);

      // Add first, last and active classes to the list of links to help out themers.
      if ($i == 1) {
        $class[] = 'first';
      }
      if ($i == $num_links) {
        $class[] = 'last';
      }
      if (isset($link['href']) && ($link['href'] == $_GET['q'] || ($link['href'] == '<front>' && drupal_is_front_page()))
           && (empty($link['language']) || $link['language']->language == $language_url->language)) {
        $class[] = 'active';
      }
      
      //Custom Override is here for last link
      if ($i == $num_links) {
        $output .= '<li id="cn-ft-ca"' . drupal_attributes(array('class' => $class)) . '><div>';
      }
      else {
        $output .= '<li' . drupal_attributes(array('class' => $class)) . '>';
      }
      
      if (isset($link['href'])) {
        // Pass in $link as $options, they share the same keys.
        
        //Custom Override is here
        if ( isset($link['attributes']['title']) )  {
          $link['html'] = TRUE;
          $link['attributes']['rel'] = 'external';
          $output .= l('<span>'. $link['title'] . '</span>' . '<br>' . $link['attributes']['title'], $link['href'], $link);
        }
        else {
          $output .= l($link['title'], $link['href'], $link);
        }
      }
      elseif (!empty($link['title'])) {
        // Some links are actually not links, but we wrap these in <span> for adding title and class attributes.
        if (empty($link['html'])) {
          $link['title'] = check_plain($link['title']);
        }
        $span_attributes = '';
        if (isset($link['attributes'])) {
          $span_attributes = drupal_attributes($link['attributes']);
        }
        $output .= '<span' . $span_attributes . '>' . $link['title'] . '</span>';
      }

      if ($i == $num_links) {
        $output .= "</div></li>\n";
      }
      else {
        $output .= "</li>\n";
      }
      $i++;
    }

    $output .= '</ul>';
  }
  
  return $output;
}

function genesis_public_links__menu_goc_nav_bar($variables) {
  $links = $variables['links'];
  $attributes = $variables['attributes'];
  $heading = $variables['heading'];
  global $language_url;
  $output = '';

  if (count($links) > 0) {
    $output = '';

    // Treat the heading first if it is present to prepend it to the
    // list of links.
    if (!empty($heading)) {
      if (is_string($heading)) {
        // Prepare the array that will be used when the passed heading
        // is a string.
        $heading = array(
          'text' => $heading,
          // Set the default level of the heading. 
          'level' => 'h2',
        );
      }
      $output .= '<' . $heading['level'];
      if (!empty($heading['class'])) {
        $output .= drupal_attributes(array('class' => $heading['class']));
      }
      $output .= '>' . check_plain($heading['text']) . '</' . $heading['level'] . '>';
    }

    $output .= '<ul' . drupal_attributes($attributes) . '>';

    $num_links = count($links);
    $i = 1;

    foreach ($links as $key => $link) {
      $class = array($key);

      // Add first, last and active classes to the list of links to help out themers.
      if ($i == 1) {
        $class[] = 'first';
      }
      if ($i == $num_links) {
        $class[] = 'last';
      }
      if (isset($link['href']) && ($link['href'] == $_GET['q'] || ($link['href'] == '<front>' && drupal_is_front_page()))
           && (empty($link['language']) || $link['language']->language == $language_url->language)) {
        $class[] = 'active';
      }
      $output .= '<li id="cn-gcnb' . $i . '"' . drupal_attributes(array('class' => $class)) . '>';

      if (isset($link['href'])) {
        // Pass in $link as $options, they share the same keys.
        $output .= l($link['title'], $link['href'], $link);
      }
      elseif (!empty($link['title'])) {
        // Some links are actually not links, but we wrap these in <span> for adding title and class attributes.
        if (empty($link['html'])) {
          $link['title'] = check_plain($link['title']);
        }
        $span_attributes = '';
        if (isset($link['attributes'])) {
          $span_attributes = drupal_attributes($link['attributes']);
        }
        $output .= '<span' . $span_attributes . '>' . $link['title'] . '</span>';
      }

      $i++;
      $output .= "</li>\n";
    }

    $output .= '</ul>';
  }

  return $output;
}


function genesis_public_menu_local_tasks(&$variables) {
  $output = '';
  if (!empty($variables['primary'])) {
    $variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Drupal Primary tabs') . '</h2>';
    $variables['primary']['#prefix'] .= '<ul class="drupaltabs primary">';
    $variables['primary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['primary']);
  }
  if (!empty($variables['secondary'])) {
    $variables['secondary']['#prefix'] = '<h2 class="element-invisible">' . t('Drupal Secondary tabs') . '</h2>';
    $variables['secondary']['#prefix'] .= '<ul class="drupaltabs secondary">';
    $variables['secondary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['secondary']);
  }
  return $output;
}

function genesis_public_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  $crumbs = '';
  if (!empty($breadcrumb)) {
      $crumbs = '<ol class="breadcrumbs">';

      foreach($breadcrumb as $value) {
           $crumbs .= '<li>'.$value.'</li>';
      }
      $crumbs .= '</ol>';
    }
      return $crumbs;
  }
  
function genesis_public_form_alter(&$form, &$form_state, $form_id){
  if ($form_id == 'search_form'){
      $form['basic']['keys']['#id'] = 'cn-search';
      $form['basic']['submit']['#id'] = 'cn-search-submit';
  }
}

function genesis_public_preprocess_node(&$vars) {
  $node = $vars['node'];
  $vars['date'] = format_date($node->created, 'custom', 'l, d/m/Y');
}
