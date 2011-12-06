; Include Build Kit distro makefile via URL
includes[] = http://drupalcode.org/project/buildkit.git/blob_plain/refs/heads/7.x-2.x:/distro.make

; Add webexp to the full Drupal distro build
projects[webexp][type] = profile
projects[webexp][download][type] = git
projects[webexp][download][url] = git://github.com/sylus/wetkit.git