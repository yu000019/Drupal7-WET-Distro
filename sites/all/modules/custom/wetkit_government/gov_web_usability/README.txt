/**
 * @file
 * README file for gov_web_usability.
 */

Gov Web Usability
A module which extends Drupal to work better with Web Usability Theme as well as providing
sample content and various other Web Usability Theme features / integrations.

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
Chad Farquharson <Chad.Farquharson@cra-arc.gc.ca> - WET Usability Themes

For more assistance from the greater Open Source Community and the WET 
Drupal Framework Variant team please post issues at: 
http://tbs-sct.ircan-rican.gc.ca/projects/gcwwwdrupal-git
https://github.com/Web-Experience-Toolkit/Drupal7-WET-Distro

----
1.1  Introduction

Currently this module provides the following functionality:

a) Creates the default bilingual menu + menu items expected in the new Web Usability Theme 
standard.
b) Creates the default sample block content in the main front page. 
c) Creates a main view which displays a dynamic array of recent content added to
the site through the Views module.
d) Much of the initial code has been created with Features

----
2.  Developer Notes

All features related to Web Usability Theme should be integrated into this module. Where
possible try to use the Features module to extend the functionality of this 
module.
