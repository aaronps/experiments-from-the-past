%%%-------------------------------------------------------------------
%%% @author krom
%%% @copyright (C) 2016, <COMPANY>
%%% @doc
%%%
%%% @end
%%% Created : 29. Aug 2016 4:35 PM
%%%-------------------------------------------------------------------
-module(logerl).
-author("krom").

%%-behavior(application).

%% API
-export([start_link/2, log/2, log/3, info/3]).

-include("logerl.hrl").

start_link(LoggerName, PrependString) ->
    {ok, LoggerPid } = gen_event:start_link(LoggerName),

    gen_event:add_handler(LoggerPid, logerl_console, [PrependString]),

    log(LoggerPid, "Is it logging?"),

    {ok, LoggerPid}.


log(LoggerRef, Message) ->
    log(LoggerRef, Message, []).

log(LoggerRef, Message, Data) ->
    info(LoggerRef, Message, Data).

info(LoggerRef, Message, Data) ->
    TS = os:timestamp(),
    Log = #log{timestamp = logerl_dateformat:full(TS), message = Message, data = Data},

    % gen_event:notify never fails.
    gen_event:notify(LoggerRef, Log).