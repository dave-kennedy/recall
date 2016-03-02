# recall

The purpose of this program is to help me remember shell commands.

## how?

recall is invoked with a list of arguments describing the desired operation,
e.g.:

```sh
$ recall volume up
amixer -Mq set Master 1%+
    increase volume
amixer -Mq set Master 1%-
    decrease volume
```

The output includes one line for each command matching the arguments along with
a description.

Commands are defined in commands.h and can optionally include a description and
a list of additional keywords:

```c
Command commands[] = {
	/* command                     description        additional keywords */
	{ "amixer -Mq set Master 1%-", "decrease volume", "down lower sound" },
	{ "amixer -Mq set Master 1%+", "increase volume", "raise sound up" },
	...
};
```

If you find yourself defining the same additional keywords for lots of commands,
you can instead define synonyms which apply to all commands:

```c
Synonym synonyms[] = {
	"display find list print show view",
	"information status",
	...
};
```

## why?

Shell history and tab completion is only helpful if you know part of the command
you're looking for. For instance, if I want to increase the volume, I often
forget that I even need to use `amixer`, let alone the rest of the command. So I
have to ask Google or maintain a list of commands and their descriptions. This
program is just a fancy replacement for that list.
