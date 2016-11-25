/** @type HTMLCanvasElement */
var canvas = null;

/** @type CanvasRenderingContext2D */
var ctx = null;


/**
 * @constructor
 * @parameter {int} distance
 * @parameter {int} cycle
 * @parameter {int} green_time
 * @parameter {int} offset
 */
function Junction( distance, cycle, green_time, offset)
{
    this.distance = distance;
    this.cycle = cycle;
    this.green_time = green_time;
    this.offset = offset;
}

Junction.prototype.getFirstCycleStartSecond = function()
{
	return this.offset % this.cycle;
}

/**
 * @constructor
 * @param {String} color the color in css RGB format #RRGGBB
 * @param {int} second the second where the line will start
 * @param {int} distance the distance in meters where the line will start
 * @param {float} speed the km/h, if negative it goes down.
 */
function Line( color, second, distance, speed)
{
    this.color = color;
    this.second = second;
    this.distance = distance;
    this.speed = speed;
}

var show_seconds = 300;
var line_width = 5;
var junction_height = 10;

var junction_list = [
// format: distance_from_junction, cycle time, green_time (inside cycle), offset
  new Junction(   0, 60, 30, 0),
  new Junction( 500, 60, 30, 10),
  new Junction( 400, 60, 30, 40),
  new Junction( 800, 45, 25, 0)
//  
//  new Junction( 700, 60, 30, 75),
//  new Junction( 600, 30, 15, 75),
//  new Junction( 1000, 45, 40, 75)
  
];

var line_list = [
// format:  color, start_second, initial_distance, speed_in_km/h
  new Line( '#0000ff', 0, 0, 55)
//  ,new Line( '#0000ff', 60, 0, 55)
//  ,new Line( '#0000ff', 120, 0, 40)
//  ,new Line( '#00ffff', 45, 0, -45)

];



// initialized later with the values of the canvas
var draw_area = {
    left: 0,
    right: 0,
    top: 0,
    bottom: 0,
    width: 0,
    height: 0
};

var time_to_pixel = 1;

/**
 * @param {Array} jlist
 * @type int
 */
function calculate_total_distance( jlist )
{
    var total_distance = 0;
    
    for ( var n = 0; n < jlist.length; n++ )
    {
        total_distance += jlist[n].distance;
    }
    
    return total_distance;
}

function draw_band( style, from_x, from_y, n_pixels)
{
    ctx.fillStyle = style;

    var end_point = from_x + n_pixels;
    if ( end_point > draw_area.width )
    {
        n_pixels -= end_point - draw_area.width;
    }
    
    if ( from_x < 0 )
    {
        n_pixels += from_x;
        from_x = 0;
    }

    if ( n_pixels >= 1 ) // has something to draw
    {
        ctx.fillRect(from_x + draw_area.left, from_y, n_pixels, junction_height);
    }
    
    return end_point;
}

/**
 * @parameter {int} init_x
 * @parameter {Junction} junction
 */
function draw_junction_times( init_y, junction)
{
    var y_line = draw_area.bottom - init_y - ( junction_height/2 );
    
    var pixcycle =  junction.cycle  / time_to_pixel;
    var pixoffset = junction.offset / time_to_pixel;
    var pixgreen =  junction.green_time / time_to_pixel;
    var pixred =    pixcycle - pixgreen;
    
    var cycle_x = pixoffset;
    while ( cycle_x > 0 ) cycle_x -= pixcycle;
    
    for ( ; cycle_x <= draw_area.width; cycle_x += pixcycle )
    {
        var ep = draw_band("#00ff00",cycle_x, y_line, pixgreen);
        draw_band("#ff0000", ep, y_line, pixred);
    }
}

var total_distance = 0;
var pure_distance_ratio = 0;

function draw_speed_line(color, distance, second, cycle, speed )
{
	var speed_in_ms = speed * 1000 / 3600;
        
	var init_distance = speed < 0 ? total_distance - distance : distance;
	var end_second = second;
	var end_distance = init_distance;
        
        while ( end_distance >= 0 && end_distance <= total_distance 
                && end_second < show_seconds)
        {
            end_distance += speed_in_ms;
            end_second++;
        }
        
        console.log('init end dist:' + init_distance + "," + end_distance);
        
        var start_x = second / time_to_pixel;
        var start_y = init_distance / pure_distance_ratio;
        
        var end_x = end_second / time_to_pixel;
        var end_y = end_distance / pure_distance_ratio;

	var pixcycle = cycle / time_to_pixel;

        if ( start_x < 0 ) start_x = 0;
        else if ( start_x > draw_area.width ) start_x = draw_area.width

        if ( start_y < 0 ) start_y = 0;
        else if ( start_y > draw_area.height ) start_y = draw_area.height
        
        if ( end_x < 0 ) end_x = 0;
        else if ( end_x > draw_area.width ) end_x = draw_area.width

        if ( end_y < 0 ) end_y = 0;
        else if ( end_y > draw_area.height ) end_y = draw_area.height

        ctx.strokeStyle = color;
	
	ctx.beginPath();

        while ( start_x < draw_area.width )
	{	
            ctx.moveTo(draw_area.left + start_x, draw_area.bottom - start_y);
            ctx.lineTo(draw_area.left + end_x, draw_area.bottom - end_y);
	    start_x += pixcycle;
	    end_x += pixcycle;
	}

        ctx.stroke();
}

function init()
{
    canvas = document.getElementById('canvas');

    ctx = canvas.getContext("2d");
    
    draw_area.width = canvas.width - 100;
    draw_area.height = canvas.height - 100;
    draw_area.top = 50;
    draw_area.bottom = draw_area.top + draw_area.height;
    draw_area.left = 50;
    draw_area.right = draw_area.left + draw_area.width;
    
    ctx.strokeStyle = "#ff0000";
    ctx.strokeRect(0, 0, canvas.width, canvas.height);
    
    ctx.fillRect(draw_area.left, draw_area.top, draw_area.width, draw_area.height);

//    ctx.globalAlpha = 0.5;

    time_to_pixel = show_seconds/draw_area.width;

    total_distance = calculate_total_distance( junction_list );
    
//    console.log('Total distance: ' + total_distance);
//    console.log('Show seconds: ' + show_seconds);
    
    pure_distance_ratio = total_distance / draw_area.height;
    var distance_ratio = total_distance / (draw_area.height - junction_height);
    
    var current_distance = junction_height/2;
    
    for ( var n = 0; n < junction_list.length; n++ )
    {
        current_distance += junction_list[n].distance/distance_ratio;
        draw_junction_times( current_distance, junction_list[n]);
    }
    
    
    ctx.lineWidth = line_width;
    ctx.lineCap = "round";
    
    
//    for ( var li = 0; li < line_list.length; li++ )
//    {
//        var line = line_list[li];
//
//
//	NOTE: To add speed lines, put:
//		1- the color '#0000ff' is blue
//		2- 0 = the distance, this depends on the speed is positive or negative
//		3- the point where the cycle starts, this is the function call you see
//		4- the cycle time
//		5- the speed, if negative it goes down.
//
        draw_speed_line('#0000ff', 0, junction_list[0].getFirstCycleStartSecond(),junction_list[0].cycle, 55);

        draw_speed_line('#0000ff', 0, junction_list[3].getFirstCycleStartSecond(),junction_list[3].cycle, -55);
	
        

  //  }
    
}
