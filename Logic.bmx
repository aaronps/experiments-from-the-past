SuperStrict

Type LogicTask
	Method run( ms:Int ) Abstract
EndType

Type LogicGroup Extends LogicTask
	Field grouptasks:TList = New TList
	
	Method run( ms:Int ) Final
		For Local t:LogicTask = EachIn grouptasks
			t.run( ms )
		Next
	EndMethod
	
	Method addLogicTask( t:LogicTask )
		grouptasks.addLast( t )
	EndMethod
	
	Method removeLogicTask( t:LogicTask )
		grouptasks.remove( t )
	EndMethod
	
	Method clear()
		grouptasks.clear()
	EndMethod
End Type

Type LogicManager
	Global tasks:LogicGroup
	
	Function init()
		If Not tasks Then tasks = New LogicGroup
	EndFunction
	
	Function runTasks( ms:Int )
		tasks.run( ms )
	EndFunction
	
	Function addLogicTask( t:LogicTask )
		tasks.addLogicTask( t )
	EndFunction
	
	Function removeLogicTask( t:LogicTask )
		tasks.removeLogicTask( t )
	EndFunction
	
	Function clear()
		tasks.clear()
	EndFunction
EndType