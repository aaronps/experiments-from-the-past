package  
{
	import Box2D.Collision.Shapes.b2PolygonDef;
	import Box2D.Collision.Shapes.b2ShapeDef;
	import Box2D.Dynamics.b2Body;
	import Box2D.Dynamics.b2BodyDef;
	import flash.display.DisplayObjectContainer;
	import flash.display.Sprite;
	import flash.geom.Point;
	/**
	 * ...
	 * @author Aaron Perez Sanchez
	 */
	public class ChannelActor extends Actor
	{
		private var _direction:Number;
		private var _min_angle:Number;
		private var _max_angle:Number;
		
		public function ChannelActor(parent:DisplayObjectContainer, location:Point, min_angle:Number, max_angle:Number) 
		{
			_min_angle = min_angle * Math.PI / 180;
			_max_angle = max_angle * Math.PI / 180;
			var sprite:Sprite = new Sprite();
			sprite.graphics.lineStyle(1.0, 0xC5C2BC);
			sprite.graphics.beginFill(0xC5C2BC, 1);
			sprite.graphics.drawRect(-16, -25, 100, 5);
			sprite.graphics.drawRect(-16, 20, 100, 5);
			sprite.graphics.endFill();
			
			parent.addChild(sprite);
			
			var shapeDef:b2PolygonDef = new b2PolygonDef();
			shapeDef.vertexCount = 4;
			shapeDef.vertices[0].Set(-16/Physics.PIX_RATIO, -25/Physics.PIX_RATIO);
			shapeDef.vertices[1].Set((100-16)/Physics.PIX_RATIO, -25/Physics.PIX_RATIO);
			shapeDef.vertices[2].Set((100-16)/Physics.PIX_RATIO, -20/Physics.PIX_RATIO);
			shapeDef.vertices[3].Set(-16/Physics.PIX_RATIO, -20/Physics.PIX_RATIO);
			
			shapeDef.density = 0;
			shapeDef.friction = 0;
			shapeDef.restitution = 0.3;
			
			var bodyDef:b2BodyDef = new b2BodyDef();
			bodyDef.position.Set(location.x/Physics.PIX_RATIO, location.y/Physics.PIX_RATIO);			
			bodyDef.angle = _min_angle;
			
			var body:b2Body = Physics.world.CreateBody(bodyDef);
			body.CreateShape(shapeDef);
			shapeDef.vertices[0].Set(-16/Physics.PIX_RATIO, 20/Physics.PIX_RATIO);
			shapeDef.vertices[1].Set((100-16)/Physics.PIX_RATIO, 20/Physics.PIX_RATIO);
			shapeDef.vertices[2].Set((100-16)/Physics.PIX_RATIO, 25/Physics.PIX_RATIO);
			shapeDef.vertices[3].Set(-16/Physics.PIX_RATIO, 25/Physics.PIX_RATIO);
			body.CreateShape(shapeDef);
			
			body.SetMassFromShapes();
			
			_direction = 1;
			
			super(body, sprite);
		}
	
		override protected function customUpdate():void 
		{
			var oldAngle:Number = _body.GetAngle();
			
			oldAngle += 0.05 * _direction;
			if ( oldAngle >= _max_angle )
			{
				oldAngle = _max_angle;
				_direction = -_direction;
			}
			else if ( oldAngle <= _min_angle )
			{
				oldAngle = _min_angle;
				_direction = -_direction;
			}
			
			_body.SetXForm(_body.GetPosition(), oldAngle);
			
			
			
			super.customUpdate();
		}
		
	}

}