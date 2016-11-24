package  
{
	import flash.display.Stage;
	import flash.events.KeyboardEvent;
	
	/**
	 * ...
	 * @author Aaron Perez Sanchez
	 */
	public class Keyboard 
	{
		
		public static var keys:Array = new Array(256);
		
		public static function initialize(s:Stage):void
		{
			s.addEventListener(KeyboardEvent.KEY_DOWN, keyPress);
			s.addEventListener(KeyboardEvent.KEY_UP, keyRelease);
		}
		
		private static function keyPress(e:KeyboardEvent):void
		{
			keys[e.keyCode] = true;			
		}
		
		private static function keyRelease(e:KeyboardEvent):void
		{
			keys[e.keyCode] = false;
		}

	}
	
}