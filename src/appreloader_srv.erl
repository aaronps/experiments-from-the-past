%%%-------------------------------------------------------------------
%%% @author aaronps
%%% @copyright (C) 2016, <COMPANY>
%%% @doc
%%%
%%% @end
%%% Created : 22. Sep 2016 4:44 PM
%%%-------------------------------------------------------------------
-module(appreloader_srv).
-author("aaronps").

-behaviour(gen_server).

-define(SERVER, appreloader).

%% API
-export([start_link/0, reload/1, ml/1, showName/1]).

%% gen_server callbacks
-export([init/1,
    handle_call/3,
    handle_cast/2,
    handle_info/2,
    terminate/2,
    code_change/3]).

%%-record(idle{})

-record(state, {}).

%%%===================================================================
%%% API
%%%===================================================================

start_link() ->
    gen_server:start_link({local, ?SERVER}, ?MODULE, [], []).

%% reloads the application
reload(AppName) ->
    gen_server:cast(?SERVER, {reload,AppName}).

ml(AppName) ->
    gen_server:cast(?SERVER, {testit, AppName}).

showName(Name) ->
    gen_server:cast(?SERVER, {show_name, Name}).


%%%===================================================================
%%% gen_server callbacks
%%%===================================================================

init([]) ->
    {ok, #state{}}.


handle_call(_Request, _From, State) ->
    {reply, ok, State}.

handle_cast({reload, AppName}, State) ->
    reload_app(AppName),
    {noreply, State};

handle_cast({testit, AppName}, State) ->
    Modules = application:get_key(AppName, modules),
    application:stop(AppName),
    unload_modules(Modules, AppName),
    application:unload(AppName),
    {noreply, State};

handle_cast({show_name, Name}, State) ->
    io:format("---->~p<----~n", [Name]),
    {noreply, State};

handle_cast(_Request, State) ->
    {noreply, State}.


handle_info(_Info, State) ->
    {noreply, State}.


terminate(_Reason, _State) ->
    ok.


code_change(_OldVsn, State, _Extra) ->
    {ok, State}.

%%%===================================================================
%%% Internal functions
%%%===================================================================

reload_app(AppName) ->
    io:format("Going to reload ~p~n", [AppName]),
    application:stop(AppName),
    case make:all([load]) of
        up_to_date -> application:start(AppName);
        _ -> io:format("make failed~n")
    end.

unload_modules(undefined, AppName) ->
    io:format("The application ~p doesn't list any modules~n", [AppName]);

unload_modules({ok, Modules}, _AppName) ->
    [ code:delete(M) || M <- Modules ],
    [ code:purge(M)  || M <- Modules ],
    ok.


