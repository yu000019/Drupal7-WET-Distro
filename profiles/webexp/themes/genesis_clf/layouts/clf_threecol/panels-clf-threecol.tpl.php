<?php
/**
 * @file
 * Template for the 1 column panel layout.
 *
 * This template provides a three column 25%-50%-25% panel display layout.
 *
 * Variables:
 * - $id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['left']: Content in the left column.
 *   - $content['middle']: Content in the middle column.
 *   - $content['right']: Content in the right column.
 */
?>
<div class="panel-display panel-3col clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  
  <!-- Main content begins / Début du contenu principal -->
      <div id="cn-centre-col-gap"></div>
      <div id="cn-centre-col">
        <div id="cn-centre-col-inner" style="min-height: 880px; ">
                      
          <!-- GC Web Usability theme begins / Début du thème de la facilité d'emploi GC -->

            <div id="main-content" role="main">
             
                
                <div id="content">
                  <div class="panel-panel panel-col">
    <div class="inside"><?php print $content['middle']; ?></div>
  </div>
              </div>
                
            </div>

          <!-- GC Web Usability theme ends / Fin du thème de la facilité d'emploi GC -->

        </div>
      </div>
    <!-- Main content ends / Fin du contenu principal -->
  
  
  
   <!-- Primary navigation (left column) begins / Début de la navigation principale (colonne gauche) -->
    <div id="cn-left-col-gap"></div>
    <div id="cn-left-col">
      <div id="cn-left-col-inner" style="min-height: 880px; ">
        <h2 id="cn-nav">
          Primary navigation
        </h2>
        <div class="cn-left-col-default">
          <!-- GC Web Usability theme begins / Début du thème de la facilité d'emploi GC -->

          <div class="panel-panel panel-col-first">
    <div class="inside"><?php print $content['left']; ?></div>
  </div>

        <!-- GC Web Usability theme ends / Fin du thème de la facilité d'emploi GC -->
        </div>
      </div>
    </div>
    <div class="clear"></div>
    <!-- Primary navigation (left column) ends / Fin de la navigation principale (colonne gauche) -->
  
  
</div>
