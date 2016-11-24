package  
{
	import Box2D.Dynamics.b2Body;
	import flash.display.DisplayObject;
	import flash.events.EventDispatcher;
	/**
	 * ...
	 * @author Aaron Perez Sanchez
	 */
	public class Actor extends EventDispatcher
	{
		
		protected var _body:b2Body;
		protected var _displayable:DisplayObject;
		
		public function Actor(body:b2Body, displayable:DisplayObject) 
		{
			_body = body;
			_displayable = displayable;
			
			updateDisplayable();
		}
		
		public function updateNow():void
		{
			//if ( ! _body.IsStatic() ) // XXX WARNING
			//{
				updateDisplayable();
			//}
			
			customUpdate();
		}
		
		protected function customUpdate():void
		{
			// used by children.
		}
		
		public function destroy():void
		{
			// remove from world
			// TODO: finish this
		}
		
		private function updateDisplayable():void
		{
			_displayable.x = _body.GetPosition().x * Physics.PIX_RATIO;
			_displayable.y = _body.GetPosition().y * Physics.PIX_RATIO;
			_displayable.rotation = _body.GetAngle() * 180 / Math.PI;
		}
		
	}

}