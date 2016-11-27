%%%-------------------------------------------------------------------
%%% @author krom
%%% @copyright (C) 2016, <COMPANY>
%%% @doc
%%%
%%% @end
%%% Created : 29. Aug 2016 7:35 PM
%%%-------------------------------------------------------------------
{application, logerl, [
    {description, "A logger for Erlang"},
    {vsn, "1.0.0"},
    {modules, [logerl, logerl_dateformat, logerl_console]},
    {registered, []},
    {applications, [
        kernel,
        stdlib
    ]},
%%    {mod, {logerl, []}},
    {env, []}
]}.