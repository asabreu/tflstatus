/* standard includes */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* application includes */
#include "line.h"

int current_line = -1;

void add_line() {
	current_line++;
}

void set_id(char * id) {
	lines[current_line].id = (char*)malloc(strlen(id) + 1 * sizeof(char));
	strcpy(lines[current_line].id, id);
}

void set_name(char * name) {
	lines[current_line].name= (char*)malloc(strlen(name) + 1 * sizeof(char));
	strcpy(lines[current_line].name, name);
}

void set_status_severity(int status_severity) {
	lines[current_line].status_severity = status_severity;
}

void set_status_severity_description(char * status_severity_description) {
	lines[current_line].status_severity_description = (char*)malloc(strlen(status_severity_description) + 1 * sizeof(char));
	strcpy(lines[current_line].status_severity_description, status_severity_description);
}

void set_reason(char * reason) {
	lines[current_line].reason = (char*)malloc(strlen(reason) + 1 * sizeof(char));
	strcpy(lines[current_line].reason, reason);
}
