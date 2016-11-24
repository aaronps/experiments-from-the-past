package 
{
	import flash.display.Bitmap;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.net.URLRequest;
	import flash.text.TextField;
	
	import flash.display.Loader;
	
	/**
	 * ...
	 * @author Aaron Perez Sanchez
	 */
	public class Main extends Sprite 
	{
		private var tf:TextField;
		private var tfg:TextField;
		
		[Embed(source = "emb_images/title.png")]
		private var titleImageClass:Class;
		private var titleImage:Bitmap = new titleImageClass();
		
		private var gameGrid:GameGrid;
		
		public function Main():void 
		{
			if (stage) init();
			else addEventListener(Event.ADDED_TO_STAGE, init);
		}
		
		private function init(e:Event = null):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, init);
			// entry point
			
			addChild(titleImage);
			
			gameGrid = new GameGrid(212,150);
			addChild(gameGrid);
			
			tf = new TextField();
			tf.wordWrap = true;
			tf.multiline = true;
			tf.textColor = 0xffffff;
			tf.width = 100;
			tf.y = 200;
			addChild(tf);
			
			tfg = new TextField();
			tfg.text = "Grid";
			tfg.wordWrap = true;
			tfg.multiline = true;
			tfg.textColor = 0xffffff;
			tfg.width = 100;
			tfg.y = 250;
			addChild(tfg);
			
			graphics.beginFill(0);
			graphics.drawRect(0, 0, 612, 550);
			graphics.endFill();
			
			stage.addEventListener(MouseEvent.MOUSE_MOVE, onMouseMove);
			stage.addEventListener(Event.ENTER_FRAME, onFrameEnter);
		}
		
		private function onFrameEnter(e:Event):void
		{
			if ( gameGrid.hasWinner() )
			{
				tfg.text = "Player " + gameGrid.getWinner() + " wins";
			}
		}
		
		private function onMouseMove(e:MouseEvent):void
		{
			tf.text = "Pos= "
				+ e.localX + "," + e.localY
				+ " -- "
				+ e.stageX + "," + e.stageY;
		}

		private function onMouseGridClick(e:MouseEvent):void
		{
			tfg.text = "Pos= "
				+ e.localX + "," + e.localY
				+ " -- "
				+ e.stageX + "," + e.stageY;
		}
				
	}
	
}