%%%-------------------------------------------------------------------
%%% @author krom
%%% @copyright (C) 2016, <COMPANY>
%%% @doc
%%%
%%% @end
%%% Created : 29. Aug 2016 7:10 PM
%%%-------------------------------------------------------------------
-module(logerl_console).
-author("krom").
-behaviour(gen_event).


%% API
-export([init/1, handle_event/2, handle_call/2, handle_info/2, terminate/2, code_change/3]).

-include("logerl.hrl").

-record(state, {name}).

init(Name) ->
    io:format( ?MODULE_STRING ++ " ---> Init Name: '~s'~n",[Name]),
    {ok, #state{name=Name}}.

%% init(Params) ->
%%     io:format( ?MODULE_STRING ++ " ---> Init Params: ~p~n",[Params]),
%%     {ok, #state{}}.

handle_event(#log{timestamp=Timestamp, message=Message, data=[]}, State) ->
    io:format("~s ~s ~s~n", [Timestamp, State#state.name, Message]),
    {ok, State};

handle_event(#log{timestamp=Timestamp, message=Message, data=Data}, State) ->
    F = io_lib:format("~s ~s~n", [Timestamp, Message]),
    io:format(F, [Data]),
    {ok, State};

handle_event(Event, State) ->
    io:format( ?MODULE_STRING ++ " ---> Handler Event: ~p~n",[Event]),
    {ok, State}.

handle_call(Request, State) ->
    io:format( ?MODULE_STRING ++ " ---> Handler Request: ~w~n",[Request]),
    Reply = ok,
    {ok, Reply, State}.

handle_info(Info, State) ->
    io:format( ?MODULE_STRING ++ " ---> Handle info: ~w~n",[Info]),
    {ok, State}.

terminate(_Arg, State) ->
    io:format( ?MODULE_STRING ++ " ---> called terminate '~s'~n", [State#state.name]),
    ok.

code_change(_OldVsn, State, _Extra) ->
    io:format( ?MODULE_STRING ++ " ---> called code_change, old: ~w~n", [_OldVsn]),
    {ok, State}.


