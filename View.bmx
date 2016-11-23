SuperStrict

Type View
	Field parent:View
	Field x:Int
	Field y:Int
	Field width:Int
	Field height:Int
	
	Method draw() Abstract

	Method setParent( parent:View )
		Self.parent = parent
	EndMethod

	Method onMouseIn()
	EndMethod
	Method onMouseOut()
	EndMethod
	Method onMouseButton( mx:Int, my:Int) 
	EndMethod
	Method onMouseMove( mx:Int, my:Int)
	EndMethod

EndType

Type ViewGroup Extends View
	Field childlist:TList = New TList
	Field mouseview:View

	Method addChild( child:View )
		childlist.addlast(child)
	EndMethod
	
	Method removeChild( child:View )
		childlist.Remove(child)
		If mouseview = child Then mouseview = Null
	EndMethod
	
	Method draw() Final
		SetOrigin( x, y )
		For Local v:View = EachIn childlist
			v.draw()
		Next
	EndMethod
	
	Method onMouseOut()
		If mouseview Then
			mouseview.onMouseOut()
			mouseview = Null
		EndIf
	EndMethod

	Method onMouseButton( mx:Int, my:Int ) Final
		If mouseview Then
			mouseview.onMouseButton ( mx - mouseview.x, my - mouseview.y )
		EndIf
	EndMethod

	Method onMouseMove( mx:Int, my:Int ) Final
		Local vlink:TLink = childlist.LastLink()
		Local found:Int = 0
		While vlink
			Local v:View = View(vlink.Value())
			If mx >= v.x And mx <= v.x+v.width And my >= v.y And my <= v.y+v.height Then
				If v <> mouseview Then
					If mouseview Then mouseview.onMouseOut()
					v.onMouseIn()
					mouseview = v
				EndIf
				mouseview.onMouseMove ( mx - v.x, my - v.y )
				found = 1
 				Exit
			EndIf
			vlink = vlink.PrevLink()
		Wend
		If Not found And mouseview Then
			mouseview.onMouseOut()
			mouseview = Null
		EndIf
	EndMethod
EndType

Type ViewManager
	Global views:ViewGroup
	
	Function init()
		If Not views Then views = New ViewGroup
		' WARNING!!! if size is smaller than before maybe some childs are out of view
		GetViewport( views.x, views.y, views.width, views.height )
	EndFunction
	
	Function draw()
		views.draw()
	EndFunction
	
	Function onMouseMove( x:Int, y:Int )
		views.onMouseMove(x,y)
	EndFunction
	
	Function onMouseButton( x:Int, y:Int )
		views.onMouseButton( x, y )
	EndFunction
	
	Function addView ( v:View )
		views.addChild(v)
	EndFunction
	
	Function removeView( v:View )
		views.removeChild( v )
	EndFunction

EndType