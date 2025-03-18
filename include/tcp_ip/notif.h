/*      Compiler: gcc
 *       
 *      Notification chain (NFC) header file
 *      Linked list of notif_chain_elem_t structs
 * 
 * 
 */
#ifndef __NOTIF_CHAIN_
#define __NOTIF_CHAIN_

#include "gluethread/Glthreads.h"
#include <stddef.h>

#define MAX_NOTIF_SIZE 64
#endif


typedef struct notif_chain_ {
    char nfc_name[64]; 
    glll_t notif_chain_head;
} notif_chain_t;


typedef struct notif_chain_elem {

    char key[MAX_NOTIF_SIZE];
    size_t key_size;
    bool is_key_set;
    nfc_app_cb app_cb; // callback
    glll_t glue;

} notif_chain_elem_t;

void nfc_register_notif_chain(notif_chain_t *nfc, notif_chain_elem_t *nfce);

void nfc_invoke_notif_chain(notif_chain_t *nfc, void *arg, size_t arg_size, char *key, size_t key_size);

