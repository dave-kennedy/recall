#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "commands.h"

Result results[NUM_COMMANDS];

int main(int argc, char **argv)
{
	int a, c, found, r;
	char current[MAX_TEXT_LENGTH + MAX_DESC_LENGTH + MAX_KEYWORDS_LENGTH
		+ MAX_SYNONYM_LENGTH + 4];

	for (a = 1; a < argc; ++a)
		convert_lower(argv[a]);
	for (c = 0; c < NUM_COMMANDS; ++c) {
		current[0] = '\0';
		sprintf(current, "%s %s %s", commands[c].text,
				commands[c].description, commands[c].keywords);
		convert_lower(current);
		append_synonyms(current);
		/* count words in both argv and current */
		found = 0;
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

void convert_lower(char *string)
{
	while (*string != '\0') {
		*string = tolower(*string);
		++string;
	}
}

void append_synonyms(char *string)
{
	int s, num_words, w;
	char *words[MAX_SYNONYM_LENGTH];

	for (s = 0; s < NUM_SYNONYMS; ++s) {
		num_words = split_string(synonyms[s], words);
		for (w = 0; w < num_words; ++w)
			if (strstr(string, words[w]) != NULL) {
				strcat(string, synonyms[s]);
				break;
			}
	}
}

int split_string(char *string, char **words)
{
	char *word;
	int i;

	word = strtok(string, " ");
	for (i = 0; word != NULL; ++i) {
		words[i] = malloc(strlen(word) + 1);
		strcpy(words[i], word);
		word = strtok(NULL, " ");
	}
	return i;
}

int compare_results(const void *a, const void *b)
{
	Result *r1;
	Result *r2;

	r1 = (Result *)a;
	r2 = (Result *)b;
	return r2->found - r1->found;
}
