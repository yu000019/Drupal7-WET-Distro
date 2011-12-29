<?php
/**
 * @file
 * gov_web_usability.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function gov_web_usability_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'connected_block_content';
  $strongarm->value = '<a href="http://twitter.com/#!/">
                    <img class="image-actual" alt="Twitter" src="profiles/webexp/themes/genesis_clf/socialicons/sl_twitter.png">
                  </a> 
                  <a href="http://www.youtube.com/">
                    <img class="image-actual" alt="YouTube" src="profiles/webexp/themes/genesis_clf/socialicons/sl_youtube.png">
                  </a>
                  <a href="/rss.xml">
                    <img class="image-actual" alt="RSS" src="profiles/webexp/themes/genesis_clf/socialicons/sl_rss.png">
                  </a>';
  $export['connected_block_content'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'connected_block_content_fr';
  $strongarm->value = '<a href="http://twitter.com/#!/transport_gc">
                    <img class="image-actual" alt="Twitter" src="profiles/webexp/themes/genesis_clf/socialicons/sl_twitter.png">
                  </a> 
                  <a href="http://www.youtube.com/TransportCanada">
                    <img class="image-actual" alt="YouTube" src="profiles/webexp/themes/genesis_clf/socialicons/sl_youtube.png">
                  </a>
                  <a href="/rss.xml">
                    <img class="image-actual" alt="RSS" src="profiles/webexp/themes/genesis_clf/socialicons/sl_rss.png">
                  </a>';
  $export['connected_block_content_fr'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'minister_block_content';
  $strongarm->value = '<h3>Meet the Minister</h3>
<div class="cn-minister-inner">
	<div class="cn-minister-image">
		<div><img alt="The Honourable minister name" height="149" src="profiles/webexp/themes/genesis_clf/css/theme-gcwu-fegc/images/minister.JPG" width="99" /></div>
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
';
  $export['minister_block_content'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'minister_block_content_fr';
  $strongarm->value = '<h3>Rencontrez le ministre</h3>
<div class="cn-minister-inner">
	<div class="cn-minister-image">
		<div><img alt="Le nom de l\'honorable ministre" height="149" src="profiles/webexp/themes/genesis_clf/css/theme-gcwu-fegc/images/minister.JPG" width="99" /></div>
	</div>
	<div class="cn-minister-info">
		<p>L\'honorable<br />
			<strong>nom du ministère</strong></p>
		<ul>
			<li>
				<a href="minister">A propos de la ministre</a></li>
			<li>
				<a href="minister/portfolio">Son portefeuille</a></li>
		</ul>
	</div>
</div>
';
  $export['minister_block_content_fr'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'priorities_block_content';
  $strongarm->value = '<div id="cn-gc-priorities-inner">
	<ul>
		<li>
			<img alt="Image 1 (220x70)" height="70" src="profiles/webexp/themes/genesis_clf/css/theme-gcwu-fegc/images/priorities-image1.JPG" title="Image 1 (220x70)" width="220" /></li>
		<li>
			<img alt="Image 2 (220x70)" height="70" src="profiles/webexp/themes/genesis_clf/css/theme-gcwu-fegc/images/priorities-image2.JPG" title="Image 2 (220x70)" width="220" /></li>
		<li>
			<img alt="Image 3 (220x70)" height="70" src="profiles/webexp/themes/genesis_clf/css/theme-gcwu-fegc/images/priorities-image3.JPG" title="Image 3 (220x70)" width="220" /></li>
	</ul>
</div>

';
  $export['priorities_block_content'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'priorities_block_content_fr';
  $strongarm->value = '<div id="cn-gc-priorities-inner">
	<ul>
		<li>
			<img alt="Image 1 (220x70)" height="70" src="profiles/webexp/themes/genesis_clf/css/theme-gcwu-fegc/images/priorities-image1.JPG" title="Image 1 (220x70)" width="220" /></li>
		<li>
			<img alt="Image 2 (220x70)" height="70" src="profiles/webexp/themes/genesis_clf/css/theme-gcwu-fegc/images/priorities-image2.JPG" title="Image 2 (220x70)" width="220" /></li>
		<li>
			<img alt="Image 3 (220x70)" height="70" src="profiles/webexp/themes/genesis_clf/css/theme-gcwu-fegc/images/priorities-image3.JPG" title="Image 3 (220x70)" width="220" /></li>
	</ul>
</div>

';
  $export['priorities_block_content_fr'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'videos_block_content';
  $strongarm->value = '<div class="background-dark">
	<div class="mediaplayer">
		<img alt="" class="posterimg" src="profiles/webexp/themes/genesis_clf/images/recruit-recrue-600.png" />
		<ul class="mp-downloadable">
			<li class="mp-mp4 cn-invisible">
				<a href="http://www.statcan.gc.ca/employment-emploi/video/flv/recruit-recrue-eng.flv"><abbr title="Flash Video">FLV</abbr> format</a> (22<abbr title="Megabyte">MB</abbr>)</li>
			<li class="mp-mov">
				<a href="http://www.statcan.gc.ca/employment-emploi/video/mov/recruit-recrue-eng.mov"><abbr title="Apple QuickTime Video">MOV</abbr> format</a> (31<abbr title="Megabyte">MB</abbr>)</li>
			<li class="mp-wmv">
				<a href="http://www.statcan.gc.ca/employment-emploi/video/wmv/recruit-recrue-eng.wmv"><abbr title="Windows Media Video">WMV</abbr> format</a> (36<abbr title="Megabyte">MB</abbr>)</li>
			<li class="mp-tt cn-invisible">
				<a href="profiles/webexp/themes/genesis_clf/xml/recruit-recrue-eng.xml">Timed Text format (captions only)</a></li>
			<li>
				<a href="http://www.statcan.gc.ca/employment-emploi/video/recruit-recrue-trans-eng.html" title="Transcript">Transcript</a></li>
		</ul>
	</div>
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
';
  $export['videos_block_content'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'videos_block_content_fr';
  $strongarm->value = '<div class="background-dark">
	<div class="mediaplayer">
		<img alt="" class="posterimg" src="profiles/webexp/themes/genesis_clf/images/recruit-recrue-600.png" />
		<ul class="mp-downloadable">
			<li class="mp-mp4 cn-invisible">
				<a href="http://www.statcan.gc.ca/employment-emploi/video/flv/recruit-recrue-eng.flv"><abbr title="Flash Video">FLV</abbr> format</a> (22<abbr title="Megabyte">MB</abbr>)</li>
			<li class="mp-mov">
				<a href="http://www.statcan.gc.ca/employment-emploi/video/mov/recruit-recrue-eng.mov"><abbr title="Apple QuickTime Video">MOV</abbr> format</a> (31<abbr title="Megabyte">MB</abbr>)</li>
			<li class="mp-wmv">
				<a href="http://www.statcan.gc.ca/employment-emploi/video/wmv/recruit-recrue-eng.wmv"><abbr title="Windows Media Video">WMV</abbr> format</a> (36<abbr title="Megabyte">MB</abbr>)</li>
			<li class="mp-tt cn-invisible">
				<a href="profiles/webexp/themes/genesis_clf/xml/recruit-recrue-eng.xml">Le format Timed Text (légendes seulement)</a></li>
			<li>
				<a href="http://www.statcan.gc.ca/employment-emploi/video/recruit-recrue-trans-eng.html" title="Transcript — Join a world leader - Statistics Canada">Transcript</a></li>
		</ul>
	</div>
	<p><strong>Expérience Web Toolkit Vidéo</strong></p>
	<p>Cette section est pour le contenu vidéo lié. Souvent c\'est le meilleur endroit pour introduire votre ministère ou organisme.</p>
</div>
<ul class="list-bullet-none indent-none">
	<li>
		<a href="multimedia/help">Aide multimédia</a></li>
	<li>
		<a href="transcripts">Les transcriptions et les formats de rechange</a></li>
</ul>
<p><a href="video/gallery">Visitez la galerie de vidéos</a></p>
';
  $export['videos_block_content_fr'] = $strongarm;

  return $export;
}