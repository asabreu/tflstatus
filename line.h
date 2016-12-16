#ifndef LINE_H
#define LINE_H

/* standard includes */
#include <stdio.h>
#include <string.h>

#define KNUMBEROFLINES	11

/* holder for line info */
struct line_st {
	char * id;
	char * name;
	int status_severity;
	char * status_severity_description;
	char * reason;
};

/* holder of lines */
struct line_st lines[KNUMBEROFLINES];

void add_line();
void set_id(char * id);
void set_name(char * name);
void set_status_severity(int status_severity);
void set_status_severity_description(char * status_severity_description);
void set_reason(char * reason);

#endif
