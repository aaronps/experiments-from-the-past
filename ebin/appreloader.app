%%%-------------------------------------------------------------------
%%% @author aaronps
%%% @copyright (C) 2016, <COMPANY>
%%% @doc
%%%
%%% @end
%%% Created : 22. Sep 2016 4:37 PM
%%%-------------------------------------------------------------------
{application, appreloader, [
    {description, "Application compiler and reloader"},
    {vsn, "1.0.2"},
    {registered, [appreloader]},
    {applications, [
        kernel,
        stdlib
    ]},
    {modules, [appreloader, appreloader_app, appreloader_sup, appreloader_srv]},
    {mod, {appreloader_app, []}},
    {env, []}
]}.