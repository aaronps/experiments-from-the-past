SuperStrict

Import "View.bmx"

Type State
	Method stateEntry() Abstract
	Method stateExit() Abstract
	Method logic() Abstract
	Method draw() Abstract
	Method handleInput() Abstract
EndType

Type StateManager
	Global _state:State
	Global _nextstate:State
	Global _prevstate:State
	Global _stateList:TList
	Global _ENDGAME:Int
	
	Function addState ( name:String, st:State)
		Local t:StateMap = New StateMap
		t.name = name
		t.state = st
		_stateList.addLast(t)
	EndFunction
	
	Function changeState ( name:String )
		For Local t:StateMap = EachIn _statelist
			If t.name = name Then _nextState = t.state; Exit
		Next
	EndFunction
	
	Function handleStateChange()
		If _nextstate Then
			_prevstate = _state
			_state = _nextstate
			_nextstate = Null
			If _prevstate Then _prevstate.stateExit()
			_state.stateEntry()
		EndIf
	EndFunction
	
	Function initializeStates()
		_state = Null
		_nextstate = Null
		_prevstate = Null
		_stateList = New TList
		_ENDGAME = 0
	EndFunction
	
	Function endGame()
		_ENDGAME = 1
	EndFunction
	
	Function handleInput()
		While PollEvent()
			Select EventID()
				Case EVENT_APPTERMINATE
					endGame()
				Case EVENT_MOUSEDOWN
					ViewManager.onMouseButton( EventX(), EventY() )
					_state.handleInput()
				Case EVENT_MOUSEMOVE
					ViewManager.onMouseMove( EventX(), EventY() )
				Case EVENT_KEYDOWN
					_state.handleInput()
			EndSelect
		Wend
		_state.handleInput()
	EndFunction
	
	Function logic()
		_state.logic()
	EndFunction
	
	Function draw()
		SetOrigin( 0, 0 )
		_state.draw()
	EndFunction
	
EndType

Type StateMap
	Field name:String
	Field state:State
EndType