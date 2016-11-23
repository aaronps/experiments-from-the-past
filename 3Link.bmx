SuperStrict
' 3LINK

Import "Particle.bmx"
Import "View.bmx"
Import "Logic.bmx"
Import "State.bmx"

Import "MainMenuState.bmx"
Import "PlayState.bmx"

Graphics 640, 480

LogicManager.init() ' Must be first

ViewManager.init()
SetBlend(ALPHABLEND)

SeedRnd MilliSecs()

StateManager.initializeStates()
StateManager.addState("mainmenu", New MainMenuState)
StateManager.addState("play", New PlayState)
StateManager.changeState("mainmenu")

'ParticleManager.Init()

While Not StateManager._ENDGAME
	StateManager.handleStateChange()
	StateManager.handleInput()
	StateManager.logic()
	LogicManager.runTasks( MilliSecs() )
	Cls
	ViewManager.draw()
	StateManager.draw()
'	ParticleManager.drawall()
	Flip
Wend

