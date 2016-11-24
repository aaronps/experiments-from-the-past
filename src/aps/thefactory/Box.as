package aps.thefactory 
{
	import flash.display.Bitmap;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	/**
	 * ...
	 * @author Aaron Perez Sanchez
	 */
	public class Box 
	{
		public static const BOX_WIDTH:int = 32;
		public static const BOX_HEIGHT:int = 32;
		
		[Embed(source = 'images/boxes.png')] private static var BoxesClass:Class;
		public static var images:Bitmap = new BoxesClass();
		public static var normalBoxRects:Array;
		public static var transBoxRects:Array;
		
		public static function initBoxes():void
		{
			normalBoxRects = new Array(images.width / BOX_WIDTH);
			transBoxRects = new Array(images.width / BOX_WIDTH);
			for ( var n:int = 0; n < normalBoxRects.length; ++n )
			{
				normalBoxRects[n] = new Rectangle(n * BOX_WIDTH, 0, BOX_WIDTH, BOX_HEIGHT);
				transBoxRects[n] = new Rectangle(n * BOX_WIDTH, BOX_HEIGHT, BOX_WIDTH, BOX_HEIGHT);
			}
		}
		
		public var tileX:int;
		public var tileY:int;
		public var type:int;
		public var loc:Point;
		public var speedFactor:Number;
		public var dropFactor:Number;
		
		public var topY:int;
		public var bottomY:int;
		public var leftX:int;
		public var rightX:int;
		
		public var bounds:Rectangle;
		public var velocity:Point;
		public var acceleration:Point;
		
		public var newBounds:Rectangle;
		public var canGoUp:Boolean;
		public var canGoDown:Boolean;
		public var canGoLeft:Boolean;
		public var canGoRight:Boolean;
		
		public function Box(tileX:int, tileY:int, type:int) 
		{
			this.tileX = tileX;
			this.tileY = tileY;
			this.type = type;
			// this loc.x should be 5+ not 6+
			this.loc = new Point( tileX * 16, tileY * 16 );
			//this.loc.offset(3,3);
			this.speedFactor = 1.0;
			/* Explanation of bounds:
			 * x + 6 because the bounds has to be on center of tile (x)
			 * y - 5: 5 is = 10 of zdeep + 1 of border = 11, 16 - 11 = 5, 16 is half of tile.
			 */
			this.bounds = new Rectangle( loc.x, loc.y, 20, 20);
			this.dropFactor = 1.0;
			this.newBounds = bounds.clone();
			this.velocity = new Point(0, 0);
			this.acceleration = new Point(0, 0);
		}
		
	}
	
}