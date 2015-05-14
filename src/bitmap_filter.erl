-module(bitmap_filter).

-export([init/0, filter/1]).
-on_load(init/0).

%% NOTE : this is a bad idea
priv_dir(Mod) ->
    Ebin = filename:dirname(code:which(Mod)),
    filename:join(filename:dirname(Ebin), "priv").

init() ->
    PrivDir = priv_dir(strg),
    ok = erlang:load_nif(filename:join(PrivDir, "bitmap_filter"), 0).

 % Hack - overriden by init, which is called in on_load.
 % I couldn't find another way that the compiler or code load didn't complain about.
 filter(DefaultArgs) ->
    DefaultArgs.
