package aps.thefactory 
{
	import flash.display.BitmapData;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	import flash.display.Bitmap;
	/**
	 * ...
	 * @author Aaron Perez Sanchez
	 */
	public class Elevator
	{
		
		[Embed(source = "images/elevator.png")] private static var ElevatorClass:Class;
		public static var image:Bitmap = new ElevatorClass();
		
		public var locked:Boolean;
		public var wantsToMove:int;
		public var loc:Point;
		public var speed:Number;
		public var tileX:int;
		public var fromYTile:int;
		public var toYTile:int;
		public var bounds:Rectangle;
		public var fromY:Number;
		public var toY:Number;
		public var wantsUp:Boolean;
		public var wantsDown:Boolean;
		public var newBounds:Rectangle;
		
		public function Elevator( tileX:int, tileY:int, fromYTile:int, toYTile:int )
		{
			trace("New elevator: " + tileX +"," + tileY + " range " + fromYTile + "," + toYTile );
			this.tileX = tileX;
			this.fromYTile = fromYTile;
			this.toYTile = toYTile
			this.fromY = fromYTile * 16;
			this.toY = toYTile * 16;
			this.loc = new Point( 0, 0 );
			this.locked = false;
			this.wantsToMove = 0;
			this.speed = 100 / 1000;
			bounds = new Rectangle( ((tileX - 1) * 16), (tileY * 16) , 48, 16 );
			this.wantsUp = false;
			this.wantsDown = false;
			this.newBounds = bounds.clone();
		}
		
		public function draw(canvas:BitmapData):void
		{
			//canvas.copyPixels(Elevator.image.bitmapData, Elevator.image.bitmapData.rect, loc);
			canvas.fillRect(bounds, 0xff00);
		}
		
	}
	
}