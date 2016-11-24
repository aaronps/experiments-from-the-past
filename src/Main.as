package 
{
	import flash.display.Sprite;
	import flash.events.Event;
	import eyebreaker.gameview;
	
	/**
	 * ...
	 * @author Aaron Perez Sanchez
	 */
	public class Main extends Sprite 
	{
		private var gview:gameview;
		public function Main():void 
		{
			if (stage) init();
			else addEventListener(Event.ADDED_TO_STAGE, init);
		}
		
		private function init(e:Event = null):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, init);
			gview = new gameview();
			addChild(gview);
			// entry point
		}
		
	}
	
}