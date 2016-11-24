package  
{
	import Box2D.Collision.Shapes.b2CircleDef;
	import Box2D.Common.Math.b2Vec2;
	import Box2D.Dynamics.b2Body;
	import Box2D.Dynamics.b2BodyDef;
	import flash.display.DisplayObjectContainer;
	import flash.display.Shape;
	import flash.display.Sprite;
	import flash.geom.Point;
	/**
	 * ...
	 * @author Aaron Perez Sanchez
	 */
	public class CoinActor extends Actor
	{
		private static const COIN_DIAMETER:int = 32;
		
		public function CoinActor(parent:DisplayObjectContainer, location:Point, velocity:Point) 
		{
			var coinSprite:Shape = new CoinSprite();
			coinSprite.scaleX = COIN_DIAMETER / coinSprite.width;
			coinSprite.scaleY = COIN_DIAMETER / coinSprite.height;
			parent.addChild(coinSprite);
			
			var coinShapeDef:b2CircleDef = new b2CircleDef();
			coinShapeDef.radius = COIN_DIAMETER / 2 / Physics.PIX_RATIO;
			coinShapeDef.density = 10;
			coinShapeDef.friction = 0.8;
			coinShapeDef.restitution = 0.2;
			
			var coinBodyDef:b2BodyDef = new b2BodyDef()
			coinBodyDef.position.Set(location.x/Physics.PIX_RATIO, location.y/Physics.PIX_RATIO);
			
			var coinBody:b2Body = Physics.world.CreateBody(coinBodyDef);
			coinBody.CreateShape(coinShapeDef);
			coinBody.SetMassFromShapes();
			
			var vVect:b2Vec2 = new b2Vec2(velocity.x / Physics.PIX_RATIO, velocity.y / Physics.PIX_RATIO);
			coinBody.SetLinearVelocity(vVect);
			
			super(coinBody, coinSprite);
			
		}
	
		override protected function customUpdate():void 
		{
			if ( _displayable.y > _displayable.stage.stageHeight )
			{
				//trace("Coin Out");
			}
			super.customUpdate();
		}
		
	}

}