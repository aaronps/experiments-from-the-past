%%%-------------------------------------------------------------------
%%% @author krom
%%% @copyright (C) 2016, <COMPANY>
%%% @doc
%%%
%%% @end
%%% Created : 27. Sep 2016 8:08 PM
%%%-------------------------------------------------------------------
-module(testlisten_socket_sup).
-author("krom").

-behaviour(supervisor).

%% API
-export([start_link/0]).

%% Supervisor callbacks
-export([init/1]).

-define(SERVER, ?MODULE).

%%%===================================================================
%%% API functions
%%%===================================================================

start_link(Socket) ->
    supervisor:start_link(, ?MODULE, [Socket]).

%%%===================================================================
%%% Supervisor callbacks
%%%===================================================================

init([Socket]) ->
    % one_for_one, one_for_all, rest_for_one, simple_one_for_one; in seconds
    SupFlags = #{strategy => simple_one_for_one, intensity => 1, period => 5},
    AChild = #{
        id      => socket, % anything but a pid()
        start   => {testlisten_socket, start_link, [self(), Socket]}
%%        restart => permanent, %% permanent | temporary | transient
%%        shutdown=> 5000,      %% brutal_kill | number (ms) | infinity
%%        type    => worker,    %% worker | supervisor
%%        modules => ['Module'] %% Module or dynamic (if gen_event)
    },
    {ok, {SupFlags, [AChild]}}.

%%%===================================================================
%%% Internal functions
%%%===================================================================
