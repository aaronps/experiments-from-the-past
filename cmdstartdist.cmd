@echo off & escript %~f0 %* & exit /b
%%
%%! -hidden -connect_all false
main(Args) ->
	WantedName = "sckfw",	
	GotName = net_start(WantedName),
	io:format("This is an erlang script, with name: ~p~n", [GotName]),
	io:format("Arguments: ~p~n", [Args]).

net_start(Wanted) ->
	NewName = list_to_atom(Wanted),
	case net_kernel:start([NewName, shortnames]) of
		{ok, _} -> NewName;
		{error, _} -> net_start(Wanted,1)
	end.

net_start(Wanted, Index) when Index < 10 ->
	NewName = list_to_atom(Wanted ++ integer_to_list(Index)),
	io:format("Trying: ~p~n", [NewName]),
	case net_kernel:start([NewName, shortnames]) of
		{ok, _} -> NewName;
		{error, E} ->
			io:format("Failed with: ~p~n", [E]),
			net_start(Wanted,Index+1)
	end;

net_start(Wanted, Index) ->
	erlang:error(too_many_nodes, [Wanted, Index]).
	

