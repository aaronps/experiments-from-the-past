package 
{
	import aps.thefactory.Factory;
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.events.TimerEvent;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	import flash.utils.getTimer;
	import flash.utils.Timer;
	
	/**
	 * ...
	 * @author Aaron Perez Sanchez
	 */
	public class Main extends Sprite 
	{
		private var curframe:uint;
		
		private var canvas:BitmapData;
		private var canvasBM:Bitmap;

		private var factory:Factory;
		
		private var lastFrameTime:int;
		
		public static const FRAME_RATE:int = 60;
		private var gameTimer:Timer;
		private var timerPeriod:Number = 1000 / FRAME_RATE;
		private var prevTime:int = 0;
		private var afterTime:int = 0;
		private var timeDiff:int = 0;
		private var sleepTime:int = 0;
		private var overSleepTime:int = 0;
		private var timeExcess:int = 0;
		
		public function Main():void 
		{
			if (stage) init();
			else addEventListener(Event.ADDED_TO_STAGE, init);
		}
		
		private function init(e:Event = null):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, init);
			// entry point
			canvas = new BitmapData(640, 480, false, 0);
			canvasBM = new Bitmap(canvas);
			addChild(canvasBM);
			curframe = 0;
			
			factory = new Factory();
			
			//addEventListener(Event.ENTER_FRAME, onFrame);
			stage.addEventListener(KeyboardEvent.KEY_DOWN, onKeyEvent);
			stage.addEventListener(KeyboardEvent.KEY_UP, onKeyEvent);
			lastFrameTime = 0; // getTimer();
			gameTimer = new Timer(timerPeriod, 1);
			
			gameTimer.addEventListener(TimerEvent.TIMER, mainLoop);
			gameTimer.start();

		}
		
		private function mainLoop(e:TimerEvent):void
		{
			prevTime = getTimer();
			overSleepTime = ( prevTime - afterTime ) - sleepTime;
			
			factory.logic(timerPeriod);
			
			canvas.lock();
			canvas.fillRect(canvas.rect, 0);
			factory.draw(canvas);
			canvas.unlock();
			
			afterTime = getTimer();
			timeDiff = afterTime - prevTime;
			sleepTime = ( timerPeriod - timeDiff ) - overSleepTime;
			if ( sleepTime <= 0 )
			{
				timeExcess -= sleepTime;
				sleepTime = 2;
			}
			
			gameTimer.reset();
			gameTimer.delay = sleepTime;
			gameTimer.start();
			
			while ( timeExcess > timerPeriod )
			{
				// do movement things.
				factory.logic(timerPeriod);
				timeExcess -= timerPeriod;
			}
			
			e.updateAfterEvent();
		}
		
		private function onKeyEvent(e:KeyboardEvent):void
		{
			switch ( e.keyCode )
			{
				case 81: // Q
					factory.firstElevatorUp( e.type == KeyboardEvent.KEY_DOWN );
					break;
				case 65: // A
					factory.firstElevatorDown( e.type == KeyboardEvent.KEY_DOWN );
					break;
				case 80: // P
					factory.secondElevatorUp( e.type == KeyboardEvent.KEY_DOWN );
					break;
				case 76: // L
					factory.secondElevatorDown( e.type == KeyboardEvent.KEY_DOWN );
					break;
				case 32: // " "
					if ( e.type == KeyboardEvent.KEY_DOWN )
					{
						factory.switchPause();
					}
					break;
			}
			
		}
		
	}
	
}