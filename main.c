#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "commands.h"

Result results[NUM_COMMANDS];

int main(int argc, char *argv[])
{
	char current[MAX_TEXT_LENGTH + MAX_DESC_LENGTH + MAX_KEYWORDS_LENGTH];
	int a, c, found, r;

	/* convert argv to lowercase */
	for (a = 1; a < argc; ++a)
		convert_lower(argv[a]);
	for (c = 0; c < NUM_COMMANDS; ++c) {
		sprintf(current, "%s %s %s", commands[c].text,
				commands[c].description, commands[c].keywords);
		/* convert current to lowercase */
		convert_lower(current);
		found = 0;
		/* count words in both argv and current */
		for (a = 1; a < argc; ++a)
			if (strstr(current, argv[a]) != NULL)
				++found;
		if (found == 0)
			continue;
		results[c].found = found;
		strcpy(results[c].text, commands[c].text);
		strcpy(results[c].description, commands[c].description);
	}
	/* sort results with most words in common with argv at top */
	qsort(results, NUM_COMMANDS, sizeof(*results), compare_results);
	/* only print MAX_RESULTS results */
	for (r = 0; r < MAX_RESULTS && results[r].found > 0; ++r) {
		printf("%s\n", results[r].text);
		printf("    %s\n", results[r].description);
	}
	return 0;
}

int compare_results(const void *a, const void *b)
{
	Result *r1 = (Result *)a;
	Result *r2 = (Result *)b;

	return r2->found - r1->found;
}

void convert_lower(char *string)
{
	while (*string != '\0') {
		*string = tolower(*string);
		++string;
	}
}
