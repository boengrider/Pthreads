/*
* Create two threads
* Each trhead sends a request to the same URL
* Each thread uses easy curl interface 
 // Main https://everything.curl.dev/transfers/drive/multi.html
    // Write callback https://everything.curl.dev/transfers/callbacks/write.html
*/
#include <curl/curl.h>
#include <curl/curlver.h>
#include <curl/easy.h>
#include <curl/options.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <memory.h>
#include <pthread.h>

#define THREAD_CREATE_OK 0
#define CURL_ERROR_PREFIX "curl error: "
CURL *easy_handle; // will be resued by threads
size_t write_callback(char *data, size_t size, size_t nmemb, void *user_buffer);
static size_t mem_write_callback(void *data, size_t size, size_t nmemb, void *user_buffer);
static size_t mem_header_callback(void *data, size_t size, size_t nmemb, void *user_buffer);
static int progress_callback(void *clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow);
void *dl_thread(void *args);

struct curl_response {
    char *data;
    size_t size;
};

struct dl_thread_args_t {
    char *url;
};



int main(int argc, char *argv[])
{
   
 
    // Worker thread realated stuff
    int status;
    pthread_t dl_threadA, dlThreadB;
    struct dl_thread_args_t dlArgsA = { "https://dsl.sk" };
    struct dl_thread_args_t dlArgsB = dlArgsA;

    // Downloader thread A
    status = pthread_create(&dl_threadA, NULL, dl_thread, (void*)&dlArgsA);
    if(status != THREAD_CREATE_OK) {
        fprintf(stderr, "Error creating a new thread\n");
        exit(EXIT_FAILURE);
    }

    // Downloader thread B
    status = pthread_create(&dlThreadB, NULL, dl_thread, (void*)&dlArgsB);
    if(status != THREAD_CREATE_OK) {
        fprintf(stderr, "Error creating a new thread\n");
        exit(EXIT_FAILURE);
    }

    // Some libcurl stuff on the main thread
    curl_version_info_data *version = curl_version_info( CURLVERSION_NOW );
    printf("Using libcurl version: %s\n", version->version);
    curl_global_init( CURL_GLOBAL_DEFAULT );
    

    // Join with the main thread
    pthread_join(dl_threadA, NULL);
    pthread_join(dlThreadB, NULL);
    
    curl_global_cleanup();

   
}

/******************************************************/
/**************** Function definitions  ***************/
/******************************************************/
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

static size_t mem_write_callback(void *data, size_t size, size_t nmemb, void *user_buffer)
{
   
    struct curl_response *__memory = (struct curl_response*)user_buffer;
    size_t curlAmountTransmitted = size * nmemb;
    
    //Allocate sufficient amount of memory plus one byte more to store null terminator for later printing
    void *tmp = realloc((void*)__memory->data, __memory->size + curlAmountTransmitted + 1);

    if(!tmp)
    {
        // realloc failed
        fprintf(stderr, "%s\n", "memory allocation has failed\n");
        return -1;
    }

    __memory->data = tmp;
    memcpy(&__memory->data[__memory->size], data, curlAmountTransmitted);
    __memory->size += curlAmountTransmitted;
    __memory->data[__memory->size] = 0;


    return curlAmountTransmitted;
}

static size_t mem_header_callback(void *data, size_t size, size_t nmemb, void *user_buffer)
{
    
    struct curl_response *__memory = (struct curl_response*)user_buffer;
    size_t curlAmountTransmitted = size * nmemb;
    
     //Allocate sufficient amount of memory plus one byte more to store null terminator for later printing
     void *tmp = realloc((void*)__memory->data, __memory->size + curlAmountTransmitted + 1);

     if(!tmp)
     {
         // realloc failed
         fprintf(stderr, "%s\n", "memory allocation has failed\n");
         return -1;
     }
 
     __memory->data = tmp;
     memcpy(&__memory->data[__memory->size], data, curlAmountTransmitted);
     __memory->size += curlAmountTransmitted;
     __memory->data[__memory->size] = 0;
 
 
     return curlAmountTransmitted;
}

static int progress_callback(void *clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow)
{
    fprintf(stdout, "... downloading data: %ld bytes of %ld\n", dlnow, dltotal);

    return 0;
}

void *dl_thread(void *args) {

    struct dl_thread_args_t *thread_args = (struct dl_thread_args_t*)args;

    // This will hold a readable error message
    char CURL_ERROR_MESSAGE_BUFFER[CURL_ERROR_SIZE]; 

    struct curl_response body = { .data = malloc(0), .size = 0 };
    struct curl_response header = { .data = malloc(0), .size = 0 };

     // Initialize easy handle. 
     easy_handle = curl_easy_init();

     // Set error buffer
     CURLcode rc = curl_easy_setopt(easy_handle, CURLOPT_ERRORBUFFER, CURL_ERROR_MESSAGE_BUFFER);
     if(rc != CURLE_OK)
         fprintf(stderr, "%s %s\n", CURL_ERROR_PREFIX, curl_easy_strerror(rc));
 
     // Set URL
     rc = curl_easy_setopt(easy_handle, CURLOPT_URL, thread_args->url);
     if(rc != CURLE_OK)
         fprintf(stderr, "%s %s\n", CURL_ERROR_PREFIX, CURL_ERROR_MESSAGE_BUFFER);
 
     // Set SSL version
     rc = curl_easy_setopt(easy_handle, CURLOPT_SSLVERSION, CURL_SSLVERSION_MAX_TLSv1_3);
     if(rc != CURLE_OK)
         fprintf(stderr, "%s %s\n", CURL_ERROR_PREFIX, CURL_ERROR_MESSAGE_BUFFER);
 
     // Register read callback with libcurl so that we can do other things than just default fwrite call
     rc = curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, mem_write_callback);
     if(rc != CURLE_OK)
         fprintf(stderr, "%s %s\n", CURL_ERROR_PREFIX, CURL_ERROR_MESSAGE_BUFFER);
 
     // libcurl will pass this pointer to our body callback
     rc = curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, (void*)&body);
     if(rc != CURLE_OK)
         fprintf(stderr, "%s %s\n", CURL_ERROR_PREFIX, CURL_ERROR_MESSAGE_BUFFER);
 
     // Register header callback with libcurl 
     rc = curl_easy_setopt(easy_handle, CURLOPT_HEADERFUNCTION, mem_header_callback);
     if(rc != CURLE_OK)
         fprintf(stderr, "%s %s\n", CURL_ERROR_PREFIX, CURL_ERROR_MESSAGE_BUFFER);
 
     // libcurl will pass this pointer to our header callback
     rc = curl_easy_setopt(easy_handle, CURLOPT_HEADERDATA, (void*)&header);
     if(rc != CURLE_OK)
         fprintf(stderr, "%s %s\n", CURL_ERROR_PREFIX, CURL_ERROR_MESSAGE_BUFFER);
 
     if(rc != CURLE_OK)
        return (void*)0;


           
    // All options set successfully byond this point
    // Perform the transfer
    CURLcode result = curl_easy_perform(easy_handle);
    if(result != CURLE_OK) 
    {
        fprintf(stdout, "%s %s\n", CURL_ERROR_PREFIX, CURL_ERROR_MESSAGE_BUFFER);
        free(header.data);
        free(body.data);
    }

    // All OK. Print received data + header
    //fprintf(stdout, "Bytes transmitted %lu\n%s\n", body.size, body.data);
    fprintf(stdout, "Header:\n%s\n", header.data);
    fprintf(stdout, "Header:\n%s\n", body.data);

    // Release memory
    free(header.data);
    free(body.data);
    

    return (void*)0;
}