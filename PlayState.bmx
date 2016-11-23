SuperStrict

Import "State.bmx"
Import "Particle.bmx"

Import "View.bmx"

Incbin "tiles.png"
Incbin "border.png"
Incbin "numbers.png"

Global tiles:TImage
Global tileborder:TImage
Global numbers:TImage


Type PlayState Extends State

	Field points:Int
	Field timer:TTimer
	Field gmview:GameView

	Method stateEntry()
		If Not tiles Then tiles = LoadAnimImage("incbin::tiles.png",64, 64, 0, 8, -1)
		If Not numbers Then numbers = LoadAnimImage("incbin::numbers.png", 32, 50, 0, 10, -1)
		If Not tileborder Then tileborder = LoadImage("incbin::border.png")
		If Not gmview Then gmview = GameView.Create ( 128, 64, 256, 256 )
		
		ViewManager.addView( gmview )
		ViewManager.onMouseMove( MouseX(), MouseY() )
		
		SetAlpha(1.0)
		'GMap.Generate(1,1)
		points = 0
		timer = CreateTimer(1)
	EndMethod
	
	Method stateExit()
		StopTimer(timer)
		ViewManager.removeView( gmview )
	EndMethod
	
	Method logic()
		Local finished:Int = 1
		
		'For Local t:Int = EachIn GMap._map
		'	If t >= 0 Then
		'		finished = 1
		'		Exit
		'	EndIf
		'Next
		
		If Not finished Or timer.ticks() > 60 Then StateManager.changeState("mainmenu")

	EndMethod

	Method draw()
		'GMap.draw()
		DrawNumber((60 - timer.ticks()), 288,20)
		DrawText ( "Points: " + points, 500, 0)
	EndMethod

	Method handleInput()
		Select EventID()
			Case EVENT_KEYDOWN
				If EventData() = KEY_ESCAPE StateManager.changeState ("mainmenu")
			Case Event_MOUSEDOWN
				'points:+GMap.checkSelected( EventX(), EventY())
		EndSelect
	EndMethod

EndType

Function drawNumber ( n:Int, x:Int, y:Int)
	Local ns:String = n
	Local px:Int = x
	For Local c:Int = 0 To ns.length-1
		Local cc:Int = ns[c] - $30
		If cc >= 0 And cc <= 9 Then
			DrawImage(numbers, px, y, cc)
			px:+numbers.width
		EndIf
	Next


EndFunction

Type Tile Extends View
	Global tileimages:TImage
	'Global tileborder:TImage
	Field tilenum:Int
	Field hilh:Int

	Function Create:Tile( n:Int, px:Int, py:Int )
		If Not tileimages Then tileimages = LoadAnimImage("incbin::tiles.png",64, 64, 0, 8, -1)
		'If Not tileborder Then tileborder = LoadImage("incbin::border.png")
		Local til:Tile = New Tile
		til.tilenum = n
		til.x = px
		til.y = py
		til.width = 64
		til.height = 64
		til.hilh = 0
		Return til
	EndFunction

	Method draw ()
		If hilh Then SetRotation(45)
		DrawImage tileimages, x, y, tilenum
		If hilh Then SetRotation(0)
	EndMethod
	
	Method onMouseIn()
		hilh = 1
	EndMethod
	
	Method onMouseOut()
		hilh = 0
	EndMethod
	
EndType

Type GameView Extends ViewGroup
	Field map:Tile[]
	
	Function Create:GameView( sx:Int, sy:Int, swidth:Int, sheight:Int)
		Local gv:GameView = New GameView
		gv.x = sx
		gv.y = sy
		gv.width = swidth
		gv.height = sheight
		Local ppp:Int = 0
		For Local n:Int = 0 To 3
			Local t:Tile = Tile.Create( n, ppp, 0 )
			gv.addChild( t )
			ppp:+64
		Next
		Return gv
	EndFunction
EndType
Rem
Type GMap
	Global _map:Int[]
	Global _lines:Int
	Global _columns:Int
	Global _selected:Int
	Global _initx:Int
	Global _inity:Int
	
	Function Generate( lin:Int, col:Int )
		_lines = lin
		_columns = col
		_map = New Int[lin*col]
		
		
		Local til:Int[8]
		Local remain:Int = lin*col
		
		For Local n:Int = 0 To 7
			til[n]=0
		Next
		
		Local n:Int = 0
		While remain > 0
			til[n]:+2
			remain:-2
			n:+1
			If n > 7 Then n = 0
		Wend
		
		For Local n:Int = 0 To (lin*col)-1
			Repeat
				Local v:Int = Rand(0,7)
				If til[v] > 0 Then
					_map[n] = v
					til[v]:-1
					Exit
				EndIf
			Forever
		Next
		
		_initx = 32
		_inity = 64
		_selected = -1	
	
	EndFunction

	Function draw()
		SetAlpha(1.0)
		
		For Local curline:Int = 0 To _lines-1
			For Local curcolumn:Int = 0 To _columns-1
				Local t:Int = _map[(curline*_columns)+curcolumn]
				If t >= 0 Then
					If _selected = (curline*_columns)+curcolumn Then
						SetColor(64,64,64)
					Else
						SetColor(255,255,255)
					EndIf
					DrawImage(tiles, _initx + (curcolumn*64), _inity +(curline*64)		, t )
					SetColor(255,255,255)
					'SetBlend(ALPHABLEND)					
					'DrawImage(tiles, _initx + (curcolumn*64), _inity +(curline*64)		, t)
					'If _selected = (curline*_columns)+curcolumn Then
					'	SetBlend(LIGHTBLEND)
					'	DrawImage(tileborder, _initx + (curcolumn*64), _inity +(curline*64)		 )
					'	SetBlend(ALPHABLEND)
					'EndIf
				EndIf
			Next
		Next
	EndFunction
	
	Function checkSelected:Int ( x:Int, y:Int )
		If x < _initx And y < _inity Then
			Return 0
		EndIf
		Local col:Int = (x-_initx)/64
		Local lin:Int = (y-_inity)/64
		
		Local newselected:Int = -1
		
		If col < _columns And lin < _lines Then
			newselected = ( col + ( lin * _columns))
		EndIf
		
		If newselected >= 0 And _map[newselected] > -1 Then
			If _selected >= 0 Then
				If newselected = _selected Then
					_selected = -1
				Else If _map[newselected] <> _map[_selected] Then
					_selected = newselected
				Else
					Local pary:Int = _selected / _columns
					Local parx:Int = _selected - (pary*_columns)
					pary = (pary*64)+_inity
					parx = (parx*64)+_initx
					Local pary2:Int = newselected / _columns
					Local parx2:Int = newselected - (pary2*_columns)
					pary2 = (pary2*64)+_inity
					parx2 = (parx2*64)+_initx
					For Local n:Int = 0 To 100
						Local vx:Double
						Local vy:Double
						Repeat
							vx = Rnd(-2.0,2.0)
							vy = Rnd(-2.0,2.0)
						Until vx <> 0.0 Or vy <> 0.0
						ParticleManager.AddParticle( Particle.Create( Rnd(parx,parx+64), Rnd(pary, pary+64), vx, vy, Rnd(0.7,1.0))) 
						ParticleManager.AddParticle( Particle.Create( Rnd(parx2,parx2+64), Rnd(pary2, pary2+64), vx, vy, Rnd(0.7,1.0))) 
					Next
					_map[_selected] = -1
					_map[newselected] = -1
					_selected = -1
					Return 100
				EndIf
			Else
				_selected = newselected
			EndIf
		EndIf
		Return 0
	
	EndFunction
	

EndType
EndRem
