/**
 * An application to retrieve tube status from TFL and display the output in the UNIX terminal
 *
 * Requirements:
 *
 * json-c - https://github.com/json-c/json-c
 * libcurl - http://curl.haxx.se/libcurl/c
 *
 * Build:
 *
 * make
 *
 * Run:
 *
 * ./tflstatus
 *
 */

/* standard includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/* application includes */
#include "fetch.h"
#include "parse.h"
#include "display.h"

/* json-c (https://github.com/json-c/json-c) */
#include <json.h>

/* libcurl (http://curl.haxx.se/libcurl/c) */
#include <curl/curl.h>

const char *VERSION = "1.0";

int is_cmd_valid(char *cmd) {
	if (strncmp("--help", cmd, strlen(cmd)) == 0 || strncmp("help", cmd, strlen(cmd)) == 0) {
		return 1;
	}

	return 0;
}

int main(int argc, char *argv[]) {

	if (argc != 1) {
		if (argc != 2) {
			int i;
    	printf("tflstatus: The following are not valid commands. See 'tflstatus --help'.\n");
  		for (i = 1; i < argc; i++) {
				char *cmd = argv[i];
				if (!is_cmd_valid(cmd)) printf("'%s' ", argv[i]);
			}

			printf("\n");

		} else {
			char *cmd = argv[1];
			if (is_cmd_valid(cmd)) {
				printf("usage: %s [--version]\n", argv[0]);

			} else if (strncmp("--version", cmd, strlen(cmd)) == 0) {
				printf("%s version %s\n", argv[0], VERSION);

			} else {
				printf("tflstatus: '%s' is not a tflstatus command. See 'tflstatus --help'.\n", cmd);
				printf("usage: %s [--version]\n", argv[0]);
			}
		}

		return 0;
	}

    CURL *ch;                                               /* curl handle */
    CURLcode rcode;                                         /* curl result code */

    struct json_object *json;                               /* json post body */
    enum json_tokener_error jerr = json_tokener_success;    /* json parse error */

    struct curl_fetch_st curl_fetch;                        /* curl fetch struct */
    struct curl_fetch_st *cf = &curl_fetch;                 /* pointer to fetch struct */
    struct curl_slist *headers = NULL;                      /* http headers to send with request */

    /* url to tfl api site */
    char *url = "https://api.tfl.gov.uk/line/mode/tube/status?detail=true";

    /* init curl handle */
    if ((ch = curl_easy_init()) == NULL) {
        /* log error */
        fprintf(stderr, "ERROR: Failed to create curl handle in fetch_session");
        /* return error */
        return 1;
    }

    /* set content type */
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");

    /* set curl options */
    curl_easy_setopt(ch, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(ch, CURLOPT_HTTPHEADER, headers);

    /* fetch page and capture return code */
    rcode = curl_fetch_url(ch, url, cf);

    /* cleanup curl handle */
    curl_easy_cleanup(ch);

    /* free headers */
    curl_slist_free_all(headers);

    /* check return code */
    if (rcode != CURLE_OK || cf->size < 1) {
        /* log error */
        fprintf(stderr, "ERROR: Failed to fetch url (%s) - curl said: %s",
            url, curl_easy_strerror(rcode));
        /* return error */
        return 2;
    }

    /* check payload */
    if (cf->payload != NULL) {
        /* print result */
        //printf("CURL Returned: \n%s\n", cf->payload);
        /* parse return */
        json = json_tokener_parse_verbose(cf->payload, &jerr);
        /* free payload */
        free(cf->payload);

    } else {
        /* error */
        fprintf(stderr, "ERROR: Failed to populate payload");
        /* free payload */
        free(cf->payload);
        /* return */
        return 3;
    }

    /* check error */
    if (jerr != json_tokener_success) {
        /* error */
        fprintf(stderr, "ERROR: Failed to parse json string");
        /* free json object */
        json_object_put(json);
        /* return */
        return 4;
    }

    /* debugging */
    //printf("Parsed JSON: %s\n", json_object_to_json_string(json));

	/* parse */
	json_parse(json);

	/* display date time */
	display_date_time();

	/* display line status */
	for	(int l = 0; l < KNUMBEROFLINES; l++) {
		display_line_status(&lines[l]);
	}
	
	printf("\n"); /* add blank footer line for additional spacing */

	/* exit */
	return 0;
}
