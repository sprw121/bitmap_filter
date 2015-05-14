REBAR := `pwd`/rebar

all: compile

compile:
	@$(REBAR) compile

clean:
	@$(REBAR) clean
	c_src/build.sh clean

ct: compile
	ct_run -dir test -pa ebin -verbosity 0 -logdir .ct/logs -erl_args +K true +A 10

.PHONY: compile ct
