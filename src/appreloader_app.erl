%%%-------------------------------------------------------------------
%%% @author aaronps
%%% @copyright (C) 2016, <COMPANY>
%%% @doc
%%%
%%% @end
%%% Created : 22. Sep 2016 4:39 PM
%%%-------------------------------------------------------------------
-module(appreloader_app).
-author("aaronps").

-behaviour(application).

%% Application callbacks
-export([start/2, stop/1]).


start(_StartType, _StartArgs) -> appreloader_sup:start_link().

stop(_State) -> ok.

%%%===================================================================
%%% Internal functions
%%%===================================================================
