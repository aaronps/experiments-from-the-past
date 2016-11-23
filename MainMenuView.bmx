SuperStrict

Import "View.bmx"
Import "Logic.bmx"

Incbin "title.png"

Type MainMenuView Extends ViewGroup

	Method New()
		GetViewport( x, y, width, height )
		addChild( New MainMenuTitle )
	EndMethod
	

EndType

Type MainMenuTitle Extends View
	Field titlealpha:Double
	Field title:TImage
	Field fade:FadeLogic
	
	Method New()
		titlealpha = 0.0
		If Not title title = LoadImage("incbin::title.png")
		width = title.width
		height = title.height
		Local vx:Int
		Local vy:Int
		Local vw:Int
		Local vh:Int
		GetViewport( vx, vy, vw, vh )
		x = (vw/2) - (width/2) + vx
		y = (vh/2) - (height/2) + vy
		fade = FadeLogic.create( Self )
		LogicManager.addLogicTask( fade )
	EndMethod
	
	Method draw()
		SetAlpha( titlealpha )
		DrawImage( title, x, y )
	EndMethod

EndType

Type FadeLogic Extends LogicTask
	Field owner:MainMenuTitle
	
	Function Create:FadeLogic( o:MainMenuTitle )
		Local t:FadeLogic = New FadeLogic
		t.owner = o
		Return t
	EndFunction
	
	Method run( ms:Int )
		owner.titlealpha:+0.015
		If owner.titlealpha > 1.0 Then
			owner.titlealpha = 1.0
			LogicManager.removeLogicTask( Self )
		EndIf
	EndMethod
EndType
