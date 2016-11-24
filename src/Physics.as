package  
{
	import Box2D.Collision.b2AABB;
	import Box2D.Common.Math.b2Vec2;
	import Box2D.Dynamics.b2World;
	/**
	 * ...
	 * @author Aaron Perez Sanchez
	 */
	public final class Physics
	{
		public static const FPS:int = 30;
		public static const PIX_RATIO:int = 30;
		private static var _world:b2World;
		
		public static function createWorld(gravity:Number):void
		{
			var bounds:b2AABB = new b2AABB();
			bounds.lowerBound.Set( -2000/PIX_RATIO, -2000/PIX_RATIO);
			bounds.upperBound.Set( 2000/PIX_RATIO, 2000/PIX_RATIO);
			
			var g:b2Vec2 = new b2Vec2(0, gravity);
			var allowSleep:Boolean = true;
			_world = new b2World(bounds, g, allowSleep);
		}
		
		public static function get world():b2World { return _world; }
		
	}

}