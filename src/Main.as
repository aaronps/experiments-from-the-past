package 
{
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.geom.Rectangle;
	import flash.text.TextField;
	
	/**
	 * ...
	 * @author Aaron Perez Sanchez
	 */
	public class Main extends Sprite 
	{
		private var player1:Player;
		private var player2:Player;
		private var ball:Ball;
		
		private var player1text:TextField;
		private var player2text:TextField;
		
		public function Main():void 
		{
			if (stage) init();
			else addEventListener(Event.ADDED_TO_STAGE, init);
		}
		
		private function init(e:Event = null):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, init);
			// entry point
			
			Keyboard.initialize(stage);
			
			var grect:Rectangle = new Rectangle(0, 0, stage.stageWidth, stage.stageHeight);
			
			player1 = new Player("Player", 0, grect);
			player2 = new Player("Computer", stage.stageWidth - 5, grect);
			ball = new Ball(stage.stageWidth / 2, stage.stageHeight / 2, grect);
			
			player1text = new TextField();
			player2text = new TextField();
			player1text.selectable = false;
			player2text.selectable = false;
			player1text.textColor = 0xffffff;
			player2text.textColor = 0xffffff;
			resetStats();
			
			player1text.x = stage.stageWidth / 8;
			player2text.x = stage.stageWidth - ( stage.stageWidth / 4);
			addChild(player1text);
			addChild(player2text);
			player1.isRealPlayer = true;
			addEventListener(Event.ENTER_FRAME, onFrameEnter);
		}
		
		private function resetStats():void
		{
			player1.resetScore();
			player2.resetScore();
			updateScoreText();
		}
		
		private function updateScoreText():void
		{
			player1text.text = player1.getScoreString();
			player2text.text = player2.getScoreString();
		}
			
		private function onFrameEnter(e:Event):void
		{
			player1.move(ball);
			player2.move(ball);
			ball.move();
			
			if ( ! ball.collide(player1) && ! ball.collide(player2) )
			{
				if ( ball.x < 2 )
				{
					player2.addScore(1);
					updateScoreText();
					ball.reset();
				}
				
				if ( ball.x > stage.stageWidth-2 )
				{
					player1.addScore(1);
					updateScoreText();
					ball.reset();
				}
			}			
			draw();
		}
		
		private function draw():void
		{
			graphics.clear();
			player1.draw(graphics);
			player2.draw(graphics);
			ball.draw(graphics);
		}
		
	}
	
}