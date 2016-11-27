%%%-------------------------------------------------------------------
%%% @author aaronps
%%% @copyright (C) 2016, <COMPANY>
%%% @doc
%%%
%%% @end
%%% Created : 22. Sep 2016 4:39 PM
%%%-------------------------------------------------------------------
-module(appreloader_sup).
-author("aaronps").

-behaviour(supervisor).

%% API
-export([start_link/0]).

%% Supervisor callbacks
-export([init/1]).

-define(SERVER, ?MODULE).

%%%===================================================================
%%% API functions
%%%===================================================================

start_link() ->
    supervisor:start_link({local, ?SERVER}, ?MODULE, []).

%%%===================================================================
%%% Supervisor callbacks
%%%===================================================================

init([]) ->
    % one_for_one, one_for_all, rest_for_one, simple_one_for_one; in seconds
    SupFlags = #{strategy => one_for_one, intensity => 1, period => 5},
    AChild = #{
        id      => reloader, % anything but a pid()
        start   => {appreloader_srv, start_link, []}
%%        restart => permanent, %% permanent | temporary | transient
%%        shutdown=> 5000,      %% brutal_kill | number (ms) | infinity
%%        type    => worker,    %% worker | supervisor
%%        modules => ['Module'] %% Module or dynamic (if gen_event)
    },
    {ok, {SupFlags, [AChild]}}.

%%%===================================================================
%%% Internal functions
%%%===================================================================
