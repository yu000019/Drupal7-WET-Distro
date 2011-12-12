/**
 * @file
 * README file for WebExp Installation Profile.
 */

Web Experience Toolkit Installation Profile
This is the main installation profile for the Web Experience Toolkit in Drupal
Distribution.

CONTENTS
--------

1.  Contributor(s)
2.  Introduction
3.  Developer notes

----
1.  Contributor(s)

There are a wide range of contributors to this project. However for specific concerns
please consider contacting:

Andrew Sinkinson <andrew.sinkinson@statcan.gc.ca> - Manager
William Hearn <william.hearn@statcan.gc.ca> - Initial Development of Code and Distribution
William Roboly <william.roboly@tpsgc-pwgsc.gc.ca> - Architecture and Government Standards
Mike Gifford <mike@openconcept.ca> - Accessibility
Paul Jackson <paul.jackson@tbs-sct.gc.ca> - Web Experience Toolkit
Chad Farquharson <Chad.Farquharson@cra-arc.gc.ca> - WET Usability Themes

For more assistance from the greater Open Source Community and the WET 
Drupal Framework Variant team please post issues at: 
http://tbs-sct.ircan-rican.gc.ca/projects/gcwwwdrupal-git
https://github.com/Web-Experience-Toolkit/Drupal7-WET-Distro


----
2.  Introduction

The install file as mentioned previously only concerns itself with the adding 
of default users, roles, and permissions. Basically the install file deals with 
all automated tasks that do not rely on user feedback and occur early in the 
Drupal bootstrap. While the code itself is very well documented a brief 
explanation is given below.
The main function in the .install file is hook_install where hook is replaced 
by the name of the install profile (which incidentally also matches the name 
given in the name field in the .info file).
Inside this function and in order the following functionality is coded:

a) Adding Default Text Formats
b) Enabling the Default Theme (CLF_Custom)
c) Enabling some standard blocks in the Dashboard Interface
d) Inserting predefined content types into Drupal (Article, Page)
e) Creation of Default RDF Mappings
f) Various variables being set (User Settings)
g) Creation of a Default Taxonomy Group (Tags)
h) Instantiation of various fields using the Field API
i) Creation of default roles and permissions (Administrator, Authenticated, 
  Anonymous)
j) Creation of the expected Menu System based on Governmental standards

It is also important to mention this install profile uses the features module 
and in particular the global_initial_settings custom features module for much of
its multilingual integration. 

----
3.  Developer Notes

When wishing to extend this module please use the sub profiler design as 
specified at Drupal.org. Overtime there will be many iterations and sub profiles
associated with this profile.

To install this installation profile in an alternative method a drush.make file
has also been provided
