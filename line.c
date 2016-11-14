/* standard includes */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* application includes */
#include "line.h"

int currentLine = -1;

void addLine() {
	currentLine++;
}

void setId(char *id) {
	lines[currentLine].id = (char*)malloc(strlen(id) + 1 * sizeof(char));
	strcpy(lines[currentLine].id, id);
}

void setName(char *name) {
	lines[currentLine].name= (char*)malloc(strlen(name) + 1 * sizeof(char));
	strcpy(lines[currentLine].name, name);
}

void setStatusSeverity(int statusSeverity) {
	lines[currentLine].statusSeverity = statusSeverity;
}

void setStatusSeverityDescription(char *statusSeverityDescription) {
	lines[currentLine].statusSeverityDescription = (char*)malloc(strlen(statusSeverityDescription) + 1 * sizeof(char));
	strcpy(lines[currentLine].statusSeverityDescription, statusSeverityDescription);
}

void setReason(char *reason) {
	lines[currentLine].reason = (char*)malloc(strlen(reason) + 1 * sizeof(char));
	strcpy(lines[currentLine].reason, reason);
}
