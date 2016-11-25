
var canvas = null;
var ctx = null;

var map_elements = [];
var to_rotate = [];
var angle = 0.0;

function init()
{
    canvas = document.getElementById('drawcanvas');
    ctx = canvas.getContext("2d");
    
//    CanvasRenderingContext2D.

    ctx.lineCap = "square";
    
    var new_ele;
    
//    map_elements.push(MapFuncs.create_image('images/vertical_floor.jpg',1024/2,768/2, 504, 600));
    map_elements.push(MapFuncs.create_image('images/vertical_floor.jpg',1024/2,768/2, 588, 700));
    
    map_elements.push(MapFuncs.create_elevator(380, 112, 20.0, 0.0));
    map_elements.push(MapFuncs.create_elevator(435, 112, 20.0, 0.0));
    
    new_ele = MapFuncs.create_valve(435, 212, 10.0, 0.0);
    new_ele.autorotate = { speed: 1 };
    to_rotate.push(new_ele);
    map_elements.push(new_ele);
    
    new_ele = MapFuncs.create_valve(435, 312, 10.0, 0.0);
    new_ele.autorotate = { speed: 2 };
    to_rotate.push(new_ele);
    map_elements.push(new_ele);
    
    
    new_ele = MapFuncs.create_camera(635, 212, 15.0, 45);
    new_ele.autorotate = { speed: 1, min: 45, max: 180 };
    to_rotate.push(new_ele);
    map_elements.push(new_ele);

    new_ele = MapFuncs.create_camera(335, 412, 15.0, 270);
    new_ele.autorotate = { speed: 2, min: 270, max: 359 };
    to_rotate.push(new_ele);
    map_elements.push(new_ele);
    
    
    
//    draw_map(ctx, map_elements);
    window.setInterval(timely_draw, 25);
}

var MapFuncs = {
    create_image: function(path, x, y, width, height)
    {
        var img = new Image();
        img.src = path;
        
        return {
            x: x,
            y: y,
            scale: 1.0,
            rotation: 0.0,
            width: width,
            height: height,
            img: img,
            draw: this.draw_image
        };
    },
    create_elevator: function(x, y, scale, rotation)
    {
        return {
            x: x,
            y: y,
            scale: scale || 1.0,
            rotation: rotation || 0.0,
            draw: this.draw_elevator
        };
    },
    
    create_valve: function( x, y, scale, rotation )
    {
        return {
            x: x,
            y: y,
            scale: scale || 1.0,
            rotation: rotation || 0.0,
            draw: this.draw_valve
        };
    },
    
    create_camera: function( x, y, scale, rotation )
    {
        return {
            x: x,
            y: y,
            scale: scale || 1.0,
            rotation: rotation || 0.0,
            draw: this.draw_camera
        };
    },
    
    draw_image: function(ctx)
    {
//        ctx.scale(1,-1);
        ctx.drawImage(this.img, -(this.width/2), -(this.height/2), this.width, this.height);
    },
    
    draw_elevator: function(ctx)
    {
        ctx.strokeStyle = "black";
        ctx.fillStyle = "green";
        ctx.lineWidth = 0.12;

        ctx.beginPath();
            ctx.moveTo(-1.0, -0.5);
            ctx.lineTo(1.0, -0.5);
            ctx.lineTo(1.0, 0.5);
            ctx.lineTo(-1.0, 0.5);
            ctx.lineTo(-1.0, -0.5);
            
        ctx.fill();
        ctx.stroke();
    },
    
    draw_camera: function(ctx)
    {
        ctx.strokeStyle = "black";
        ctx.fillStyle = "red";
        ctx.lineWidth = 0.12;

        ctx.beginPath();
            ctx.moveTo(-1.0, -0.5);
            ctx.lineTo(1.0, -0.5);
            ctx.lineTo(1.0, 0.5);
            ctx.lineTo(-1.0, 0.5);
            ctx.lineTo(-1.0, -0.5);
            
            ctx.moveTo(1.0, 0.25);
            ctx.lineTo(1.5, 0.5);
            ctx.lineTo(1.5, -0.5);
            ctx.lineTo(1.0, -0.25);
            
        ctx.fill();
        ctx.stroke();
    },
    
    draw_valve: function()
    {
        ctx.strokeStyle = "black";
        ctx.fillStyle = "yellow";
        ctx.lineWidth = 0.12;

        ctx.beginPath();
            ctx.arc(0, 0, 1.0, 0, 2*Math.PI, false);
            
            ctx.moveTo(0.0, -1.0);
            ctx.lineTo(0.0, 1.0);
            ctx.moveTo(-1.0, 0.0);
            ctx.lineTo(1.0, 0.0);
            
            
        ctx.fill();
        ctx.stroke();
    }
    
    


};


function draw_map(ctx, arr)
{
    ctx.setTransform(1, 0, 0, 1, 0, 0);
    ctx.clearRect(0, 0, 1024, 768);

    var ele, n, m;
    ctx.setTransform(1, 0, 0, 1, 0.5, 0.5);
    // these lines to modify the full canvas matrix
                ctx.translate(1024/2, 768/2);
                ctx.scale(1.2, 1.2);
//                ctx.rotate(90*Math.PI/180);
                ctx.rotate(angle);
//
                ctx.translate(-1024/2,-768/2);


    for ( n=0, m=arr.length; n<m; n++ )
    {
        ele = arr[n];

        ctx.save();

        ctx.translate(ele.x, ele.y);
        ctx.scale(ele.scale, ele.scale);
        ctx.rotate(ele.rotation*Math.PI/180);

        ele.draw(ctx);

        ctx.restore();
    }
}

function timely_draw()
{
    var n, ne, ele, new_ang;
    
    draw_map(ctx, map_elements);

    for ( n = 0, ne = to_rotate.length; n < ne; n++ )
    {
        ele = to_rotate[n];
        new_ang = ele.rotation + ele.autorotate.speed;
        if ( ele.autorotate.min == null )
        {
            while ( new_ang > 360 ) { new_ang -= 360; }
        }
        else
        {
            if ( new_ang <= ele.autorotate.min )
            {
                new_ang = ele.autorotate.min;
                ele.autorotate.speed = -ele.autorotate.speed;
            }
            else if ( new_ang >= ele.autorotate.max )
            {
                new_ang = ele.autorotate.max;
                ele.autorotate.speed = -ele.autorotate.speed;
            }
        }
        
        ele.rotation = new_ang;
    }
    
    angle += Math.PI/720;
    while ( angle >= (Math.PI*2) )
    {
        angle -= Math.PI*2;
    }
}

