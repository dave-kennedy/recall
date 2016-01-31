# recall

The purpose of this program is to help me remember bash commands.

## how?

recall is invoked with a list of arguments describing the desired operation,
e.g.:

```bash
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
Command commands[NUM_COMMANDS] = {
	/* command                     description        additional keywords */
	{ "amixer -Mq set Master 1%-", "decrease volume", "down lower sound" },
	{ "amixer -Mq set Master 1%+", "increase volume", "raise sound up" },
	...
};
```

If you find yourself defining the same additional keywords for lots of commands,
you can instead define synonyms which apply to all commands:

```c
Synonym synonyms[NUM_SYNONYMS] = {
	"display find list print show view",
	"information status",
	...
};
```

## why?

The built-in history and tab completion in bash is only helpful if you know part
of the command you're looking for. For instance, if I want to print a list of
orphaned packages I might not remember `pacman -Qdt` but I will probably at
least remember `pacman`. So I can try to find it in my command line history (if
it goes back that far) or I can scan the output of `man pacman` for the word
"orphan." This gets old fast.

However, if I want to increase the volume, I often forget that I even need to
use `amixer`, let alone the rest of the command. So I have to ask Google or
maintain a list of commands and their descriptions. This program is just a fancy
replacement for that list.
