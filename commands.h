#define NUM_COMMANDS 8

Command commands[NUM_COMMANDS] = {
	/* command                     description        additional keywords */
	{ "amixer -Mq set Master 1%-", "decrease volume", "lower down" },
	{ "amixer -Mq set Master 1%+", "increase volume", "raise up" },
	{ "makepkg -sri", "build and install a package using a PKGBUILD" },
	{ "makepkg -efi", "rebuild and reinstall a package using a PKGBUILD" },
	{ "pacman -Qdt", "list orphaned packages", "find" },
	{ "pacman -Qe", "list explicitly installed packages", "find" },
	{ "pacman -Ql [package]", "list files owned by package", "find" },
	{ "pacman -Qo [file]", "list packages that own file", "find owned" }
};
