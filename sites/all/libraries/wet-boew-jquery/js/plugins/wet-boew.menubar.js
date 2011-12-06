 /*
 * Menu bar v1.0a7 / Barre de menu v1.0a7
 * Web Experience Toolkit (WET) / Boîte à outils de l'expérience Web (BOEW)
 * Terms and conditions of use: http://tbs-sct.ircan.gc.ca/projects/gcwwwtemplates/wiki/Terms
 * Conditions régissant l'utilisation : http://tbs-sct.ircan.gc.ca/projects/gcwwwtemplates/wiki/Conditions
 */

/** load the hoverintent mechanism **/
PE.load("jquery.hoverintent.js");
PE.load("jquery.focus.js");

// this is a simplfied version of the jQuery UI widget-menu navigation system. This will be re-written to use jQuery UI at a later date.
(function($) {
	// main function to execute on navigational element
	$.fn.menubar = function() {

		var dictionary = {
			subMenuHelp : (PE.language === 'eng') ? " (open the submenu with the down arrow key)" : " (ouvrir le sous-menu avec la touche de la flèche descendante)"
		};
		
		var hoverIntentConfig = {maxSpeed:5, enterTimeout:500, leaveTimeout: 500}
		
		var $menu = $(this);
		var menuBorderBottom = $menu.parent().css("border-bottom-width");
		var allClosed = false;
		var type = {
			megamenu : $menu.hasClass("wet-boew-megamenu"),
			tabbedmenu : $menu.hasClass("wet-boew-tabbedmenu")
		};
		
		// Correct the CSS
		$menu.css({"float":"none","position":"absolute"});
		
		// lets take care of some aria requirements first
		$menu.attr("role", "menubar");

		// for now we are only targetting li's and a's
		$menu.find("li, a").each(function(index, value) {
			// lets traverse all elements to do our magic
			var $elm = $(this);

			// lets give all li's a presentation role
			if ($elm.is('li')) $elm.attr("role", "presentation");

			// now we look at the clickable links
			if ($elm.is('a')) {
				// lets give this a role of menuitem
				$elm.attr("role", "menuitem");

				//Is the link from the top level?
				if($elm.parentsUntil(".wet-boew-menu", ".showcase").size() < 1){
					// lets see if this menu items has a siblings ul
					var $childmenu = $elm.closest('li').find('.showcase');

					// lets set the children menus
					if ($childmenu.size() > 0) {
						// we know that this anchor has childern
						$elm.attr("aria-haspopup", "true").addClass("hassubmenu").wrapInner("<span class=\"expandicon\"><span class=\"sublink\"></span></span>");
						$childmenu.attr("role", "menu").attr("aria-expanded", "false").attr("aria-hidden", "true");

						//Add the submenu help
						$elm.append("<span class=\"cn-invisible\">" + dictionary.subMenuHelp + "</span>");

						//bind keyboard action to the link
						$elm.bind('keydown', function(e){
							//Only acting on unmodified arrows
							if (!(e.shiftKey || e.ctrlKey || e.altKey || e.metaKey)){
								if (e.keyCode === 27) {
									hideAllSubMenus();
									return false;
								} else if (e.keyCode === 40) {
									goToSubMenu (this);
									return false;
								}
							}
						});
						// Escape key handling for IE6/7
						$elm.bind('keypress', function(e){
							//Only acting on unmodified arrows
							if (!(e.shiftKey || e.ctrlKey || e.altKey || e.metaKey)){
								if (e.keyCode === 27) {
									hideAllSubMenus();
									return false;
								}
							}
						});

						// bind the element to a focus and hover behaviour
						$elm.closest('li').bind("mouseenterintent set", hoverIntentConfig, function(){showSubMenu(this);});
						$elm.bind("focus", function(){showSubMenu(this);});
						
						// bind element unhover behaviour
						$elm.closest('li').bind("mouseleaveintent", hoverIntentConfig, function(){hideSubMenu(this);});
					} else {
						$elm.closest('li').bind("mouseenterintent set", hoverIntentConfig, function(){hideAllSubMenus();});
						$elm.bind("focus", hideAllSubMenus);
					}
	 
					//bind the side arrows key navigation
					$elm.bind('keydown', function(e){
						//Only acting on unmodified arrows
						if (!(e.shiftKey || e.ctrlKey || e.altKey || e.metaKey)){
							if (e.keyCode === 39) {
								next = $elm.closest('li').next('li').find('a:eq(0)');
								if (next.length > 0) next.focus();
								else $menu.children().eq(0).find('a:eq(0)').focus();
								return false;
							}else if (e.keyCode === 37) {
								if (!$elm.closest('li').prev('li').find('a:eq(0)').focus()) $menu.children().eq(0).focus();
								prev = $elm.closest('li').prev('li').find('a:eq(0)');
								if (prev.length > 0) prev.focus();
								else $menu.children().eq($menu.children().length - 1).find('a:eq(0)').focus();
								return false;
							}
						}
					});
				}else{
					//Disable tabbing of child menu items
					if (window.cssEnabled) {
						$elm.attr("tabindex", -1);
					}

					//Bind keyboard input on submenu links to allow pressing escape to close
					$elm.bind('keydown', function(e){
						//Only acting on unmodified arrows
						if (!(e.shiftKey || e.ctrlKey || e.altKey || e.metaKey)){
							if (type.tabbedmenu) {
								/** Tabbed menu begins **/
								var allSubMenuLinks = $elm.closest('.showcase-visible').find('a');
								
								if (e.keyCode === 27) {
									hideSubMenuOnEscape(this);
									return false;
								}else if (e.keyCode == 39){
									var newIndex = allSubMenuLinks.index($elm) + 1;
									if (newIndex < allSubMenuLinks.size()){
										allSubMenuLinks.eq(newIndex).focus();
									}else{
										//Set the focus to the next top link
										$elm.closest('.showcase-visible').closest('li').next('li').find('a:eq(0)').focus();
									}
									return false;
								}else if (e.keyCode == 40){
									var newIndex = allSubMenuLinks.index($elm) + 1;
									if (newIndex < allSubMenuLinks.size()){
										allSubMenuLinks.eq(newIndex).focus();
									}else{
										//Set the focus to the first link in the submenu
										allSubMenuLinks.eq(0).focus();
									}
									return false;
								}else if (e.keyCode == 38 || e.keyCode == 37 ){
									var newIndex = allSubMenuLinks.index($elm) - 1
									if (newIndex >= 0){
										allSubMenuLinks.eq(newIndex).focus();
										return false;
									}else{
										//Set the focus on the parent
										$elm.closest('.showcase-visible').closest('li').find('a:eq(0)').focus();
										return false;
									}
								}
								/** Tabbed menu ends **/
							} else {
								/** Mega menu begins **/
								if (e.keyCode === 27) {
									hideSubMenuOnEscape(this);
									return false;
								}else if (e.keyCode == 40){
									var allSubMenuLinks = $elm.closest('.showcase-visible').find('a');
									var newIndex = allSubMenuLinks.index($elm) + 1;
									if (newIndex < allSubMenuLinks.size()){
										allSubMenuLinks.eq(newIndex).focus();
									}else{
										//Set the focus to the first submenu link
										allSubMenuLinks.eq(0).focus();
									}
									return false;
								}else if (e.keyCode == 38){
									var allSubMenuLinks = $elm.closest('.showcase-visible').find('a');
									var newIndex = allSubMenuLinks.index($elm) - 1
									if (newIndex >= 0){
										allSubMenuLinks.eq(newIndex).focus();
										return false;
									}else{
										//Set the focus on the parent
										$elm.closest('.showcase-visible').closest('li').find('a:eq(0)').focus();
										return false;
									}
								}else if (e.keyCode == 37 || e.keyCode == 39){
									var allSubMenuLinks = $elm.closest('.showcase-visible').find('a');
									var headerLinks = allSubMenuLinks.filter(':header a');
									var index = allSubMenuLinks.index($elm);
									
									//Get the closest header to the link
									var parentHeader = -1;
									headerLinks.each(function(){
										if (allSubMenuLinks.index($(this)) <= index && parentHeader < headerLinks.index($(this))){
											parentHeader = headerLinks.index($(this));
										}
									})
									
									if (e.keyCode == 37){
										if (parentHeader > 0){
											headerLinks.eq(--parentHeader).focus();
										}else{
											//Set the focus to the next top link
											$elm.closest('.showcase-visible').closest('li').prev('li').find('a:eq(0)').focus();
										}
									}else if (e.keyCode == 39){
										if (parentHeader <  headerLinks.size() - 1){
											headerLinks.eq(++parentHeader).focus();
										}else{
											//Set the focus to the next top link
											$elm.closest('.showcase-visible').closest('li').next('li').find('a:eq(0)').focus();
										}
									}
									return false;
								}
								/** Mega menu ends **/
							}
						}
					});
					// Escape key handling for IE6/7
					$elm.bind('keypress', function(e){
						if (e.keyCode === 27) {
							hideSubMenuOnEscape(this);
							return false;
						}
					});
				}

				// this is lone link in a list
				if ($elm.parent().index() < 1) {
					$elm.parent().addClass("first-in-list");
				}
			}
		})

		// a show menu function to bind to the aria-haspopup up element
		function showSubMenu(topLink) {
			// locally scoped node for performance sake
			$node = $(topLink);

			// now lets cleas all menu's
			hideAllSubMenus();

			var $showcase = $node.closest('li').find('.showcase');
			// tweak aria
			$showcase.attr("aria-expanded", "true");
			$showcase.attr("aria-hidden", "false");
	
			// now show
			$showcase.toggleClass('showcase showcase-visible');
			if (type.tabbedmenu) {
				$menu.parent().css("border-bottom-width","0px");
				correctContainerOverflow($menu.parent(), $showcase.children());
			}
			$node.find(".hassubmenu").addClass("submenuopen");
			allClosed = false;

			if (type.tabbedmenu) {
				/** Tabbed menu begins **/
				if ( /MSIE 7/.test(navigator.userAgent) ) {
					var bottom = $showcase.outerHeight() + ($showcase.offset().top - $("#cn-centre-col-inner").offset().top);
					if ($("#cn-centre-col-inner").height() < bottom) {
						$("#cn-centre-col-inner").css("min-height", bottom);
					}
				} else if (/MSIE ((5\.5)|6)/.test(navigator.userAgent)) {
					var bottom = $showcase.outerHeight() + ($showcase.offset().top - $("#cn-centre-col-inner").offset().top);
					if ($("#cn-centre-col-inner").innerHeight() < bottom) {
						$("#cn-centre-col-inner").css("height", bottom);
					}
				}
				/** Tabbed menu ends **/
			} else {
				/** Mega menu begins **/
				setTimeout(function(){
					if ( /MSIE 7/.test(navigator.userAgent) ) {
						var bottom = $showcase.outerHeight() + ($showcase.offset().top - $("#cn-centre-col-inner").offset().top) ;
						if ($("#cn-centre-col-inner").height() < bottom) $("#cn-centre-col-inner").css("min-height", bottom);
					} else if (/MSIE ((5\.5)|6)/.test(navigator.userAgent)) {
						var bottom = $showcase.outerHeight() + ($showcase.offset().top - $("#cn-centre-col-inner").offset().top) ;
						if ($("#cn-centre-col-inner").innerHeight() < bottom) $("#cn-centre-col-inner").css("height", bottom);
					}
				},10);
				/** Mega menu ends **/
			}
		}

		function goToSubMenu(topLink){
			if (allClosed) showSubMenu(topLink);
		
			var $node = $(topLink);
			var $subMenu = $node.closest('li').find('.showcase-visible');

			//Re-enable tabbing
			$subMenu.find('a').attr('tabindex', '0');
			// setTimeout so that JAWS doesn't ignore the .focus() on a usually non-focusable element.
			setTimeout(function(){$subMenu.find('a[href]:first').focus();},0);
		}

		// a hide menu function to bind to the aria-haspopup up element
		function hideSubMenu(topLink) {
			// locally scoped node for performance sake
			var $node = $(topLink);
			var $showcase = $node.closest('li').find('.showcase-visible');
			
			$showcase.attr("aria-expanded", "false");
			$showcase.attr("aria-hidden", "true");
			$showcase.toggleClass('showcase showcase-visible');
			if (type.tabbedmenu) {
				correctContainerOverflow($menu.parent(), $node.closest('li'));
				$menu.parent().css("border-bottom-width",menuBorderBottom); 
			}
			$node.find(".hassubmenu").removeClass("submenuopen");
			// remove the tabindex to increase usability
			$showcase.find('a').attr("tabindex", -1);

			if (type.tabbedmenu) {
				/** Tabbed menu begins **/
				setTimeout(function(){
					if ($menu.find('.showcase-visible').size() < 1){
						if ( /MSIE 7/.test(navigator.userAgent) ){
							$("#cn-centre-col-inner").css("min-height", "");
							$("#cn-centre-col-inner").css("margin-top", "");
						}
						else if (/MSIE ((5\.5)|6)/.test(navigator.userAgent)){
							$("#cn-centre-col-inner").css("height", "");
							$("#cn-centre-col-inner").css("margin-top", "");
						}
					}
				},100);
				/** Tabbed menu ends **/
			} else {
				/** Mega menu begins **/
				if ($menu.find('.showcase-visible').size() < 1){
					if ( /MSIE 7/.test(navigator.userAgent) ) $("#cn-centre-col-inner").css("min-height", "");
					else if (/MSIE ((5\.5)|6)/.test(navigator.userAgent)) $("#cn-centre-col-inner").css("height", "");
				}
				/** Mega menu begins **/
			}
		}

		function hideSubMenuOnEscape(link){
			var topLink = $(link).closest('.showcase-visible').closest('li').find('a:eq(0)');
			topLink.focus();
			setTimeout(function(){
				hideSubMenu(topLink);
				allClosed = true;
			}, 100);
		}
	 
		function hideAllSubMenus(){
			$menu.find(".showcase-visible").each(function(){
				$(this).closest('li').trigger('mouseleaveintent');
			});
			allClosed = true;
		}
		
		function correctContainerOverflow($outerContainer, $innerContainer) {
			oldOuterHeight = $outerContainer.outerHeight();
			topBorder = oldOuterHeight - $outerContainer.innerHeight();
			newOuterHeight = ($innerContainer.offset().top + $innerContainer.outerHeight()) - $outerContainer.offset().top;
			$outerContainer.css("height",newOuterHeight - topBorder);
			if (/MSIE ((5\.5)|6|7)/.test(navigator.userAgent)) {
				if (newOuterHeight >= oldOuterHeight) $("#cn-cols-inner").css("top",-1);
				else $("#cn-cols-inner").css("top",0);
			}
		}
				   
		// auto-magic current page finding
		/**
		*  Developer's notes: This approach relies on a stable breadcrumb system.
		*     The idea is to use the breadcrumb as a way to activate the appropiate menu item and inject the nav-current class in that element
		*     if there is no breadcrumb then it is safe to assume this is a home page and the default no-links shown behaviour is triggered
		*     @class-switch : page-match-off - this will tell the menu not to try to match menu location with page location
		*/
		var $vbrumbs = $('#cn-bc, #cn-bcrumb');
		var $results, $navCurrent;
		if ($vbrumbs.size() > 0 || !$menu.hasClass('page-match-off')) {
			$bcLinks = $vbrumbs.find('li a');
			if ($bcLinks.size() > 1) {
				$results = $menu.find('li a[href="'+$bcLinks.eq(1).attr('href')+'"]');
				if ($results.size() == 1) {
					$results.addClass('nav-current');
					$navCurrent = $results;
					if (type.tabbedmenu) {
						if ($bcLinks.size() > 2) {
							$results = $menu.find('li a[href="'+$bcLinks.eq(2).attr('href')+'"]');
							if ($results.size() == 1) $results.addClass('nav-current-sub');
						} else {
							$results = $menu.find('li a[href="'+window.location.pathname+'"]');
							if ($results.size() == 1) $results.addClass('nav-current-sub');
						}
					}
				}
			} else {
				$results = $menu.find('li a[href="'+window.location.pathname+'"]');
				if ($results.size() == 1) $results.addClass('nav-current');
			}
		}
		
		if ($navCurrent == null) $navCurrent = $menu.find(".nav-current");
		if ($navCurrent.length > 0) {
			// Open the tab for the current page
			if (type.tabbedmenu && $navCurrent.hasClass("hassubmenu")) showSubMenu($navCurrent.closest("li"));
		
			// Handle hover/focus for the menu bar	
			$menu.hover(
				function() {if ($navCurrent.hasClass("nav-current")) $navCurrent.toggleClass("nav-current nav-current-off");},
				function() {if ($navCurrent.hasClass("nav-current-off")) $navCurrent.toggleClass("nav-current nav-current-off");}
			).focusin(
				function() {if ($navCurrent.hasClass("nav-current")) $navCurrent.toggleClass("nav-current nav-current-off");}
			).focusout(
				function() {
					if ($navCurrent.hasClass("nav-current-off")) $navCurrent.toggleClass("nav-current nav-current-off");
					if (type.tabbedmenu) {
						showSubMenu($(".nav-current").closest("li"));
					} else {
						hideAllSubMenus();
					}
				}
			).bind("mouseleaveintent", hoverIntentConfig, function(){if (type.tabbedmenu && $navCurrent.length > 0 && $navCurrent.hasClass("nav-current") && $navCurrent.hasClass("hassubmenu")) showSubMenu($(".nav-current").closest("li"));});
		} else {
			$menu.focusout(function() {hideAllSubMenus();});
		}
		
		// Handle changes in text size, zoom size, and window size
		ResizeEvents.eventElement.bind('x-initial-sizes x-text-resize x-zoom-resize x-window-resize', function (){
			if (type.tabbedmenu && $(".showcase-visible")) {
				correctContainerOverflow($menu.parent(), $(".showcase-visible").children());
			} else {
				correctContainerOverflow($menu.parent(), $menu.children().eq(0));
			}
		});
		ResizeEvents.initialise();
	};
       
	/**
	*  commonbar is a centralized ajax bar
	*  TODO: name is reserved for now
	*/
	$.fn.commonbar = function() { };
	
	$(document).ready(function() {
			$(".wet-boew-menubar .wet-boew-menu").each(function() {
					$(this).menubar();
			});
	})
})(jQuery)