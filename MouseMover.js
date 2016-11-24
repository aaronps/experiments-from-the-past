
function MouseMover()
{
    this.pagx = ko.observable(0);
    this.pagy = ko.observable(0);
    this.cvx  = ko.observable(0);
    this.cvy  = ko.observable(0);
//    this.canvas = document.getElementById('mouse_mov');
//    this.ctx = this.canvas.getContext('2d');
    
//    this.width = this.canvas.width;
//    this.height = this.canvas.height;
    
//    this.mover_x = ko.observable(Math.round(this.width/2));
//    this.mover_y = ko.observable(Math.round(this.height/2));
    
//    var jcanvas = jQuery(this.canvas);
//    jcanvas.bind('mousedown', {view:this}, function(event){
//        event.data.view.startDrag(event.clientX, event.clientY);
//        return false;
//    });
//    
//    this.canvas_offset = jQuery(this.allcanvas).offset();
    
//    this.draw();
    
}

MouseMover.prototype = {
    startDrag: function( x, y )
    {
        this.drag_x = x;
        this.drag_y = y;
        var jwin = jQuery(window);
        jwin.bind('mouseup.drag', {view:this}, function(event){
            event.data.view.stopDrag(event.pageX, event.pageY);
        });
        jwin.bind('mousemove.drag', {view:this}, function(event){
            var v = event.data.view;
            v.pagx(event.pageX);
            v.pagy(event.pageY);
            
            
            
            var tile_x = Math.floor((x-offset.left) / this.tile_width());
            var tile_y = Math.floor((y-offset.top) / this.tile_height());
            
            var tiles_in_row = Math.floor(this.image.width / this.tile_width());
            
            var real_tile = tile_y * tiles_in_row + tile_x;
            
            this.currentTile(real_tile);

            
            v.cvx()
            
            event.data.view.moveDrag(event.clientX, event.clientY);
        });
    },
    stopDrag: function(x, y)
    {
        if ( ! this.was_dragged )
        {
            // do something
        }
        this.was_dragged = false;
        this.drag_x = null;
        this.drag_y = null;
        var jwin = jQuery(window);
        jwin.unbind('mouseup.drag');
        jwin.unbind('mousemove.drag');
    },
    moveDrag: function( x, y )
    {
        if ( this.drag_x != null && this.drag_y != null )
        {
//            var diff_x = x - this.drag_x;
//            var diff_y = y - this.drag_y;

//            this.all_xpos += diff_x*2;
//            this.all_ypos += diff_y*2;
            
//            var canw = this.allcanvas.width;
//            var canh = this.allcanvas.height;
            
//            var end_x = this.all_xpos + canw;
//            if ( end_x >= this.image.width )
//            {
//                this.all_xpos = this.image.width - canw - 1;
//            }

//            var end_y = this.all_ypos + canh;
//            if ( end_y >= this.image.height ) this.all_ypos = this.image.height- canh-1;
//
//            if ( this.all_xpos < 0 ) this.all_xpos = 0;
//            if ( this.all_ypos < 0 ) this.all_ypos = 0;


            this.drag_x = x;
            this.drag_y = y;

//            this.refreshAllCanvas();
            
            this.was_dragged = true;
        }
    },
    draw: function()
    {
        var ctx = this.ctx;

        ctx.lineWidth=4;

        ctx.beginPath();
            ctx.arc(64, 64, 62, Math.PI*2, 0, true);
            ctx.closePath();
            ctx.strokeStyle="#0000ff";
        ctx.stroke();
        ctx.beginPath();
            ctx.arc(64, 64, 20, Math.PI*2, 0, true);
            ctx.closePath();
            ctx.strokeStyle="#000080";
        ctx.stroke();
        
    }
    
};

var mouse_mover = new MouseMover();

var viewModel = {
    screenX: ko.observable(0),
    screenY: ko.observable(0),
    clientX: ko.observable(0),
    clientY: ko.observable(0),
    pageX: ko.observable(0),
    pageY: ko.observable(0)
};

viewModel.screenXY = ko.dependentObservable(function(){
    return this.screenX() + ',' + this.screenY();
}, viewModel);

viewModel.clientXY = ko.dependentObservable(function(){
    return this.clientX() + ',' + this.clientY();
}, viewModel);

viewModel.pageXY = ko.dependentObservable(function(){
    return this.pageX() + ',' + this.pageY();
}, viewModel);

jQuery(window).mousemove(function(event){
    viewModel.screenX(event.screenX);
    viewModel.screenY(event.screenY);
    viewModel.clientX(event.clientX);
    viewModel.clientY(event.clientY);
    viewModel.pageX(event.pageX);
    viewModel.pageY(event.pageY);
    
    return false;
});

ko.applyBindings(viewModel, document.getElementById('mouseinfo'));


jQuery(window).bind('mousedown', function(event){
    return false;
});

