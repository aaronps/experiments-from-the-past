%%%-------------------------------------------------------------------
%%% @author krom
%%% @copyright (C) 2015, <COMPANY>
%%% @doc
%%% Final notes
%%%    normal concat is the best average
%%%    to create binary, use normal concat and to binary, is best that way
%%%    io_lib:format is the slowest, maybe because it has to parse formatting
%%%
%%% @end
%%% Created : 13. Oct 2015 2:36 PM
%%%-------------------------------------------------------------------
-module(dateformattime).
-author("krom").

-define(TEST_TIMESTAMP, {1444, 718765, 3000}).
-define(NewTimestamp(N), {1440, 718765, N}).

-define(DEF_TEST(Name, FunName),
    Name(MAX) ->
    io:format("Starting test: ~s for ~s max ~B~n", [??Name, ??FunName, MAX * 1000]),
    F = fun Fun(0) -> FunName(?NewTimestamp(0));
        Fun(N) -> FunName(?NewTimestamp(N)), Fun(N - 1)
    end,
    VAL = (MAX - 1) * 1000,
    F(VAL)
).

%% API
-compile(export_all).

?DEF_TEST(test_iolib, iolib).
?DEF_TEST(test_miformat_concat, miformat_concat).
?DEF_TEST(test_miformat_concat2, miformat_concat2).
?DEF_TEST(test_miformat_concat3, miformat_concat3).
?DEF_TEST(test_miformat_concat4, miformat_concat4).
?DEF_TEST(test_miformat_list, miformat_list).
?DEF_TEST(test_miformat_iolist, miformat_iolist).
?DEF_TEST(test_miformat_iolist2, miformat_iolist2).
?DEF_TEST(test_miformat_iolist3, miformat_iolist3).
?DEF_TEST(test_miformat_iolist4, miformat_iolist4).
?DEF_TEST(test_miformat_iolist4b, miformat_iolist4b).
?DEF_TEST(test_miformat_iolist5, miformat_iolist5).
?DEF_TEST(test_miformat_binary, miformat_binary).
?DEF_TEST(test_miformat_binaryx, miformat_binaryx).
?DEF_TEST(test_miformat_binary2, miformat_binary2).
?DEF_TEST(test_miformat_binary3, miformat_binary3).

iolib({_, _, MS} = Timestamp) ->
    {{Year, Month, Day}, {Hour, Minute, Second}} = calendar:now_to_local_time(Timestamp),
    io_lib:format("~B-~2..0B-~2..0B ~2..0B:~2..0B:~2..0B.~3..0B",
        [Year, Month, Day, Hour, Minute, Second, MS div 1000]).

-define(ToStr2(N), [$0 + N div 10, $0 + N rem 10]).
-define(ToStr3(N), [($0 + (N div 100)), ($0 + ((N div 10) rem 10)), ($0 + (N rem 10))]).

-define(IfToStr2(N), if N > 9 -> ?ToStr2(N); true -> ($0 + N) end). 

miformat_concat({_, _, UMS} = Timestamp) ->
    MS = UMS div 1000,
    {{Year, Month, Day}, {Hour, Minute, Second}} = calendar:now_to_local_time(Timestamp),
    integer_to_list(Year)
    ++ "-" ++ ?ToStr2(Month)
        ++ "-" ++ ?ToStr2(Day)
        ++ " " ++ ?ToStr2(Hour)
        ++ ":" ++ ?ToStr2(Minute)
        ++ ":" ++ ?ToStr2(Second)
        ++ "." ++ ?ToStr3(MS).

miformat_concat3({_, _, UMS} = Timestamp) ->
    MS = UMS div 1000,
    {{Year, Month, Day}, {Hour, Minute, Second}} = calendar:now_to_local_time(Timestamp),
    integer_to_list(Year)
    ++ "-" ++ num2(Month)
        ++ "-" ++ num2(Day)
        ++ " " ++ num2(Hour)
        ++ ":" ++ num2(Minute)
        ++ ":" ++ num2(Second)
        ++ "." ++ ?ToStr3(MS).

miformat_concat4({_, _, UMS} = Timestamp) ->
    MS = UMS div 1000,
    NT = nt(),
    {{Year, Month, Day}, {Hour, Minute, Second}} = calendar:now_to_local_time(Timestamp),
    integer_to_list(Year)
    ++ "-" ++ element(Month+1,NT)
        ++ "-" ++ element(Day+1, NT)
        ++ " " ++ element(Hour+1, NT)
        ++ ":" ++ element(Minute+1, NT)
        ++ ":" ++ element(Second+1, NT)
        ++ "." ++ ?ToStr3(MS).

miformat_concat2({_, _, UMS} = Timestamp) ->
    MS = UMS div 1000,
    {{Year, Month, Day}, {Hour, Minute, Second}} = calendar:now_to_local_time(Timestamp),
    integer_to_list(Year)
    ++ [$- | ?ToStr2(Month)]
        ++ [$- | ?ToStr2(Day)]
        ++ [32 | ?ToStr2(Hour)]
        ++ [$: | ?ToStr2(Minute)]
        ++ [$: | ?ToStr2(Second)]
        ++ [$. | ?ToStr3(MS)].

-define(Hi(X), X div 10).
-define(Lo(X), X rem 10).
-define(HL(X), $0 + (X div 10), $0 + (X rem 10)).
-define(H3(X), $0 + (X div 100), $0 + ((X div 10) rem 10), $0 + (X rem 10)).

miformat_list({_, _, UMS} = Timestamp) ->
    MS = UMS div 1000,
    {{Year, Month, Day}, {Hour, Minute, Second}} = calendar:now_to_local_time(Timestamp),
    YearLast = Year rem 2000,
    [
        $2,$0,
        ?HL(YearLast),
        $-, ?HL(Month),
        $-, ?HL(Day),
        32, ?HL(Hour),
        $:, ?HL(Minute),
        $:, ?HL(Second),
        $., ?H3(MS)
    ].

miformat_iolist({_, _, UMS} = Timestamp) ->
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

miformat_iolist3({_, _, UMS} = Timestamp) ->
    MS = UMS div 1000,
    {{Year, Month, Day}, {Hour, Minute, Second}} = calendar:now_to_local_time(Timestamp),
    [
        integer_to_binary(Year),
		$-, ?IfToStr2(Month),
        $-, ?IfToStr2(Day),
        32, ?IfToStr2(Hour),
        $:, ?IfToStr2(Minute),
        $:, ?IfToStr2(Second),
        $., ?ToStr3(MS)
	].

miformat_iolist4({_, _, UMS} = Timestamp) ->
    MS = UMS div 1000,
    {{Year, Month, Day}, {Hour, Minute, Second}} = calendar:now_to_local_time(Timestamp),
    [
        integer_to_list(Year),
		$-, num2(Month),
        $-, num2(Day),
        32, num2(Hour),
        $:, num2(Minute),
        $:, num2(Second),
        $., ?ToStr3(MS)
	].

miformat_iolist4b({_, _, UMS} = Timestamp) ->
    MS = UMS div 1000,
    {{Year, Month, Day}, {Hour, Minute, Second}} = calendar:now_to_local_time(Timestamp),
    [
        integer_to_binary(Year),
		$-, bnum2(Month),
        $-, bnum2(Day),
        32, bnum2(Hour),
        $:, bnum2(Minute),
        $:, bnum2(Second),
        $., ?ToStr3(MS)
	].
miformat_iolist5({_, _, UMS} = Timestamp) ->
    MS = UMS div 1000,
    {{Year, Month, Day}, {Hour, Minute, Second}} = calendar:now_to_local_time(Timestamp),
	N = nt(),
    [
        integer_to_binary(Year),
		$-, element(Month+1, N),
        $-, element(Day+1, N),
        32, element(Hour+1, N),
        $:, element(Minute+1, N),
        $:, element(Second+1, N),
        $., ?ToStr3(MS)
	].
	
miformat_iolist2({_, _, UMS} = Timestamp) ->
    MS = UMS div 1000,
    {{Year, Month, Day}, {Hour, Minute, Second}} = calendar:now_to_local_time(Timestamp),
    iolist_to_binary([
        integer_to_list(Year),
        "-", ?ToStr2(Month),
        "-", ?ToStr2(Day),
        " ", ?ToStr2(Hour),
        ":", ?ToStr2(Minute),
        ":", ?ToStr2(Second),
        ".", ?ToStr3(MS)
    ]).

miformat_binary({_, _, MS} = Timestamp) ->
    {{Year, Month, Day}, {Hour, Minute, Second}} = calendar:now_to_local_time(Timestamp),
    <<
    (integer_to_binary(Year))/binary,
    $-, (bin2(Month))/binary,
    $-, (bin2(Day))/binary,
    32, (bin2(Hour))/binary,
    $:, (bin2(Minute))/binary,
    $:, (bin2(Second))/binary,
    $., (bin3(MS div 1000))/binary
    >>.

miformat_binaryx({_, _, UMS} = Timestamp) ->
    MS = UMS div 1000,
    {{Year, Month, Day}, {Hour, Minute, Second}} = calendar:now_to_local_time(Timestamp),
    <<
    (integer_to_binary(Year))/binary,
    $-, ($0 + (Month div 10)), ($0 + (Month rem 10)),
    $-, ($0 + (Day div 10)), ($0 + (Day rem 10)),
    32, ($0 + (Hour div 10)), ($0 + (Hour rem 10)),
    $:, ($0 + (Minute div 10)), ($0 + (Minute rem 10)),
    $:, ($0 + (Second div 10)), ($0 + (Second rem 10)),
    $., ($0 + (MS div 100)), ($0 + ((MS div 10) rem 10)), ($0 + (MS rem 10))
    >>.

bin2(N) when N < 10 -> <<$0, ($0 + N)>>;
bin2(N) -> <<($0 + (N div 10)), ($0 + (N rem 10))>>.
%bin2(N) -> integer_to_binary(N).

bin3(N) when N < 10 -> <<$0, $0, ($0 + N)>>;
bin3(N) when N < 100 -> <<$0, (integer_to_binary(N))/binary>>;
bin3(N) -> integer_to_binary(N).

miformat_binary2({_, _, MS} = Timestamp) ->
    {{Year, Month, Day}, {Hour, Minute, Second}} = calendar:now_to_local_time(Timestamp),
    MS2 = MS div 1000,
    B0 = integer_to_binary(Year),
    B1 = if
             Month < 10 -> <<B0/binary, $-, $0, ($0 + Month)>>;
             true -> <<B0/binary, $-, $1, (38 + Month)>> % 38 is $0 - 10
         end,
    B2 = if
             Day < 10 -> <<B1/binary, $-, $0, ($0 + Day)>>;
             true -> <<B1/binary, $-, ($0 + (Day div 10)), ($0 + (Day rem 10))>>
         end,
    B3 = if
             Hour < 10 -> <<B2/binary, 32, $0, ($0 + Hour)>>;
             true ->
                 <<B2/binary, 32, ($0 + (Hour div 10)), ($0 + (Hour rem 10))>>
         end,
    B4 = if
             Minute < 10 -> <<B3/binary, $:, $0, ($0 + Minute)>>;
             true ->
                 <<B3/binary, $:, ($0 + (Minute div 10)), ($0 + (Minute rem 10))>>
         end,
    B5 = if
             Second < 10 -> <<B4/binary, $:, $0, ($0 + Second)>>;
             true ->
                 <<B4/binary, $:, ($0 + (Second div 10)), ($0 + (Second rem 10))>>
         end,
    B6 = if
             MS2 < 10 -> <<B5/binary, $., $0, $0, ($0 + MS2)>>;
             MS2 < 100 ->
                 <<B5/binary, $., $0, ($0 + (MS2 div 10)), ($0 + (MS2 rem 10))>>;
             true ->
                 <<B5/binary, $., ($0 + (MS2 div 100)), ($0 + ((MS2 div 10) rem 10)), ($0 + (MS2 rem 10))>>
         end,
    B6.


miformat_binary3({_, _, MS} = Timestamp) ->
    {{Year, Month, Day}, {Hour, Minute, Second}} = calendar:now_to_local_time(Timestamp),
    MS2 = MS div 1000,
    B0 = integer_to_binary(Year),
    B1 = <<B0/binary, $-, ($0 + (Month div 10)), ($0 + (Month rem 10))>>,
    B2 = <<B1/binary, $-, ($0 + (Day div 10)), ($0 + (Day rem 10))>>,
    B3 = <<B2/binary, 32, ($0 + (Hour div 10)), ($0 + (Hour rem 10))>>,
    B4 = <<B3/binary, $:, ($0 + (Minute div 10)), ($0 + (Minute rem 10))>>,
    B5 = <<B4/binary, $:, ($0 + (Second div 10)), ($0 + (Second rem 10))>>,
    B6 = <<B5/binary, $., ($0 + (MS2 div 100)), ($0 + ((MS2 div 10) rem 10)), ($0 + (MS2 rem 10))>>,
    B6.

nt() -> {
    "00", "01", "02", "03", "04", "05", "06", "07", "08", "09",
    "10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
    "20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
    "30", "31", "32", "33", "34", "35", "36", "37", "38", "39",
    "40", "41", "42", "43", "44", "45", "46", "47", "48", "49",
    "50", "51", "52", "53", "54", "55", "56", "57", "58", "59"
}.

num2(0) -> "00";
num2(1) -> "01";
num2(2) -> "02";
num2(3) -> "03";
num2(4) -> "04";
num2(5) -> "05";
num2(6) -> "06";
num2(7) -> "07";
num2(8) -> "08";
num2(9) -> "09";

num2(10) -> "10";
num2(11) -> "11";
num2(12) -> "12";
num2(13) -> "13";
num2(14) -> "14";
num2(15) -> "15";
num2(16) -> "16";
num2(17) -> "17";
num2(18) -> "18";
num2(19) -> "19";

num2(20) -> "20";
num2(21) -> "21";
num2(22) -> "22";
num2(23) -> "23";
num2(24) -> "24";
num2(25) -> "25";
num2(26) -> "26";
num2(27) -> "27";
num2(28) -> "28";
num2(29) -> "29";

num2(30) -> "30";
num2(31) -> "31";
num2(32) -> "32";
num2(33) -> "33";
num2(34) -> "34";
num2(35) -> "35";
num2(36) -> "36";
num2(37) -> "37";
num2(38) -> "38";
num2(39) -> "39";

num2(40) -> "40";
num2(41) -> "41";
num2(42) -> "42";
num2(43) -> "43";
num2(44) -> "44";
num2(45) -> "45";
num2(46) -> "46";
num2(47) -> "47";
num2(48) -> "48";
num2(49) -> "49";

num2(50) -> "50";
num2(51) -> "51";
num2(52) -> "52";
num2(53) -> "53";
num2(54) -> "54";
num2(55) -> "55";
num2(56) -> "56";
num2(57) -> "57";
num2(58) -> "58";
num2(59) -> "59".


bnum2(0) -> <<"00">>;
bnum2(1) -> <<"01">>;
bnum2(2) -> <<"02">>;
bnum2(3) -> <<"03">>;
bnum2(4) -> <<"04">>;
bnum2(5) -> <<"05">>;
bnum2(6) -> <<"06">>;
bnum2(7) -> <<"07">>;
bnum2(8) -> <<"08">>;
bnum2(9) -> <<"09">>;

bnum2(10) -> <<"10">>;
bnum2(11) -> <<"11">>;
bnum2(12) -> <<"12">>;
bnum2(13) -> <<"13">>;
bnum2(14) -> <<"14">>;
bnum2(15) -> <<"15">>;
bnum2(16) -> <<"16">>;
bnum2(17) -> <<"17">>;
bnum2(18) -> <<"18">>;
bnum2(19) -> <<"19">>;

bnum2(20) -> <<"20">>;
bnum2(21) -> <<"21">>;
bnum2(22) -> <<"22">>;
bnum2(23) -> <<"23">>;
bnum2(24) -> <<"24">>;
bnum2(25) -> <<"25">>;
bnum2(26) -> <<"26">>;
bnum2(27) -> <<"27">>;
bnum2(28) -> <<"28">>;
bnum2(29) -> <<"29">>;

bnum2(30) -> <<"30">>;
bnum2(31) -> <<"31">>;
bnum2(32) -> <<"32">>;
bnum2(33) -> <<"33">>;
bnum2(34) -> <<"34">>;
bnum2(35) -> <<"35">>;
bnum2(36) -> <<"36">>;
bnum2(37) -> <<"37">>;
bnum2(38) -> <<"38">>;
bnum2(39) -> <<"39">>;

bnum2(40) -> <<"40">>;
bnum2(41) -> <<"41">>;
bnum2(42) -> <<"42">>;
bnum2(43) -> <<"43">>;
bnum2(44) -> <<"44">>;
bnum2(45) -> <<"45">>;
bnum2(46) -> <<"46">>;
bnum2(47) -> <<"47">>;
bnum2(48) -> <<"48">>;
bnum2(49) -> <<"49">>;

bnum2(50) -> <<"50">>;
bnum2(51) -> <<"51">>;
bnum2(52) -> <<"52">>;
bnum2(53) -> <<"53">>;
bnum2(54) -> <<"54">>;
bnum2(55) -> <<"55">>;
bnum2(56) -> <<"56">>;
bnum2(57) -> <<"57">>;
bnum2(58) -> <<"58">>;
bnum2(59) -> <<"59">>.


