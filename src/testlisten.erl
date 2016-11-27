%%%-------------------------------------------------------------------
%%% @author krom
%%% @copyright (C) 2016, <COMPANY>
%%% @doc
%%%
%%% @end
%%% Created : 27. Sep 2016 6:49 PM
%%%-------------------------------------------------------------------
-module(testlisten).
-author("krom").

-behaviour(application).

%% application callback
-export([start/2, stop/1]).


start(_StartType,_StartArgs) ->
    io:format("testlisten:start~n"),
    testlisten_sup:start_link().

stop(_State) ->
    io:format("testlisten:stop~n"),
    ok.

