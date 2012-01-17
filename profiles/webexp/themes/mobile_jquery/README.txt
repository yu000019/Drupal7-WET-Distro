name         = mobile_jquery 7.x-1.1-beta1
description  = A starting poing in developing your jQuery Mobile theme
  
To use this theme, the following moduels must be installed an enabled:
  
	-views
	-views_ui
	-domain
	-domain_theme

1. Enable the mobile_jquery 7.x-1.1-beta1 theme. /admin/appearance
  
2. Add: include DRUPAL_ROOT . '/sites/all/modules/contrib/domain/settings.inc'; at the end of settings.php file for the site. (adjust the path accordingly so that it finds the settings.inc in the domain (module) directory.
  
3. Set up a subdomain (m.example.com or mobile.example.com)  in Apache.
 
4. In Drupal, create the domain that you just set up in Apache/ /admin/structure/domain
  
5. Ensure that your new mobile domain is NOT the default domain. 
  
6. Click Edit Domain for your mobile subdomain and select the Theme tab. This is where you select the mobile_jquery 7.x-1.1-beta1 as the default theme FOR THE SUBDOMAIN.
  
7. Along with the js code, much of the default CSS is being pulled from http://code.jquery.com (http://code.jquery.com/mobile/1.0a4/jquery.mobile-1.0a4.min.css), as is set in the theme's html.tpl.php file. 
The custom CSS in /themes/mobile_jquery/styles/mobile_jquery.css will override the default - so edit this to make any style changes.
  
*******************
This set-up does not include any device detection.
  
To add this element of functionality to your website by redirecting traffic to your subdomain depending on the user's device, some javascript must be added to your original domain site.
This can be accomplished using: https://github.com/sebarmeli/JS-Redirection-Mobile-Site/
  
