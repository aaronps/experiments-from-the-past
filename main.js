/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

$(window).load(run_main);

var _canvas = null;
var _ctx = null;

var color = "770000";
var color_change = 0x111100;

var tileset_image = null;

function Tileset()
{
    this.width = 16;
    this.height = 16;
    this.image = null;
}

Tileset.prototype.load = function(name)
{
    this.image = new Image();
    this.image._owner = this;
    // XNOTE onload runs on the IMAGE object context
    this.image.onload = this.show_it;
    this.image.src = name;
};

Tileset.prototype.show_it = function()
{
    alert('shit ' + this._owner.width);
    $('#img_selector').append(this);
};

var tileset = new Tileset();

function run_main()
{
    _canvas = document.getElementById("mainCanvas");
    _ctx = _canvas.getContext("2d");

//    tileset_image = new Image();
//    tileset_image.onload = add_image;
//    tileset_image.src = "img/tileset_16x16_final_1.png";
    tileset.load("img/tileset_16x16_final_1.png");

    window.setTimeout(main_timer, 1000);
}

var res = "It:";

function main_timer()
{
//    var ccc = HTMLCanvasElement.getContext("2d");
//    CanvasRenderingContext2D.
    var bef = _ctx.fillStyle;
    _ctx.fillStyle = "#" + color;
    var aft = _ctx.fillStyle;
    _ctx.fillRect(50, 50, 50, 50);
    
    var aft2 = _ctx.fillStyle;

    res += typeof(bef) + ":" + bef + "," + typeof(aft) + ":" + aft +","+ typeof(aft2) + ":" + aft2;
}

function add_image()
{
    alert('here it comes');
    var i = document.createElement("img");
    i.src = tileset_image.src;
    $('#img_selector').append(tileset_image);
}

function add_element()
{
    var nimg = document.createElement("p");
    nimg.innerHTML = "Shit";
    document.getElementById("img_selector").appendChild(nimg);
    var im = new Image();
}

function remove_text()
{


}
