SuperStrict

Import "State.bmx"
Import "View.bmx"

Import "Logic.bmx"

Import "MainMenuView.bmx"

Type MainMenuState Extends State
	Field menu:MainMenuView

	Method stateEntry()		
		If Not menu Then menu = New MainMenuView
		ViewManager.addView( menu )
	EndMethod
	
	Method stateExit()
		ViewManager.removeView( menu )
	EndMethod

	Method logic()
	EndMethod

	Method draw()
	EndMethod

	Method handleInput()
		Select EventID()
			Case EVENT_KEYDOWN
				If EventData() = KEY_ESCAPE Then 
					StateManager.endGame()
				Else
					StateManager.changeState("play")
				EndIf
			Case EVENT_MOUSEDOWN
				StateManager.changeState("play")
		EndSelect
	EndMethod
EndType
