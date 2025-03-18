/*      Compiler: gcc
 *       
 *      Notification chain (NFC) implementation file
 *      Linked list of notif_chain_elem_t structs
 * 
 * 
 */

 #include <stdlib.h>
 #include <memory.h>
 #include <assert.h>
 #include "tcp_ip/notif.h"

 void nfc_register_notif_chain(notif_chain_t *nfc, notif_chain_elem_t *nfce)
{
    //allocate memory on the heap worth of one notif_chain_elem_t struct
    notif_chain_elem_t *new_nfce = calloc(1, sizeof(notif_chain_elem_t));

    //copy contents from *nfc parameter to the newly allocated memory chunk
    memcpy(new_nfce, nfce, sizeof(notif_chain_elem_t));

    //add struct to the linked list (glued)
    glll_init(&new_nfce->glue);
    glll_add(&nfc->notif_chain_head, &new_nfce->glue);
}

void nfc_invoke_notif_chain(notif_chain_t *nfc, void *arg, size_t arg_size, char *key, size_t key_size)
{
    glll_t curr;
    notif_chain_elem_t *nfce;

    assert(key_size <= MAX_NOTIF_SIZE);

    
}

