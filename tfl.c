#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "jsmn.h"

#include "json.h"
#include "log.h"
#include "buf.h"

char URL[] = "https://api.tfl.gov.uk/line/mode/tube/status?detail=true";

int main(void)
{
    char *js = json_fetch(URL);

    jsmntok_t *tokens = json_tokenise(js);

    //typedef enum { START, OBJECT, KEY, PRINT, SKIP, STOP } parse_state;
    //parse_state state = START;

    size_t object_tokens = 0;

	for (size_t i = 0; i < JSON_TOKENS; i++)
    //for (size_t i = 0, j = 1; j > 0; i++, j--)
    {
        jsmntok_t *t = &tokens[i];

        // Should never reach uninitialized tokens
        log_assert(t->start != -1 && t->end != -1);

        //if (t->type == JSMN_ARRAY || t->type == JSMN_OBJECT)
        //    j += t->size;
 	
 		printf("type: %u\n", t->type);
	
 		if (t->type == JSMN_STRING && json_token_streq(js, t, "id")) {
			char *key = json_token_tostr(js, t);
	    	printf("\ntoken:%s\n", key);

			jsmntok_t *tv = &tokens[i+1];
			char *value = json_token_tostr(js, tv);
			printf("value:%s\n", value);
         
          	object_tokens = t->size;
          	printf("tokens: %zu\n", object_tokens);	
		}

/*
        switch (state)
        {
            case START:
                if (t->type != JSMN_ARRAY)
                	log_die("Invalid response: root element must be an array.");

                state = KEY;
                object_tokens = t->size;

                if (object_tokens == 0)
                    state = STOP;

                break;

            case KEY:
                object_tokens--;

                if (t->type != JSMN_STRING)
                    log_die("Invalid response: object keys must be strings.");

                state = SKIP;

                for (size_t i = 0; i < sizeof(KEYS)/sizeof(char *); i++)
                {
                    if (json_token_streq(js, t, KEYS[i]))
                    {
                        printf("%s: ", KEYS[i]);
                        state = PRINT;
                        break;
                    }
                }

                break;

            case SKIP:
                if (t->type != JSMN_STRING && t->type != JSMN_PRIMITIVE)
                    log_die("Invalid response: object values must be strings or primitives.");

                object_tokens--;
                state = KEY;

                if (object_tokens == 0)
                    state = STOP;

                break;

            case PRINT:
                if (t->type != JSMN_STRING && t->type != JSMN_PRIMITIVE)
                    log_die("Invalid response: object values must be strings or primitives.");

                char *str = json_token_tostr(js, t);
                puts(str);

                object_tokens--;
                state = KEY;

                if (object_tokens == 0)
                    state = STOP;

                break;

            case STOP:
                // Just consume the tokens
                break;

            default:
                log_die("Invalid state %u", state);
        }
*/
    }

    return 0;
}
