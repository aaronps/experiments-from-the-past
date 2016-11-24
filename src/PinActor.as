package  
{
	import Box2D.Collision.Shapes.b2CircleDef;
	import Box2D.Common.Math.b2Vec2;
	import Box2D.Dynamics.b2Body;
	import Box2D.Dynamics.b2BodyDef;
	import flash.display.DisplayObjectContainer;
	import flash.display.Shape;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	/**
	 * ...
	 * @author Aaron Perez Sanchez
	 */
	public class PinActor extends Actor
	{
		public static const PIN_DIAMETER:int = 8;
		
		public function PinActor(parent:DisplayObjectContainer, location:Point)
		{
			var pinSprite:Sprite = new PinSprite();
			pinSprite.scaleX = PIN_DIAMETER / pinSprite.width;
			pinSprite.scaleY = PIN_DIAMETER / pinSprite.height;
			pinSprite.addEventListener(MouseEvent.MOUSE_DOWN, onMouseDown);
			pinSprite.addEventListener(MouseEvent.MOUSE_UP, onMouseUp);
			parent.addChild(pinSprite);
			
			var pinShapeDef:b2CircleDef = new b2CircleDef();
			pinShapeDef.radius = PIN_DIAMETER / 2 / Physics.PIX_RATIO;
			pinShapeDef.density = 0;
			pinShapeDef.friction = 0;
			pinShapeDef.restitution = 0.2;
			
			var pinBodyDef:b2BodyDef = new b2BodyDef()
			pinBodyDef.position.Set(location.x/Physics.PIX_RATIO, location.y/Physics.PIX_RATIO);
			
			var pinBody:b2Body = Physics.world.CreateBody(pinBodyDef);
			pinBody.CreateShape(pinShapeDef);
			pinBody.SetMassFromShapes();
			
			super(pinBody, pinSprite);
			
		}
		
		private function onMouseDown(e:MouseEvent):void 
		{
			Sprite(_displayable).startDrag();
			_displayable.addEventListener(MouseEvent.MOUSE_MOVE, onDragMouseMove);
			e.stopPropagation();
		}
		
		private function onDragMouseMove(e:MouseEvent):void 
		{
			var pv:b2Vec2 = new b2Vec2(e.stageX / Physics.PIX_RATIO, e.stageY / Physics.PIX_RATIO);
			_body.SetXForm( pv, 0);
			e.updateAfterEvent();
		}
		
		private function onMouseUp(e:MouseEvent):void 
		{
			Sprite(_displayable).stopDrag();
			_displayable.removeEventListener(MouseEvent.MOUSE_MOVE, onDragMouseMove);
		}
		
	}

}