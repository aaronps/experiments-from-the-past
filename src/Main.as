package 
{
	import Box2D.Collision.b2AABB;
	import Box2D.Collision.Shapes.b2CircleDef;
	import Box2D.Collision.Shapes.b2MassData;
	import Box2D.Dynamics.b2Body;
	import Box2D.Dynamics.b2BodyDef;
	import flash.display.Shape;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	
	/**
	 * ...
	 * @author Aaron Perez Sanchez
	 */
	public class Main extends Sprite 
	{
		
		private var _coinActor:CoinActor;
		private var _actors:Array;
		
		private var _testshape:Shape;
		
		private var _levelData:Array =
		[
			[ 120, 120 ], [ 80, 130 ], [ 100, 140 ], [64, 30]
		];
		
		public function Main():void 
		{
			if (stage) init();
			else addEventListener(Event.ADDED_TO_STAGE, init);
		}
		
		private function init(e:Event = null):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, init);
			// entry point
			
			setupPhysics();
			
			_actors = new Array();
			
			createCoin();
			createLevel();
			
			addEventListener(Event.ENTER_FRAME, onFrameEnter);
			stage.addEventListener(MouseEvent.MOUSE_DOWN, onMouseDown);
			
			//graphics.beginFill(0x00ff00);
			//graphics.drawCircle(25, 25, 10);
			//graphics.endFill();
			
		}
		
		private function onMouseDown(e:MouseEvent):void 
		{
			if ( e.stageY > 100 )
			{
				trace("Adding pin at " + e.stageX + "," + e.stageY);
				_actors.push( new PinActor(this, new Point(e.stageX, e.stageY)));
			}
			else
			{
				trace("Adding coin at " + e.stageX + "," + e.stageY);
				_actors.push( new CoinActor(this, new Point(e.stageX, e.stageY), new Point(0,0)));
			}
		}
		
		private function createLevel():void
		{
			for each ( var p:Array in _levelData )
			{
				_actors.push( new PinActor(this, new Point(p[0], p[1])));
			}
			
			var vertWall:Array =
			[
				[ [0,0], [10,0], [10,320], [0,320] ]
			];
			
			_actors.push(new StaticActor(this, new Point(0, 0), vertWall));
			_actors.push(new StaticActor(this, new Point(390, 0), vertWall));
			
			var floor:Array =
			[
				[ [0,0], [400,0], [400,10], [0,10] ]
			];

			_actors.push(new StaticActor(this, new Point(0, 310), floor));
			
			var lefttRamp:Array =
			[
				[ [0,0], [170,20], [160,25], [0,5] ]
			];
			
			_actors.push(new StaticActor( this, new Point(0, 40), lefttRamp));
			
			var rightRamp:Array =
			[
				[ [0, 20], [170, 0], [170, 5], [10, 25] ]
			];
			
			_actors.push(new StaticActor( this, new Point(230, 40), rightRamp));
			
			_actors.push(new ChannelActor(this, new Point(200, 65), 15, 165 ));
			//_actors.push(new ChannelActor(this, new Point(170, 65), 35, 145 ));
			
		}
		
		private function onFrameEnter(e:Event):void 
		{
			Physics.world.Step(1 / Physics.FPS, 10);
			
			for each ( var actor:Actor in _actors )
			{
				actor.updateNow();
			}
			
		}
		
		private function createCoin():void
		{	
			_coinActor = new CoinActor(this, new Point(20, 20), new Point(10, -10));
			_actors.push(_coinActor);
			
		}
		
		private function setupPhysics():void
		{
			Physics.createWorld(9.8);
		}
		
	}
	
}