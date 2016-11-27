%%%-------------------------------------------------------------------
%%% @author krom
%%% @copyright (C) 2015, <COMPANY>
%%% @doc
%%%
%%% @end
%%% Created : 13. Oct 2015 2:36 PM
%%%-------------------------------------------------------------------
-module(logerl_dateformat).
-author("krom").

%% API
-export([full/1, full_iolist/1]).

-define(ToStr2(N), [$0 + N div 10, $0 + N rem 10]).
-define(ToStr3(N), [($0 + (N div 100)), ($0 + ((N div 10) rem 10)), ($0 + (N rem 10))]).

full({_, _, UMS} = Timestamp) ->
    MS = UMS div 1000,
    {{Year, Month, Day}, {Hour, Minute, Second}} = calendar:now_to_local_time(Timestamp),
    integer_to_list(Year)
    ++ "-" ++ ?ToStr2(Month)
        ++ "-" ++ ?ToStr2(Day)
        ++ " " ++ ?ToStr2(Hour)
        ++ ":" ++ ?ToStr2(Minute)
        ++ ":" ++ ?ToStr2(Second)
        ++ "." ++ ?ToStr3(MS).

full_iolist({_, _, UMS} = Timestamp) ->
    MS = UMS div 1000,
    {{Year, Month, Day}, {Hour, Minute, Second}} = calendar:now_to_local_time(Timestamp),
    [
        integer_to_list(Year),
        $-, ?ToStr2(Month),
        $-, ?ToStr2(Day),
        32, ?ToStr2(Hour),
        $:, ?ToStr2(Minute),
        $:, ?ToStr2(Second),
        $., ?ToStr3(MS)
    ].
