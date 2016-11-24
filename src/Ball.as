package  
{
	import flash.display.Graphics;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	
	/**
	 * ...
	 * @author Aaron Perez Sanchez
	 */
	public class Ball 
	{
		private var pos:Point;
		private var speed:Point;
		private var startPos:Point;
		private var ballRect:Rectangle;
		private var stageRect:Rectangle;
		private var ballrad:Number;
		
		public function get x():Number { return pos.x; }
		public function get y():Number { return pos.y; }
		public function get xspeed():Number { return speed.x; }
		
		public function Ball(x:int, y:int, stageRect:Rectangle ) 
		{
			pos = new Point(x, y);
			startPos = pos.clone();
			
			this.stageRect = stageRect;
			
			speed = new Point( -4, -1);
			ballrad = 3;
			
			ballRect = new Rectangle(x-(ballrad/2), y-(ballrad/2), ballrad, ballrad);
		}
		
		public function reset():void
		{
			pos.x = startPos.x;
			pos.y = startPos.y;
			ballRect.x = pos.x - (ballrad / 2);
			ballRect.y = pos.y - (ballrad / 2);
			speed.x = -4;
			speed.y = -1;
		}
		
		public function move():void
		{
			pos.offset(speed.x, speed.y);

			if ( pos.x < stageRect.left)
			{
				pos.x = stageRect.left;
				speed.x = -speed.x;
			}
			
			if ( pos.y < stageRect.top)
			{
				pos.y = stageRect.top;
				speed.y = -speed.y;
			}
			
			if ( pos.x > stageRect.right )
			{
				pos.x = stageRect.right;
				speed.x = -speed.x;
			}
			
			if ( pos.y > stageRect.bottom )
			{
				pos.y = stageRect.bottom;
				speed.y = -speed.y;
			}
			
			ballRect.x = pos.x - (ballrad / 2);
			ballRect.y = pos.y - (ballrad / 2);
		}
		
		public function draw(g:Graphics):void
		{
			g.beginFill(0xffffff);
			g.drawCircle(pos.x, pos.y, ballrad);
			g.endFill();
		}
		
		public function collide(p:Player):Boolean
		{
			if ( p.prect.intersects(ballRect) )
			{
				// split the rect of the player in 5 zones and see where it hit
				var plength:Number = p.prect.height
				
				// on corner hit, y is added double
				var cornerhit:Number = plength / 10; // = 10%
				
				//on halfhit, y is added little
				var halfhit:Number = cornerhit * 4; // = 20%
				
				// top corner hit
				if ( pos.y < p.prect.top + cornerhit)
				{
					speed.y -= (speed.y/2)+2;
				}
				else if ( pos.y > p.prect.bottom - cornerhit )
				{
					speed.y += (speed.y/2)+2;
				}
				else if ( pos.y < p.prect.top + halfhit )
				{
					speed.y -= (speed.y/2)+1;
				}
				else if ( pos.y > p.prect.bottom - halfhit )
				{
					speed.y += (speed.y/2)+1;
				}
				
				speed.x = -speed.x;
				return true;
			}
			return false;
		}
		
	}
	
}