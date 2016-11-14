/* standard includes */
#include <stdio.h>
#include <string.h>

/* holder for line info */
struct line_st {
	char *id;
	char *name;
	int statusSeverity;
	char *statusSeverityDescription;
	char *reason;
};

