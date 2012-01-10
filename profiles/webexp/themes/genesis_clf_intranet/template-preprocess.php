<?php

function genesis_clf_intranet_preprocess_html(&$vars) {  
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

function genesis_clf_intranet_preprocess_page(&$vars) { 
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

function genesis_clf_intranet_preprocess_node(&$vars) {
  $node = $vars['node'];
  $vars['date'] = format_date($node->created, 'custom', 'l, d/m/Y');
}
