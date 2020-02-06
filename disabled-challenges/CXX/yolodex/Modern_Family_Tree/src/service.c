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
#include "cgc_stdint.h"
#include "cgc_errno.h"
#include "cgc_libc.h"
#include "cgc_recv_all.h"
#include "cgc_send.h"
#include "cgc_memcmp.h"
#include "cgc_memcpy.h"

#include "cgc_people.h"

Person *cgc_person_list = NULL;
uint32_t cgc_total_person_count = 0;
Search *cgc_search_map = NULL;

const char cgc_ADD_PERSON[4]            =   {'\xa0','\xa1','\xa2','\xa3'};
const char cgc_SET_BIOLOGICAL_CHILD[4]  =   {'\xbc','\xbc','\xbc','\xbc'};
const char cgc_SET_ADOPTED_CHILD[4]     =   {'\xac','\xac','\xac','\xac'};
const char cgc_SET_UNION[4]             =   {'\xf0','\xf1','\xf2','\xf3'};
const char cgc_SET_DECEASED[4]          =   {'\xde','\xce','\xde','\xce'};
const char cgc_SET_SEPARATED[4]         =   {'\x50','\x11','\x50','\x11'};
const char cgc_ARE_RELATED[4]           =   {'\x50','\x01','\x50','\x01'};
const char cgc_DEGREES[4]               =   {'\x50','\xFF','\x50','\xFF'};

static char OK[4] = {0};
static char ERR[4] = {0};

typedef struct request Request;
struct request {
    char cmd[4];
    cgc_size_t bytes;
};


/**
 * Get the current status of this search lock
 *
 * @param p_id  Person ID
 * @param rt    Relation type
 * @return TRUE if locked, else FALSE
 */
uint8_t cgc_is_search_locked(uint32_t p_id, R_TYPES rt) {
    for (uint32_t i = 0; i < cgc_total_person_count; i++) {
        if (p_id == cgc_search_map[i].p->id) {
            return cgc_search_map[i].visited & rt;
        }
    }
    cgc__terminate(ERRNO_LOCK);
}

/**
 * Set the search lock on this person and Relation type to prevent looping.
 *
 * @param p_id  Person ID
 * @param rt    Relation type
 */
void cgc_set_search_lock(uint32_t p_id, R_TYPES rt) {
    for (uint32_t i = 0; i < cgc_total_person_count; i++) {
        if (p_id == cgc_search_map[i].p->id) {
            cgc_search_map[i].visited = cgc_search_map[i].visited | rt;
            return;
        }
    }
    cgc__terminate(ERRNO_LOCK);
}

/**
 * Free the search map
 */
void cgc_free_search_map(void) {
    cgc_free(cgc_search_map);
    cgc_search_map = NULL;
}

/**
 * Create a new search map
 *
 * @return SUCCESS on succeess, else -1 on error
 */
int cgc_new_search_map(void) {
    if (cgc_total_person_count > (SIZE_MAX / sizeof(Search) - 1))
        return -1; // prevent overflow calloc size

    if (NULL != cgc_search_map) cgc_free_search_map();

    cgc_search_map = cgc_calloc(cgc_total_person_count * sizeof(Search));
    MALLOC_OK(cgc_search_map);

    Person *p = cgc_person_list;
    uint32_t idx = 0;
    while (NULL != p) {
        cgc_search_map[idx++].p = p;
        p = p->next;
    }

    return SUCCESS;
}


/**
 * Determine if 2 people are related and if so, how many degrees of separation
 *
 * @param p1    Pointer to first Person
 * @param p2    Pointer to second Person
 * @return 0 if self, number of degrees >0 if related, else -1 if not related
 */
int cgc_degrees_of_separation(Person *p1, Person *p2) {
    int ret = 0;

    if ((NULL == p1) || (NULL == p2)) {
        return -1;
    }

    // ## check self
    if (p1 == p2) return 0;

    // ## check immediate relations

    // search p1.adopted
    if (FALSE == cgc_is_search_locked(p1->id, RT_ADOPTED_CHILD)) {
        cgc_set_search_lock(p1->id, RT_ADOPTED_CHILD);
        for (int i = 0; i < 10; i++) {
            ret = cgc_degrees_of_separation(p1->children.adopted[i].person, p2);
            if (0 <= ret) {
                return 1 + ret;
            }
        }
    }

    // search p1.biological
    if (FALSE == cgc_is_search_locked(p1->id, RT_BIO_CHILD)) {
        cgc_set_search_lock(p1->id, RT_BIO_CHILD);
        for (int i = 0; i < 10; i++) {
            ret = cgc_degrees_of_separation(p1->children.biological[i].person, p2);
            if (0 <= ret) {
                return 1 + ret;
            }
        }
    }

    // search p1.biological_mother
    if (FALSE == cgc_is_search_locked(p1->id, RT_MOTHER)) {
        cgc_set_search_lock(p1->id, RT_MOTHER);
        ret = cgc_degrees_of_separation(p1->parents.biological_mother.person, p2);
        if (0 <= ret) {
            return 1 + ret;
        }
    }

    // search p1.biological_father
    if (FALSE == cgc_is_search_locked(p1->id, RT_FATHER)) {
        cgc_set_search_lock(p1->id, RT_FATHER);
        ret = cgc_degrees_of_separation(p1->parents.biological_father.person, p2);
        if (0 <= ret) {
            return 1 + ret;
        }
    }

    // search p1.adopting
    if (FALSE == cgc_is_search_locked(p1->id, RT_ADOPTING_PARENT)) {
        cgc_set_search_lock(p1->id, RT_ADOPTING_PARENT);
        ret = cgc_degrees_of_separation(p1->parents.adopting[0].person, p2);
        if (0 <= ret) {
            return 1 + ret;
        }

        ret = cgc_degrees_of_separation(p1->parents.adopting[1].person, p2);
        if (0 <= ret) {
            return 1 + ret;
        }
    }

    // search p1.current
    if (FALSE == cgc_is_search_locked(p1->id, RT_PARTNER)) {
        cgc_set_search_lock(p1->id, RT_PARTNER);
        ret = cgc_degrees_of_separation(p1->partners.current.person, p2);
        if (0 <= ret) {
            return 1 + ret;
        }
    }

    // search p1.former
    if (FALSE == cgc_is_search_locked(p1->id, RT_FORMER)) {
        cgc_set_search_lock(p1->id, RT_FORMER);
        ret = cgc_degrees_of_separation(p1->partners.former[0].person, p2);
        if (0 <= ret) {
            return 1 + ret;
        }

        ret = cgc_degrees_of_separation(p1->partners.former[1].person, p2);
        if (0 <= ret) {
            return 1 + ret;
        }
    }


    return -1;
}

/**
 * Determine if a parent has reached their max of 10 biological children
 *
 * @param parent    Pointer to parent
 * @return TRUE if can have more, else FALSE if they cannot
 */
int cgc_can_have_more_biological_children(Person *parent) {
    cgc_size_t count = sizeof(parent->children.biological) / sizeof(parent->children.biological[0]);

    for (int idx = 0; idx < count; idx++) {
        if (PERSON_UNKNOWN == parent->children.biological[idx].person_id) {
            return TRUE;
        }
    }
    // already has count children
    return FALSE;
}

/**
 * Set the biological child Relation in the parent
 *
 * @param child     Pointer to child
 * @param parent    Pointer to parent
 * @return SUCCESS on success, else -1
 */
int cgc_set_biological_child(Person *child, Person *parent) {
    cgc_size_t count = sizeof(parent->children.biological) / sizeof(parent->children.biological[0]);

    for (int idx = 0; idx < count; idx++) {
        if (PERSON_UNKNOWN == parent->children.biological[idx].person_id) {
            parent->children.biological[idx].person_id = child->id;
            parent->children.biological[idx].person = child;
            return SUCCESS;
        }
    }
    // already has count children
    return -1;
}

/**
 * Set the biological mother Relation in the child
 *
 * @param child     Pointer to child
 * @param mother    Pointer to mother
 */
void cgc_set_biological_mother(Person *child, Person *mother) {
    child->parents.biological_mother.person_id = mother->id;
    child->parents.biological_mother.person = mother;
}

/**
 * Set the biological father Relation in the child
 *
 * @param child     Pointer to child
 * @param father    Pointer to father
 */
void cgc_set_biological_father(Person *child, Person *father) {
    child->parents.biological_father.person_id = father->id;
    child->parents.biological_father.person = father;
}

/**
 * Unset the adopted child Relation in the parent
 *
 * @param child     Pointer to child
 * @param parent    Pointer to parent
 * @param idx       Parent index
 * @return SUCCESS on success, else -1
 */
int cgc_unset_adopted_child(Person *child, Person *parent) {
    cgc_size_t count = sizeof(parent->children.adopted) / sizeof(parent->children.adopted[0]);

    for (int i = 0; i < count; i++) {
        if (child->id == parent->children.adopted[i].person_id) {
            parent->children.adopted[i].person_id = PERSON_UNKNOWN;
            parent->children.adopted[i].person = NULL;

            parent->shift(parent, parent->id);
            return SUCCESS;
        }
    }
    return -1;
}

/**
 * Determine if a parent has reached their max of 10 adopted children
 *
 * @param parent    Pointer to parent
 * @return TRUE if can have more, else FALSE if they cannot
 */
int cgc_can_have_more_adopted_children(Person *parent) {
    cgc_size_t count = sizeof(parent->children.adopted) / sizeof(parent->children.adopted[0]);

    for (int i = 0; i < count; i++) {
        if (PERSON_UNKNOWN == parent->children.adopted[i].person_id) {
            return TRUE;
        }
    }
    // already has count children
    return FALSE;
}

/**
 * Set the adopted child Relation in the parent
 *
 * @param child     Pointer to child
 * @param parent    Pointer to parent
 * @param idx       Parent index
 * @return SUCCESS on success, else -1
 */
int cgc_set_adopted_child(Person *child, Person *parent) {
    cgc_size_t count = sizeof(parent->children.adopted) / sizeof(parent->children.adopted[0]);

    for (int i = 0; i < count; i++) {
        if (PERSON_UNKNOWN == parent->children.adopted[i].person_id) {
            parent->children.adopted[i].person_id = child->id;
            parent->children.adopted[i].person = child;

            return SUCCESS;
        }
    }
    return -1;
}

/**
 * Set the adopting parent Relation in the child
 *
 * @param child     Pointer to child
 * @param parent    Pointer to parent
 * @param idx       Parent index
 */
void cgc_set_adopting_parent(Person *child, Person *parent, uint32_t idx) {
    child->parents.adopting[idx].person_id = parent->id;
    child->parents.adopting[idx].person = parent;
}

/**
 * Unset the union Relationship between 2 persons.
 *
 * @param person1   Pointer to first person
 * @param person2   Pointer to second person
 * @return SUCCESS on success, else -1
 */
int cgc_separate_two_persons(Person *person1, Person *person2) {

    if (PERSON_UNKNOWN == person2->id) {
        return -1;
    }

#ifdef PATCHED_1
    if (PERSON_UNKNOWN == person1->partners.former[0].person_id) {
        person1->partners.former[0].person_id = person2->id;
        person1->partners.former[0].person = person2;
    } else {
        person1->partners.former[1].person_id = person2->id;
        person1->partners.former[1].person = person2;
    }
#else
    // VULN: uses idx 1 and 2 instead of 0 and 1 into former[]
    if (PERSON_UNKNOWN == person1->partners.former[1].person_id) {
        person1->partners.former[1].person_id = person2->id;
        person1->partners.former[1].person = person2;
    } else {
        person1->partners.former[2].person_id = person2->id;
        person1->partners.former[2].person = person2;
    }
#endif

#ifdef PATCHED_2
    if (PERSON_UNKNOWN == person2->partners.former[0].person_id) {
        person2->partners.former[0].person_id = person1->id;
        person2->partners.former[0].person = person1;
    } else {
        person2->partners.former[1].person_id = person1->id;
        person2->partners.former[1].person = person1;
    }

#else
    // VULN: uses idx 1 and 2 instead of 0 and 1 into former[]
    if (PERSON_UNKNOWN == person2->partners.former[1].person_id) {
        person2->partners.former[1].person_id = person1->id;
        person2->partners.former[1].person = person1;
    } else {
        person2->partners.former[2].person_id = person1->id;
        person2->partners.former[2].person = person1;
    }
#endif

    person1->partners.current.person_id = PERSON_UNKNOWN;
    person1->partners.current.person = NULL;

    person2->partners.current.person_id = PERSON_UNKNOWN;
    person2->partners.current.person = NULL;

    return SUCCESS;
}

/**
 * Set the union Relationship between 2 persons.
 *
 * @param person1   Pointer to first person
 * @param person2   Pointer to second person
 * @return SUCCESS on success, else -1
 */
int cgc_union_two_persons(Person *person1, Person *person2) {
    int ret = SUCCESS;

    // set partner in person 1
    if (PERSON_UNKNOWN != person1->partners.current.person_id) {
        ret = cgc_separate_two_persons(person1, person1->partners.current.person);
        if (-1 == ret) goto utp_end;
    }
    person1->partners.current.person_id = person2->id;
    person1->partners.current.person = person2;

    // set partner in person 2
    if (PERSON_UNKNOWN != person2->partners.current.person_id) {
        ret = cgc_separate_two_persons(person2, person2->partners.current.person);
        if (-1 == ret) goto utp_end;
    }
    person2->partners.current.person_id = person1->id;
    person2->partners.current.person = person1;

utp_end:
    return ret;
}

/**
 * Determine if 2 people are related
 *
 * @param p1    Pointer to first Person
 * @param p2    Pointer to second Person
 * @return RELATED if related, NOT_RELATED if not related, else -1 on error
 */
int cgc_find_are_related(Person *p1, Person *p2) {
    int ret = 0;
    ret = cgc_new_search_map();
    if (-1 == ret) goto far_end;

    // 0 == self, >0 == related, -1 == error
    ret = cgc_degrees_of_separation(p1, p2);
    cgc_free_search_map();

    if (0 > ret) {
        return NOT_RELATED;
    } else if (0 <= ret) {
        return RELATED;
    }

far_end:
    return -1;
}




/**
 * Add a new person to the family tree
 *
 * @param bytes     Number of bytes available to receive
 * @return SUCCESS on success, else -1
 */
int cgc_cmd_add_person(cgc_size_t bytes) {
    int ret = SUCCESS;
    Person *p;

    if (bytes != PERSON_IN_SZ) {
        return -1;
    }

    char *buf = cgc_calloc(PERSON_IN_SZ);
    MALLOC_OK(buf);
    RECV(buf, PERSON_IN_SZ);

    p = cgc_new_person(buf);
    if (NULL == p) {
        ret = -1;
        goto cap_end;
    }

    cgc_add_person_to_list(&cgc_person_list, p);
    cgc_total_person_count++;

cap_end:
    cgc_free(buf);

    return ret;
}

/**
 * Process the input to set a biological child relationship between child 
 * and its father and/or mother.
 *
 * @param bytes     Number of bytes available to receive
 * @return SUCCESS on success, else -1
 */
int cgc_cmd_set_biological_child(cgc_size_t bytes) {
    int ret = SUCCESS;
    cgc_size_t bytes_needed = 3*sizeof(uint32_t);  // IDs for child, mother, and father

    if (bytes != bytes_needed) {
        return -1;
    }

    char *buf = cgc_calloc(bytes_needed);
    MALLOC_OK(buf);
    RECV(buf, bytes_needed);

    uint32_t *id = (uint32_t *)buf;

    Person *child  = cgc_get_person_by_id(cgc_person_list, id[0]);
    Person *mother = cgc_get_person_by_id(cgc_person_list, id[1]);
    Person *father = cgc_get_person_by_id(cgc_person_list, id[2]);

    // parent and children relations default to PERSON_UNKNOWN, so only change
    // if a known person is given as each parent.
    // Also, make sure both parents can have more biological children
    if ((NULL == child) || (NULL == mother) || (NULL == father) ||
        (FALSE == cgc_can_have_more_biological_children(mother)) ||
        (FALSE == cgc_can_have_more_biological_children(father))) {
        ret = -1;
        goto sbc_end;
    }

    // set child first, because it can fail; althrough it shouldn't if we got this far
    ret = cgc_set_biological_child(child, mother);
    if (-1 == ret) goto sbc_end;        
    cgc_set_biological_mother(child, mother);

    // set child first, because it can fail; althrough it shouldn't if we got this far
    ret = cgc_set_biological_child(child, father);
    if (-1 == ret) goto sbc_end; 
    cgc_set_biological_father(child, father);

sbc_end:
    cgc_free(buf);

    return ret;
}

/**
 * Process the input to set an adopted child relationship between child 
 * and its one or two parents.
 *
 * @param bytes     Number of bytes available to receive
 * @return SUCCESS on success, else -1
 */
int cgc_cmd_set_adopted_child(cgc_size_t bytes) {
    int ret = SUCCESS;
    cgc_size_t bytes_needed = 3*sizeof(uint32_t);  // IDs for child, parent1, and parent2

    if (bytes != bytes_needed) {
        return -1;
    }

    char *buf = cgc_calloc(bytes_needed);
    MALLOC_OK(buf);
    RECV(buf, bytes_needed);

    uint32_t *id = (uint32_t *)buf;

    Person *child  = cgc_get_person_by_id(cgc_person_list, id[0]);
    Person *parent1 = cgc_get_person_by_id(cgc_person_list, id[1]);
    Person *parent2 = cgc_get_person_by_id(cgc_person_list, id[2]);

    // parent and children relations default to PERSON_UNKNOWN, so only change
    // if an existing/valid person is given as at least one parent.
    // Also, make sure valid parents can have more adopted children
    if ((NULL == child) || 
        ((NULL == parent1) && (NULL == parent2)) ||
        ((NULL != parent1) && (FALSE == cgc_can_have_more_adopted_children(parent1))) ||
        ((NULL != parent2) && (FALSE == cgc_can_have_more_adopted_children(parent2)))) {
        ret = -1;
        goto sac_end;
    }

    // if this child has existing adopting parents, remove this child from those parents
    if (PERSON_UNKNOWN != child->parents.adopting[0].person_id) {
        ret = cgc_unset_adopted_child(child, child->parents.adopting[0].person);
        if (-1 == ret) {
            goto sac_end;
        }
    }

    if (PERSON_UNKNOWN != child->parents.adopting[1].person_id) {
        ret = cgc_unset_adopted_child(child, child->parents.adopting[1].person);
        if (-1 == ret) {
            goto sac_end;
        }
    }

    // set child first, because it can fail; although it shouldn't if we got this far
    if (NULL != parent1) {
        ret = cgc_set_adopted_child(child, parent1);
        if (-1 == ret) goto sac_end;
        cgc_set_adopting_parent(child, parent1, 0);
    }

    // set child first, because it can fail; although it shouldn't if we got this far
    if (NULL != parent2) {
        ret = cgc_set_adopted_child(child, parent2);
        if (-1 == ret) goto sac_end;
        cgc_set_adopting_parent(child, parent2, 1);
    }

sac_end:
    cgc_free(buf);

    return ret;
}

/**
 * Process the input to set a union between 2 persons.
 *
 * @param bytes     Number of bytes available to receive
 * @return SUCCESS on success, else -1
 */
int cgc_cmd_set_union(cgc_size_t bytes) {
    int ret = SUCCESS;
    cgc_size_t bytes_needed = 2*sizeof(uint32_t);  // IDs for person1 and person2

    if (bytes != bytes_needed) {
        return -1;
    }

    char *buf = cgc_calloc(bytes_needed);
    MALLOC_OK(buf);
    RECV(buf, bytes_needed);

    uint32_t *id = (uint32_t *)buf;

    Person *person1  = cgc_get_person_by_id(cgc_person_list, id[0]);
    Person *person2 = cgc_get_person_by_id(cgc_person_list, id[1]);
    if ((NULL == person1) || (NULL == person2)) {
        ret = -1;
        goto su_end;
    }
    ret = cgc_union_two_persons(person1, person2);

su_end:
    cgc_free(buf);

    return ret;
}

/**
 * Process the input to set a person as deceased.
 *
 * @param bytes     Number of bytes available to receive
 * @return SUCCESS on success, else -1
 */
int cgc_cmd_set_deceased(cgc_size_t bytes) {
    int ret = SUCCESS;
    cgc_size_t bytes_needed = sizeof(uint32_t) + sizeof(uint16_t);  // ID, death_year for person1

    if (bytes != bytes_needed) {
        return -1;
    }

    char *buf = cgc_calloc(bytes_needed);
    MALLOC_OK(buf);
    RECV(buf, bytes_needed);

    uint32_t *id = (uint32_t *)buf;
    uint16_t *death_year = (uint16_t *)buf;

    Person *person1  = cgc_get_person_by_id(cgc_person_list, id[0]);
    if (NULL == person1) {
        ret = -1;
        goto die_end;
    }
    person1->lifecycle.death_year = death_year[2];

die_end:
    cgc_free(buf);
    return ret;
}

/**
 * Process the input to set 2 persons as separated
 *
 * @param bytes     Number of bytes available to receive
 * @return SUCCESS on success, else -1
 */
int cgc_cmd_set_separated(cgc_size_t bytes) {
    int ret = SUCCESS;
    cgc_size_t bytes_needed = 2*sizeof(uint32_t);  // IDs for person1 and person2

    if (bytes != bytes_needed) {
        return -1;
    }

    char *buf = cgc_calloc(bytes_needed);
    MALLOC_OK(buf);
    RECV(buf, bytes_needed);

    uint32_t *id = (uint32_t *)buf;

    Person *person1  = cgc_get_person_by_id(cgc_person_list, id[0]);
    Person *person2 = cgc_get_person_by_id(cgc_person_list, id[1]);
    if ((NULL == person1) || (NULL == person2)) {
        ret = -1;
        goto ss_end;
    }

    ret = cgc_separate_two_persons(person1, person2);

ss_end:
    cgc_free(buf);
    return ret;
}

/**
 * Process the input to determine if there is a relationship between 2 people
 *
 * @param bytes     Number of bytes available to receive
 * @return SUCCESS on success, else -1 on error
 */
int cgc_cmd_are_related(cgc_size_t bytes) {
    int ret = SUCCESS;
    cgc_size_t bytes_needed = 2*sizeof(uint32_t);  // IDs for person1 and person2

    if (bytes != bytes_needed) {
        return -1;
    }

    char *buf = cgc_calloc(bytes_needed);
    MALLOC_OK(buf);
    RECV(buf, bytes_needed);

    uint32_t *id = (uint32_t *)buf;

    Person *person1  = cgc_get_person_by_id(cgc_person_list, id[0]);
    Person *person2 = cgc_get_person_by_id(cgc_person_list, id[1]);
    if ((NULL == person1) || (NULL == person2)) {
        ret = -1;
        goto ar_end;
    }

    ret = cgc_find_are_related(person1, person2);
    if ((RELATED == ret) || (NOT_RELATED == ret)) {
        cgc_send((char *)&ret, sizeof(int));
        ret = SUCCESS;
    }

ar_end:
    cgc_free(buf);

    return ret;
}

/**
 * Process the input to determine the degrees of separation between 2 people
 *
 * @param bytes     Number of bytes available to receive
 * @return SUCCESS on success, else -1 on error
 */
int cgc_cmd_degrees_of_separation(cgc_size_t bytes) {
    int ret = SUCCESS;
    cgc_size_t bytes_needed = 2*sizeof(uint32_t);  // IDs for person1 and person2

    if (bytes != bytes_needed) {
        return -1;
    }

    char *buf = cgc_calloc(bytes_needed);
    MALLOC_OK(buf);
    RECV(buf, bytes_needed);

    uint32_t *id = (uint32_t *)buf;

    Person *person1  = cgc_get_person_by_id(cgc_person_list, id[0]);
    Person *person2 = cgc_get_person_by_id(cgc_person_list, id[1]);
    if ((NULL == person1) || (NULL == person2)) {
        ret = -1;
        goto ds_end;
    }

    ret = cgc_new_search_map();
    if (-1 == ret) goto ds_end;

    // ret -> 0 == self, >0 == related, -1 == error
    ret = cgc_degrees_of_separation(person1, person2);
    cgc_free_search_map();

    // send -1 for not related, 0 if self, >0 if related by some degree
    cgc_send((char *)&ret, sizeof(int));
    ret = SUCCESS;

ds_end:
    cgc_free(buf);

    return ret;

}

/**
 * Create a checksum of the flag page to use as the OK/ERR byte strings
 */
void cgc_gen_result_bufs(void) {
    const char *fp = (char *)FLAG_PAGE;
    for (unsigned int idx = 0; idx < 4095; idx+=2) {
        OK[idx % 4] ^= fp[idx];
        ERR[(idx + 1) % 4] ^= fp[idx + 1];
    }
}

int main(int cgc_argc, char *cgc_argv[]) {

    int ret = 0;
    cgc_size_t bytes = 0;

    cgc_gen_result_bufs();

    while (TRUE) {
        Request req;
        RECV(&req, sizeof(Request));

        if (0 == cgc_memcmp(cgc_ADD_PERSON, (const char *)req.cmd, sizeof(cgc_ADD_PERSON))) {
            ret = cgc_cmd_add_person(req.bytes);
        } else if (0 == cgc_memcmp(cgc_SET_BIOLOGICAL_CHILD, (const char *)req.cmd, sizeof(cgc_SET_BIOLOGICAL_CHILD))) {
            ret = cgc_cmd_set_biological_child(req.bytes);
        } else if (0 == cgc_memcmp(cgc_SET_ADOPTED_CHILD, (const char *)req.cmd, sizeof(cgc_SET_ADOPTED_CHILD))) {
            ret = cgc_cmd_set_adopted_child(req.bytes);
        } else if (0 == cgc_memcmp(cgc_SET_UNION, (const char *)req.cmd, sizeof(cgc_SET_UNION))) {
            ret = cgc_cmd_set_union(req.bytes);
        } else if (0 == cgc_memcmp(cgc_SET_DECEASED, (const char *)req.cmd, sizeof(cgc_SET_DECEASED))) {
            ret = cgc_cmd_set_deceased(req.bytes);
        } else if (0 == cgc_memcmp(cgc_SET_SEPARATED, (const char *)req.cmd, sizeof(cgc_SET_SEPARATED))) {
            ret = cgc_cmd_set_separated(req.bytes);
        } else if (0 == cgc_memcmp(cgc_ARE_RELATED, (const char *)req.cmd, sizeof(cgc_ARE_RELATED))) {
            ret = cgc_cmd_are_related(req.bytes);
        } else if (0 == cgc_memcmp(cgc_DEGREES, (const char *)req.cmd, sizeof(cgc_DEGREES))) {
            ret = cgc_cmd_degrees_of_separation(req.bytes);
        } else  {
            ret = -1;
        }

        if (0 == ret) {
            cgc_send(OK, sizeof(OK));
        } else {
            cgc_send(ERR, sizeof(ERR));
	        break;
        }

    }

    return 0;
}
