-module(bitmap_filter).

-export([init/0, filter/1]).
-on_load(init/0).

init() ->
    erlang:load_nif("./bitmap_filter", 0).

% Hack - overriden by init, which is called in on_load.
% I couldn't find another way that the compiler or code load didn't complain about.
filter(DefaultArgs) ->
    DefaultArgs.
