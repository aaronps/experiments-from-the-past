package  
{
	import Box2D.Collision.Shapes.b2PolygonDef;
	import Box2D.Collision.Shapes.b2ShapeDef;
	import Box2D.Common.Math.b2Vec2;
	import Box2D.Dynamics.b2Body;
	import Box2D.Dynamics.b2BodyDef;
	import flash.display.DisplayObjectContainer;
	import flash.display.Sprite;
	import flash.geom.Point;
	/**
	 * ...
	 * @author Aaron Perez Sanchez
	 */
	public class StaticActor extends Actor
	{
		
		public function StaticActor(parent:DisplayObjectContainer, location:Point, coords:Array) 
		{
			var body:b2Body = createBodyFromCoordinates(coords, location);
			
			var sprite:Sprite = createSpriteFromCoordinates(coords, location, parent);
			
			super(body, sprite);
		}
		
		private function createSpriteFromCoordinates(coords:Array, location:Point, parent:DisplayObjectContainer):Sprite
		{
			var newSprite:Sprite = new Sprite();
			
			newSprite.graphics.lineStyle(1, 0xE0DDA0);
			
			for each ( var shapePoints:Array in coords )
			{
				var firstPoint:Point = new Point(shapePoints[0][0], shapePoints[0][1]);
				newSprite.graphics.moveTo(firstPoint.x, firstPoint.y);
				newSprite.graphics.beginFill(0xED9C94);
				
				for each ( var newPoint:Array in shapePoints )
				{
					newSprite.graphics.lineTo(newPoint[0], newPoint[1]);
				}
				
				newSprite.graphics.lineTo(firstPoint.x, firstPoint.y);
				newSprite.graphics.endFill();
			}
			
			newSprite.x = location.x;
			newSprite.y = location.y;
			parent.addChild(newSprite);
			
			return newSprite;
		}
		
		private function createBodyFromCoordinates(coords:Array, location:Point):b2Body
		{
			var shapes:Array = new Array();
			
			for each ( var shapePoints:Array in coords )
			{
				var newShape:b2PolygonDef = new b2PolygonDef();
				newShape.vertexCount = shapePoints.length;
				for ( var i:int = 0; i < shapePoints.length; ++i )
				{
					newShape.vertices[i].Set(shapePoints[i][0] / Physics.PIX_RATIO,
											 shapePoints[i][1] / Physics.PIX_RATIO);
					
				}
				
				newShape.density = 0;
				newShape.friction = 1;
				newShape.restitution = 0.2;
				
				shapes.push(newShape);
			}
			
			var bodyDef:b2BodyDef = new b2BodyDef();
			bodyDef.position.Set(location.x / Physics.PIX_RATIO, location.y / Physics.PIX_RATIO);
			
			var body:b2Body = Physics.world.CreateBody(bodyDef);
			
			for each ( var s:b2ShapeDef in shapes )
			{
				body.CreateShape(s);
			}
			
			body.SetMassFromShapes();
			
			return body;
		}
		
	}

}