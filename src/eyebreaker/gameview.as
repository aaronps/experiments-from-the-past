package eyebreaker 
{
	import flash.display.Sprite
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.geom.Rectangle;
	import flash.geom.Point;
	/**
	 * ...
	 * @author Aaron Perez Sanchez
	 */
	public class gameview extends Sprite
	{
		[Embed(source = "blocks1.png")]
		private var blocks1Class:Class;
		private var blocks:Bitmap = new blocks1Class();

		private const blockwidth:int = 64;
		private const blockheight:int = 64;
		
		private var maparray:Array;
		private var cols:int;
		private var lines:int;
		private var numdiffblocks:int;
		private var canvas:Bitmap;
		private var canvasBD:BitmapData;
		
		public function gameview() 
		{
			canvasBD = new BitmapData(512, 384, false, 0xffffff);
			canvas = new Bitmap(canvasBD);
			addChild(canvas);
			reset();
			
		}
		
		private function randomSort(elementA:Object, elementB:Object):Number
		{
			return Math.random() - 0.5;
		}
		
		private function reset():void
		{
			cols = 6;
			lines = 5;
			numdiffblocks = blocks.width / blockwidth;
			
			var totalblocks:int = cols * lines;
			var countArray:Array = new Array();
			var counter:int = 0;
			var currentblock:int = 0;
			
			for ( counter = 0; counter < numdiffblocks; ++counter)
			{
				countArray.push(0);
			}
			
			
			var finalblocks:int = 0;
			for ( counter = totalblocks; counter > 1; counter -= 2)
			{
				countArray[currentblock] += 2;
				finalblocks += 2;
				
				++currentblock;
				if ( currentblock >= numdiffblocks )
				{
					currentblock = 0;
				}
			}
			
			maparray = new Array();
			while ( finalblocks > 0 )
			{
				var v:int;
				do
				{
					v = Math.floor(Math.random() * countArray.length);
				} while ( countArray[v] == 0 );
				
				maparray.push(v);
				--finalblocks;
				--countArray[v];
			}
			
			var r:Rectangle = new Rectangle(0, 0, 64, 64);
			var p:Point = new Point(0, 0);
			for ( var n:int = 0; n < maparray.length; ++n)
			{
				r.x = maparray[n] * 64;
				
				canvasBD.copyPixels(blocks.bitmapData, r, p);
				
				p.x += 64;
				if ( p.x >= canvasBD.width )
				{
					p.y += 64;
					p.x = 0;					
				}
			}

			
			
		}
		
		
	}
	
}