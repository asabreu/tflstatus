/* standard includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <time.h>

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

#define KLINENAMEWIDTH	20

/* forward declaration */
char *centerStr(char *str);
char *repeatStr(char *str, size_t count);

void displayDateTime() {
	time_t timer;
	char buffer[26];
	struct tm* tm_info;
	
	time(&timer);
	tm_info = localtime(&timer);

	strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
	puts(buffer);
}

void displayLineStatus(struct line_st *line) {
	char *id = line->id;
	char *name = centerStr(line->name);

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
	
	printf("\t%s\n", line->statusSeverityDescription);
	
	if (line->reason != NULL) {
		printf(KREASON "%s" KRESET, line->reason);
		printf("\n");
	}
}

char *centerStr(char *str) {
	int strLength = strlen(str);
	int availableSpace = KLINENAMEWIDTH - strLength;
	int leftPadding = 0;
	int rightPadding = 0;
	if (availableSpace < 0) {
		availableSpace = 0;
	
	} else {
		int m = availableSpace % 2;
		if (m == 0 ) {
			leftPadding = availableSpace/2;
			rightPadding = leftPadding;	
		} else {
			leftPadding = availableSpace/2;
			rightPadding = availableSpace - leftPadding;	
		}
	}
	
	char *padding = " ";
	char *leftString = repeatStr(padding, leftPadding);
	char *rightString = repeatStr(padding, rightPadding);

	char *final = (char *) malloc(1 + KLINENAMEWIDTH); 
   	strcpy(final, leftString);
	strcat(final, str);
	strcat(final, rightString);

	return final;
}

char *repeatStr(char *str, size_t count) {
    if (count == 0) return NULL;
    char *ret = malloc (strlen(str) * count + count);
    if (ret == NULL) return NULL;
    strcpy(ret, str);
    while (--count > 0) {
        strcat(ret, str);
    }

    return ret;
}
