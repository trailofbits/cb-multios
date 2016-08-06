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

#include <libcgc.h>
#include <stdint.h>
#include <errno.h>
#include "libc.h"
#include "recv_all.h"
#include "send.h"
#include "memcmp.h"
#include "memcpy.h"

#include "people.h"

Person *person_list = NULL;
uint32_t total_person_count = 0;
Search *search_map = NULL;

const char ADD_PERSON[4]            =   {'\xa0','\xa1','\xa2','\xa3'};
const char SET_BIOLOGICAL_CHILD[4]  =   {'\xbc','\xbc','\xbc','\xbc'};
const char SET_ADOPTED_CHILD[4]     =   {'\xac','\xac','\xac','\xac'};
const char SET_UNION[4]             =   {'\xf0','\xf1','\xf2','\xf3'};
const char SET_DECEASED[4]          =   {'\xde','\xce','\xde','\xce'};
const char SET_SEPARATED[4]         =   {'\x50','\x11','\x50','\x11'};
const char ARE_RELATED[4]           =   {'\x50','\x01','\x50','\x01'};
const char DEGREES[4]               =   {'\x50','\xFF','\x50','\xFF'};

static char OK[4] = {0};
static char ERR[4] = {0};

typedef struct request Request;
struct request {
    char cmd[4];
    size_t bytes;
};


/**
 * Get the current status of this search lock
 *
 * @param p_id  Person ID
 * @param rt    Relation type
 * @return TRUE if locked, else FALSE
 */
uint8_t is_search_locked(uint32_t p_id, R_TYPES rt) {
    for (uint32_t i = 0; i < total_person_count; i++) {
        if (p_id == search_map[i].p->id) {
            return search_map[i].visited & rt;
        }
    }
    _terminate(ERRNO_LOCK);
}

/**
 * Set the search lock on this person and Relation type to prevent looping.
 *
 * @param p_id  Person ID
 * @param rt    Relation type
 */
void set_search_lock(uint32_t p_id, R_TYPES rt) {
    for (uint32_t i = 0; i < total_person_count; i++) {
        if (p_id == search_map[i].p->id) {
            search_map[i].visited = search_map[i].visited | rt;
            return;
        }
    }
    _terminate(ERRNO_LOCK);
}

/**
 * Free the search map
 */
void free_search_map(void) {
    free(search_map);
    search_map = NULL;
}

/**
 * Create a new search map
 *
 * @return SUCCESS on succeess, else -1 on error
 */
int new_search_map(void) {
    if (total_person_count > (SIZE_MAX / sizeof(Search) - 1))
        return -1; // prevent overflow calloc size

    if (NULL != search_map) free_search_map();

    search_map = calloc(total_person_count * sizeof(Search));
    MALLOC_OK(search_map);

    Person *p = person_list;
    uint32_t idx = 0;
    while (NULL != p) {
        search_map[idx++].p = p;
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
int degrees_of_separation(Person *p1, Person *p2) {
    int ret = 0;

    if ((NULL == p1) || (NULL == p2)) {
        return -1;
    }

    // ## check self
    if (p1 == p2) return 0;

    // ## check immediate relations

    // search p1.adopted
    if (FALSE == is_search_locked(p1->id, RT_ADOPTED_CHILD)) {
        set_search_lock(p1->id, RT_ADOPTED_CHILD);
        for (int i = 0; i < 10; i++) {
            ret = degrees_of_separation(p1->children.adopted[i].person, p2);
            if (0 <= ret) {
                return 1 + ret;
            }
        }
    }

    // search p1.biological
    if (FALSE == is_search_locked(p1->id, RT_BIO_CHILD)) {
        set_search_lock(p1->id, RT_BIO_CHILD);
        for (int i = 0; i < 10; i++) {
            ret = degrees_of_separation(p1->children.biological[i].person, p2);
            if (0 <= ret) {
                return 1 + ret;
            }
        }
    }

    // search p1.biological_mother
    if (FALSE == is_search_locked(p1->id, RT_MOTHER)) {
        set_search_lock(p1->id, RT_MOTHER);
        ret = degrees_of_separation(p1->parents.biological_mother.person, p2);
        if (0 <= ret) {
            return 1 + ret;
        }
    }

    // search p1.biological_father
    if (FALSE == is_search_locked(p1->id, RT_FATHER)) {
        set_search_lock(p1->id, RT_FATHER);
        ret = degrees_of_separation(p1->parents.biological_father.person, p2);
        if (0 <= ret) {
            return 1 + ret;
        }
    }

    // search p1.adopting
    if (FALSE == is_search_locked(p1->id, RT_ADOPTING_PARENT)) {
        set_search_lock(p1->id, RT_ADOPTING_PARENT);
        ret = degrees_of_separation(p1->parents.adopting[0].person, p2);
        if (0 <= ret) {
            return 1 + ret;
        }

        ret = degrees_of_separation(p1->parents.adopting[1].person, p2);
        if (0 <= ret) {
            return 1 + ret;
        }
    }

    // search p1.current
    if (FALSE == is_search_locked(p1->id, RT_PARTNER)) {
        set_search_lock(p1->id, RT_PARTNER);
        ret = degrees_of_separation(p1->partners.current.person, p2);
        if (0 <= ret) {
            return 1 + ret;
        }
    }

    // search p1.former
    if (FALSE == is_search_locked(p1->id, RT_FORMER)) {
        set_search_lock(p1->id, RT_FORMER);
        ret = degrees_of_separation(p1->partners.former[0].person, p2);
        if (0 <= ret) {
            return 1 + ret;
        }

        ret = degrees_of_separation(p1->partners.former[1].person, p2);
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
int can_have_more_biological_children(Person *parent) {
    size_t count = sizeof(parent->children.biological) / sizeof(parent->children.biological[0]);

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
int set_biological_child(Person *child, Person *parent) {
    size_t count = sizeof(parent->children.biological) / sizeof(parent->children.biological[0]);

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
void set_biological_mother(Person *child, Person *mother) {
    child->parents.biological_mother.person_id = mother->id;
    child->parents.biological_mother.person = mother;
}

/**
 * Set the biological father Relation in the child
 *
 * @param child     Pointer to child
 * @param father    Pointer to father
 */
void set_biological_father(Person *child, Person *father) {
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
int unset_adopted_child(Person *child, Person *parent) {
    size_t count = sizeof(parent->children.adopted) / sizeof(parent->children.adopted[0]);

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
int can_have_more_adopted_children(Person *parent) {
    size_t count = sizeof(parent->children.adopted) / sizeof(parent->children.adopted[0]);

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
int set_adopted_child(Person *child, Person *parent) {
    size_t count = sizeof(parent->children.adopted) / sizeof(parent->children.adopted[0]);

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
void set_adopting_parent(Person *child, Person *parent, uint32_t idx) {
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
int separate_two_persons(Person *person1, Person *person2) {

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
int union_two_persons(Person *person1, Person *person2) {
    int ret = SUCCESS;

    // set partner in person 1
    if (PERSON_UNKNOWN != person1->partners.current.person_id) {
        ret = separate_two_persons(person1, person1->partners.current.person);
        if (-1 == ret) goto utp_end;
    }
    person1->partners.current.person_id = person2->id;
    person1->partners.current.person = person2;

    // set partner in person 2
    if (PERSON_UNKNOWN != person2->partners.current.person_id) {
        ret = separate_two_persons(person2, person2->partners.current.person);
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
int find_are_related(Person *p1, Person *p2) {
    int ret = 0;
    ret = new_search_map();
    if (-1 == ret) goto far_end;

    // 0 == self, >0 == related, -1 == error
    ret = degrees_of_separation(p1, p2);
    free_search_map();

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
int cmd_add_person(size_t bytes) {
    int ret = SUCCESS;
    Person *p;

    if (bytes != PERSON_IN_SZ) {
        return -1;
    }

    char *buf = calloc(PERSON_IN_SZ);
    MALLOC_OK(buf);
    RECV(buf, PERSON_IN_SZ);

    p = new_person(buf);
    if (NULL == p) {
        ret = -1;
        goto cap_end;
    }

    add_person_to_list(&person_list, p);
    total_person_count++;

cap_end:
    free(buf);

    return ret;
}

/**
 * Process the input to set a biological child relationship between child 
 * and its father and/or mother.
 *
 * @param bytes     Number of bytes available to receive
 * @return SUCCESS on success, else -1
 */
int cmd_set_biological_child(size_t bytes) {
    int ret = SUCCESS;
    size_t bytes_needed = 3*sizeof(uint32_t);  // IDs for child, mother, and father

    if (bytes != bytes_needed) {
        return -1;
    }

    char *buf = calloc(bytes_needed);
    MALLOC_OK(buf);
    RECV(buf, bytes_needed);

    uint32_t *id = (uint32_t *)buf;

    Person *child  = get_person_by_id(person_list, id[0]);
    Person *mother = get_person_by_id(person_list, id[1]);
    Person *father = get_person_by_id(person_list, id[2]);

    // parent and children relations default to PERSON_UNKNOWN, so only change
    // if a known person is given as each parent.
    // Also, make sure both parents can have more biological children
    if ((NULL == child) || (NULL == mother) || (NULL == father) ||
        (FALSE == can_have_more_biological_children(mother)) ||
        (FALSE == can_have_more_biological_children(father))) {
        ret = -1;
        goto sbc_end;
    }

    // set child first, because it can fail; althrough it shouldn't if we got this far
    ret = set_biological_child(child, mother);
    if (-1 == ret) goto sbc_end;        
    set_biological_mother(child, mother);

    // set child first, because it can fail; althrough it shouldn't if we got this far
    ret = set_biological_child(child, father);
    if (-1 == ret) goto sbc_end; 
    set_biological_father(child, father);

sbc_end:
    free(buf);

    return ret;
}

/**
 * Process the input to set an adopted child relationship between child 
 * and its one or two parents.
 *
 * @param bytes     Number of bytes available to receive
 * @return SUCCESS on success, else -1
 */
int cmd_set_adopted_child(size_t bytes) {
    int ret = SUCCESS;
    size_t bytes_needed = 3*sizeof(uint32_t);  // IDs for child, parent1, and parent2

    if (bytes != bytes_needed) {
        return -1;
    }

    char *buf = calloc(bytes_needed);
    MALLOC_OK(buf);
    RECV(buf, bytes_needed);

    uint32_t *id = (uint32_t *)buf;

    Person *child  = get_person_by_id(person_list, id[0]);
    Person *parent1 = get_person_by_id(person_list, id[1]);
    Person *parent2 = get_person_by_id(person_list, id[2]);

    // parent and children relations default to PERSON_UNKNOWN, so only change
    // if an existing/valid person is given as at least one parent.
    // Also, make sure valid parents can have more adopted children
    if ((NULL == child) || 
        ((NULL == parent1) && (NULL == parent2)) ||
        ((NULL != parent1) && (FALSE == can_have_more_adopted_children(parent1))) ||
        ((NULL != parent2) && (FALSE == can_have_more_adopted_children(parent2)))) {
        ret = -1;
        goto sac_end;
    }

    // if this child has existing adopting parents, remove this child from those parents
    if (PERSON_UNKNOWN != child->parents.adopting[0].person_id) {
        ret = unset_adopted_child(child, child->parents.adopting[0].person);
        if (-1 == ret) {
            goto sac_end;
        }
    }

    if (PERSON_UNKNOWN != child->parents.adopting[1].person_id) {
        ret = unset_adopted_child(child, child->parents.adopting[1].person);
        if (-1 == ret) {
            goto sac_end;
        }
    }

    // set child first, because it can fail; although it shouldn't if we got this far
    if (NULL != parent1) {
        ret = set_adopted_child(child, parent1);
        if (-1 == ret) goto sac_end;
        set_adopting_parent(child, parent1, 0);
    }

    // set child first, because it can fail; although it shouldn't if we got this far
    if (NULL != parent2) {
        ret = set_adopted_child(child, parent2);
        if (-1 == ret) goto sac_end;
        set_adopting_parent(child, parent2, 1);
    }

sac_end:
    free(buf);

    return ret;
}

/**
 * Process the input to set a union between 2 persons.
 *
 * @param bytes     Number of bytes available to receive
 * @return SUCCESS on success, else -1
 */
int cmd_set_union(size_t bytes) {
    int ret = SUCCESS;
    size_t bytes_needed = 2*sizeof(uint32_t);  // IDs for person1 and person2

    if (bytes != bytes_needed) {
        return -1;
    }

    char *buf = calloc(bytes_needed);
    MALLOC_OK(buf);
    RECV(buf, bytes_needed);

    uint32_t *id = (uint32_t *)buf;

    Person *person1  = get_person_by_id(person_list, id[0]);
    Person *person2 = get_person_by_id(person_list, id[1]);
    if ((NULL == person1) || (NULL == person2)) {
        ret = -1;
        goto su_end;
    }
    ret = union_two_persons(person1, person2);

su_end:
    free(buf);

    return ret;
}

/**
 * Process the input to set a person as deceased.
 *
 * @param bytes     Number of bytes available to receive
 * @return SUCCESS on success, else -1
 */
int cmd_set_deceased(size_t bytes) {
    int ret = SUCCESS;
    size_t bytes_needed = sizeof(uint32_t) + sizeof(uint16_t);  // ID, death_year for person1

    if (bytes != bytes_needed) {
        return -1;
    }

    char *buf = calloc(bytes_needed);
    MALLOC_OK(buf);
    RECV(buf, bytes_needed);

    uint32_t *id = (uint32_t *)buf;
    uint16_t *death_year = (uint16_t *)buf;

    Person *person1  = get_person_by_id(person_list, id[0]);
    if (NULL == person1) {
        ret = -1;
        goto die_end;
    }
    person1->lifecycle.death_year = death_year[2];

die_end:
    free(buf);
    return ret;
}

/**
 * Process the input to set 2 persons as separated
 *
 * @param bytes     Number of bytes available to receive
 * @return SUCCESS on success, else -1
 */
int cmd_set_separated(size_t bytes) {
    int ret = SUCCESS;
    size_t bytes_needed = 2*sizeof(uint32_t);  // IDs for person1 and person2

    if (bytes != bytes_needed) {
        return -1;
    }

    char *buf = calloc(bytes_needed);
    MALLOC_OK(buf);
    RECV(buf, bytes_needed);

    uint32_t *id = (uint32_t *)buf;

    Person *person1  = get_person_by_id(person_list, id[0]);
    Person *person2 = get_person_by_id(person_list, id[1]);
    if ((NULL == person1) || (NULL == person2)) {
        ret = -1;
        goto ss_end;
    }

    ret = separate_two_persons(person1, person2);

ss_end:
    free(buf);
    return ret;
}

/**
 * Process the input to determine if there is a relationship between 2 people
 *
 * @param bytes     Number of bytes available to receive
 * @return SUCCESS on success, else -1 on error
 */
int cmd_are_related(size_t bytes) {
    int ret = SUCCESS;
    size_t bytes_needed = 2*sizeof(uint32_t);  // IDs for person1 and person2

    if (bytes != bytes_needed) {
        return -1;
    }

    char *buf = calloc(bytes_needed);
    MALLOC_OK(buf);
    RECV(buf, bytes_needed);

    uint32_t *id = (uint32_t *)buf;

    Person *person1  = get_person_by_id(person_list, id[0]);
    Person *person2 = get_person_by_id(person_list, id[1]);
    if ((NULL == person1) || (NULL == person2)) {
        ret = -1;
        goto ar_end;
    }

    ret = find_are_related(person1, person2);
    if ((RELATED == ret) || (NOT_RELATED == ret)) {
        send((char *)&ret, sizeof(int));
        ret = SUCCESS;
    }

ar_end:
    free(buf);

    return ret;
}

/**
 * Process the input to determine the degrees of separation between 2 people
 *
 * @param bytes     Number of bytes available to receive
 * @return SUCCESS on success, else -1 on error
 */
int cmd_degrees_of_separation(size_t bytes) {
    int ret = SUCCESS;
    size_t bytes_needed = 2*sizeof(uint32_t);  // IDs for person1 and person2

    if (bytes != bytes_needed) {
        return -1;
    }

    char *buf = calloc(bytes_needed);
    MALLOC_OK(buf);
    RECV(buf, bytes_needed);

    uint32_t *id = (uint32_t *)buf;

    Person *person1  = get_person_by_id(person_list, id[0]);
    Person *person2 = get_person_by_id(person_list, id[1]);
    if ((NULL == person1) || (NULL == person2)) {
        ret = -1;
        goto ds_end;
    }

    ret = new_search_map();
    if (-1 == ret) goto ds_end;

    // ret -> 0 == self, >0 == related, -1 == error
    ret = degrees_of_separation(person1, person2);
    free_search_map();

    // send -1 for not related, 0 if self, >0 if related by some degree
    send((char *)&ret, sizeof(int));
    ret = SUCCESS;

ds_end:
    free(buf);

    return ret;

}

/**
 * Create a checksum of the flag page to use as the OK/ERR byte strings
 */
void gen_result_bufs(void) {
    const char *fp = (char *)FLAG_PAGE;
    for (unsigned int idx = 0; idx < 4095; idx+=2) {
        OK[idx % 4] ^= fp[idx];
        ERR[(idx + 1) % 4] ^= fp[idx + 1];
    }
}

int main(void) {

    int ret = 0;
    size_t bytes = 0;

    gen_result_bufs();

    while (TRUE) {
        Request req;
        RECV(&req, sizeof(Request));

        if (0 == memcmp(ADD_PERSON, (const char *)req.cmd, sizeof(ADD_PERSON))) {
            ret = cmd_add_person(req.bytes);
        } else if (0 == memcmp(SET_BIOLOGICAL_CHILD, (const char *)req.cmd, sizeof(SET_BIOLOGICAL_CHILD))) {
            ret = cmd_set_biological_child(req.bytes);
        } else if (0 == memcmp(SET_ADOPTED_CHILD, (const char *)req.cmd, sizeof(SET_ADOPTED_CHILD))) {
            ret = cmd_set_adopted_child(req.bytes);
        } else if (0 == memcmp(SET_UNION, (const char *)req.cmd, sizeof(SET_UNION))) {
            ret = cmd_set_union(req.bytes);
        } else if (0 == memcmp(SET_DECEASED, (const char *)req.cmd, sizeof(SET_DECEASED))) {
            ret = cmd_set_deceased(req.bytes);
        } else if (0 == memcmp(SET_SEPARATED, (const char *)req.cmd, sizeof(SET_SEPARATED))) {
            ret = cmd_set_separated(req.bytes);
        } else if (0 == memcmp(ARE_RELATED, (const char *)req.cmd, sizeof(ARE_RELATED))) {
            ret = cmd_are_related(req.bytes);
        } else if (0 == memcmp(DEGREES, (const char *)req.cmd, sizeof(DEGREES))) {
            ret = cmd_degrees_of_separation(req.bytes);
        } else  {
            ret = -1;
        }

        if (0 == ret) {
            send(OK, sizeof(OK));
        } else {
            send(ERR, sizeof(ERR));
	        break;
        }

    }

    return 0;
}
