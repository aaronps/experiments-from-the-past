package  
{
	import flash.display.Graphics;
	import flash.geom.Rectangle;
	
	/**
	 * ...
	 * @author Aaron Perez Sanchez
	 */
	public class Player 
	{
		private var pscore:int;
		private var pname:String;

		private var stageRect:Rectangle;
		public var prect:Rectangle;
		public var isRealPlayer:Boolean;
		
		public function Player(name:String, xpos:int, stageRect:Rectangle )
		{
			this.stageRect = stageRect;
			isRealPlayer = false;
			
			pscore = 0;
			pname = name;
			
			prect = new Rectangle(xpos, 100, 5, 40);
			
		}
		
		public function get score():int
		{
			return pscore;
		}
		
		public function resetScore():void
		{
			pscore = 0;
		}
		
		public function getScoreString():String
		{
			return pname + ": " + pscore; // + "--" + stageRect.width + "," + stageRect.height;
		}
		
		public function addScore(score:int):void
		{
			pscore += score;
		}
		
		public function move(ball:Ball):void
		{
			if ( isRealPlayer )
			{
				if ( Keyboard.keys[65] ) // 'A'
				{
					moveDown();
				}
				
				if ( Keyboard.keys[81]) // 'Q'
				{
					moveUp();
				}
			}
			else
			{
				if (   (ball.x > prect.x && ball.x < stageRect.right-50 && ball.xspeed < 0)
					|| (ball.x < prect.x && ball.x > stageRect.left+50 && ball.xspeed > 0) )
				{
					if ( ball.y < prect.top + (prect.height / 6) )
					{
						moveUp();
					}
					else if ( ball.y > prect.bottom - (prect.height / 6) )
					{
						moveDown();
					}
				}
			}
				/*
			}
			if ( Keyboard.keys[76] ) // 'L'
			{
				player2.moveDown();
			}
			
			if ( Keyboard.keys[80]) // 'P'
			{
				player2.moveUp();
			}
*/

		}
		
		public function moveUp():void
		{
			prect.y -= 3;
			if ( prect.y < stageRect.top )
			{
				prect.y = stageRect.top;
			}
		}
		
		public function moveDown():void
		{
			prect.y += 3;
			if ( prect.bottom > stageRect.bottom )
			{
				prect.y = stageRect.bottom - prect.height;
			}
		}
			
		public function draw(g:Graphics):void
		{
			g.beginFill(0xffffff);
			g.drawRect(prect.x, prect.y, prect.width, prect.height);
			g.endFill();
			if ( prect.x > 100 )
			{
				g.beginFill(0xff0000);
				g.drawRect(0, prect.y + prect.height / 2, stageRect.width, 2);
				g.endFill();
			}
		}
		
	}
	
}