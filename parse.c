/* standard includes */
#include <stdio.h>
#include <string.h>

/* application includes */
#include "parse.h"
#include "line.h"
  
/* json-c (https://github.com/json-c/json-c) */
#include <json.h>

/* forward Declaration */
void print_json_value(struct json_object *jobj);
void json_parse_array(struct json_object *jobj, char *key);
void json_parse(struct json_object *jobj);
void stateUpdate(char *key);

typedef enum {
	TYPE,
	ID, NAME,
	STATUSSEVERITY, STATUSSEVERITYDESCRIPTION, REASON,
	SKIP
} parse_field;

/* the current field of the parser */
parse_field field = SKIP;

/* state flags */
typedef enum { false, true } bool;
bool isInLine = false;
bool isInLineStatuses = false;

/* printing the value corresponding to boolean, double, integer and strings */
void print_json_value(struct json_object *jobj) {
 	//printf(">>> print_json_value\n"); 

	enum json_type type = json_object_get_type(jobj); /* getting the type of the json object */
	//printf("type: %u\n", type);
  	switch (type) {
 		case json_type_null:
		case json_type_object:
		case json_type_array:
     		break;

    	case json_type_boolean:
			//printf("value: %s\n", json_object_get_boolean(jobj)? "true": "false");
            break;

    	case json_type_double:
        	//printf("value: %lf\n", json_object_get_double(jobj));
            break;

    	case json_type_int:
		{
			int value = json_object_get_int(jobj);
        	//printf("value: %d\n", value); 
       		if (field == STATUSSEVERITY) { 
				setStatusSeverity(value);
			} 	
		}
		   break;

    	case json_type_string:
		{
			const char *value = json_object_get_string(jobj);
        	//printf("value: %s\n", value); 

			if (field == TYPE) {
 				if (strncmp("Tfl.Api.Presentation.Entities.Line, Tfl.Api.Presentation.Entities", value, strlen(value)) == 0) {
					addLine();
					isInLine = true;
					isInLineStatuses = false;
 				}			
			
			} else if (field == ID) {
				setId((char *)value);
			} else if (field == NAME) {
				setName((char *)value);
			} else if (field == STATUSSEVERITYDESCRIPTION) {
				setStatusSeverityDescription((char *)value);
			} else if (field == REASON) {
				if (value != NULL) {
					setReason((char *)value);
				}
			}
		} 
			break;
	}
}

void json_parse_array(struct json_object *jobj, char *key) {
 	//printf(">>> json_parse_array\n"); 

	enum json_type type;

	struct json_object *jarray = jobj; /* simply get the array */
  	if (key) {
		struct json_object *o = NULL;
    	if (json_object_object_get_ex(jobj, key, &o)) {  /* getting the array if it is a key value pair */
			jarray = o;
		}  	
	}	

  	int arraylen = json_object_array_length(jarray); /* getting the length of the array */
  	//printf("Array Length: %d\n", arraylen);
  
	int i;
  	struct json_object *jvalue;

  	for (i=0; i< arraylen; i++) {
    	jvalue = json_object_array_get_idx(jarray, i); /* getting the array element at position i */
    	type = json_object_get_type(jvalue);

    	if (type == json_type_array) {
    	  	json_parse_array(jvalue, NULL);

    	} else if (type != json_type_object) {
	     	//printf("value[%d]: ", i);
    	  	print_json_value(jvalue);
    	
		} else {
			json_parse(jvalue);
  		}	
  	}	
}

/* parsing the json object */
void json_parse(struct json_object *jobj) {
	//printf(">>> json_parse\n");	

	enum json_type type = json_object_get_type(jobj); /* getting the type of the json object */
    //printf("type: %u\n", type);

	if (type == json_type_array) {
		json_parse_array(jobj, NULL);
		return;
	
	} else if (type != json_type_object) {
		return;
	}

	json_object_object_foreach(jobj, key, val) { /* passing through every array element */
		//printf("Key is [%s] %d\n", key, (val == NULL));

		stateUpdate(key);

		type = json_object_get_type(val);
    	switch (type) {
			case json_type_null:
				break;

      		case json_type_boolean: 
      		case json_type_double: 
      		case json_type_int: 
      		case json_type_string: 
				print_json_value(val);
            	break; 

      		case json_type_object:
			{
				struct json_object *o = NULL;
				if (json_object_object_get_ex(jobj, key, &o)) {
                	json_parse(o);
				}
			}
                break;

      		case json_type_array:
            	json_parse_array(jobj, key);
            	break;
    	}
	}	
}

/* state machine */
void stateUpdate(char *key) {
	field = SKIP;

	if (strncmp("$type", key, strlen(key)) == 0) {
		field = TYPE;
	}

	if (isInLine == true && isInLineStatuses == false) {
		if (strncmp("id", key, strlen(key)) == 0) {
			field = ID;	
		} else if (strncmp("name", key, strlen(key)) == 0) {
			field = NAME;
		} else if (strncmp("lineStatuses", key, strlen(key)) == 0) {
			isInLineStatuses = true;
		}
	
	} else if (isInLine == true && isInLineStatuses == true) { 
		if (strncmp("statusSeverity", key, strlen(key)) == 0) {
             field = STATUSSEVERITY;
         } else if (strncmp("statusSeverityDescription", key, strlen(key)) == 0) {
             field = STATUSSEVERITYDESCRIPTION;
         } else if (strncmp("reason", key, strlen(key)) == 0) {
             field = REASON;
       }	
	}
}

