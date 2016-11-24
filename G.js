var G = (function(){
/**
 *  VECTOR
 */
    function Vector(x, y, z)
    {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    Vector.MidPoint = function(list)
    {
        var new_vect = new Vector(list[0].x, list[0].y, list[0].z);
        var n = list.length;
        while ( --n )
        {
            new_vect.x += list[n].x;
            new_vect.y += list[n].y;
            new_vect.z += list[n].z;
        }
        
        new_vect.x /= list.length;
        new_vect.y /= list.length;
        new_vect.z /= list.length;
        return new_vect;
    };

    Vector.prototype.Clone = function()
    {
        return new Vector(this.x, this.y, this.z);
    };

    Vector.prototype.sub = function(other)
    {
        this.x -= other.x;
        this.y -= other.y;
        this.z -= other.z;
    };

    Vector.prototype.add = function(other)
    {
        this.x += other.x;
        this.y += other.y;
        this.z += other.z;
    };
    
    Vector.prototype.div = function(value)
    {
        this.x /= value;
        this.y /= value;
        this.z /= value;
    };
    
    Vector.CrossProduct = function(v1, v2)
    {
        var n = new Vector(0,0,0);
        n.x =   (v1.y*v2.z) - (v1.z*v2.y);
        n.y =   (v1.x*v2.z) - (v1.z*v2.x);
        n.z =   (v1.x*v2.y) - (v1.y*v2.x);
        return n;
    };

    Vector.prototype.normalize = function()
    {
        var nx = this.x * this.x;
        var ny = this.y * this.y;
        var nz = this.z * this.z;
        
        var av = Math.sqrt(nx+ny+nz);
        
        this.x /= av;
        this.y /= av;
        this.z /= av;
    };

    Vector.DotProduct = function(v1,v2)
    {
        return (v1.x*v2.x) + (v1.y*v2.y) + (v1.z*v2.z);
    };

    Vector.prototype.toString = function()
    {
        return "Vector["+this.x+","+this.y+","+this.z+"]";
    };

/**
 *  GeometricData
 */
    function GeometricData(vertex, faces, normals)
    {
        this.vertex = vertex || [];
        this.faces = faces || [];
        this.face_centers = [];
        this.normals = normals || [];
        
        this.recalculateCenters();
        this.recalculateNormals();
    }

    GeometricData.prototype.recalculateCenters = function()
    {
        var num_vertex = this.vertex.length;
        var centers = this.face_centers;
        var faces = this.faces;
        var face, center;
        for ( var f=0, max_f = this.faces.length; f < max_f; ++f)
        {
            face = faces[f];
            center = this.vertex[face[0]].Clone();
            for (var v = face.length; --v; )
            {
                center.add(this.vertex[face[v]]);
            }
            
            center.div(face.length);
            centers[f] = center;
        }
    }

// XXX if more than 3 vertex, it could be possible that it is not flat, so
// the "normal" would be wrong.
    GeometricData.prototype.recalculateNormals = function()
    {
        var num_vertex = this.vertex.length;

        var max_f = this.faces.length;
        for (var f = 0; f < max_f; ++f )
        {
            var face = this.faces[f];
            if ( face.length > 2 )
            {
                var p1 = this.vertex[face[0]];
                var p2 = this.vertex[face[1]];
                var p3 = this.vertex[face[2]];

                var v1 = p2.Clone();
                v1.sub(p1);
                var v2 = p3.Clone();
                v2.sub(p1);
                var normal = Vector.CrossProduct(v1, v2);
                normal.normalize();
                this.normals[f] = normal;
                /*
                // xx from this point is debug
                console.log("Normal is: " + normal);
                var mp = Vector.MidPoint([p1,p2,p3]);

                normal.x *= 10;
                normal.y *= 10;
                normal.z *= 10;
                
                var end_point = mp.Clone();
                end_point.add(normal);
                
                this.vertex.push(mp);
                this.vertex.push(end_point);
                var f1 = num_vertex++;
                var f2 = num_vertex++;
                
                this.faces.push([f1, f2, f1, f2]);
                */
            }
        }
    };

    GeometricData.prototype.movePoints = function(x,y,z)
    {
        var v = this.vertex;
        for (var n = v.length; n-- ; )
        {
            var p = v[n];
            p.x += x;
            p.y += y;
            p.z += z;
        }
    };

/**
 *  SHAPES
 */
    function createRectangle(x,y,z)
    {
        var hx = x/2;
        var hy = y/2;
        var hz = z/2;
        
        var ver = [
            new Vector( hx, hy, -hz),
            new Vector( hx, hy,  hz),
            new Vector(-hx, hy,  hz),
            new Vector(-hx, hy, -hz),
            new Vector( hx,-hy, -hz),
            new Vector( hx,-hy, hz),
            new Vector(-hx,-hy, hz),
            new Vector(-hx,-hy,-hz),
        ];
        
        var fac = [
            [0, 1, 2, 3], // top cover
            [4, 7, 6, 5], // bottom
            [4, 0, 1, 5], // right side
            [4, 7, 3, 0], // back side
            [6, 2, 3, 7], // left side
            [1, 2, 6, 5], // that front side
        ];
        
        var res = new GeometricData( ver, fac);
        //res.recalculateNormals();
        return res;
    }

/**
 *  SceneElement
 */
    function SceneElement(data, location, rotation)
    {
        this.data = data;
        this.location = location || new Vector(0.0, 0.0, 0.0);
        this.rotation = rotation || [ 0.0, 0.0, 0.0];
        
        this.sin_rotation = [ 0.0, 0.0, 0.0 ];
        this.cos_rotation = [ 0.0, 0.0, 0.0 ];
        
        //this.rotated_vertex = [];
        this.world_vertex = [];
        this.camera_vertex = [];
        this.screen_pixel = [];
        
        this.visible_faces = [];
        this.num_visible_faces = 0;
    }

/**
 *  Scene
 */
    function Scene()
    {
        this.elements = [];
        this.num_elements = 0;
        
        this.camera = {
            loc: new Vector(0.0, 0.0, 0.0),
            angle: [0.0, 0.0, 0.0],
            normal: new Vector(0.0, 0.0, -1.0)
        };
    };

    Scene.prototype.addElement = function addElement(el)
    {
        this.elements[this.num_elements++] = el;
    };
    
    Scene.prototype.calc_transformations = function calc_transformations()
    {
        var el;
        
        var cam_sinx = Math.sin(-this.camera.angle[0]);
        var cam_siny = Math.sin(-this.camera.angle[1]);
        var cam_sinz = Math.sin(-this.camera.angle[2]);
        var cam_cosx = Math.cos(-this.camera.angle[0]);
        var cam_cosy = Math.cos(-this.camera.angle[1]);
        var cam_cosz = Math.cos(-this.camera.angle[2]);
        
        var cam_x = this.camera.loc.x;
        var cam_y = this.camera.loc.y;
        var cam_z = this.camera.loc.z;
        
        for ( var n = this.num_elements; n--; )
        {
            el = this.elements[n];
            
            /* Using matrix to transform ...
            var obj_mat = G.create_identity_matrix();
            G.matrix_apply_rotations(obj_mat, el.rotation);
            //G.matrix_translate(obj_mat, obj.location);    
            obj_mat[12] += el.location.x;
            obj_mat[13] += el.location.y;
            obj_mat[14] += el.location.z;

            
            var camera_mat = G.create_identity_matrix();
            camera_mat[12] += this.camera.loc.x;
            camera_mat[13] += this.camera.loc.y;
            camera_mat[14] += this.camera.loc.z;
            G.matrix_apply_rotations(camera_mat, this.camera.angle);
            //G.matrix_translate(camera_mat, scene.camera.loc);

            
            var orig_vertex = el.data.vertex;
            var world_vertex = el.world_vertex;
            var camera_vertex = el.camera_vertex;
            var len = orig_vertex.length;
            for ( var v = 0; v < len; ++v )
            {
                world_vertex[v] = G.mul_matrix_vertex_to_new_array(obj_mat, orig_vertex[v]);
                camera_vertex[v] = G.mul_matrix_array_to_new_array(camera_mat, world_vertex[v]);
                //world_vertex[v] = G.mul_matrix_vertex_to_new_array(obj_mat, orig_vertex[v]);
            }
            */
            var sinx = Math.sin(el.rotation[0]);
            var siny = Math.sin(el.rotation[1]);
            var sinz = Math.sin(el.rotation[2]);
            var cosx = Math.cos(el.rotation[0]);
            var cosy = Math.cos(el.rotation[1]);
            var cosz = Math.cos(el.rotation[2]);
            
            var orig_vertex = el.data.vertex;
            var world_vertex = el.world_vertex;
            var camera_vertex = el.camera_vertex;

            var x;
            var y;
            var z;
            
            var tx; // TEMPORAL HOLDERS
            var ty;
            var tz;
            
            var len = orig_vertex.length;
            
            for ( var v = 0; v < len; ++v )
            {
                x = orig_vertex[v].x;// * (-1.0);
                y = orig_vertex[v].y;
                z = orig_vertex[v].z;
                    
                //x = (-1.0) * x;
                
                tx = (cosx * x) - (sinx * z);
                ty = (cosy * y) - (siny * tx);
                tz = (sinx * x) + (cosx * z);
                
                x = (cosy * tx) + (siny * y) + el.location.x;
                y = (sinz * tz) - (cosz * ty)+ el.location.y;
                z = (cosz * tz) - (sinz * ty)+ el.location.z;

                world_vertex[v] = [x, y, z];
                
                x += cam_x;
                y += -cam_y;
                z += cam_z;
                
                tx = (cam_cosx * x) - (cam_sinx * z);
                ty = (cam_cosy * y) - (cam_siny * tx);
                tz = (cam_sinx * x) + (cam_cosx * z);
                
                x = (cam_cosy * tx) + (cam_siny * y) ;//+ cam_x;
                y = (cam_sinz * tz) - (cam_cosz * ty);//+ cam_y;
                z = (cam_cosz * tz) - (cam_sinz * ty);//+ cam_z;
                
                camera_vertex[v] = [ x, y, z ];
            }
            
        }
    };
    
    Scene.prototype.project = function(view)
    {
        var el, vertex, screen_pixel, vertex_z, ver, zd;
        for ( var n = this.num_elements; n--; )
        {
            el = this.elements[n];
            
            vertex = el.camera_vertex;
            screen_pixel = el.screen_pixel;

            for ( var v = 0, mv = vertex.length; v < mv ; ++v )
            {
                ver = vertex[v]
                vertex_z = ver[2];
                zd = view.d / vertex_z;
                screen_pixel[v] = 
                [ // XXX "y * -d" to reverse y on screen
        //            (((ver[0] * View.d)/vertex_z)+visual_area_half_width )*x_ratio,
        //            (((ver[1] * View.d)/vertex_z)+visual_area_half_height)*y_ratio
                    (ver[0] *  zd) + view.mid_x,
                    (ver[1] * -zd) + view.mid_y
                ];
            }
        }
    }
    
/**
 *  View
 */
    function View(w, h)
    {
        this.d = 256,
        this.pos_x = 0,
        this.pos_y = 0,
        this.size_x = w,
        this.size_y = h,
        this.mid_x = w/2,
        this.mid_y = h/2,
        this.win_size_x = w,
        this.win_size_y = h
    }

/**
 *  Return
 */
    return {
        Vector: Vector,
        View: View,
        GeometricData: GeometricData,
        SceneElement: SceneElement,
        Scene: Scene,
        createRectangle: createRectangle
    };
})();


/*
 1. Initialize all the local coordinates of every vertices
  2. Set the global matrix to an identity matrix
  3. Scale the global matrix with the scaling of the object
  4. Rotate the global matrix with the angle of the object
  5. Translate the global matrix with the position of the object
  6. Multiply the local coordinates by the global matrix to get the world
     coordinates
  7. Set the global matrix to an identity matrix
  8. Translate the global matrix with the negative position of the viewer
  9. Rotate the global matrix with the negative angle of the viewer
 10. Multiply the world coordinates by the global matrix to get the aligned
     coordinates
 11. Project the aligned coordinates to get the screen coordinates
*/

/*
|   1   0   0   0   |
|   0   1   0   0   |
|   0   0   1   0   |
|   0   0   0   1   |
Identity

|   1     0       0      0  |
|   0   cos(x)  -sin(x)  0  |
|   0   sin(x)  cos(x)   0  |
|   0     0       0      1  |
X Rotation

|   cos(y)  0   sin(y)  0   |
|   0       1   0       0   |
|   -sin(y) 0   cos(y)  0   |
|   0       0   0       1   |
Y Rotation

|   cos(z)  -sin(z) 0   0   |
|   sin(z)  cos(z)  0   0   |
|   0       0       1   0   |
|   0       0       0   1   |
Z Rotation

|   1   0   0   Tx  |
|   0   1   0   Ty  |
|   0   0   1   Tz  |
|   0   0   0   1   |
Translation

|   Sx  0   0   0   |
|   0   Sy  0   0   |
|   0   0   Sz  0   |
|   0   0   0   1   |
Scaling

*/

G.create_identity_matrix = function()
{
    return [ 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 ];
};

G.matrix_apply_rotations = function(m, r)
{
    var cos_a = Math.cos(r[0]);
    var sin_a = Math.sin(r[0]);
    var ma = [ 1,0,0,0, 0,cos_a,sin_a,0, 0,-sin_a,cos_a,0, 0,0,0,1 ];
    G.mul_matrix_matrix(m, ma);
    
    cos_a = Math.cos(r[1]);
    sin_a = Math.sin(r[1]);
    ma = [ cos_a,0,-sin_a,0, 0,1,0,0, sin_a,0,cos_a,0, 0,0,0,1 ];
    G.mul_matrix_matrix(m, ma);
    
    cos_a = Math.cos(r[2]);
    sin_a = Math.sin(r[2]);
    ma = [ cos_a,sin_a,0,0, -sin_a,cos_a,0,0, 0,0,1,0, 0,0,0,1 ];
    G.mul_matrix_matrix(m, ma);
};

G.matrix_rotate_x = function(m, a)
{
    var cos_a = Math.cos(a);
    var sin_a = Math.sin(a);
    var ma = [ 1,0,0,0, 0,cos_a,-sin_a,0, 0,sin_a,cos_a,0, 0,0,0,1 ];
    G.mul_matrix_matrix(m, ma);
};

G.matrix_rotate_y = function(m, a)
{
    var cos_a = Math.cos(a);
    var sin_a = Math.sin(a);
    var ma = [ cos_a,0,sin_a,0, 0,1,0,0, -sin_a,0,cos_a,0, 0,0,0,1 ];
    G.mul_matrix_matrix(m, ma);
};

G.matrix_rotate_z = function(m, a)
{
    var cos_a = Math.cos(a);
    var sin_a = Math.sin(a);
    var ma = [ cos_a,-sin_a,0,0, sin_a,cos_a,0,0, 0,0,1,0, 0,0,0,1 ];
    G.mul_matrix_matrix(m, ma);
};

G.matrix_translate = function(m, v)
{
//    var ma = [ 1,0,0,v.x, 0,1,0,v.y, 0,0,1,v.z, 0,0,0,1 ];
    var ma = [ 1,0,0,0, 0,1,0,0, 0,0,1,0, v.x,v.y,v.z,1 ];
    G.mul_matrix_matrix(m, ma);
}

G.mul_matrix_matrix = function(m1, m2)
{
    var a = m1[0];
    var b = m1[1];
    var c = m1[2];
    var d = m1[3];
    
    m1[ 0] = (a*m2[0]) + (b*m2[4]) + (c*m2[ 8]) + (d*m2[12]); 
    m1[ 1] = (a*m2[1]) + (b*m2[5]) + (c*m2[ 9]) + (d*m2[13]); 
    m1[ 2] = (a*m2[2]) + (b*m2[6]) + (c*m2[10]) + (d*m2[14]); 
    m1[ 3] = (a*m2[3]) + (b*m2[7]) + (c*m2[11]) + (d*m2[15]);

    a = m1[4];
    b = m1[5];
    c = m1[6];
    d = m1[7];
    
    m1[ 4] = (a*m2[0]) + (b*m2[4]) + (c*m2[ 8]) + (d*m2[12]); 
    m1[ 5] = (a*m2[1]) + (b*m2[5]) + (c*m2[ 9]) + (d*m2[13]); 
    m1[ 6] = (a*m2[2]) + (b*m2[6]) + (c*m2[10]) + (d*m2[14]); 
    m1[ 7] = (a*m2[3]) + (b*m2[7]) + (c*m2[11]) + (d*m2[15]);

    a = m1[8];
    b = m1[9];
    c = m1[10];
    d = m1[11];
    
    m1[ 8] = (a*m2[0]) + (b*m2[4]) + (c*m2[ 8]) + (d*m2[12]); 
    m1[ 9] = (a*m2[1]) + (b*m2[5]) + (c*m2[ 9]) + (d*m2[13]); 
    m1[10] = (a*m2[2]) + (b*m2[6]) + (c*m2[10]) + (d*m2[14]); 
    m1[11] = (a*m2[3]) + (b*m2[7]) + (c*m2[11]) + (d*m2[15]);

    a = m1[12];
    b = m1[13];
    c = m1[14];
    d = m1[15];
    
    m1[12] = (a*m2[0]) + (b*m2[4]) + (c*m2[ 8]) + (d*m2[12]); 
    m1[13] = (a*m2[1]) + (b*m2[5]) + (c*m2[ 9]) + (d*m2[13]); 
    m1[14] = (a*m2[2]) + (b*m2[6]) + (c*m2[10]) + (d*m2[14]); 
    m1[15] = (a*m2[3]) + (b*m2[7]) + (c*m2[11]) + (d*m2[15]);
};

G.add_matrix_matrix = function(m1, m2)
{
    for ( var n = 0; n < m1.length; n++)
    {
        m1[n] += m2[n];
    }
    
}

G.mul_matrix_vertex = function(m, v, res)
{
    res.x = (v.x * m[0]) + (v.y * m[1]) + (v.z * m[2])  + m[3];
    res.y = (v.x * m[4]) + (v.y * m[5]) + (v.z * m[6])  + m[7];
    res.z = (v.x * m[8]) + (v.y * m[9]) + (v.z * m[10]) + m[11];
};

G.mul_matrix_vertex_to_new_array = function(m, v)
{
    return [
//        (v.x * m[0]) + (v.y * m[1]) + (v.z * m[2])  + m[3],
//        (v.x * m[4]) + (v.y * m[5]) + (v.z * m[6])  + m[7],
//        (v.x * m[8]) + (v.y * m[9]) + (v.z * m[10]) + m[11]
        (v.x * m[0]) + (v.y * m[4]) + (v.z * m[8])  + m[12],
        (v.x * m[1]) + (v.y * m[5]) + (v.z * m[9])  + m[13],
        (v.x * m[2]) + (v.y * m[6]) + (v.z * m[10]) + m[14]
    ];
};

G.mul_matrix_array_to_new_array = function(m, v)
{
    return [
//        (v[0] * m[0]) + (v[1] * m[1]) + (v[2] * m[2])  + m[3],
//        (v[0] * m[4]) + (v[1] * m[5]) + (v[2] * m[6])  + m[7],
//        (v[0] * m[8]) + (v[1] * m[9]) + (v[2] * m[10]) + m[11]
        (v[0] * m[0]) + (v[1] * m[4]) + (v[2] * m[8])  + m[12],
        (v[0] * m[1]) + (v[1] * m[5]) + (v[2] * m[9])  + m[13],
        (v[0] * m[2]) + (v[1] * m[6]) + (v[2] * m[10]) + m[14]
    ];
};


G.createStaticLine = function(_from, _to)
{
    var gdata = new GeometricData([_from, _to],[[0,1]]);
    var res = new SceneElement(gdata);
    return res;
};

G.createStaticSquare = function(_from, _to)
{
    var top_left;
    var bottom_right;
    
    if ( _from.x == _to.x )
    {
        top_left     = new Vector(_from.x, _to.y, _from.z);
        bottom_right = new Vector(_from.x, _from.y, _to.z);
    }
    else if ( _from.y == _to.y )
    {
        top_left     = new Vector(_from.x, _from.y, _to.z);
        bottom_right = new Vector(_to.x, _from.y, _from.z);
    }
    else // same z
    {
        top_left     = new Vector(_from.x, _to.y, _from.z);
        bottom_right = new Vector(_to.x, _from.y, _from.z);
    }
    
    var vertex = [
        _from,
        top_left,
        _to,
        bottom_right
    ];
    
    var faces = [[0, 1, 2, 3]];
    var gdata = new GeometricData(vertex,faces);
    var res = new SceneElement(gdata);
    return res;
};

/* for reference
 * 
 * 100 oper per matrix mul
 * 3 rot = 300 oper
 * 
 * 8 vertex * 18 oper per vertex = 144 oper 
 * 
 * 300+144 = 444 oper + 3 (add translation ) = 447 oper
 * 
 * ----
 * 
 * 18 per rotation
 * 
 * 3 per translation = 21 total * 8 = 168 operations
 * 
 * 
 * 
[ // vertex
        new Vector( 30, 30,-30),
        new Vector( 30, 30, 30),
        new Vector(-30, 30, 30),
        new Vector(-30, 30,-30), // far face until here
        new Vector( 30,-30,-30),
        new Vector( 30,-30, 30),
        new Vector(-30,-30, 30),
        new Vector(-30,-30,-30) // near face
    ],
    [ // faces
        [0, 1, 2, 3], // top cover
        [4, 7, 6, 5], // bottom
        [4, 0, 1, 5], // right side
        [4, 7, 3, 0], // back side
        [6, 2, 3, 7], // left side
        [1, 2, 6, 5], // that front side
    ]


function pre_calc_rotation(obj)
{
    var angles = obj.rotation;
    var sins = obj.sin_rotation;
    var coss = obj.cos_rotation;
    sins[0] = Math.sin(angles[0]);
    sins[1] = Math.sin(angles[1]);
    sins[2] = Math.sin(angles[2]);
    coss[0] = Math.cos(angles[0]);
    coss[1] = Math.cos(angles[1]);
    coss[2] = Math.cos(angles[2]);
}

function calc_rotation(obj)
{
    var sins = obj.sin_rotation;
    var coss = obj.cos_rotation;
    var orig_vertex = obj.data.vertex;
    var rotated_vertex = obj.rotated_vertex;

    var x = 0.0;
    var y = 0.0;
    var z = 0.0;
    
    var tx = 0.0; // TEMPORAL HOLDERS
    var ty = 0.0;
    var tz = 0.0;
    
    var len = orig_vertex.length;
    
    for ( var v = 0; v < len; ++v )
    {
        x = orig_vertex[v].x;// * (-1.0);
        y = orig_vertex[v].y;
        z = orig_vertex[v].z;
            
        //x = (-1.0) * x;
        
        tx = (coss[0] * x) - (sins[0] * z);
        ty = (coss[1] * y) - (sins[1] * tx);
        tz = (sins[0] * x) + (coss[0] * z);
        
        x = (coss[1] * tx) + (sins[1] * y);
        y = (sins[2] * tz) - (coss[2] * ty);
        z = (coss[2] * tz) - (sins[2] * ty);

        rotated_vertex[v] = [x, y, z];
    }
}

function calc_translation(obj)
{
    var orig_vertex = obj.rotated_vertex;
    var translated_vertex = obj.translated_vertex;

    var px = obj.location.x;
    var py = obj.location.y;
    var pz = obj.location.z;
    
    var len = orig_vertex.length;
    
    for ( var v = 0; v < len; ++v)
    {
        translated_vertex[v] = 
        [
            orig_vertex[v][0] + px,
            orig_vertex[v][1] + py,
            orig_vertex[v][2] + pz,
        ];
    }
}

 
function calc_visibility(obj)
{
    var faces = obj.data.faces;
    var visible_faces = obj.visible_faces;
    var num_visible_faces = 0;
    var points = obj.translated_vertex;
    
    var face;
    var max_f = faces.length;
    for ( var f = 0; f < max_f; ++f )
    {
        face = faces[f];
        var sp;
        if ( face.length > 2 )
        {
            // face0.x * ( (face1.y * face2.z) - (face2.y*face1.z) )
            // face1.x * ( (face2.y * face0.z) - (face0.y*face2.z) )
            // face2.x * ( (face0.y * face1.z) - (face1.y*face0.z) )
            
            var sp1 = ( points[face[0]][0] *
                         ( (points[face[1]][1] * points[face[2]][2])
                          -(points[face[2]][1] * points[face[1]][2])
                          )
                       );// * (-1.0);
                            
            var sp2 = points[face[1]][0] *
                         ( (points[face[2]][1] * points[face[0]][2])
                          -(points[face[0]][1] * points[face[2]][2])
                          );
    
            var sp3 = points[face[2]][0] *
                         ( (points[face[0]][1] * points[face[1]][2])
                          -(points[face[1]][1] * points[face[0]][2])
                          );
    
            sp = sp1 - sp2 - sp3;
        }
        else
        {
            sp = -1;
        }
        if ( testid == false )
            visible_faces[num_visible_faces++] = face;
        else if ( sp <= 0 )
            visible_faces[num_visible_faces++] = face;
    }
    
    obj.num_visible_faces = num_visible_faces;
}

*/
