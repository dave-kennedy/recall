#define MAX_TEXT_LENGTH 100
#define MAX_DESC_LENGTH 100
#define MAX_KEYWORDS_LENGTH 100
#define MAX_SYNONYM_LENGTH 100
#define MAX_RESULTS 3

typedef struct {
	char text[MAX_TEXT_LENGTH];
	char description[MAX_DESC_LENGTH];
	char keywords[MAX_KEYWORDS_LENGTH];
} Command;
typedef struct {
	int found;
	char text[MAX_TEXT_LENGTH];
	char description[MAX_DESC_LENGTH];
} Result;
typedef char Synonym[MAX_SYNONYM_LENGTH];

void convert_lower(char *);
void append_synonyms(char *);
int split_string(char *, char **);
int compare_results(const void *, const void *);
