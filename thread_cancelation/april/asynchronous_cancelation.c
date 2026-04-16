#include <curl/curl.h>
#include <curl/curlver.h>
#include <curl/easy.h>
#include <curl/options.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>


#define CURL_ERROR_PREFIX "curl error: "
CURL *easy_handle; // will be resued by threads
size_t write_callback(char *data, size_t size, size_t nmemb, void *user_buffer);
static size_t mem_write_callback(char *data, size_t size, size_t nmemb, void *user_buffer);

struct curl_response {
    char *data;
    size_t size;
};



int main()
{
   
    struct curl_response user_data = { .data = 0, .size = 10 };

    char *p_new_mem;
    fprintf(stdout, "p_new_mem %p\nPointer to data %p\nAllocated memory so far %lu\n", p_new_mem, user_data.data, user_data.size);
    p_new_mem = realloc((void*)user_data.data, user_data.size + 1000);

    fprintf(stdout, "p_new_mem %p\nPointer to data %p\nAllocated memory so far %lu\n", p_new_mem, user_data.data, user_data.size);
    p_new_mem = realloc((void*)user_data.data, user_data.size + 1000);

    fprintf(stdout, "p_new_mem %p\nPointer to data %p\nAllocated memory so far %lu\n", p_new_mem, user_data.data, user_data.size);
    p_new_mem = realloc((void*)user_data.data, user_data.size + 1000);

    free(p_new_mem);
    return 0;
    // Main https://everything.curl.dev/transfers/drive/multi.html
    // Write callback https://everything.curl.dev/transfers/callbacks/write.html
   

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
    rc = curl_easy_setopt(easy_handle, CURLOPT_URL, "https://dsl.sk/");
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
    rc = curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, (void*)&user_data);
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

    // Print received data
    fprintf(stdout, "%s\n", user_data.data);
    
    curl_global_cleanup();
    exit(EXIT_SUCCESS);
}

size_t write_callback(char *data, size_t size, size_t nmemb, void *user_buffer)
{
    // Realoc apropriate amount for buffer to hold data received 
    user_buffer = realloc(user_buffer, size * nmemb);
    char *str_terminator = user_buffer + (size * nmemb) + 1;
    fprintf(stdout, "curl received data at %p\n", data);
    fprintf(stdout, "Dry run. Would copy %lu bytes to the specified userspace buffer at %p\n", size * nmemb, user_buffer);

    // Copy data from lib address space to ours
    memcpy(user_buffer, data, size * nmemb);

    // Terminate the string so it can be printed
    *str_terminator = 0;

    // Tell libcurl how much we copied
    return (size_t)size * nmemb;
}

static size_t mem_write_callback(char *data, size_t size, size_t nmemb, void *user_buffer)
{
    size_t curlAmountTransmitted = size * nmemb;
    struct curl_response *response = (struct curl_response*)user_buffer;

    // response->size will grow between each mem_write_callback call
    char *ptr = realloc(response->data, response->size + curlAmountTransmitted + 1);
}