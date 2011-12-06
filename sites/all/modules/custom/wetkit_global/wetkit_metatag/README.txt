README.txt
==========

OVERVIEW
==================

A module that extends the MetaTag Module built by Acquia to support the standard Government of Canada Meta Tags.

COMPATIBILITY NOTES
==================
- This Module is designed to work with Drupal 7 + MetaTag Module (7.x-1.0)

INSTALLATION / CONFIGURATION
============================
	1. Please ensure i18n + i18n multilingual variables is properly configured to enable such variables as site_name to be translated to french depending on language context
	2. Enable the MetaTags Module
	3. Enable the WetKit Metatags Module
	4. Depending on your context (see next section) when viewing content certain metatags will appear
	5. Configuration Settings Page Exists at:
		a) /admin/config/search/metatags
		   /admin/config/search/metatags/config/<context>
		   <node edit screen> (allows one last attempt to override)
        6. In html.tpl.php make sure the title attribute is declared as outside scope of metatag module:
           <title><?php print $head_title; ?></title>
	
CONTEXTS
========
	
	Global (MetaTags Exist SiteWide)
	dc:title
	dc:sitename
	dc:url
	
	Global:Frontpage (Metatags Existing just on Front Page)
	dc:title (inheritance)
	dc:url (inheritance)
	
	Node (Metatags Exist on node view)
	dc:title
	dc:description
	dc:url
	date
	dcterms.issued
	dcterms.modified
	author
	
	Taxonomy Term (Metatags Existing on Taxonomy Term View)
	dc:title
	dc:description
	
	User (Metatags Existing on User View)
	dc:type
	dc:title
	dc:image
	
EXTENDING
========
	
    Please note MetaTags can be further extended through custom code base or gui interface using following design patterns:
	Node: Article
	user/1
	taxonomy/term/1
	node/1
	
MORE INFORMATION AND LICENSE
==================
Licensed under the terms of the GNU Lesser General Public License:
    http://www.opensource.org/licenses/lgpl-license.ph

UNIT TEST
==================
- Unit Test have yet to be written

AUTHOR/MAINTAINER OF PLUGIN
===========================
- sylus @ drupal.org <William Hearn>
