<?php
/**
 * @file
 * Default theme implementation to display the basic html structure of a single
 * Drupal page.
 *
 * Variables:
 * - $css: An array of CSS files for the current page.
 * - $language: (object) The language the site is being displayed in.
 *   $language->language contains its textual representation.
 *   $language->dir contains the language direction. It will either be 'ltr' or 'rtl'.
 * - $rdf_namespaces: All the RDF namespace prefixes used in the HTML document.
 * - $grddl_profile: A GRDDL profile allowing agents to extract the RDF data.
 * - $head_title: A modified version of the page title, for use in the TITLE tag.
 * - $head: Markup for the HEAD section (including meta tags, keyword tags, and
 *   so on).
 * - $styles: Style tags necessary to import all CSS files for the page.
 * - $scripts: Script tags necessary to load the JavaScript files and settings
 *   for the page.
 * - $page_top: Initial markup from any modules that have altered the
 *   page. This variable should always be output first, before all other dynamic
 *   content.
 * - $page: The rendered page content.
 * - $page_bottom: Final closing markup from any modules that have altered the
 *   page. This variable should always be output last, after all other dynamic
 *   content.
 * - $classes String of classes that can be used to style contextually through
 *   CSS.
 * - $in_overlay: TRUE if the page is in the overlay.
 *
 * @see template_preprocess()
 * @see template_preprocess_html()
 * @see template_process()
 */
?><!DOCTYPE html>
<html lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>" <?php print $rdf_namespaces; ?> profile="<?php print $grddl_profile; ?>">
<head>
<?php print $head; ?>
<title><?php print $head_title; ?></title>
<?php print $styles; ?>
<?php print $scripts; ?>
<!--[if lt IE 9]><script src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script><![endif]-->
</head>
<?php // modify the layout by changing the id, see layout.css ?>
<body <?php print $attributes;?> itemscope="itemscope" itemtype="http://schema.org/WebPage"> 
  <?php if ($is_front): ?>
  <div id="cn-body-inner-1col">
  <?php endif; ?>
  <?php if (!$is_front): ?>
  <?php print $layout_desc; ?>
  <?php print $layout_id; ?>
  <?php endif; ?>
  <div id="cn-skip-head">
    <ul id="cn-tphp">
      <li id="cn-sh-link-1"><a href="#cn-cont"><?php print t('Skip to main content'); ?></a></li>
      <li id="cn-sh-link-2"><a href="#cn-nav"><?php print t('Skip to footer'); ?></a></li>
    </ul>
  </div>
  <?php print $page_top; ?>
    <div id="wcms_container" class="<?php print $classes; ?>">
      <?php print $page; ?>
    </div>
    <?php print $page_bottom; ?>
  </div>
  <span id="text-resize" style="position: absolute; left: -9999px; bottom: 0; font-size: 100%; font-family: Courier New, mono; margin: 0; padding: 0;">&nbsp;</span>
</body>
</html>