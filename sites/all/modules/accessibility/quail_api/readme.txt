
CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Dependencies
 * Installation
 * Contributers
 * ToDo
 * Errata



INTRODUCTION
------------

Current Maintainer: Kevin Day <thekevinday@gmail.com>.

Provides an API for the 3rd-party Quail Library to drupal modules.
Quail API is a complete rewrite of parts of the Drupal 6 project called "Accessible Content".


The Quail Library is a 3rd-party PHP project located at: <quail-lib.org> and <code.google.com/p/quail-lib/>.
This 3rd-party libary provides accessiblity validation for common web-accessiblity standards, such as: Section 508 and WCAG 2.
Unlike other web accessiblity scanners, such as WAVE (<wave.webaim.org>), the Quail Library includes context-specific validation.
This validation is a double-edged sword in that it helps catch and identify far more violations to a given standard but at the cost of producing more false positives.


The Accessible Content module in which this module was based off of was written by Kevin Miller.
The mentioned project may be found on drupals website at <drupal.org/project/accessible_content>.
The original feature request for a drupal 7 version of the Accessible Content module may be found on drupals website at <drupal.org/node/1071830>.



DEPENDENCIES
------------
libraries module: <drupal.org/project/libraries>.



INSTALLATION
------------
Add the module to /sites/all/modules/.

Download the 3rd-party Quail Library from <code.google.com/p/quail-lib/>.
Extract the library into /sites/all/libraries/ as a directory called 'quail-lib'.
Therefore the 3rd-party Quail Library should be located at /sites/all/libraries/quail/.

Although this is optional, I strongly suggest applying the patch located at miscellaneous/quail-bug_fixes.patch.
For instructions on how to apply a patch, read <drupal.org/patch>.

To use the functionality provided by this project, another module must be used.
Try the quail_api_node module from <drupal.org/project/1293724> to make use of the provided functionality.


CONTRIBUTERS
------------
Drupal 7 version by Kevin Day.
Original version by Kevin Miller.



TODO
----
(This section will be removed once an official stable version is released.)
- Review code and ensure that all drupal standards are followed where possible.
- Have developers review the functionality and make any changes while the API can be safely changed.
- Look into providing basic usage tutorials and examples, such as views integration.
- Write documentation for this project.


ERRATA
------
The 3rd-party Quail Library has a number of problems that should be fixed to get the best possible usage experience.
The upstream developer has not responded or fixed any of the bugs and as such the patches for these problems will be distributed with this project.

A list of issues have been reported upstream at <code.google.com/p/quail-lib/issues/list>:
- <code.google.com/p/quail-lib/issues/detail?id=29>
- <code.google.com/p/quail-lib/issues/detail?id=30>
- <code.google.com/p/quail-lib/issues/detail?id=31>
- <code.google.com/p/quail-lib/issues/detail?id=32>
- <code.google.com/p/quail-lib/issues/detail?id=33>
- <code.google.com/p/quail-lib/issues/detail?id=34>
- <code.google.com/p/quail-lib/issues/detail?id=35>

There have been more issues that I got tired of reporting them when there is no upstream activity.
