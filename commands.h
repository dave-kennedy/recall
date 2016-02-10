Synonym synonyms[] = {
	"display find list print show view",
	"information status",
	"remote upstream"
};

Command commands[] = {
	/* command                     description        additional keywords */
	{ "amixer -Mq set Master 1%-", "decrease volume", "down lower sound" },
	{ "amixer -Mq set Master 1%+", "increase volume", "raise sound up" },
	{ "curl -LO [url]", "download a file" },
	{ "date -I", "print date in ISO 8601 format" },
	{ "date -Is", "print date and time in ISO 8601 format" },
	{ "dkms status [module]", "show status of dynamic kernel module" },
	{ "diff -y --suppress-common-lines [file1] [file2]",
		"compare files side by side", "difference" },
	{ "expr [expression]", "evaluate expression",
		"add arithmetic divide math multiply numbers subtract" },
	{ "fc-cache -frv", "rebuild fontconfig cache", "fonts" },
	{ "fc-list", "list fonts known by fontconfig" },
	{ "fc-match [font]", "show font that would be used by fontconfig",
		"resolve substitute" },
	{ "free [device] -h", "show free space on device", "disk drive" },
	{ "git branch -vv", "list local branches and remote repositories" },
	{ "git push -u [remote] [branch]",
		"push local branch to remote repository", "create new" },
	{ "git remote -v", "list remote repositories" },
	{ "ip link show [device]", "show status of network adapter",
		"ethernet wifi wireless" },
	{ "iw dev [device] link", "show status of wireless network adapter",
		"wifi" },
	{ "makepkg -si", "build and install package using PKGBUILD" },
	{ "makepkg -fi", "rebuild and reinstall package using PKGBUILD" },
	{ "pacman -Qdt", "list orphaned packages" },
	{ "pacman -Qe", "list explicitly installed packages" },
	{ "pacman -Ql [package]", "list files owned by package" },
	{ "pacman -Qo [file]", "list packages that own file", "owned" }
};

#define NUM_COMMANDS (sizeof(commands) / sizeof(Command))
#define NUM_SYNONYMS (sizeof(synonyms) / sizeof(Synonym))
