/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "libcgc.h"
#include "cgc_ll.h"


int cgc_head_check(alloc_head_t *h){
    if(h == NULL)
        return HEADNODENULL;
    if(h->n == NULL)
        return HEADALLOCNODENULL;
    return 0;
}

int cgc_check_next_node_for(alloc_node_t *n) {
    return n != NULL && n->next != NULL;
}

alloc_head_t * cgc_init_ll(){
    alloc_head_t * h;
    int r = cgc_allocate(sizeof(alloc_head_t), 0, (void **) &h);
    if(r != 0)
        return NULL;
    h->n_nodes = 0;
    h->n = NULL;
    return h;
}

alloc_node_t * cgc_get_head(alloc_head_t *h){
    if(h == NULL)
        return NULL;
    return h->n;
}


//safely do this so we dont rollover
void cgc_dec_nodes(alloc_head_t *head){
    if(head && head->n_nodes > 0)
        head->n_nodes -= 1;
}






alloc_node_t * cgc_get_node(alloc_head_t *head, alloc_node_t *a){
    alloc_node_t * n = cgc_get_head(head);
    while(n != NULL){
        if(n == a){
            return n;
        }
        n = n->next;
    }
    return NULL;

}
int cgc_remove_node(alloc_head_t *head, alloc_node_t *t){
    if(t == NULL)
        return UNLINKNULL;

    alloc_node_t *p = NULL;
    alloc_node_t *n = cgc_get_head(head);
    while(n != NULL){    
        if(n == t){
            // ensure p is not null before unlink and if it is we're at head
            if(p)
                p->next = n->next;
            else
                head->n = n->next;

            cgc_dec_nodes(head);
            return 0;
        }



        p = n;
        n = n->next;

    }
    
    return UNLINKFAIL;
}


int cgc_add_node_tail(alloc_head_t *head, alloc_node_t *a){
    int hc = cgc_head_check(head);
    if(hc == HEADALLOCNODENULL){
        head->n_nodes += 1;
        head->n = a;
        a->next = NULL;
        return OPOKAY;
    }

    alloc_node_t *n = cgc_get_head(head);
    while(n != NULL){    
        
        if(n->next == NULL){
            n->next = a;
            head->n_nodes +=1;
            return OPOKAY;
        
        }
        n = n->next;

    }
    
    return LINKFAIL;


}


int cgc_add_node(alloc_head_t *head, alloc_node_t *a){
    int hc = cgc_head_check(head);
    if(hc == HEADALLOCNODENULL){
        head->n_nodes += 1;
        head->n = a;
        a->next = NULL;
        return OPOKAY;
    }


    if(hc > 0)
        return hc;
    
    a->next = cgc_get_head(head);
    head->n = a;
    head->n_nodes += 1;
    return OPOKAY;
}

int cgc_count_entries(alloc_head_t *head){
    int hc = cgc_head_check(head);
    if(hc > 0)
        return hc;

    int count = 0;

    for(alloc_node_t *n = head->n; n->next != NULL; n = n->next){
        count += 1;
    }
    return count;
}



