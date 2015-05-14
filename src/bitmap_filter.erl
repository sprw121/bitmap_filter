-module(bitmap_filter).

-export([init/0, filter/1]).
-on_load(init/0).

init() ->
    PrivDir = case code:priv_dir(?MODULE) of
        {error, _} ->
            EbinDir = filename:dirname(code:which(?MODULE)),
            AppPath = filename:dirname(EbinDir),
            filename:join(AppPath, "priv");
        Path ->
            Path
    end,
    erlang:load_nif(filename:join(PrivDir, "bitmap_filter"), 0).

% Hack - overriden by init, which is called in on_load.
% I couldn't find another way that the compiler or code load didn't complain about.
filter(DefaultArgs) ->
    DefaultArgs.
