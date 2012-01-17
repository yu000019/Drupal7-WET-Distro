<div <?php print drupal_attributes($page['attributes_array']['page']); ?>>
    <div class="header" <?php print drupal_attributes($page['attributes_array']['header']); ?>>
      
        
      <?php if ($logo): ?>
        <h1>
         <a href="<?php print $front_page; ?>"><img src="<?php print $logo ?>" alt="<?php print t('Home'); ?>" /> </a> 
        </h1>
      <?php endif; ?>

<a href="../../" title="<?php print t('Back'); ?>" data-rel="back" data-icon="back" data-direction="reverse"><span><?php print t('Back'); ?></span></a>
 
      <?php if ($tabs): ?><?php print render($tabs); ?><?php endif; ?>  
      <?php if ($action_links): ?><div data-role="navbar"><ul class="action-links"><?php print render($action_links); ?></ul></div><?php endif; ?>
		</div> <!-- /#header -->
	<?php if ($is_front): ?>
	 <?php print theme('links__system_main_menu', array('links' => $main_menu, 'attributes' => array('id' => 
'main_menu', 'class' 
=>
array('links', 'inline', 'clearfix')))); ?>


	<?php endif; ?>


<div class="main-content" <?php print drupal_attributes($page['attributes_array']['content']); ?>>

	      <div class="content-primary">

	        <?php print render($page['header']); ?>
					<?php if ($breadcrumb): ?>
			      <div id="breadcrumb"></div>
			    <?php endif; ?>
			    <?php print $messages; ?>	
	        <?php if ($page['highlighted']): ?><div class="highlighted"><?php print render($page['highlighted']); ?></div><?php endif; ?>
	        <?php print render($title_prefix); ?>
	        <?php if ($title): ?><h2 class="title" class="page-title"><?php print $title; ?></h2><?php endif; ?>
	        <?php print render($title_suffix); ?>
	        <?php print render($page['help']); ?>
	        <?php print render($page['content']); ?>
	      </div> <!-- /.content-primary -->
				
				<div class="content-secondary">
				
		   <?php if ($main_menu || $secondary_menu): ?>
		      <div class="navigation">
			<?php if (!$is_front): ?>
		  	    <?php print theme('links__system_main_menu', array('links' => $main_menu, 'attributes' => array('id' => 'main-menu', 'class' => 
array('links', 'inline', 'clearfix')), 'heading' => t('Main Menu'))); ?>
		    <!--    <?php print theme('links__system_secondary_menu', array('links' => $secondary_menu, 'attributes' => array('id' => 'secondary-menu', 'class' => array('links', 'inline', 'clearfix')), 'heading' => t('Secondary Menu'))); ?> -->
			<?php endif; ?>
		      </div> <!-- /#navigation -->
		    <?php endif; ?>
				
	      <?php if ($page['sidebar_first']): ?>
	        <div class="sidebar-first" class="column sidebar">
	          <?php print render($page['sidebar_first']); ?>
	        </div> <!-- /#sidebar-first -->
	      <?php endif; ?>

	      <?php if ($page['sidebar_second']): ?>
	        <div class="sidebar-second" class="column sidebar">
	          <?php print render($page['sidebar_second']); ?>
	        </div> <!-- /#sidebar-second -->
	      <?php endif; ?>
				</div><!-- /.content-secondary -->
					    
    </div>

    <div class="footer" <?php print drupal_attributes($page['attributes_array']['footer']); ?>>        
<!--
<?php if ($site_name): ?>
    <h1 class="site-name"><?php print $site_name; ?></h1> 
        <?php endif; ?>   --->
     
 <?php print render($page['footer']); ?>
    </div> <!-- /#footer -->

</div> <!-- /#page -->
