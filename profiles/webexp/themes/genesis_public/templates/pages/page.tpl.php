<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/garland.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 * - $in_overlay: TRUE if the page is in the overlay.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlight']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 */
?>

<div id="cn-head">
  <div id="cn-head-inner">
    <header itemscope="itemscope" itemtype="http://schema.org/WPHeader">

      <nav role="navigation">
        <div id="cn-gcnb">
          <h2><?php print t('Public Organization navigation bar'); ?></h2>
          <div id="cn-gcnb-inner">
            <div id="fip-pcim-gcnb" itemscope="itemscope" itemtype="http://schema.org/WPAdBlock">
              <div id="cn-sig">
                <div id="cn-sig-inner">
                  <?php if ($language->language == 'en'): ?>
                    <div id="fip-pcim-sig-eng" title="Public Organization">
                      <img src="/<?php print(drupal_get_path('theme', 'genesis_public'));?>/css/theme-gcwu-fegc/fip-pcim/images/sig-eng.gif" width="214" height="20" alt="Public Organization">
                    </div>
                  <?php endif;?>

                  <?php if ($language->language == 'fr'): ?>
                    <div id="fip-pcim-sig-fra" title="organisation publique">
                      <img src="/<?php print(drupal_get_path('theme', 'genesis_public'));?>/css/theme-gcwu-fegc/fip-pcim/images/sig-fra.gif" width="214" height="20" alt="organisation publique">
                    </div>
                  <?php endif;?>  
                </div>
              </div>
              <?php print $menu_gov_bar; ?>
            </div>
          </div>
        </div>
      </nav>

      <div id="cn-banner" role="banner">
        <div id="cn-banner-inner">
          <div id="cn-wmms">
            <div id="cn-wmms-inner">
              <?php if ($language->language == 'en'): ?>
                <div id="fip-pcim-wmms" title="Symbol of the Public Organization"><img src="/<?php print(drupal_get_path('theme', 'genesis_public'));?>/css/theme-gcwu-fegc/fip-pcim/images/wmms.gif" width="126" height="30" alt="Symbol of the Public Organization"></div>
              <?php endif;?>

              <?php if ($language->language == 'fr'): ?>
                <div id="fip-pcim-wmms" title="Symbole du organisation publique"><img src="/<?php print(drupal_get_path('theme', 'genesis_public'));?>/css/theme-gcwu-fegc/fip-pcim/images/wmms.gif" width="126" height="30" alt="Symbole du organisation publique"></div>
              <?php endif;?>
            </div>
          </div>  

          <?php if ($linked_site_logo || $site_name || $site_slogan): ?>
            <div id="branding">
              <?php if ($site_name || $site_slogan): ?>
                <hgroup<?php if (!$site_slogan && $hide_site_name): ?> class="<?php print $visibility; ?>"<?php endif; ?>>
                  <div id="cn-site-title">

                    <?php if ($site_name): ?>
                      <p id="cn-site-title-inner"<?php if ($hide_site_name): ?> class="<?php print $visibility; ?>"<?php endif; ?>><?php print $site_name; ?></p>
                    <?php endif; ?>

                    <?php if ($site_slogan): ?>
                      <h2 id="site-slogan"><?php print $site_slogan; ?></h2>
                    <?php endif; ?>

                  </div>
                </hgroup>
              <?php endif; ?>
            </div>        
          <?php endif; ?>

          <section role ="search">
            <div id="cn-search-box">
              <h2><?php print t('Search'); ?></h2>
              <?php if ($search_box): ?>
                <div id="cn-search-box-inner"><?php print $search_box; ?></div>
              <?php endif; ?>
            </div>
          </section>

        </div>
      </div>
   
      <nav role="navigation">
        <div id="cn-psnb">
          <h2><?php print t('Primary site navigation bar'); ?></h2>
          <div id="cn-psnb-inner">
            <div class="wet-boew-menubar wet-boew-megamenu" itemscope="itemscope" itemtype="http://schema.org/SiteNavigationElement">
              <?php if ($main_menu_links): ?>
                <div class="main-menu-inner">
                  <?php print $mega_menu['content']; ?>
                </div>
               <?php endif; ?>
            </div>
            
            <?php if ($header_blocks = render($page['header'])): ?>
              <div id="header-blocks">
                <?php print $header_blocks; ?>
              </div>
            <?php endif; ?>
          
          </div>
        </div>
        <div id="cn-bc">
          <h2><?php print t('Breadcrumbs'); ?></h2>
          <div id="cn-bc-inner">
            <?php print $breadcrumb; ?>
          </div>
        </div>     
      </nav>
      
    </header>
  </div>
</div>

<div id="cn-cols">
  <div id="cn-cols-inner" class="equalize">
  
    <div id="cn-centre-col" role="main" itemprop="mainContentOfPage">
      <div id="cn-centre-col-inner">
              
          <h1 id="cn-cont" class="cn-invisible">Public Organization - Drupal CLF3</h1>
         
          <section>
            <?php print $messages; ?>
            <?php if ($help = render($page['help'])): print $help; endif; ?>
            <?php if ($secondary_content = render($page['secondary_content'])): ?>
              <div id="secondary-content">
                <?php print $secondary_content; ?>
              </div>
            <?php endif; ?> 

            <?php if ($highlighted = render($page['highlighted'])): ?>
              <div id="highlighted"><?php print $highlighted; ?></div>
            <?php endif; ?>

            <div id="main-content" role="main">
              <?php print render($title_prefix); ?>
              <?php if ($title): ?>
                <h1 id="page-title"><?php print $title; ?></h1>
              <?php endif; ?>
              <?php print render($title_suffix); ?>

              <?php if ($tabs = render($tabs)): ?>
                <div class="local-tasks"><?php print $tabs; ?></div>
              <?php endif; ?>

              <?php if ($action_links = render($action_links)): ?>
                <ul class="action-links"><?php print $action_links; ?></ul>
              <?php endif; ?>

              <div id="content">
                <?php print render($page['content']); ?>
                <?php print $feed_icons; ?>
              </div>
            </div>
          </section>
       
        </div>
      </div>

    <div id="cn-left-col">
      <div id="cn-left-col-inner" style="min-height: 680px; ">
        <nav role="navigation">
          <h2 id="cn-nav">Primary navigation (left column)</h2>
          <div class="cn-left-col-default">
            <?php if ($sidebar_first = render($page['sidebar_first'])): ?>
              <div id="sidebar-first" class="sidebar">
                <?php print $sidebar_first; ?>
              </div>
            <?php endif; ?>
          </div>
        </nav>
      </div>
    </div>

  </div>
</div>

<div id="cn-foot"><div id="cn-foot-inner">
	<footer itemscope="itemscope" itemtype="http://schema.org/WPFooter">
		<h2 id="cn-nav"><?php print t('Footer'); ?></h2>
    
    <nav role="navigation">
			<div id="cn-sft">
				<h3><?php print t('Site Footer'); ?></h3>
				<div id="cn-sft-inner" itemscope="itemscope" itemtype="http://schema.org/SiteNavigationElement">
					<div id="cn-ft-tctr">
            <?php print $menu_gov_terms_bar; ?>
        	</div>
					<div class="clear"></div>
					<section>
						<div class="span-2">
              <?php print $menu_gov_about_bar; ?>
        		</div>
					</section>
					<section>
						<div class="span-2">
              <?php print $menu_gov_news_bar; ?>
        		</div>
					</section>
					<section>
						<div class="span-2">
              <?php print $menu_gov_contact_bar; ?>
    				</div>
					</section>
					<section>
						<div class="span-2">
              <?php print $menu_gov_connected_bar; ?>
    				</div>
					</section>
          
        <?php if ($tertiary_content = render($page['tertiary_content'])): ?>
          <div id="tertiary-content"><?php print $tertiary_content; ?></div>
        <?php endif; ?>

        <?php if ($page_footer = render($page['footer'])): ?>
          <footer id="footer" role="contentinfo"><?php print $page_footer; ?></footer>
        <?php endif; ?>
          
				</div>
			</div>
		</nav>
	
    <nav role="navigation">
			<div id="cn-gcft">
				<h3><?php print t('Public Organization Footer'); ?></h3>
				<div id="cn-gcft-inner">
					<div id="fip-pcim-gcft" itemscope="itemscope" itemtype="http://schema.org/WPAdBlock">
              <?php print $menu_gov_footer_bar; ?>
  				</div>
				</div>
			</div>
		</nav>

  </footer>
	</div>
</div>
