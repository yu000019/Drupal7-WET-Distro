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

<!-- Header begins / Début de l'en-tête -->
<div id="cn-head">
  <div id="cn-head-inner">
    <header itemscope="itemscope" itemtype="http://schema.org/WPHeader">
      <!-- GC Web Usability theme begins / Début du thème de la facilité d'emploi GC -->
      
      <!-- GC navigation bar begins / Début de la barre de menu GC -->    
      <nav role="navigation">
        <div id="cn-gcnb">
          <h2><?php print t('Government of Canada navigation bar'); ?></h2>
          <div id="cn-gcnb-inner">
            <div id="fip-pcim-gcnb" itemscope="itemscope" itemtype="http://schema.org/WPAdBlock">
              <div id="cn-sig">
                <div id="cn-sig-inner">
                  <?php if ($language->language == 'en'): ?>
                    <div id="fip-pcim-sig-eng" title="Government of Canada">
                      <img src="/<?php print(drupal_get_path('theme', 'genesis_clf_intranet'));?>/css/theme-gcwu-fegc/fip-pcim/images/sig-eng.gif" width="214" height="20" alt="Government of Canada">
                    </div>
                  <?php endif;?>

                  <?php if ($language->language == 'fr'): ?>
                    <div id="fip-pcim-sig-fra" title="Gouvernement du Canada">
                      <img src="/<?php print(drupal_get_path('theme', 'genesis_clf_intranet'));?>/css/theme-gcwu-fegc/fip-pcim/images/sig-fra.gif" width="214" height="20" alt="Gouvernement du Canada">
                    </div>
                  <?php endif;?>  
                </div>
              </div>
              <!-- Custom Drupal WET: Header -->
              <div id="cn-intranetnb">
                <div id="cn-intranetnb-inner">
                  <?php print $menu_gov_bar; ?>
                </div>
              </div>
              <!-- /Custom Drupal WET: Header -->
              
              <div id="cn-wmms">
                <div id="cn-wmms-inner">
                  <?php if ($language->language == 'en'): ?>
                    <div id="fip-pcim-wmms" title="Symbol of the Government of Canada"><img src="/<?php print(drupal_get_path('theme', 'genesis_clf_intranet'));?>/css/theme-gcwu-fegc/fip-pcim/images/wmms.gif" width="126" height="30" alt="Symbol of the Government of Canada"></div>
                  <?php endif;?>

                  <?php if ($language->language == 'fr'): ?>
                    <div id="fip-pcim-wmms" title="Symbole du gouvernement du Canada"><img src="/<?php print(drupal_get_path('theme', 'genesis_clf_intranet'));?>/css/theme-gcwu-fegc/fip-pcim/images/wmms.gif" width="126" height="30" alt="Symbole du gouvernement du Canada"></div>
                  <?php endif;?>
                </div>
              </div>  
              
            </div>
          </div>
        </div>
      </nav>
      <!-- GC navigation bar ends / Fin de la barre de navigation GC -->
      
      <!-- Banner begins / Début de la bannière -->
      <div id="cn-banner" role="banner">
        <div id="cn-banner-inner">

          <!-- Drupal Content Begins -->
          <?php if ($linked_site_logo || $site_name || $site_slogan): ?>
            <div id="branding">
              <?php if ($site_name || $site_slogan): ?>
                <hgroup<?php if (!$site_slogan && $hide_site_name): ?> class="<?php print $visibility; ?>"<?php endif; ?>>
                  <div id="cn-site-title">

                    <!-- Site title begins / Début du titre du site -->
                    <?php if ($site_name): ?>
                      <p id="cn-site-title-inner"<?php if ($hide_site_name): ?> class="<?php print $visibility; ?>"<?php endif; ?>><?php print $site_name; ?></p>
                    <?php endif; ?>
                    <!-- Site title ends / Fin du titre du site -->

                    <?php if ($site_slogan): ?>
                      <h2 id="site-slogan"><?php print $site_slogan; ?></h2>
                    <?php endif; ?>

                  </div>
                </hgroup>
              <?php endif; ?>
            </div>        
          <?php endif; ?>
          <!-- Drupal Content Ends -->
          
          <!-- Site search begins / Début de la recherche du site -->
          <section role ="search">
            <div id="cn-search-box">
              <h2><?php print t('Search'); ?></h2>
              <?php if ($search_box): ?>
                <div id="cn-search-box-inner"><?php print $search_box; ?></div>
              <?php endif; ?>
            </div>
          </section>
          <!-- Site search ends / Fin de la recherche du site -->
          
        </div>
      </div>
      <!-- Banner ends / Fin de la bannière -->
      
      <div class="cn-subsite-1" id="cn-subsite">
	  		<p><a href="#">Sub site name</a></p>
      </div>
   
      <nav role="navigation">
        <!-- Primary site navigation bar begins / Début de la barre de navigation primaire du site -->
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
        <!-- Primary site navigation bar ends / Fin de la barre de navigation primaire du site -->

      </nav>
      
      <!-- GC Web Usability theme ends / Fin du thème de la facilité d'emploi GC -->
    </header>
  </div>
</div>
<!-- Header ends / Fin de l'en-tête -->   

<!-- Columns begin / Début des colonnes -->
<div id="cn-cols">
  <div id="cn-cols-inner" class="equalize">
    
    <!-- Main content begins / Début du contenu principal -->
      <div id="cn-centre-col" role="main" itemprop="mainContentOfPage">
        <div id="cn-centre-col-inner">
          
            <!-- Begin Tabs -->
              <?php if ($slider = render($page['slideshow'])): ?>
               <?php print $slider; ?>
              <?php endif; ?>
            <!-- End Tabs -->       
           
            <!-- GC Web Usability theme begins / Début du thème de la facilité d'emploi GC -->
            <?php print $messages; ?>
            <?php if ($help = render($page['help'])): print $help; endif; ?>
            <?php if ($secondary_content = render($page['secondary_content'])): ?>
              <div id="secondary-content">
                <?php print $secondary_content; ?>
              </div>
            <?php endif; ?> 
            
            <!-- Content title begins / Début du titre du contenu -->
            <h1 id="cn-cont" class="cn-invisible"><?php print t('Government of Canada - Drupal CLF3'); ?></h1>
            <!-- Content Title ends / Fin du titre du contenu -->
            
            <!-- cn-content begins / Début du cn-content -->
            <div id="cn-content"> 
              
              <div id="cn-headlines" class="span-3">
                 <?php if ($headlines = render($page['headlines'])): ?>
                   <?php print $headlines; ?>
                 <?php endif; ?>
              </div>

              <div id="cn-video" class="span-3">
                  <?php if ($videos = render($page['videos'])): ?>
                       <?php print $videos; ?>
                  <?php endif; ?>
              </div>

              <div id="cn-connect" class="span-6">
                  <?php if ($connected = render($page['connected'])): ?>
                       <?php print $connected; ?>
                  <?php endif; ?>
              </div>
              
            </div>
            <!-- cn-content ends / Fin du cn-content -->

            <!-- Supplemental content begins / Début du contenu supplémentaire -->
            <aside role="complementary">
              <div id="cn-aside">
                <h2><?php print t('Supplemental Content'); ?></h2>
                
                <!-- Government priorities begin / Début des priorités du gouvernement -->
                <?php if ($priorities = render($page['priorities'])): ?>
                  <?php print $priorities; ?>
                <?php endif; ?>
                <!-- Government priorities end / Fin des priorités du gouvernement -->

                <!-- Minister information begins / Début de l'information du ministre -->
                <?php if ($minister = render($page['minister'])): ?>
                  <?php print $minister; ?>
                <?php endif; ?>
                <!-- Minister information ends / Fin de l'information du ministre -->
                
              </div>
            </aside>
            <div class="clear"></div>
            <!-- Supplemental content ends / Fin du contenu supplémentaire -->

          <!-- GC Web Usability theme ends / Fin du thème de la facilité d'emploi GC -->
        </div>
      </div>
    <!-- Main content ends / Fin du contenu principal -->
    
  </div>
</div>
<!-- Columns end / Fin des colonnes -->    
      
<!-- Footer begins / Début du pied de page -->
<div id="cn-foot"><div id="cn-foot-inner">
	<footer itemscope="itemscope" itemtype="http://schema.org/WPFooter">
		<h2 id="cn-nav"><?php print t('Footer'); ?></h2>
    <!-- GC Web Usability theme begins / Début du thème de la facilité d'emploi GC -->
		<!-- Site footer begins / Début du pied de page du site -->
		<nav role="navigation">
			<div id="cn-sft">
				<h3><?php print t('Site Footer'); ?></h3>
				<div id="cn-sft-inner" itemscope="itemscope" itemtype="http://schema.org/SiteNavigationElement">
					<div id="cn-ft-tctr">
            <!-- Custom Drupal WET: Terms -->
            <?php print $menu_gov_terms_bar; ?>
            <!-- /Custom Drupal WET: Terms -->
					</div>
					<div class="clear"></div>
					<section>
						<div class="span-2">
              <!-- Custom Drupal GOC About Bar -->
              <?php print $menu_gov_about_bar; ?>
              <!-- /Custom Drupal GOC About Bar -->
						</div>
					</section>
					<section>
						<div class="span-2">
              <!-- Custom Drupal WET: News -->
              <?php print $menu_gov_news_bar; ?>
              <!-- /Custom Drupal WET: News -->
						</div>
					</section>
					<section>
						<div class="span-2">
              <!-- Custom Drupal GOC Contact Bar -->
              <?php print $menu_gov_contact_bar; ?>
              <!-- /Custom Drupal GOC Contact Bar -->
						</div>
					</section>
					<section>
						<div class="span-2">
              <!-- Custom Drupal GOC Connected Bar -->
              <?php print $menu_gov_connected_bar; ?>
              <!-- /Custom Drupal GOC Connected Bar -->
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
		<!-- Site footer ends / Fin du pied de page du site -->

  <!-- GC Web Usability theme ends / Fin du thème de la facilité d'emploi GC -->
	</footer>
	</div>
</div>
<!-- Footer ends / Fin du pied de page -->
