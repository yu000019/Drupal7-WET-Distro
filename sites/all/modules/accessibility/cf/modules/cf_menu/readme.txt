The drupal menu core prevents administrators from seeing the unpublished nodes in the admin menu.
  See: http://drupal.org/node/460408#comment-4367202
  See: http://drupal.org/node/460408#comment-4525794

Errata:
  This requires a patch against drupal core function (drupal-7.x-add_menu_tree_check_access-1.patch).
  To apply this patch, got do the root of your drupal directory and issue the following command
  patch -p1 -i sites/all/modules/cf/modules/cf_menu/drupal-7.x-add_menu_tree_check_access-1.patch
