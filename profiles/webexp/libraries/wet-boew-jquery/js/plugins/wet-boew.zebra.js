/*!
 * Zebra striping v1.1 / Rayage du zèbre v1.1
 * Web Experience Toolkit (WET) / Boîte à outils de l'expérience Web (BOEW)
 * Terms and conditions of use: http://tbs-sct.ircan.gc.ca/projects/gcwwwtemplates/wiki/Terms
 * Conditions régissant l'utilisation : http://tbs-sct.ircan.gc.ca/projects/gcwwwtemplates/wiki/Conditions
 */
 
/** Change Log
 * 2010.07.09 - Dave Schindler - Initial version
 * 2010.07.12 - Dave Schindler - Rewrote striping code to handle nested tables/lists as separate arrays.
 * 2010.07.13 - Dave Schindler - Rewrote striping code to better handle nested tables/lists. Nested lists now alternate which class they start with, but tables don't. Tables now work with or without headers.
 **/
(function($) {
	$.fn.zebra = {
		
		defaults : {
			tableEvenClass : "table-even",
			tableOddClass : "table-odd",
			listEvenClass : "list-even",
			listOddClass : "list-odd"
		},
		
		init : function (){
			$(".zebra").each(function(i) {
				var $this = $(this);
				if ($this.is('table')) {

					var $trs = $this.find('tr').filter(function() {
						return $(this).parent("thead").length === 0;
					});
					
					// note: even/odd's indices start at 0
					$trs.filter(':odd').addClass($.fn.zebra.defaults.tableEvenClass);
					$trs.filter(':even').addClass($.fn.zebra.defaults.tableOddClass);
				} else {
					var $lis = $this.find('li');
					var parity = ($this.parents('li').length + 1) % 2;
					$lis.filter(':odd').addClass(parity === 0 ? $.fn.zebra.defaults.listOddClass : $.fn.zebra.defaults.listEvenClass);
					$lis.filter(':even').addClass(parity === 1 ? $.fn.zebra.defaults.listOddClass : $.fn.zebra.defaults.listEvenClass);
				}
			});
		}
	}
	
	Utils.addCSSSupportFile(Utils.getSupportPath() + "/zebra/style.css");
	
	$(document).ready(function() {
		$.fn.zebra.init();
	});
})(jQuery);
