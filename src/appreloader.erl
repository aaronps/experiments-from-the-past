%%%-------------------------------------------------------------------
%%% @author krom
%%% @copyright (C) 2016, <COMPANY>
%%% @doc
%%%
%%% @end
%%% Created : 22. Sep 2016 9:15 PM
%%%-------------------------------------------------------------------
-module(appreloader).
-author("krom").

%% API
-export([reload/1, log/1]).


reload(AppName) -> appreloader_srv:reload(AppName).
log(String) -> appreloader_srv:showName(String).
