/* standard includes */
#include <stdio.h>

/* application includes */
#include "parse.h"
  
/* json-c (https://github.com/json-c/json-c) */
#include <json.h>

/* printing the value corresponding to boolean, double, integer and strings */
void print_json_value(struct json_object *jobj) {
 	printf(">>> print_json_value\n"); 

	enum json_type type = json_object_get_type(jobj); /* getting the type of the json object */
	printf("type: %u\n", type);
  	switch (type) {
 		case json_type_null:
		case json_type_object:
		case json_type_array:
     		break;

    	case json_type_boolean:
			printf("value: %s\n", json_object_get_boolean(jobj)? "true": "false");
            break;

    	case json_type_double:
        	printf("value: %lf\n", json_object_get_double(jobj));
            break;

    	case json_type_int:
        	printf("value: %d\n", json_object_get_int(jobj));
            break;

    	case json_type_string:
        	printf("value: %s\n", json_object_get_string(jobj));
            break;
	}
}

void json_parse_array(struct json_object *jobj, char *key) {
 	printf(">>> json_parse_array\n"); 

	void json_parse(struct json_object *jobj); /* forward Declaration */
	enum json_type type;

	struct json_object *jarray = jobj; /* simply get the array */
  	if (key) {
		struct json_object *o = NULL;
    	if (json_object_object_get_ex(jobj, key, &o)) {  /* getting the array if it is a key value pair */
			jarray = o;
		}  	
	}	

  	int arraylen = json_object_array_length(jarray); /* getting the length of the array */
  	printf("Array Length: %d\n", arraylen);
  
	int i;
  	struct json_object *jvalue;

  	for (i=0; i< arraylen; i++) {
    	jvalue = json_object_array_get_idx(jarray, i); /* getting the array element at position i */
    	type = json_object_get_type(jvalue);
		printf("type: %u\n", type);

    	if (type == json_type_array) {
    	  	json_parse_array(jvalue, NULL);

    	} else if (type != json_type_object) {
	     	printf("value[%d]: ",i);
    	  	print_json_value(jvalue);
    	
		} else {
			json_parse(jvalue);
  		}	
  	}	
}

/* parsing the json object */
void json_parse(struct json_object *jobj) {
	printf(">>> json_parse\n");	

	enum json_type type = json_object_get_type(jobj); /* getting the type of the json object */
    printf("type: %u\n", type);

	if (type == json_type_array) {
		json_parse_array(jobj, NULL);
		return;
	
	} else if (type != json_type_object) {
		return;
	}

	json_object_object_foreach(jobj, key, val) { /* passing through every array element */
		printf("Key is [%s] %d", key, (val == NULL));

		type = json_object_get_type(val);
		printf("type: %u\n", type);
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
