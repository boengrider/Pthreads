#include <curl/curl.h>
#include <curl/curlver.h>

int main()
{
    //https://everything.curl.dev/transfers/easyhandle.html

    // This will hold a readable error message
    char CURL_ERROR_MESSAGE_BUFFER[CURL_ERROR_SIZE]; 

    curl_version_info_data *version = curl_version_info( CURLVERSION_NOW );
    printf("Using libcurl version: %s\n", version->version);

    // Global init. Call only once in the main thread
    curl_global_init( CURL_GLOBAL_DEFAULT );

    
}