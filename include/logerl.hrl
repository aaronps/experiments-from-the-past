%%%-------------------------------------------------------------------
%%% @author krom
%%% @copyright (C) 2016, <COMPANY>
%%% @doc
%%%
%%% @end
%%% Created : 29. Aug 2016 5:09 PM
%%%-------------------------------------------------------------------
-author("krom").

-record(log,{timestamp, message = "", data = "", level=info}).
