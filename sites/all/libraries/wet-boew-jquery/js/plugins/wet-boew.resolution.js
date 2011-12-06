/*!
 * CSS Grid System v1.3a9a / Système de grille CSS v1.3a9a
 * Web Experience Toolkit (WET) / Boîte à outils de l'expérience Web (BOEW)
 * Terms and conditions of use: http://tbs-sct.ircan.gc.ca/projects/gcwwwtemplates/wiki/Terms
 * Conditions régissant l'utilisation : http://tbs-sct.ircan.gc.ca/projects/gcwwwtemplates/wiki/Conditions
 */

/** 
 * 
 *  ie6Reflow - Reflow bug fix for IE6 for @ref http://michelf.com/weblog/2005/liquid-image/ 
 * 
 * **/
function addLoadEvent(func) {
	var oldonload = window.onload;
	if (typeof window.onload != 'function') {
		window.onload = func;
	} else {
		window.onload = function() {
			if (oldonload) {
				oldonload();
			}
			func();
		}	
	}
}

var ie6Reflow = {
	init: function(){
		if ($.browser.msie && $.browser.version < 8 ) {
			addLoadEvent(screenResolution);
			window.onresize = screenResolution;
			function screenResolution(){
				var pixels = document.documentElement.clientWidth;
				var style = (pixels>=960&&pixels<1200)? $('body').removeClass('gc-elastic'):$('body').addClass('gc-elastic');
			};
		}    
	}
}


/**
 * @plugin Resolution Mapper for Alternating Style Sheets
 * @author Mario Bonito
 * @department Transport Canada / Transports Canada
 * @todo - look to preload stylesheets inorder to reduce choppiness in switch
 */
var currWidth = 960;
var rMapper = {
	adjust : function() {
		var newWidth = $(window).width();
		var frameworkFile = $("#framework-responsive");
		var currHref = frameworkFile.attr('href');
		if (newWidth >= 960 && newWidth < 1200 && (currWidth < 960 || currWidth >= 1200)) {
			if (currWidth >= 1200) {
				frameworkFile.attr('href',currHref.replace("framework-large", "framework-default"));
			} else {
				frameworkFile.attr('href',currHref.replace("framework-small", "framework-default"));
			}
			currWidth = newWidth;
		}
		else if (newWidth >= 1200 && currWidth < 1200) {
			if (currWidth >= 960) {
				frameworkFile.attr('href',currHref.replace("framework-default", "framework-large"));
			} else {
				frameworkFile.attr('href',currHref.replace("framework-small", "framework-large"));
			}
			currWidth = newWidth;
		}
		else if (newWidth < 960 && currWidth >= 960) {
			if (currWidth >= 1200) {
				frameworkFile.attr('href',currHref.replace("framework-large", "framework-small"));
			} else {
				frameworkFile.attr('href',currHref.replace("framework-default", "framework-small"));
			}
			currWidth = newWidth;
		}
	}
};

/**
 * Strict Runtime Binding - Advanced jQuery
 */
rMapper.adjust();
jQuery.event.add(window, "resize", rMapper.adjust);

/**
 *  Runtime 
 */
 
$("document").ready(function(){   ie6Reflow.init(); });