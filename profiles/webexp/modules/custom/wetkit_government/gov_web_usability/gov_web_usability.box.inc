<?php
/**
 * @file
 * gov_web_usability.box.inc
 */

/**
 * Implements hook_default_box().
 */
function gov_web_usability_default_box() {
  $export = array();

  $box = new stdClass;
  $box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $box->api_version = 1;
  $box->delta = 'connected_box';
  $box->plugin_key = 'wetkit_box';
  $box->title = 'Stay Connected';
  $box->description = 'Stay Connected Box';
  $box->options = array(
    'en-title' => 'Stay Connected',
    'en-body' => array(
      'value' => '<p><a href="http://twitter.com/#!/"><img alt="Twitter" class="image-actual" src="/profiles/webexp/themes/genesis_clf/socialicons/sl_twitter.png" /> </a> <a href="http://www.youtube.com/"> <img alt="YouTube" class="image-actual" src="/profiles/webexp/themes/genesis_clf/socialicons/sl_youtube.png" /> </a> <a href="/rss.xml"> <img alt="RSS" class="image-actual" src="/profiles/webexp/themes/genesis_clf/socialicons/sl_rss.png" /> </a></p>
',
      'format' => 'full_html',
    ),
    'fr-title' => 'Restez connecté',
    'fr-body' => array(
      'value' => '<p><a href="http://twitter.com/#!/"><img alt="Twitter" class="image-actual" src="/profiles/webexp/themes/genesis_clf/socialicons/sl_twitter.png" /> </a> <a href="http://www.youtube.com/"> <img alt="YouTube" class="image-actual" src="/profiles/webexp/themes/genesis_clf/socialicons/sl_youtube.png" /> </a> <a href="/rss.xml"> <img alt="RSS" class="image-actual" src="/profiles/webexp/themes/genesis_clf/socialicons/sl_rss.png" /> </a></p>
',
      'format' => 'full_html',
    ),
  );
  $export['connected_box'] = $box;

  $box = new stdClass;
  $box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $box->api_version = 1;
  $box->delta = 'minister_box';
  $box->plugin_key = 'wetkit_box';
  $box->title = 'Minister Box';
  $box->description = 'Minister Box';
  $box->options = array(
    'en-title' => '<none>',
    'en-body' => array(
      'value' => '<h3>
	Meet the Minister</h3>
<div class="cn-minister-inner">
	<div class="cn-minister-image">
		<div>
			<img alt="The Honourable minister name" height="149" src="/profiles/webexp/themes/genesis_clf/wetcss/wet-boew-theme-gcwu-fegc-v1.0b5/theme-gcwu-fegc/images/minister.JPG" width="99" /></div>
	</div>
	<div class="cn-minister-info">
		<p>The Honourable<br />
			<strong>minister name</strong></p>
		<ul>
			<li>
				<a href="minister">About the minister</a></li>
			<li>
				<a href="minister/portfolio">His portfolio</a></li>
		</ul>
	</div>
</div>
',
      'format' => 'full_html',
    ),
    'fr-title' => '<none>',
    'fr-body' => array(
      'value' => '<h3>
	Rencontrez le ministre</h3>
<div class="cn-minister-inner">
	<div class="cn-minister-image">
		<div>
			<img alt="Le nom de l&#39;honorable ministre" height="149" src="/profiles/webexp/themes/genesis_clf/wetcss/wet-boew-theme-gcwu-fegc-v1.0b5/theme-gcwu-fegc/images/minister.JPG" width="99" /></div>
	</div>
	<div class="cn-minister-info">
		<p>L&#39;honorable<br />
			<strong>nom du minist&egrave;re</strong></p>
		<ul>
			<li>
				<a href="minister">A propos de la ministre</a></li>
			<li>
				<a href="minister/portfolio">Son portefeuille</a></li>
		</ul>
	</div>
</div>
',
      'format' => 'full_html',
    ),
  );
  $export['minister_box'] = $box;

  $box = new stdClass;
  $box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $box->api_version = 1;
  $box->delta = 'priorities_box';
  $box->plugin_key = 'wetkit_box';
  $box->title = 'Priorities Box';
  $box->description = 'Priorities Box';
  $box->options = array(
    'en-title' => 'Priorities',
    'en-body' => array(
      'value' => '<div id="cn-gc-priorities-inner">
	<ul>
		<li>
			<img alt="Image 1 (220x70)" height="70" src="/profiles/webexp/themes/genesis_clf/wetcss/wet-boew-theme-gcwu-fegc-v1.0b5/theme-gcwu-fegc/images/prio1-eng.png" title="Image 1 (220x70)" width="220" /></li>
		<li>
			<img alt="Image 2 (220x70)" height="70" src="/profiles/webexp/themes/genesis_clf/wetcss/wet-boew-theme-gcwu-fegc-v1.0b5/theme-gcwu-fegc/images/prio2-eng.png" title="Image 2 (220x70)" width="220" /></li>
		<li>
			<img alt="Image 3 (220x70)" height="70" src="/profiles/webexp/themes/genesis_clf/wetcss/wet-boew-theme-gcwu-fegc-v1.0b5/theme-gcwu-fegc/images/prio3-eng.png" title="Image 3 (220x70)" width="220" /></li>
	</ul>
</div>
',
      'format' => 'full_html',
    ),
    'fr-title' => 'Priorités',
    'fr-body' => array(
      'value' => '<div id="cn-gc-priorities-inner">
	<ul>
		<li>
			<img alt="Image 1 (220x70)" height="70" src="/profiles/webexp/themes/genesis_clf/wetcss/wet-boew-theme-gcwu-fegc-v1.0b5/theme-gcwu-fegc/images/prio1-fra.png" title="Image 1 (220x70)" width="220" /></li>
		<li>
			<img alt="Image 2 (220x70)" height="70" src="/profiles/webexp/themes/genesis_clf/wetcss/wet-boew-theme-gcwu-fegc-v1.0b5/theme-gcwu-fegc/images/prio2-fra.png" title="Image 2 (220x70)" width="220" /></li>
		<li>
			<img alt="Image 3 (220x70)" height="70" src="/profiles/webexp/themes/genesis_clf/wetcss/wet-boew-theme-gcwu-fegc-v1.0b5/theme-gcwu-fegc/images/prio3-fra.png" title="Image 3 (220x70)" width="220" /></li>
	</ul>
</div>
',
      'format' => 'full_html',
    ),
  );
  $export['priorities_box'] = $box;

  $box = new stdClass;
  $box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $box->api_version = 1;
  $box->delta = 'videos_box';
  $box->plugin_key = 'wetkit_box';
  $box->title = 'Videos Box';
  $box->description = 'Videos Box';
  $box->options = array(
    'en-title' => 'Videos',
    'en-body' => array(
      'value' => '<div class="background-dark">
	<div class="mediaplayer">
		<img alt="" class="posterimg" src="/profiles/webexp/themes/genesis_clf/images/video.jpg" /></div>
	<p><strong>Web Experience Toolkit Video</strong></p>
	<p>This section is for video related content. Often this is the best place to introduce your department or organization.</p>
</div>
<ul class="list-bullet-none indent-none">
	<li>
		<a href="multimedia/help">Multimedia Help</a></li>
	<li>
		<a href="transcripts">Transcripts and Alternative Formats</a></li>
</ul>
<p><a href="video/gallery">Visit the Video Gallery</a></p>
',
      'format' => 'full_html',
    ),
    'fr-title' => 'Vidéos',
    'fr-body' => array(
      'value' => '<div class="background-dark">
	<div class="mediaplayer">
		<img alt="" class="posterimg" src="/profiles/webexp/themes/genesis_clf/images/video.jpg" /></div>
	<p><strong>Exp&eacute;rience Web Toolkit Vid&eacute;o</strong></p>
	<p>Cette section est pour le contenu vid&eacute;o li&eacute;. Souvent c&#39;est le meilleur endroit pour introduire votre minist&egrave;re ou organisme.</p>
</div>
<ul class="list-bullet-none indent-none">
	<li>
		<a href="multimedia/help">Aide multim&eacute;dia</a></li>
	<li>
		<a href="transcripts">Les transcriptions et les formats de rechange</a></li>
</ul>
<p><a href="video/gallery">Visitez la galerie de vid&eacute;os</a></p>
',
      'format' => 'full_html',
    ),
  );
  $export['videos_box'] = $box;

  return $export;
}
