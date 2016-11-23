SuperStrict

Import "Logic.bmx"

Incbin "cirpar2.png"

Type Particle
	Field x:Double
	Field y:Double
	Field xspeed:Double
	Field yspeed:Double
	Field alpha:Double
	
	Function Create:Particle( _x:Double, _y:Double, _xspeed:Double, _yspeed:Double, _alpha:Double)
		Local p:Particle = New Particle
		p.x = _x
		p.y = _y
		p.xspeed = _xspeed
		p.yspeed = _yspeed
		p.alpha = _alpha
		Return p
	EndFunction
	
	Method logic()
		x:+ xspeed
		y:+ yspeed
		alpha:- 0.01
		'If y >= 480 - ParticleManager.star.height Then yspeed = -yspeed + 1.0
		yspeed:+ 0.1
		
	EndMethod
	
	Method draw()
		SetAlpha (alpha)
		DrawImage ( ParticleManager.star , x, y)
	EndMethod
	

EndType

Type ParticleManager
	Global plist:TList
	Global star:TImage
	Global logic:ParticleLogic
	
	Function Init()
		plist = New TList
		star = LoadImage("incbin::cirpar2.png")
		If Not logic Then logic = New ParticleLogic
		LogicManager.addLogicTask( logic )
	EndFunction
	
	Function AddParticle( p:Particle )
		plist.addlast(p)
	EndFunction
	
	Function logicall()
		For Local p:Particle = EachIn plist
			p.logic()
			If p.alpha <= 0 Then plist.Remove(p)
		Next
	EndFunction
	
	Function drawall()
		SetBlend (LIGHTBLEND)
		For Local p:Particle = EachIn plist
			p.draw()
		Next
		SetBlend(ALPHABLEND)
	EndFunction
EndType

Type ParticleLogic Extends LogicTask
	Method run( ms:Int )
		ParticleManager.logicall()
	EndMethod
EndType

'Rem
'Graphics 640, 480
'SetBlend(ALPHABLEND)

'ParticleManager.Init()

'While Not KeyHit (KEY_ESCAPE)
'	Cls
	
'	While ParticleManager.plist.count() < 100
'		ParticleManager.AddParticle ( Particle.Create ( Rand(0,200), Rand(0,200), Rand (0,2), Rand(0,2), Rnd(0.2,1.0)))
'	Wend
	
'	ParticleManager.logicall()
'	ParticleManager.drawall()
	
'	Flip
	
	
'Wend
'endrem