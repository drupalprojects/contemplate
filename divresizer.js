(function ($) {

Drupal.contemplate.divResizable = function() {
  $('div.resizable:not(.processed)').each(function() {
    var div = $(this).addClass('processed'), staticOffset = null;

    var grippie = $('div.grippie', $(this).parent())[0];
    grippie.style.marginRight = (grippie.offsetWidth - $(this)[0].offsetWidth) +'px';

    function startDrag(e) {
      staticOffset = div.height() - e.pageY;
      div.css('opacity', 0.25);
      $(document).mousemove(performDrag).mouseup(endDrag);
      return false;
    }

    function performDrag(e) {
      div.height(Math.max(32, staticOffset + e.pageY) + 'px');
      return false;
    }

    function endDrag(e) {
      $(document).unbind("mousemove", performDrag).unbind("mouseup", endDrag);
      div.css('opacity', 1);
    }
  });
}

$(document).ready(Drupal.contemplate.divResizable);

})(jQuery);
