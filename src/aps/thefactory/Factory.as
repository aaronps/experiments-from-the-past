package aps.thefactory 
{
	import flash.accessibility.Accessibility;
	import flash.display.BitmapData;
	import flash.display.Bitmap;
	import flash.geom.ColorTransform;
	import flash.text.TextField;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	import flash.text.TextFormat;
	
	/**
	 * ...
	 * @author Aaron Perez Sanchez
	 */
	public class Factory 
	{
		private var isPaused:Boolean;
		
		private var toptext:BitmapData;
		
		private const LELECODE:int = 0xe0;
		private const RELECODE:int = 0xe1;
		
		private var layers:Array;
		private var walkable:Array;
		private var elevators:Array;
		private var boxes:Array;
		
		public function Factory( )
		{
			isPaused = false;
			Box.initBoxes();
			MainTilesTileSet.Init();
			tile16x16TileSet.Init();
			
			toptext = new BitmapData(640, 64, false, 0);
			
			var tf:TextField = new TextField();
			tf.width = 640;
			tf.height = 60;
			//tf.backgroundColor = 0;
			//tf.textColor = 0xff0000;
			//tf.text = "Victor, usa: Q=Izquierda Arriba, A=Izquierda Abajo, P=Derecha Arriba, L=Derecha Abajo, ESPACIO=Pausa\nPulsa Espacio para empezar, tienes que poner las cajas que aparecen con las cajas semitransparentes";
			tf.text = "0123456789";
			
			var tfor:TextFormat = new TextFormat();
			tfor.color = 0xff0000;
			tfor.size = 40;
			tf.setTextFormat(tfor);
			
			toptext.draw(tf);
			
			elevators = new Array(1); // first elevator ignored.
			
			boxes = new Array(1); // first box not used.
			
			// XXX create layers
			
			layers = new Array(3);
			//layers[0] = MainTilesTileSet.MapLevel1;
			layers[0] = tile16x16TileSet.Maptest;
			var curline:int;
			var curcolumn:int;
			var tmpline:Array;
			
			for ( var curlayer:int = 1; curlayer < 3; ++curlayer)
			{
				var tmparray:Array = new Array(layers[0].length);
				for ( curline = 0; curline < tmparray.length; ++curline )
				{
					tmpline = new Array(layers[0][0].length);
					for ( curcolumn = 0; curcolumn < tmpline.length; ++curcolumn )
					{
						tmpline[curcolumn] = 0;
					}
					tmparray[curline] = tmpline;
				}
				layers[curlayer] = tmparray;
			}
			
			/*
			 * Walkable: blocks of 16x16 (double of lines and columsn)
			 */
			walkable = new Array(layers[0].length * 2);
			for ( curline = 0; curline < walkable.length; ++curline )
			{
				tmpline= new Array(layers[0][0].length * 2);
				for ( curcolumn = 0; curcolumn < tmpline.length; ++curcolumn )
				{
					tmpline[curcolumn] = true; // all walkable by default
				}
				walkable[curline] = tmpline;
			}
			
			// XXX create layers finish
			
			// XXX populate extra layers
			
			var x:int;
			var y:int;
			
			var codes:Array = tile16x16TileSet.MaptestCodes;
			
			// look for elevators
			for ( x = 0; x < codes[0].length; ++x )
			{
				var ystart:int = 0;
				var yend:int = 0;
				var geny:int = 0;
				
				for ( y = 0; y < codes.length; ++y )
				{
					if ( codes[y][x] >= 0xe0 && codes[y][x] <= 0xef )
					{
						if ( ystart == 0 )
						{
							ystart = y;
						}
						else
						{
							yend = y;
						}
						
						if ( codes[y][x] == 0xe1 )
						{
							geny = y;
						}
					}
					if ( codes[y][x] == 0xff )
					{
						boxes.push ( new Box( x, y, 0 ) );
					}
				}
				
				if ( geny > 0 )
				{
					var elev:Elevator = new Elevator ( x, geny, ystart, yend );
					elevators.push( elev );
					var elevYCenter:int = Math.floor ( (elev.bounds.y + ( elev.bounds.height / 2 ))/16 );
					var elevXCenter:int = Math.floor ( (elev.bounds.x + ( elev.bounds.width / 2 ))/16 );
					layers[1][elevYCenter][elevXCenter] = elevators.length - 1;
				}
			}
				
			// generate walkable map
			for ( y = 0; y < layers[0].length; ++y )
			{
				var linebounds:Array = tile16x16TileSet.Maptest[y];
				
				for ( x = 0; x < linebounds.length; ++x )
				{	
					if ( linebounds[x] )
					{
						walkable[y][x] = false;
					}
					
				}
			}
			
			//boxes.push ( new Box( 6, 5, 1 ) );
			//boxes.push ( new Box( 5, 3, 1 ) );
			//boxes.push ( new Box( 2, 1, 0 ) );
			//boxes.push ( new Box( 30, 2, 1 ) );
			
			//for ( x = 0; x < 60; ++x )
			//{
				//boxes.push( new Box( 1+ Math.floor(Math.random() * 38), 1+Math.floor(Math.random() * 28), 0) );
			//}
			
			
			// XXX populate extra layers finish
			
			
		}
		
		public function draw(canvas:BitmapData):void
		{
			var p:Point = new Point(0, 0);
			var p2:Point = new Point(0, 0);
			canvas.copyPixels(toptext, toptext.rect, p);
			
			var type:int;
			var x:int;
			var y:int;
			
			
			//for ( x = 0; x < MainTilesTileSet.MapLevel1Width; ++x )
			for ( x = 0; x < tile16x16TileSet.MaptestWidth; ++x )
			{

				//p.y = 480-tile16x16TileSet.TileHeight;
				p.y = 0;
				p.x = x * tile16x16TileSet.TileWidth;
				//for ( y = MainTilesTileSet.MapLevel1Height-1; y >= 0; --y )
				for ( y = 0; y < tile16x16TileSet.MaptestHeight; ++y )
				{
					type = layers[0][y][x];
					if ( type > 0 )
					{
						//canvas.copyPixels(MainTilesTileSet.MainTilesImage.bitmapData, MainTilesTileSet.TileRects[type], p);
						canvas.copyPixels(tile16x16TileSet.tile16x16Image.bitmapData, tile16x16TileSet.TileRects[type], p);
					}
					
					type = layers[1][y][x]; // XXX here elevator
					if ( type > 0 )
					{
						elevators[type].draw(canvas);
						//canvas.fillRect(elevators[type].bounds, 0xff);
					}
					
					//p.y -= MainTilesTileSet.TileHeight;
					p.y += tile16x16TileSet.TileHeight;
				}
				
			}
			
			//drawWalkableMap(canvas);
			
			for ( x = 1; x < boxes.length; ++x )
			{
				//canvas.copyPixels(Box.images.bitmapData, Box.normalBoxRects[boxes[x].type],	new Point( boxes[x].bounds.x - 1, boxes[x].bounds.y - 11));
				canvas.fillRect(boxes[x].bounds, 0xffffff);
			}
		}

		private function drawWalkableMap(canvas:BitmapData):void
		{
			var walkableRect:Rectangle = new Rectangle(0, 0, 16, 16);
			
			for ( var y:int = 0; y < walkable.length; ++y )
			{
				walkableRect.y = (y * 16);
				walkableRect.x = 0;
				for ( var x:int = 0; x < walkable[y].length; ++x )
				{
					if ( !walkable[y][x] )
					{
						canvas.fillRect(walkableRect, 0x008080);
					}
					walkableRect.x += 16;
				}
				
			}
		}
		
		private function isWalkableLine(lineStart:int, lineEnd:int, start:int, end:int):Boolean
		{
			var x:int;
			while ( lineStart <= lineEnd )
			{
				x = start
				while ( x <= end )
				{
					if ( ! walkable[lineStart][x] )
					{
						return false;
					}
					++x;
				}
				++lineStart;
			}
			return true;
		}
		
		private function isWalkableColumn(column:int, start:int, end:int):Boolean
		{
			while ( start <= end )
			{
				if ( ! walkable[start][column] )
				{
					return false;
				}
				++start;
			}
			return true;
		}
		
		private function collideWithOtherBox(b:Box, boxnum:int, boxstart:int):Number
		{
			for ( var n:int = boxstart+1; n < boxes.length; ++n )
			{
				if ( boxes[n] != b && b.bounds.intersects(boxes[n].bounds) )
				{
					return n;
				}
			}
			return 0;
		}
		
		private function newBoundsCollideWithOtherBox(b:Box, boxnum:int, boxstart:int):Number
		{
			for ( var n:int = boxstart+1; n < boxes.length; ++n )
			{
				if ( boxes[n] != b && b.newBounds.intersects(boxes[n].newBounds) )
				{
					return n;
				}
			}
			return 0;
		}
		
		private function collideWithBox(r:Rectangle, boxstart:int):int
		{
			while ( ++boxstart < boxes.length )
			{
				if ( r.intersects(boxes[boxstart].bounds) )
				{
					return boxstart;
				}
			}
			return 0;
		}
		
		private function moveBoxOnGravity(b:Box, timeSlice:Number, bcode:int):void
		{
			var distanceToMove:Number = (20.0 / 1000.0) * timeSlice * b.dropFactor;
			if ( moveBoxDown(b, distanceToMove, bcode) <= 0 )
			{
				b.dropFactor = 1.0;
			}
			else
			{
				b.dropFactor += 0.1;
			}
			
		}
		private function moveBoxUp(b:Box, distanceToMove:Number, bcode:int):Number
		{
			var oldY:Number = b.bounds.y;
			var collBox:int;
			var collRect:Rectangle;
			var newTopY:int;
			var canGoUp:Boolean = true;
			
			if ( isWalkableLine(b.topY, b.topY, b.leftX, b.rightX) )
			{
				b.bounds.y -= distanceToMove;
				newTopY = Math.floor( b.bounds.y / 16 );
				
				if ( b.topY -newTopY > 1 )
				{
					trace("more than 1");
					//canGoUp = false;
				}
				
				if ( ! isWalkableLine(newTopY, b.topY, b.leftX, b.rightX) )
				{
					canGoUp = false;
					//trace("Can't go up " );
					b.bounds.y = (newTopY + 1) * 16;
				}
				
				if ( canGoUp )
				{
					var otherBoxMovedDistance:Number;
					collBox = collideWithOtherBox(b, bcode, 0);
					while ( collBox > 0 )
					{
						collRect = b.bounds.intersection(boxes[collBox].bounds);
						if ( collRect.y <= b.bounds.y ) // collide in top
						{
							otherBoxMovedDistance = moveBoxUp(boxes[collBox], collRect.height,0);
							if ( otherBoxMovedDistance < collRect.height )
							{
								b.bounds.y += collRect.height - otherBoxMovedDistance;
							}
						}
						collBox = collideWithOtherBox(b, bcode, collBox);
					}
				}
				for ( var n:int = 1; n < elevators.length; ++n )
				{
					if ( b.bounds.intersects(elevators[n].bounds) )
					{
						collRect = b.bounds.intersection(elevators[n].bounds);
						if ( collRect.y <= b.bounds.y )
						{
							b.bounds.y += collRect.height;
						}
					}
				}
				
				b.topY 	= Math.floor( b.bounds.y / 16 );
				b.bottomY = Math.floor( (b.bounds.bottom-1) / 16 );
			}
			return oldY - b.bounds.y;
		}
		
		private function moveBoxDown(b:Box, distanceToMove:Number, bcode:int):Number
		{
			var oldY:Number = b.bounds.y;
			var collBox:int;
			var collRect:Rectangle;
			var newBottomY:int;
			
			if ( isWalkableLine(b.bottomY, b.bottomY, b.leftX, b.rightX) )
			{
				b.bounds.y += distanceToMove;
				newBottomY = Math.floor( (b.bounds.bottom-1) / 16 );
				
				if ( ! isWalkableLine(b.bottomY, newBottomY, b.leftX, b.rightX) )
				{
					b.bounds.y = (newBottomY * 16) - b.bounds.height ;
				}
				
				collBox = collideWithOtherBox(b, bcode, 0);
				while ( collBox > 0 )
				{
					collRect = b.bounds.intersection(boxes[collBox].bounds);
					if ( collRect.y > b.bounds.y )
					{
						b.bounds.y -= collRect.height;
					}
					collBox = collideWithOtherBox(b, bcode, collBox);
				}
				
				for ( var n:int = 1; n < elevators.length; ++n )
				{
					if ( b.bounds.intersects(elevators[n].bounds) )
					{
						collRect = b.bounds.intersection(elevators[n].bounds);
						if ( collRect.y > b.bounds.y )
						{
							b.bounds.y -= collRect.height;
						}
					}
				}
				
				b.topY 	= Math.floor( b.bounds.y / 16 );
				b.bottomY = Math.floor( (b.bounds.bottom-1) / 16 );
			}
			return b.bounds.y - oldY;
		}
		
		private function moveBoxRight(b:Box, distanceToMove:Number, bcode:int ):Number
		{
			var oldX:Number = b.bounds.x;
			if ( isWalkableColumn(b.rightX, b.topY, b.bottomY) )
			{
				b.bounds.x += distanceToMove;
				var newX:int = Math.floor( (b.bounds.right - 1) / 16 );
				if ( ! isWalkableColumn(newX, b.topY, b.bottomY) )
				{
					b.bounds.x = (newX * 16) - b.bounds.width;
				}
				
				var collBox:int = collideWithOtherBox(b, bcode, 0);
				var collRect:Rectangle;
				while ( collBox > 0 )
				{
					collRect = b.bounds.intersection(boxes[collBox].bounds);
					if ( collRect.x > b.bounds.x )
					{
						b.bounds.x -= collRect.width;
					}
					collBox = collideWithOtherBox(b, bcode, collBox);
				}
				
				for ( var n:int = 1; n < elevators.length; ++n )
				{
					if ( b.bounds.intersects(elevators[n].bounds) )
					{
						collRect = b.bounds.intersection(elevators[n].bounds);
						if ( collRect.x > b.bounds.x )
						{
							b.bounds.x -= collRect.width;
						}
					}
				}
				
				b.rightX = Math.floor( (b.bounds.right - 1) / 16 );
				b.leftX = Math.floor( b.bounds.x / 16 );
			}
			return b.bounds.x - oldX;
		}
		
		private function moveBoxLeft(b:Box, distanceToMove:Number, bcode:int):Number
		{
			var oldX:Number = b.bounds.x;
			if ( isWalkableColumn(b.leftX, b.topY, b.bottomY) )
			{
				b.bounds.x -= distanceToMove;
				var newX:int = Math.floor( b.bounds.x / 16 );
				if ( ! isWalkableColumn(newX, b.topY, b.bottomY) )
				{
					b.bounds.x = (newX + 1) * 16;
				}
				
				var collBox:int = collideWithOtherBox(b, bcode, 0);
				var collRect:Rectangle;
				while ( collBox > 0 )
				{
					collRect = b.bounds.intersection(boxes[collBox].bounds);
					if ( collRect.x <= b.bounds.x )
					{
						b.bounds.x += collRect.width;
					}
					collBox = collideWithOtherBox(b, bcode, collBox);
				}
				
				for ( var n:int = 1; n < elevators.length; ++n )
				{
					if ( b.bounds.intersects(elevators[n].bounds) )
					{
						collRect = b.bounds.intersection(elevators[n].bounds);
						if ( collRect.x <= b.bounds.x )
						{
							b.bounds.x += collRect.width;
						}
					}
				}
				
				b.rightX = Math.floor( (b.bounds.right - 1) / 16 );
				b.leftX = Math.floor( b.bounds.x / 16 );
			}
			return oldX - b.bounds.x;
		}
		
		private function moveBoxOnLine(b:Box, timeSlice:Number, bcode:int):void
		{
			var moved:Boolean = false;
			var code:int;
			var distmove:int;
			var curX:int = b.leftX;
			var distanceToMove:Number = (40.0 / 1000.0) * timeSlice * b.speedFactor;
			do
			{
				code = tile16x16TileSet.MaptestCodes[b.bottomY][curX];
				if ( code >= 0xa0 && code <= 0xaf )
				{
					distmove = code & 0x0f;
					if ( b.bounds.bottom >= (b.bottomY * 16) + distmove )
					{
						moveBoxRight(b, distanceToMove, bcode );
					}
					moved = true;
				}
				else if ( code >= 0xb0 && code <= 0xbf )
				{
					distmove= code & 0x0f;
					if ( b.bounds.bottom >= (b.bottomY * 16) + distmove )
					{
						moveBoxLeft(b, distanceToMove, bcode );
					}
					moved = true;
				}
				else if ( code >= 0xe0 && code <= 0xef )
				{
					var centerX:Number = ((curX * 16) + 8) - (b.bounds.width / 2 );
					if ( b.bounds.x < centerX )
					{
						if ( centerX - b.bounds.x < distanceToMove )
						{
							moveBoxRight(b, centerX - b.bounds.x, bcode);
						}
						else
						{
							moveBoxRight(b, distanceToMove, bcode);
						}
					}
					else if ( b.bounds.x > centerX )
					{
						if ( b.bounds.x - centerX < distanceToMove )
						{
							moveBoxLeft(b, centerX - b.bounds.x, bcode);
						}
						else
						{
							moveBoxLeft(b, distanceToMove, bcode);
						}
					}
					
				}
				++curX;
			} while ( ! moved && curX <= b.rightX )
		}
		
		private function moveElevator(elev:Elevator, timeSlice:Number):void
		{
			var elevYCenter:int = Math.floor ( (elev.bounds.y + ( elev.bounds.height / 2 ))/16 );
			var elevXCenter:int = Math.floor ( (elev.bounds.x + ( elev.bounds.width / 2 )) / 16 );
			var elevatorCode:int = layers[1][elevYCenter][elevXCenter];
			var collBox:int;
			var collRect:Rectangle;
			var distanceToMove:Number = elev.speed * timeSlice;
			var boxMovedDistance:Number;
			
			if ( elev.wantsDown )
			{
				layers[1][elevYCenter][elevXCenter] = 0;
				elev.bounds.y += distanceToMove;
				if ( elev.bounds.y > elev.toY )
				{
					elev.bounds.y = elev.toY;
				}
				
				collBox = collideWithBox(elev.bounds, 0);
				while ( collBox > 0 )
				{
					collRect = elev.bounds.intersection(boxes[collBox].bounds);
					//boxMovedDistance = moveBoxUp(boxes[collBox], collRect.height,0);
					//if ( boxMovedDistance < collRect.height )
					if ( collRect.y > elev.bounds.y )
					{
						elev.bounds.y -= collRect.height;
					}
					collBox = collideWithBox(elev.bounds, collBox);
				}
				
				elevYCenter = Math.floor ( (elev.bounds.y + ( elev.bounds.height / 2 ))/16 );
				elevXCenter = Math.floor ( (elev.bounds.x + ( elev.bounds.width / 2 ))/16 );
				
				layers[1][elevYCenter][elevXCenter] = elevatorCode;
			}
			else if ( elev.wantsUp )
			{
				layers[1][elevYCenter][elevXCenter] = 0;
				elev.bounds.y -= distanceToMove;
				if ( elev.bounds.y < elev.fromY )
				{
					elev.bounds.y = elev.fromY;
				}
				
				collBox = collideWithBox(elev.bounds, 0);
				while ( collBox > 0 )
				{
					collRect = elev.bounds.intersection(boxes[collBox].bounds);
					//trace("[ Elevator pushing up box " + collBox + " by " + collRect.height );
					boxMovedDistance = moveBoxUp(boxes[collBox], collRect.height,0);
					if ( boxMovedDistance < collRect.height )
					{
						elev.bounds.y += collRect.height - boxMovedDistance;
					}
					collBox = collideWithBox(elev.bounds, collBox);
					//trace("[ <<-- End ]");
				}
				
				
				elevYCenter = Math.floor ( (elev.bounds.y + ( elev.bounds.height / 2 ))/16 );
				elevXCenter = Math.floor ( (elev.bounds.x + ( elev.bounds.width / 2 ))/16 );
				
				layers[1][elevYCenter][elevXCenter] = elevatorCode;
			}
		}
		
		public static const GRAVITY:Number = 400; // pixels/second/second
		public static const X_ACCEL:Number = 400; // pixels/second/second
		public static const MAX_VSPEED:Number = 200; // pixels/second
		public static const MAX_HSPEED:Number = 200; // pixels/second
		
		private var ftime:Boolean = false;
		public function logic(timeSlice:Number):void
		{
			if ( isPaused ) return;
			
			var n:int;
			var b:Box;
			
			for ( n = 1; n < elevators.length; ++n )
			{
				var elev:Elevator = elevators[n];
				if ( elev.wantsUp )
				{
					elev.newBounds.y = elev.bounds.y - (elev.speed * timeSlice);
				}
				
				if ( elev.wantsDown )
				{
					elev.newBounds.y = elev.bounds.y + (elev.speed * timeSlice);
				}
			}
			
			//var newRect:Rectangle = new Rectangle(0, 0, 0, 0);
			
			for ( n = 1; n < boxes.length; ++n )
			{
				b = boxes[n];
				
				b.topY    = Math.floor(  b.bounds.y / 16 );
				b.bottomY = Math.floor( (b.bounds.bottom - 1) / 16 );
				b.leftX   = Math.floor(  b.bounds.x / 16 );
				b.rightX  = Math.floor( (b.bounds.right - 1) / 16 );
				
				
				b.acceleration.x = 0; // no X accel
				
				
				// gravity
				b.acceleration.y = GRAVITY;
				var possibleY:int = Math.floor(b.bounds.bottom / 16);
				if ( b.bottomY != possibleY )
				{
					if ( ! isWalkableLine(possibleY, possibleY, b.leftX, b.rightX ) )
					{
						b.acceleration.y = 0;
						//b.velocity.y = 0;
					}
				}
				
				// horiz move
				var moved:Boolean = false;
				var code:int;
				var distmove:int;
				var curX:int = b.leftX;
				var possibleX:int;
				//var distanceToMove:Number = (40.0 / 1000.0) * timeSlice * b.speedFactor;
				var distanceToMove:Number = X_ACCEL;
				do
				{
					//if ( curX < tile16x16TileSet.MaptestCodes[b.bottomY].length )
					if ( b.bottomY < tile16x16TileSet.MaptestCodes.length )
					{
						
					
					code = tile16x16TileSet.MaptestCodes[b.bottomY][curX];
					if ( code >= 0xa0 && code <= 0xaf )
					{
						distmove = code & 0x0f;
						if ( b.bounds.bottom >= (b.bottomY * 16) + distmove )
						{
							//b.newBounds.x = b.bounds.x + distanceToMove;
							b.acceleration.x += distanceToMove;
						}
						
						//if ( b.velocity == 0 )
						//{
							possibleX = Math.floor(b.bounds.right / 16);
							if ( b.rightX != possibleX )
							{
								if ( ! isWalkableColumn(possibleX, b.topY, b.bottomY ) )
								{
									b.acceleration.x = 0;
									//b.velocity.x = 0;
								}
							}
						//}
						moved = true;
						
					}
					else if ( code >= 0xb0 && code <= 0xbf )
					{
						distmove= code & 0x0f;
						if ( b.bounds.bottom >= (b.bottomY * 16) + distmove )
						{
							//b.newBounds.x = b.bounds.x - distanceToMove;
							b.acceleration.x -= distanceToMove;
						}
							possibleX = Math.floor((b.bounds.x-1) / 16);
							if ( b.leftX != possibleX )
							{
								if ( ! isWalkableColumn(possibleX, b.topY, b.bottomY ) )
								{
									b.acceleration.x = 0;
									//b.velocity.x = 0;
								}
							}
						moved = true;
					}
					//else if ( code >= 0xe0 && code <= 0xef )
					//{
						//var centerX:Number = ((curX * 16) + 8) - (b.bounds.width / 2 );
						//if ( b.bounds.x < centerX )
						//{
							//if ( centerX - b.bounds.x < distanceToMove )
							//{
								//b.newBounds.x = b.bounds.x + centerX - b.bounds.x;
							//}
							//else
							//{
								//b.newBounds.x = b.bounds.x + distanceToMove;
							//}
						//}
						//else if ( b.bounds.x > centerX )
						//{
							//if ( b.bounds.x - centerX < distanceToMove )
							//{
								//b.newBounds.x = b.bounds.x - (centerX - b.bounds.x);
							//}
							//else
							//{
								//b.newBounds.x = b.bounds.x - distanceToMove;
							//}
						//}
						//
					//}
					}
					++curX;
				} while ( ! moved && curX <= b.rightX )
				
				b.velocity.x += (b.acceleration.x / 1000.0) * timeSlice;
				b.velocity.y += (b.acceleration.y / 1000.0) * timeSlice;
				
				if ( ! moved )
				{
					b.velocity.x *= 0.9;
					if ( b.velocity.x > -4 && b.velocity.x < 4 )
					{
						b.velocity.x = 0;
					}
				}
				
				if ( b.velocity.y > MAX_VSPEED )
				{
					b.velocity.y = MAX_VSPEED;
				}
				else if ( b.velocity.y < -MAX_VSPEED )
				{
					b.velocity.y = -MAX_VSPEED;
				}
				
				if ( b.velocity.x > MAX_HSPEED )
				{
					b.velocity.x = MAX_HSPEED;
				}
				else if ( b.velocity.x < -MAX_HSPEED )
				{
					b.velocity.x = -MAX_HSPEED;
				}
				
				b.newBounds.x = b.bounds.x + ((b.velocity.x/1000.0) * timeSlice);
				b.newBounds.y = b.bounds.y + ((b.velocity.y/1000.0) * timeSlice);
				//b.velocity.offset(b.acceleration.x * timeSlice, b.acceleration.y*timeSlice);
				
			}
			
			var hasCollision:Boolean = false;
			var collBox:int;
			var collRect:Rectangle;
			do
			{
				hasCollision = false;
				for ( n = 1; n < boxes.length; ++n )
				{
					b = boxes[n];
					
					var newTopY:int    = Math.floor(  b.newBounds.y / 16 );
					var newBottomY:int = Math.floor( (b.newBounds.bottom - 1) / 16 );
					var newLeftX:int   = Math.floor(  b.newBounds.x / 16 );
					var newRightX:int  = Math.floor( (b.newBounds.right - 1) / 16 );
					
					if ( b.velocity.y < 0 && newTopY != b.topY && ! isWalkableLine(newTopY, newTopY, newLeftX, newRightX) )
					{
						if ( isWalkableColumn( newRightX, newTopY + 1, newTopY + (newBottomY - newTopY ) )
							&& isWalkableColumn( newLeftX, newTopY + 1, newTopY + (newBottomY - newTopY ) ) )
						{
							//isPaused = true;
							hasCollision = true;
							//b.velocity.y = -b.velocity.y;
							b.velocity.y = -b.velocity.y * 0.1;
							if ( b.velocity.y < 4 )
							{
								b.velocity.y = 0;
							}
							b.newBounds.y = (newTopY + 1) * 16;
							b.canGoUp = false;
							continue;
						}
					}
					else
					{
						b.canGoUp = true;
					}
					
					if ( b.velocity.y > 0 && newBottomY != b.bottomY && ! isWalkableLine(newBottomY, newBottomY, newLeftX, newRightX) )
					{
						if ( isWalkableColumn( newRightX, newTopY, newTopY + (newBottomY - newTopY ) -1 )
							&& isWalkableColumn( newLeftX, newTopY, newTopY + (newBottomY - newTopY ) -1 ) )
						{
							//isPaused = true;
							hasCollision = true;
							//b.velocity.y = 0;
							//b.velocity.y = -b.velocity.y;
							b.velocity.y = -b.velocity.y * 0.1;
							if ( b.velocity.y > -4 )
							{
								b.velocity.y = 0;
							}
							b.newBounds.y = (newBottomY * 16) - b.bounds.height;
							b.dropFactor = 1.0;
							b.canGoDown = false;
							continue;
						}
					}
					else
					{
						b.canGoDown = true;
					}
					
					if ( b.velocity.x < 0 && ! isWalkableColumn(newLeftX, newTopY, newBottomY ) )
					{
						//isPaused = true;
						hasCollision = true;
						//b.velocity.x = -b.velocity.x;
						b.velocity.x = -b.velocity.x*0.1;
						if ( b.velocity.x < 4 )
						{
							b.velocity.x = 0;
						}
						b.newBounds.x = (newLeftX + 1) * 16;
						b.canGoLeft = false;
						continue;
					}
					else
					{
						b.canGoLeft = true;
					}
					
					if ( b.velocity.x > 0 && ! isWalkableColumn(newRightX, newTopY, newBottomY) )
					{
						//isPaused = true;
						hasCollision = true;
						//b.velocity.x = 0;
						//b.velocity.x = -b.velocity.x;
						b.velocity.x = -b.velocity.x * 0.1;
						if ( b.velocity.x > -4 )
						{
							b.velocity.x = 0;
						}
						b.newBounds.x = (newRightX * 16) - b.bounds.width;
						b.canGoRight = false;
						continue;
					}
					else
					{
						b.canGoRight = true;
					}
					//
					// checks with map collision done
					//
				}
				
				//if ( hasCollision ) continue;
				
				for ( n = 1; !hasCollision && n < boxes.length; ++n )
				{
					b = boxes[n];
					if ( b.velocity.x == 0 && b.velocity.y == 0 )
					{
						continue;
					}
					
					collBox = newBoundsCollideWithOtherBox(b, 0, 0);
					while ( collBox > 0 )
					{
						collRect = b.newBounds.intersection(boxes[collBox].newBounds);
						//trace("Collision of box " + n + " with box " + collBox );
						//isPaused = true;
						if ( b.canGoUp && collRect.y > b.newBounds.y )
						{
							//trace("Box " + n + " can go up and " + collRect.y + " is more than " + b.newBounds.y
								//+ " height is " + collRect.height );
							b.newBounds.y -= collRect.height;
							b.velocity.y *= -0.15;
							if ( b.velocity.y > -4 && b.velocity.y < 4 )
							{
								b.velocity.y = 0;
							}
							
							//b.newBounds.y--;
							hasCollision = true;
							break;
						}
						
						if ( b.canGoLeft && collRect.right > b.newBounds.x && collRect.right < b.newBounds.right )
						{
							b.newBounds.x -= collRect.width;
							b.velocity.x *= -0.15;
							if ( b.velocity.x > -4 && b.velocity.x < 4 )
							{
								b.velocity.x = 0;
							}
							hasCollision = true;
							break;
						}
						collBox = newBoundsCollideWithOtherBox(b, 0, collBox);
					}
				}
				
			} while ( hasCollision );
			
			
			
			for ( n = 1; n < elevators.length; ++n )
			{
				elevators[n].bounds.y = elevators[n].newBounds.y;
			}
			
			for ( n = 1; n < boxes.length; ++n )
			{
				b = boxes[n];
				b.bounds.x = b.newBounds.x;
				b.bounds.y = b.newBounds.y;
			}
			
			
			//for ( n = 1; n < elevators.length; ++n )
			//{
				//moveElevator(elevators[n], timeSlice);
			//}
			//
			//for ( n = 1; n < boxes.length; ++n )
			//{
				//b = boxes[n];
				//b.topY    = Math.floor(  b.bounds.y / 16 );
				//b.bottomY = Math.floor( (b.bounds.bottom - 1) / 16 );
				//b.leftX   = Math.floor(  b.bounds.x / 16 );
				//b.rightX  = Math.floor( (b.bounds.right - 1) / 16 );
				//
				//moveBoxOnGravity(b, timeSlice, n);
				//moveBoxOnLine(b, timeSlice, n);
			//}
			
		}   
		
		public function firstElevatorUp(wants:Boolean):void
		{
			elevators[1].wantsUp = wants;
		}

		public function firstElevatorDown(wants:Boolean):void
		{
			elevators[1].wantsDown = wants;
		}

		public function secondElevatorUp(wants:Boolean):void
		{
			elevators[2].wantsUp = wants;
		}

		public function secondElevatorDown(wants:Boolean):void
		{
			elevators[2].wantsDown = wants;
		}
		
		public function switchPause():void
		{
			isPaused = ! isPaused;
		}	
	}
}