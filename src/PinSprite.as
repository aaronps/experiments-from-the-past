package  
{
	import flash.display.Sprite;
	
	/**
	 * ...
	 * @author Aaron Perez Sanchez
	 */
	public class PinSprite extends Sprite
	{
		
		public function PinSprite() 
		{
			super();
			graphics.lineStyle(1.5);
			graphics.beginFill(0xC0C0C0,1);
			graphics.drawCircle(0, 0, 8);
			graphics.endFill();
		}
		
	}

}