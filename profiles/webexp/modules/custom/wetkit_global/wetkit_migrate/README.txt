/**
 * @file
 * README file for Migrate WetKit.
 */

Migrate WetKit
An plug-in module to the migrate module which extends its capability to importing HTML.

CONTENTS
--------

1.  Contributor(s)
2.  Introduction
3.  Developer notes

----
1.  Contributor(s)

There are a wide range of contributors to this project. However for specific concerns
please consider contacting:

William Hearn <william.hearn@statcan.gc.ca> - Initial Development of Code and Distribution

For more assistance from the greater Open Source Community and the WET 
Drupal Framework Variant team please post issues at: 
http://tbs-sct.ircan-rican.gc.ca/projects/gcwwwdrupal-git
https://github.com/Web-Experience-Toolkit/Drupal7-WET-Distro

----
2.  Introduction

The Migrate Module is an extremely powerful feature and out of the box provides 
migration support for Oracle, MSSQL, Postgresql, CSV, JSON, XML, and MySQL. This
module extends that support for regular HTML files. Future versions of this 
module will also provide support for Web Crawling.

----
3. Developer Notes

This module provides an extended class derived from the Migrate Module. 
Developers wishing to extend the default functionality or possibly contribute
back their code should be aware of proper Inheritance design and encapsulation.
