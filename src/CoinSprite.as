package  
{
	import flash.display.Shape;
	
	/**
	 * ...
	 * @author Aaron Perez Sanchez
	 */
	public class CoinSprite extends Shape
	{
		
		public function CoinSprite() 
		{
			super();
			graphics.lineStyle(2.0);
			graphics.beginFill(0x4A93CE,1);
			graphics.drawCircle(0, 0, 16);
			graphics.endFill();
		}
	}

}