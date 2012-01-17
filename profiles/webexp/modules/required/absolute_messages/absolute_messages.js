Drupal.absolute_messages = Drupal.absolute_messages || {};

(function ($) {

  Drupal.absolute_messages.checkIcons = function(){
    var visible_messages = $(".absolute-messages-message:visible").not(".absolute-messages-dismiss-all").size();
    // If no messages are displayed, remove "Dismiss all" icon
    // and show "Show dismissed messages" icon.
    if (visible_messages == 0) {
      $("div.absolute-messages-dismiss-all").hide();
      $("#absolute-messages-show").show();
    };
    // Show "Dismiss all messages" icon if number of visible
    // messages is higher that configured in module settings.
    if (Drupal.absolute_messages.dismiss_all_count && visible_messages >= Drupal.absolute_messages.dismiss_all_count) {
      $("div.absolute-messages-dismiss-all").show();
    }
  };

  $(document).ready(function(){

    // Move messages from closure to right after opening of body tag.
    $("body").prepend($("#absolute-messages-messages"));

    // Make sure that we do not display more message lines than maximum
    // number of message lines defined in module settings (if defined).
    if (Drupal.absolute_messages.max_lines) {
      // Fetch current height of single message line defined in CSS.
      var line_height = parseInt($(".absolute-messages-message .content").css("line-height"));
      var current_height;
      // display-none elements do not have height, so we need to display
      // them first  (although hidden) to be able to get their height.
      // Also, force-set height to avoid "jumpy" animation.
      $(".absolute-messages-message").css({'visibility':'hidden', 'display':'block'})
                                     .css("height", $(this).height());
      $.each($(".absolute-messages-message .content"), function(){
        current_height = $(this).height();
        // Update max-height property for each line if needed.
        if (current_height > line_height * Drupal.absolute_messages.max_lines) {
          $(this).css("max-height", line_height * Drupal.absolute_messages.max_lines)
                 .addClass("collapsed")
                 .parents(".absolute-messages-message")
                 .addClass("collapsible")
                 .attr("title", "Click to see the whole message");
        }
      });
      // And hide them again so we still can manage them using jQuery sliding.
      $(".absolute-messages-message").removeAttr('style');
    }

    // Show all messages.
    $(".absolute-messages-message").not(".absolute-messages-dismiss-all").slideDown(600);
    Drupal.absolute_messages.checkIcons();

    // Dismiss single message.
    $("a.absolute-messages-dismiss").click(function(){
      $(this).parents(".absolute-messages-message").slideUp(300, function(){
        Drupal.absolute_messages.checkIcons();
      });
    });

    // Dismiss all messages.
    $("a.absolute-messages-dismiss-all").click(function(){
      $(".absolute-messages-message").slideUp(300, function(){
        Drupal.absolute_messages.checkIcons();
      });
    });

    // Show cursor as pointer when hovering over 'show dismissed messages' icon.
    // This is mainly for IE, as it does not want to change the cursor through CSS
    // over the whole element when containing element has width and height of 0px.
    $("#absolute-messages-show").hover(function(){
      $(this).css("cursor", "pointer");
    }, function(){
      $(this).css("cursor", "auto");
    });

    // Show all previously dismissed messages after clicking on 'show dismissed' icon.
    $("#absolute-messages-show").click(function(){
      $(this).hide();
      $(".absolute-messages-message").not(".absolute-messages-dismiss-all").slideDown(300, function(){
        Drupal.absolute_messages.checkIcons();
      });
    });

    // Automatic dismiss messages after specified time.
    var timeOuts = new Array();
    $.each(Drupal.absolute_messages.dismiss, function(index, value){
      if (value == 1) {
        timeOuts[index] = setTimeout(function(){
          $(".absolute-messages-"+index).slideUp(600, function(){
            Drupal.absolute_messages.checkIcons();
          });
        }, Drupal.absolute_messages.dismiss_time[index] * 1000);
      }
    });

    // Clear all timeouts on mouseover and set them again on mouseout.
    $(".absolute-messages-message").hover(function(){
      $.each(Drupal.absolute_messages.dismiss, function(index, value){
        clearTimeout(timeOuts[index]);
      });
    }, function(){
      $.each(Drupal.absolute_messages.dismiss, function(index, value){
        if (value == 1) {
          timeOuts[index] = setTimeout(function(){
            $(".absolute-messages-"+index).slideUp(600, function(){
              Drupal.absolute_messages.checkIcons();
            });
          }, Drupal.absolute_messages.dismiss_time[index] * 1000);
        }
      });
    });

    // Expand/collapse long messages.
    $(".absolute-messages-message.collapsible").click(function(){
      if ($(this).find(".content").hasClass("collapsed")) {
        $(this).find(".content")
               .css("max-height", "")
               .removeClass("collapsed")
               .addClass("expanded");
      } else {
        $(this).find(".content")
               .css("max-height", line_height * Drupal.absolute_messages.max_lines)
               .removeClass("expanded")
               .addClass("collapsed");
      }
    });

  });

})(jQuery);
