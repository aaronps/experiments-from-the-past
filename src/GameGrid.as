package  
{
	import flash.display.BitmapData;
	import flash.display.Sprite;
	import flash.display.Bitmap;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	import flash.events.MouseEvent;
	
	/**
	 * ...
	 * @author Aaron Perez Sanchez
	 */
	public class GameGrid extends Sprite
	{
		[Embed(source = "emb_images/grid.png")]
		private var gridClass:Class;
		private var gridImage:Bitmap = new gridClass();
		
		[Embed(source = "emb_images/x.png")]
		private var axeClass:Class;
		private var axeBitmap:Bitmap = new axeClass();
		
		[Embed(source = "emb_images/o.png")]
		private var circleClass:Class;
		private var circleBitmap:Bitmap = new circleClass();

		private var grid:Array;
		private var gridElements:Array;
		private var gridBitMap:Bitmap;
		private var gridBitMapData:BitmapData;
		private var currentPlayer:uint;
		private var _hasWinner:Boolean;
		private var winner:uint;
		
		public function GameGrid(x:uint, y:uint) 
		{
			this.x = x;
			this.y = y;
			currentPlayer = 0;
			
			gridElements = [ circleBitmap, axeBitmap ];
			gridBitMapData = new BitmapData(gridImage.width, gridImage.height, true, 0);
			gridBitMap = new Bitmap(gridBitMapData);
			
			resetGrid();
			renderGrid();
			
			addChild(gridImage);
			addChild(gridBitMap);
			
			addEventListener(MouseEvent.CLICK, onMouseClick);
			
		}
		
		private function resetGrid():void
		{
			grid = [ [0, 0, 0], [0, 0, 0], [0, 0, 0] ];
			_hasWinner = false;
		}
		
		private function renderGrid():void
		{
			var gx:uint;
			var gval:uint;
			for ( var gy:uint = 0; gy < 3; ++gy )
			{
				for ( gx = 0; gx < 3; ++gx )
				{
					gval = grid[gy][gx];
					if ( gval > 0 )
					{
						gridBitMapData.copyPixels(
								gridElements[gval-1].bitmapData,
								new Rectangle(0, 0, gridElements[gval-1].width, gridElements[gval-1].height),
								new Point(10 + (gx * 130), 10 + (gy * 130))
								);
					}
				}
			}
		}
		
		private function onMouseClick(e:MouseEvent):void
		{
			var px:uint = e.localX / 130;
			var py:uint = e.localY / 130;
			if ( ! _hasWinner && ! grid[py][px] )
			{
				grid[py][px] = ++currentPlayer;
				currentPlayer &= 1;
				renderGrid();
				checkWin();
			}
		}
		
		public function hasWinner():Boolean
		{
			return _hasWinner;
		}
		
		public function getWinner():uint
		{
			return winner;
		}
		
		private function checkWin():void
		{
			for ( var line:uint = 0; line < 3; ++line )
			{
				if ( isHorizLine(line) )
				{
					_hasWinner = true;
					winner = grid[line][0] - 1;
				}
				else if ( isVertLine(line) )
				{
					_hasWinner = true;
					winner = grid[0][line] - 1;
				}
			}

			if ( grid[0][0] > 0 && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] )
			{
				_hasWinner = true;
				winner = grid[0][0] - 1;
			}

			if ( grid[0][2] > 0 && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0] )
			{
				_hasWinner = true;
				winner = grid[0][2] - 1;
			}
		}
		
		private function isHorizLine(line:uint):Boolean
		{
			return grid[line][0] > 0 && grid[line][0] == grid[line][1] && grid[line][1] == grid[line][2];
		}

		private function isVertLine(line:uint):Boolean
		{
			return grid[0][line] > 0 && grid[0][line] == grid[1][line] && grid[1][line] == grid[2][line];
		}
		
		private function aiMove():void
		{
			
		}
		
	}
	
}