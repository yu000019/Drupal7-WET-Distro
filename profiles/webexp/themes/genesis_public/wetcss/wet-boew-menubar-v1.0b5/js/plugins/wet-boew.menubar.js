 /*
 * Menu bar v1.0b5 / Barre de menu v1.0b5
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
			subMenuHelp : (PE.language === 'eng') ? " (open the submenu with the down arrow key and close with the escape key)" : " (ouvrir le sous-menu avec la touche de la flèche descendante et le fermer avec la touche d'échappement)"
		};
		
		var hoverIntentConfig = {maxSpeed:5, enterTimeout:500, leaveTimeout: 500}
		
		var $scope = $(this);
		var type = {
			megamenu : $scope.hasClass("wet-boew-megamenu"),
			hsubmenu : $scope.hasClass("wet-boew-hsubmenu")
		};
		var $menu = $scope.children("ul");
		var minMenuHeightCSS = $scope.css("min-height");
		var minMenuHeight = parseInt(minMenuHeightCSS.substr(0,minMenuHeightCSS.length-2),10);
		var menuHeight = $menu.height();
		var allClosed = true;
		
		// lets take care of some aria requirements first
		$scope.attr("role","application");
		$menu.attr("role", "menubar");
		if (window.cssEnabled) {
			// disable tabbing for all but the first link
			$menu.find("a").attr("tabindex", "-1").attr("role","menuitem");
			$menu.find("li:first a:first").removeAttr("tabindex");
		}
		
		// for now we are only targetting li's and a's
		$menu.find("a").each(function(index, value) {
			// lets traverse all elements to do our magic
			var $elm = $(this);
			//Is the link from the top level?
			if($elm.parentsUntil(".wet-boew-menu", ".showcase").size() < 1){
				// lets see if this menu items has a siblings ul
				var $childmenu = $elm.closest('li').find('.showcase');

				// lets set the children menus
				if ($childmenu.size() > 0) {
					// we know that this anchor has children
					$elm.attr("aria-haspopup","true").addClass("hassubmenu").wrapInner("<span class=\"expandicon\"><span class=\"sublink\"></span></span>");
					$childmenu.attr("role", "menu").attr("aria-expanded", "false").attr("aria-hidden", "true").find(":has(:header) ul").attr("role", "menu");

					//Add the submenu help
					$elm.append("<span class=\"cn-invisible\">" + dictionary.subMenuHelp + "</span>");

					//bind keyboard action to the link
					$elm.bind('keydown', function(e){
						//Only acting on unmodified arrows
						if (!(e.ctrlKey || e.altKey || e.metaKey)){
							if (e.keyCode === 9) {
								hideAllSubMenus();
							}
							else if (!e.shiftKey) {
								if (e.keyCode === 27) {
									hideAllSubMenus();
									return false;
								} else if (e.keyCode === 40) {
									goToSubMenu (this);
									return false;
								}
							}
						}
					});
					// Escape and tab key handling for IE6/7
					$elm.bind('keypress', function(e){
						//Only acting on unmodified keys
						if (!(e.ctrlKey || e.altKey || e.metaKey)){
							if (e.keyCode === 9) {
								hideAllSubMenus();
							}
							else if (!e.shiftKey) {
								if (e.keyCode === 27) {
									hideAllSubMenus();
									return false;
								}
							}
						}
					});

					// bind the element to a focus and hover behaviour
					$elm.closest('li').bind("mouseenterintent set", hoverIntentConfig, function(){showSubMenu(this);});
					$elm.bind("focus", function(){showSubMenu(this);});
					
					// bind element unhover behaviour
					$elm.closest('li').bind("mouseleaveintent", hoverIntentConfig, function(){hideSubMenu(this);});
				} else {
					$elm.attr("aria-haspopup","false").closest('li').bind("mouseenterintent set", hoverIntentConfig, function(){hideAllSubMenus();});
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
				//Bind keyboard input on submenu links to allow pressing escape to close
				$elm.bind('keydown', function(e){
					//Only acting on unmodified arrows

					if (!(e.ctrlKey || e.altKey || e.metaKey)){
						if (e.keyCode === 9) {
							hideAllSubMenus();
						}
						else if (!e.shiftKey) {
							var allSubMenuLinks = $elm.closest('.showcase-visible').find('a');
							if (e.keyCode === 27) {
								hideSubMenuOnEscape(this);
								return false;
							}else if (e.keyCode == 40){
								var newIndex = allSubMenuLinks.index($elm) + 1;
								if (newIndex < allSubMenuLinks.size()){
									allSubMenuLinks.eq(newIndex).focus();
								}else{
									//Set the focus to the first submenu link
									allSubMenuLinks.eq(0).focus();
								}
								return false;
							}else if (type.hsubmenu) {
								/** Horizontal sub-menu begins **/
								if (e.keyCode == 39){
									var newIndex = allSubMenuLinks.index($elm) + 1;
									if (newIndex < allSubMenuLinks.size()){
										allSubMenuLinks.eq(newIndex).focus();
									}else{
										//Set the focus to the next top link
										$elm.closest('.showcase-visible').closest('li').next('li').find('a:eq(0)').focus();
									}
									return false;
								}
								else if (e.keyCode == 38 || e.keyCode == 37 ){
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
								/** Horizontal sub-menu ends **/
							} else {
								/** Mega menu begins **/
								if (e.keyCode == 38){
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
					}
				});
				// Escape and tab key handling for IE6/7
				$elm.bind('keypress', function(e){
					if (!(e.ctrlKey || e.altKey || e.metaKey)){
						if (e.keyCode === 9) {
							hideAllSubMenus();
						}
						else if (!e.shiftKey) {
							if (e.keyCode === 27) {
								hideAllSubMenus();
								return false;
							}
						}
					}
				});
			}

			// this is lone link in a list
			if ($elm.parent().index() < 1) {
				$elm.parent().addClass("first-in-list");
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
			$node.find(".hassubmenu").addClass("submenuopen");
			allClosed = false;
		}

		function goToSubMenu(topLink){
			if (allClosed) showSubMenu(topLink);
		
			var $node = $(topLink);
			var $subMenu = $node.closest('li').find('.showcase-visible');

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
			$node.find(".hassubmenu").removeClass("submenuopen");
			allClosed = true;
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
			var $showcaseVisible = $(".showcase-visible");
			var $firstMenuLi = $menu.children("li:first");
			var $lastMenuLi = $menu.children("li:last");
			$showcaseVisible.css("margin-top",0);
		
			oldOuterHeight = $outerContainer.outerHeight();
			if ($innerContainer.offset() != null && $outerContainer.offset() != null) {
				newOuterHeight = ($innerContainer.offset().top + $innerContainer.outerHeight()) - $outerContainer.offset().top;
				if (newOuterHeight < minMenuHeight) newOuterHeight = minMenuHeight;
				$outerContainer.css("min-height",newOuterHeight);
				if (/MSIE ((5\.5)|6)/.test(navigator.userAgent)) {
					$outerContainer.css("height",newOuterHeight);
				}
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
		if ($vbrumbs.size() > 0 || !$scope.hasClass('page-match-off')) {
			$bcLinks = $vbrumbs.find('li a');
			if ($bcLinks.size() > 1) {
				$results = $menu.find('li a[href="'+$bcLinks.eq(1).attr('href')+'"]');
				if ($results.size() == 1) {
					$results.addClass('nav-current');
					$navCurrent = $results;
				}
			} else {
				$results = $menu.find('li a[href="'+window.location.pathname+'"]');
				if ($results.size() == 1) $results.addClass('nav-current');
			}
		}
		
		// Handle changes in text size, zoom size, and window size
		ResizeEvents.eventElement.bind('x-initial-sizes x-text-resize x-zoom-resize x-window-resize', function (){
			minMenuHeight = minMenuHeight * $menu.height() / menuHeight;
			menuHeight = $menu.height();
			correctContainerOverflow($menu.parent(), $menu.children().eq(0));
		});
		ResizeEvents.initialise();
	};
       
	/**
	*  commonbar is a centralized ajax bar
	*  TODO: name is reserved for now
	*/
	$.fn.commonbar = function() { };
	
	$(document).ready(function() {
			$(".wet-boew-menubar").each(function() {
					$(this).menubar();
			});
	})
})(jQuery)