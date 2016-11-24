package 
{
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.ProgressEvent;
	import flash.utils.getDefinitionByName;
	
	/**
	 * ...
	 * @author Aaron Perez Sanchez
	 */
	public class Preloader extends MovieClip 
	{
		
		public function Preloader() 
		{
			addEventListener(Event.ENTER_FRAME, checkFrame);
			loaderInfo.addEventListener(ProgressEvent.PROGRESS, progress);
			// show loader
		}
		
		private function progress(e:ProgressEvent):void 
		{
			var xpos:uint = (stage.stageWidth / 2) - (102/2);
			var ypos:uint = (stage.stageHeight / 2) - (12/2);
			
			graphics.clear();
			graphics.beginFill(0);
			graphics.drawRect(xpos, ypos, 102, 12);
			graphics.beginFill(0xffffff);
			graphics.drawRect(xpos+1, ypos+1, ((e.bytesLoaded * 100) / e.bytesTotal), 10);
			graphics.endFill();

		}
		
		private function checkFrame(e:Event):void 
		{
			if (currentFrame == totalFrames) 
			{
				removeEventListener(Event.ENTER_FRAME, checkFrame);
				startup();
			}
		}
		
		private function startup():void 
		{
			// hide loader
			stop();
			loaderInfo.removeEventListener(ProgressEvent.PROGRESS, progress);
			var mainClass:Class = getDefinitionByName("Main") as Class;
			addChild(new mainClass() as DisplayObject);
		}
		
	}
	
}