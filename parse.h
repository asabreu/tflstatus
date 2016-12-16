#ifndef PARSE_H
#define PARSE_H

/* standard includes */
#include <stdio.h>
 
/* json-c (https://github.com/json-c/json-c) */
#include <json.h>

/* parsing the json object */
void json_parse(struct json_object * jobj);

#endif
