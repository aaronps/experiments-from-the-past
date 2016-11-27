%%%-------------------------------------------------------------------
%%% @author krom
%%% @copyright (C) 2016, <COMPANY>
%%% @doc
%%%
%%% @end
%%% Created : 27. Sep 2016 7:26 PM
%%%-------------------------------------------------------------------
-module(testlisten_server).
-author("krom").

-behaviour(gen_server).

%% API
-export([start_link/1]).

%% gen_server callbacks
-export([init/1,
    handle_call/3,
    handle_cast/2,
    handle_info/2,
    terminate/2,
    code_change/3]).

%%-record(idle{})

-record(state, {mysup, socketsup}).

%%%===================================================================
%%% API
%%%===================================================================

start_link(Sup) ->
    gen_server:start_link(?MODULE, [Sup], []).


%%%===================================================================
%%% gen_server callbacks
%%%===================================================================

init([Sup]) ->
    self() ! start_sup,
    {ok, #state{mysup = Sup}}.


handle_call(_Request, _From, State) ->
    {reply, ok, State}.


handle_cast(_Request, State) ->
    {noreply, State}.


handle_info(start_sup, #state{} = S) ->

    {ok, Socket} = gen_tcp:listen(20999, [binary, {active, false}]),

    SupDesc = #{
        id => socketsup,
        start => {testlisten_socket_sup, start_link, [Socket]}
    },

    {ok, SocketSup} = supervisor:start_child(S#state.mysup, #{id=> asd, start => {m,f,[]}, type => supervisor}),
    {noreply, S};

handle_info(_Info, State) ->
    {noreply, State}.


terminate(_Reason, _State) ->
    ok.


code_change(_OldVsn, State, _Extra) ->
    {ok, State}.

%%%===================================================================
%%% Internal functions
%%%===================================================================
