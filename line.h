/* standard includes */
#include <stdio.h>
#include <string.h>

#define KNUMBEROFLINES	11

/* holder for line info */
struct line_st {
	char *id;
	char *name;
	int statusSeverity;
	char *statusSeverityDescription;
	char *reason;
};

/* holder of lines */
struct line_st lines[KNUMBEROFLINES];

void addLine();
void setId(char *id);
void setName(char *name);
void setStatusSeverity(int statusSeverity);
void setStatusSeverityDescription(char *statusSeverityDescription);
void setReason(char *reason);
