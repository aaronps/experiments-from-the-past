
var canvas = null;
var ctx = null;

var FOV = 800;

var camera = 
{
    loc: {x: 250, y: 200, z: 0},
    change: {x: 4, y: 0, z: 0},
    max: {x: 200, y: 200, z: 100},
    min: {x: -200, y: 100, z: -200},
    angle: {x: -0.2, y: -0.2, z: 0.0}
};

var dobjects = [];

function init()
{
    canvas = document.getElementById('drawcanvas');
    ctx = canvas.getContext("2d");
//    CanvasRenderingContext2D.
//    ctx.lineCap = "square";

    ctx.setTransform(1, 0, 0, -1, 400.5, 300.5);

    ctx.lineWidth = 1.0;
    ctx.strokeStyle = "black";
    
    dobjects.push(cube_object);
    dobjects.push(cube_object2);
    dobjects.push(cube_object3);
    
    dobjects.push({
        model: road1_model,
        transformed_vertex: [],
        world_vertex: [],
        screen_vertex: [],
        scale: 1,
        world_location: {x: 0, y: 0, z: -20},
        visibility: []
    });
    
    dobjects.push({
        model: road1_model,
        transformed_vertex: [],
        world_vertex: [],
        screen_vertex: [],
        scale: 1,
        world_location: {x: 0, y: 0, z: -440},
        visibility: []
    });
    
    dobjects.push({
        model: road2_model,
        transformed_vertex: [],
        world_vertex: [],
        screen_vertex: [],
        scale: 1,
        world_location: {x: 10, y: 0, z: -20},
        visibility: []
    });
    
    dobjects.push({
        model: road2_model,
        transformed_vertex: [],
        world_vertex: [],
        screen_vertex: [],
        scale: 1,
        world_location: {x: -310, y: 0, z: -20},
        visibility: []
    });
    
    
    timely_change();
//    window.setInterval(timely_change, 150);

//    window.setTimeout(timely_change, 100);
    
}

function timely_change()
{
    ctx.setTransform(1, 0, 0, 1, 0, 0);
    ctx.clearRect(0, 0, 800, 600);
    ctx.setTransform(1, 0, 0, -1, 400.5, 300.5);

//    camera.loc.x += camera.change.x;
//    if ( camera.loc.x > camera.max.x )
//    {
//        camera.loc.x = camera.max.x;
//        camera.change.x = -camera.change.x;
//    }
//    else if ( camera.loc.x < camera.min.x )
//    {
//        camera.loc.x = camera.min.x;
//        camera.change.x = -camera.change.x;
//    }
//
//    camera.loc.y += camera.change.y;
//    if ( camera.loc.y > camera.max.y )
//    {
//        camera.loc.y = camera.max.y;
//        camera.change.y = -camera.change.y;
//    }
//    else if ( camera.loc.y < camera.min.y )
//    {
//        camera.loc.y = camera.min.y;
//        camera.change.y = -camera.change.y;
//    }
//    
//    camera.loc.z += camera.change.z;
//    if ( camera.loc.z > camera.max.z )
//    {
//        camera.loc.z = camera.max.z;
//        camera.change.z = -camera.change.z;
//    }
//    else if ( camera.loc.z < camera.min.z )
//    {
//        camera.loc.z = camera.min.z;
//        camera.change.z = -camera.change.z;
//    }

    var n, m;
    var vpols = [];
    for ( n=0, m=dobjects.length;n<m; n++)
    {
        transform_object(dobjects[n], vpols);
    }
    
    vpols.sort(polsorter);
    
    draw_polygons(vpols);

//    window.setTimeout(timely_change, 5);

}

function polsorter(a,b)
{
    return b.z-a.z;
}

function transform_object(obj, vpols)
{
    var n;
    var n_ver = obj.model.vertex.length;
    obj.transformed_vertex.length = n_ver;
    
    // transform local object
    for ( n=0; n < n_ver; n++ )
    {
        obj.transformed_vertex[n] =
        {
            x: obj.model.vertex[n].x * obj.scale,
            y: obj.model.vertex[n].y * obj.scale,
            z: obj.model.vertex[n].z * obj.scale
        }
    }

    var cv =
    {
        sin: {x: Math.sin(camera.angle.x), y: Math.sin(camera.angle.y), z: Math.sin(camera.angle.z)},
        cos: {x: Math.cos(camera.angle.x), y: Math.cos(camera.angle.y), z: Math.cos(camera.angle.z)}
    };
    
    var curver, x, y, z, xa, za, ya;
    var ox, oy, oz;
    
    obj.world_vertex.length = n_ver;
    // to world
    for ( n=0; n < n_ver; n++ )
    {
        curver = obj.transformed_vertex[n];
        ox = obj.world_location.x + curver.x - camera.loc.x;
        oy = obj.world_location.y + curver.y - camera.loc.y;
        oz = obj.world_location.z + curver.z - camera.loc.z;
        
//        xa = (cv.cos.x * ox) - (cv.sin.x * oz);
//        za = (cv.sin.x * ox) + (cv.cos.x * oz);
//        
//        x  = (cv.cos.y * xa) + (cv.sin.y * oy);
//        
//        ya = (cv.cos.y * oy) - (cv.sin.y * xa);
//        
//        z  = (cv.cos.z * za) - (cv.sin.z * ya);
//        
//        y  = (cv.sin.z * za) + (cv.cos.z * ya);
        
        x = ox;
        y = (cv.cos.x * oy) - (cv.sin.x * oz);
        z = (cv.sin.x * oy) + (cv.cos.x * oz);
        
        x = (cv.cos.y * ox) - (cv.sin.y * z);
        y = y;
        z = (cv.sin.y * ox) + (cv.cos.y * z);
        
        x = (cv.cos.z * x) - (cv.sin.z * y);
        y = (cv.sin.z * ox) + (cv.cos.z * y);
        z = z;
        
        obj.world_vertex[n] =
        {
            x: x,
            y: y,
            z: z
//            x: obj.world_location.x + x - camera.loc.x,
//            y: obj.world_location.y + y - camera.loc.y,
//            z: obj.world_location.z + z - camera.loc.z

//            x: obj.world_location.x + obj.transformed_vertex[n].x - camera.loc.x,
//            y: obj.world_location.y + obj.transformed_vertex[n].y - camera.loc.y,
//            z: obj.world_location.z + obj.transformed_vertex[n].z - camera.loc.z
        }
    }
    
    // calc_visibility
    var pols = obj.model.polygon;
    var wpx = obj.world_vertex;
    var npol = pols.length;
    var p;
    obj.visibility.length = npol;
    
    var ver_0, ver_1, ver_2;
    var U = {x:0,y:0,z:0}, V = {x:0,y:0,z:0}, N = {x:0, y:0, z:0}, L = {x:0,y:0,z:0};
    var NorN = {x:0, y:0, z:0};
    var NorL = {x:0, y:0, z:0};
    var Nlen, Llen;
    var PCenter = {x:0, y:0, z:0};
    var ilu;
    
    var Znormal;
    for (n = 0; n < npol; n++ )
    {
        p = pols[n];
        ver_0 = wpx[p[0]];
        ver_1 = wpx[p[1]];
        ver_2 = wpx[p[2]];
        
        U.x = ver_2.x - ver_1.x;
        U.y = ver_2.y - ver_1.y;
        U.z = ver_2.z - ver_1.z;
        
        V.x = ver_2.x - ver_0.x;
        V.y = ver_2.y - ver_0.y;
        V.z = ver_2.z - ver_0.z;
        
        N.x = U.y * V.z - U.z * V.y;
        N.y = U.z * V.x - U.x * V.z;
        N.z = U.x * V.y - U.y * V.x;
        
        Nlen = Math.sqrt(N.x*N.x + N.y*N.y + N.z * N.z);
        
        N.x /= Nlen;
        N.y /= Nlen;
        N.z /= Nlen;
        
        PCenter.x = (ver_0.x + ver_1.x + ver_2.x) / 3;
        PCenter.y = (ver_0.y + ver_1.y + ver_2.y) / 3;
        PCenter.z = (ver_0.z + ver_1.z + ver_2.z) / 3;
        
        L.x = camera.loc.x ;
        L.y = camera.loc.y ;
        L.z = camera.loc.z - 200;
//        L.x = -PCenter.x;
//        L.y = -PCenter.y;
//        L.z = -PCenter.z;
//        L.x = camera.loc.x - PCenter.x;
//        L.y = camera.loc.y - PCenter.y;
//        L.z = camera.loc.z - PCenter.z;
//        L.x = 500;
//        L.y = 5000;
//        L.z = 5000;
        
        Llen = Math.sqrt(L.x*L.x + L.y*L.y + L.z * L.z);
        
        L.x /= Llen;
        L.y /= Llen;
        L.z /= Llen;
        
        
        ilu = N.x * L.x + N.y * L.y + N.z * L.z;
        
        console.log("ilu is " + ilu);
        
        var r,g,b;
        
        r = Math.round(obj.model.gcolor.r * ilu);
        g = Math.round(obj.model.gcolor.g * ilu);
        b = Math.round(obj.model.gcolor.b * ilu);
        
        console.log("colors are: " + "rgb(" + r + "," + g + "," + b +")");
        
        obj.model.pcolor[n] = "rgb(" + r + "," + g + "," + b +")";
        
        
        
//        Znormal=(wpx[p[1]].x-wpx[p[0]].x)*(wpx[p[0]].y-wpx[p[2]].y)-(wpx[p[1]].y-wpx[p[0]].y)*(wpx[p[0]].x-wpx[p[2]].x)
        Znormal = N.z;
        obj.visibility[n] = Znormal;
        
//        console.log("visi for " + n + " is " + obj.visibility[n]);
    }

    // to screen
    obj.screen_vertex.length = n_ver;
    var sca;
    for ( n=0; n < n_ver; n++ )
    {
        sca = FOV / (FOV+obj.world_vertex[n].z);
        obj.screen_vertex[n] =
        {
            x: obj.world_vertex[n].x * sca,
            y: obj.world_vertex[n].y * sca,
        }
    }
    
    for (n = 0; n < npol; n++ )
    {
        if ( obj.visibility[n] > 0 ) continue;
        p = pols[n];
        vpols.push({
            x1: obj.screen_vertex[p[0]].x, y1: obj.screen_vertex[p[0]].y,
            x2: obj.screen_vertex[p[1]].x, y2: obj.screen_vertex[p[1]].y,
            x3: obj.screen_vertex[p[2]].x, y3: obj.screen_vertex[p[2]].y,
            z: obj.world_vertex[p[0]].z + obj.world_vertex[p[1]].z + obj.world_vertex[p[2]].z,
            fill: obj.model.pcolor[n]
        });
    }
    
}

function draw_object(obj)
{
    var pols = obj.model.polygon;
    var vis = obj.visibility;
    var spx = obj.screen_vertex;
    var npol = pols.length;
    var p;
    for (n = 0; n < npol; n++ )
    {
        if ( vis[n] > 0 ) continue;
        
        p = pols[n];
        
        ctx.beginPath();
            ctx.moveTo(spx[p[0]].x, spx[p[0]].y);
            ctx.lineTo(spx[p[1]].x, spx[p[1]].y);
            ctx.lineTo(spx[p[2]].x, spx[p[2]].y);
            ctx.lineTo(spx[p[0]].x, spx[p[0]].y);
            ctx.fillStyle = obj.model.pcolor[n];
        ctx.fill();
//        ctx.stroke();
    }
}

function draw_polygons(pols) // of screen points
{
    var npol = pols.length;
    var p, n;
    for (n = 0; n < npol; n++ )
    {
        p = pols[n];
        
        ctx.beginPath();
            ctx.moveTo(p.x1, p.y1);
            ctx.lineTo(p.x2, p.y2);
            ctx.lineTo(p.x3, p.y3);
            ctx.lineTo(p.x1, p.y1);
            console.log("set fill: " + p.fill);
            ctx.fillStyle = p.fill;
            ctx.strokeStyle = p.fill;
//            ctx.fillStyle = "rgb(128,128,128)";
//            ctx.strokeStyle = "rgb(255,0,0)";
        ctx.fill();
        ctx.stroke();
    }
}

var road1_model =
{
    vertex:
    [
        {x: -10.0, y: 0, z: 0},
        {x:  10.0, y: 0, z: 0},
        {x:  10.0, y: 0, z: 400},
        {x: -10.0, y: 0, z: 400}
    ],
    polygon:
    [
        [0, 1, 2], // 012
        [2, 3, 0]  // 230
    ],
    pcolor:
    [
        "#808080",
        "#808080"
    ],
    gcolor: {r:0x80, g:0x80, b:0x80}

};

var road2_model =
{
    vertex:
    [
        {x:   0.0, y: 0, z: -20},
        {x: 300.0, y: 0, z: -20},
        {x: 300.0, y: 0, z:   0},
        {x:   0.0, y: 0, z:   0}
    ],
    polygon:
    [
        [0, 1, 2],
        [2, 3, 0]
    ],
    pcolor:
    [
        "#808080",
        "#808080"
    ],
    gcolor: {r:0x80, g:0x80, b:0x80}
};


var cube_model = {
    vertex:
    [
        // base
        {x: -0.5, y: 0, z: -0.5}, // 0
        {x:  0.5, y: 0, z: -0.5}, // 1
        {x:  0.5, y: 0, z:  0.5}, // 2
        {x: -0.5, y: 0, z:  0.5}, // 3
        
        //top
        {x: -0.5, y: 2, z: -0.5}, // 4
        {x:  0.5, y: 2, z: -0.5}, // 5
        {x:  0.5, y: 2, z:  0.5}, // 6
        {x: -0.5, y: 2, z:  0.5}  // 7
    ],
    polygon:
    [
        [ 0, 1, 4 ],  // front
        [ 1, 5, 4 ],  // front
        [ 1, 2, 5 ],  // -> side
        [ 2, 6, 5 ],  // -> side
        [ 2, 3, 6 ],  // back
        [ 3, 7, 6 ],  // back
        [ 3, 0, 7 ],  // <- side
        [ 0, 4, 7 ],  // <- side
        [ 4, 5, 7 ], // top
        [ 5, 6, 7 ] // top
//        [ 3, 2, 0 ], // bottom // 320
//        [ 2, 1, 0 ]  // bottom
    ],
    pcolor:
    [
        "#800000",
        "#800000",
        "#008000",
        "#008000",
        "#000080",
        "#000080",
        "#800080",
        "#800080",
        "#808000",
        "#808000",
        "#008080",
        "#008080"
    ],
    gcolor: {r:0x10, g:0xd0, b:0x10}
}

var cube_object = 
{
    model: cube_model,
    transformed_vertex: [],
    world_vertex: [],
    screen_vertex: [],
    scale: 50,
    world_location: {x: 60, y: 0, z: 20},
    visibility: []
}

var cube_object2 = 
{
    model: cube_model,
    transformed_vertex: [],
    world_vertex: [],
    screen_vertex: [],
    scale: 50,
    world_location: {x: 150, y: 0, z: 20},
    visibility: []
}

var cube_object3 = 
{
    model: cube_model,
    transformed_vertex: [],
    world_vertex: [],
    screen_vertex: [],
    scale: 50,
    world_location: {x: 200, y: 0, z: 200},
    visibility: []
}



