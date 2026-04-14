#include <curl/curl.h>
#include <curl/curlver.h>
#include <curl/easy.h>
#include <curl/options.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CURL_RESPONSE_BUFFER_SIZE (getpagesize())
#define CURL_ERROR_PREFIX "curl error: "
CURL *easy_handle; // will be resued by threads
size_t write_callback(char *data, size_t size, size_t nmemb, void *user_buffer);
int main()
{

    char CURL_RESPONSE_BUFFER[CURL_RESPONSE_BUFFER_SIZE];
    fprintf(stdout, "%d\n", getpagesize());
    // Main https://everything.curl.dev/transfers/drive/multi.html
    // Write callback https://everything.curl.dev/transfers/callbacks/write.html
    return 0;

    // This will hold a readable error message
    char CURL_ERROR_MESSAGE_BUFFER[CURL_ERROR_SIZE]; 

    curl_version_info_data *version = curl_version_info( CURLVERSION_NOW );
    printf("Using libcurl version: %s\n", version->version);

    // Global init. Call only once in the main thread
    curl_global_init( CURL_GLOBAL_DEFAULT );

    // Initialize easy handle. 
    easy_handle = curl_easy_init();

    // Set error buffer
    CURLcode rc = curl_easy_setopt(easy_handle, CURLOPT_ERRORBUFFER, CURL_ERROR_MESSAGE_BUFFER);
    if(rc != CURLE_OK)
        fprintf(stderr, "%s %s\n", CURL_ERROR_PREFIX, curl_easy_strerror(rc));

    // Set URL
    rc = curl_easy_setopt(easy_handle, CURLOPT_URL, "https://www.di.fm/");
    if(rc != CURLE_OK)
        fprintf(stderr, "%s %s\n", CURL_ERROR_PREFIX, CURL_ERROR_MESSAGE_BUFFER);

    // Set SSL version
    rc = curl_easy_setopt(easy_handle, CURLOPT_SSLVERSION, CURL_SSLVERSION_MAX_TLSv1_3);
    if(rc != CURLE_OK)
        fprintf(stderr, "%s %s\n", CURL_ERROR_PREFIX, CURL_ERROR_MESSAGE_BUFFER);

    // Register read callback with libcurl so that we can do other things than just default fwrite call
    rc = curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, write_callback);
    if(rc != CURLE_OK)
        fprintf(stderr, "%s %s\n", CURL_ERROR_PREFIX, CURL_ERROR_MESSAGE_BUFFER);

    // libcurl will pass this pointer to our callback
    rc = curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, (void*)CURL_RESPONSE_BUFFER);
    if(rc != CURLE_OK)
        fprintf(stderr, "%s %s\n", CURL_ERROR_PREFIX, CURL_ERROR_MESSAGE_BUFFER);




    // rc should be 0 if all options setting were ok
    // Exit if any option settig failed
    if(rc)
    {
        curl_global_cleanup();
        exit(EXIT_FAILURE);
    }
 
    // All options set successfully byond this point
    // Perform the transfer
    CURLcode result = curl_easy_perform(easy_handle);
    if(result != CURLE_OK)
        fprintf(stdout, "%s %s\n", CURL_ERROR_PREFIX, CURL_ERROR_MESSAGE_BUFFER);

    fprintf(stdout, "userspace buffer @%p\n", CURL_RESPONSE_BUFFER);
    
    curl_global_cleanup();
    exit(EXIT_SUCCESS);
}

size_t write_callback(char *data, size_t size, size_t nmemb, void *user_buffer)
{
    fprintf(stdout, "Dry run. Would copy %lu bytes to the specified userspace buffer @%p\n", size * nmemb, user_buffer);

    return (size_t)size * nmemb;
}