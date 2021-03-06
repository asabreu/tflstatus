/* standard includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <time.h>
#include <ctype.h>

/* application includes */
#include "display.h"

#define KBAKERLOO		"\033[38;5;231;48;5;94m"
#define KCENTRAL		"\033[38;5;231;48;5;160m"
#define KCIRCLE			"\033[38;5;16;48;5;220m"
#define KDISTRICT		"\033[38;5;231;48;5;22m"
#define KHAMMERSMITH	"\033[38;5;16;48;5;175m"
#define KJUBILEE		"\033[38;5;231;48;5;102m"
#define KMETROPOLITAN	"\033[38;5;231;48;5;89m"
#define KNORTHEN		"\033[38;5;231;48;5;16m"
#define KPICCADILLY		"\033[38;5;231;48;5;19m"
#define KVICTORIA		"\033[38;5;16;48;5;38m"
#define KWATERLOO		"\033[38;5;16;48;5;115m"

#define KRESET			"\033[m"
#define KREASON			"\x1B[33m" /* light yellow */
#define KRED			"\x1B[31m"

#define KLINENAMEWIDTH	20

/* forward declaration */
char *center_string(char *str);
char *repeat_string(char *str, size_t count);
void string_replace(char *target, const char *needle, const char *replacement);
void convert_to_uppercase(char *str);

void display_date_time() {
	printf("\n"); /* add blank header line for additional spacing */

	time_t timer;
	char buffer[26];
	struct tm* tm_info;

	time(&timer);
	tm_info = localtime(&timer);

	strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
	puts(buffer);
}

void display_line_status(struct line_st *line) {
	char *id = line->id;
	char *name = center_string(line->name);

	if (strncmp("bakerloo", id, strlen(id)) == 0) {
		printf(KBAKERLOO "%s" KRESET, name);
	} else if (strncmp("central", id, strlen(id)) == 0) {
		printf(KCENTRAL "%s" KRESET, name);
 	} else if (strncmp("circle", id, strlen(id)) == 0) {
		printf(KCIRCLE "%s" KRESET, name);
	} else if (strncmp("district", id, strlen(id)) == 0) {
		printf(KDISTRICT "%s" KRESET, name);
	} else if (strncmp("hammersmith-city", id, strlen(id)) == 0) {
		printf(KHAMMERSMITH "%s" KRESET, name);
	} else if (strncmp("jubilee", id, strlen(id)) == 0) {
		printf(KJUBILEE "%s" KRESET, name);
	} else if (strncmp("metropolitan", id, strlen(id)) == 0) {
		printf(KMETROPOLITAN "%s" KRESET, name);
	} else if (strncmp("northern", id, strlen(id)) == 0) {
		printf(KNORTHEN "%s" KRESET, name);
	} else if (strncmp("piccadilly", id, strlen(id)) == 0) {
		printf(KPICCADILLY "%s" KRESET, name);
	} else if (strncmp("victoria", id, strlen(id)) == 0) {
		printf(KVICTORIA "%s" KRESET, name);
	} else if (strncmp("waterloo-city", id, strlen(id)) == 0) {
		printf(KWATERLOO "%s" KRESET, name);
	} else {
		printf("%s", name);
	}

	if (line->status_severity != 10) { /* 10 = Good Service */
		printf(KRED "\t%s" KRESET, line->status_severity_description);
		printf("\n");
	} else {
		printf("\t%s\n", line->status_severity_description);
	}

	/* remove mention of the line in the reason to make it shorter */
	if (line->reason != NULL) {
		/* lower case */
		char *suffix = " Line: ";
		char *needle = (char *) malloc(1 + strlen(line->name) + strlen(suffix));
		strcpy(needle, line->name);
		strcat(needle, suffix);

		char *original = line->reason;
		string_replace(original, needle, "");

		/* upper case */
		convert_to_uppercase(needle);
		string_replace(original, needle, "");

		char *empty_string = repeat_string(" ", KLINENAMEWIDTH);
		printf(KREASON "\%s\t%s" KRESET, empty_string, original);
		printf("\n");
	}
}

char *center_string(char *str) {
	int str_length = strlen(str);
	int available_space = KLINENAMEWIDTH - str_length;
	int left_padding = 0;
	int right_padding = 0;
	if (available_space < 0) {
		available_space = 0;

	} else {
		int m = available_space % 2;
		if (m == 0 ) {
			left_padding = available_space/2;
			right_padding = left_padding;
		} else {
			left_padding = available_space/2;
			right_padding = available_space - left_padding;
		}
	}

	char *leftString = repeat_string(" ", left_padding);
	char *rightString = repeat_string(" ", right_padding);

	char *final = (char *) malloc(1 + KLINENAMEWIDTH);
	strcpy(final, leftString);
	strcat(final, str);
	strcat(final, rightString);

	return final;
}

char *repeat_string(char *str, size_t count) {
    if (count == 0) return NULL;
    char *ret = malloc (strlen(str) * count + count);
    if (ret == NULL) return NULL;
    strcpy(ret, str);
    while (--count > 0) {
        strcat(ret, str);
    }

    return ret;
}

void string_replace(char *target, const char *needle, const char *replacement) {
	char buffer[2048] = { 0 };
	char *insert_point = &buffer[0];
	const char *tmp = target;
	size_t needle_len = strlen(needle);
	size_t repl_len = strlen(replacement);

	while (1) {
		const char *p = strstr(tmp, needle);

		/* walked past last occurrence of needle; copy remaining part */
		if (p == NULL) {
			strcpy(insert_point, tmp);
			break;
		}

		/* copy part before needle */
		memcpy(insert_point, tmp, p - tmp);
		insert_point += p - tmp;

		/* copy replacement string */
		memcpy(insert_point, replacement, repl_len);
		insert_point += repl_len;

		/* adjust pointers, move on */
		tmp = p + needle_len;
	}

	/* write altered string back to target */
	strcpy(target, buffer);
}

void convert_to_uppercase(char *str) {
	while (*str != '\0') {
		if (islower(*str))
			*str = toupper((unsigned char) *str);
		++str;
	}
}
