#ifndef FETCH_H
#define FETCH_H

/* standard includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/* libcurl (http://curl.haxx.se/libcurl/c) */
#include <curl/curl.h>

/* holder for curl fetch */
struct curl_fetch_st {
    char * payload;
    size_t size;
};

/* callback for curl fetch */
size_t curl_callback (void * contents, size_t size, size_t nmemb, void * userp);

/* fetch and return url body via curl */
CURLcode curl_fetch_url(CURL * ch, const char * url, struct curl_fetch_st * fetch);

#endif
