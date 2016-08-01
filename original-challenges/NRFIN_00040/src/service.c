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

// Instruction format (based on GREATVIEW, even simpler):
// <op> <arg0> [<argv1> ...]
// NEW <id> <type> [<val>] -- don't have to initialize value
// SET <id> <val>
// DEL <id>

// Example "JSON":
// NEW 133 NUMBER 0 -- creates object 1337, a NUMBER; initialized to 0
// SET 133 42 -- updates object 1337 to 42
// NEW 45 STRING foo\x00
// DEL 133 -- destroy object 133 (42)
// DEL 45 -- destroy object 45 ("foo")

// Vuln:
// NEW object as type NUMBER, NUMBER field is initialized to non-NULL
// SET object with NUMBER that's too large to hold in NUMBER field, so promotion should occur, populate STRING field, set NUMBER field to NULL
    // type is not updated from NUMBER to STRING
// SERIALIZE object, type is consulted (it will be NUMBER), NUMBER field referenced, causing NULL ptr deref

#include "service.h"

// Globals
namespace_t ns;
char json[BUF_RX_SZ];

object_t * object_find(uint8_t id) {

    size_t i = 0;

    for (i=0; i<NUM_OBJS; i++) {
        if (NULL != ns.obj[i] && id == ns.obj[i]->id) {
#ifdef DEBUG
            fprintf(stderr, "[D] object_find | found object at index %d\n", i);
#endif
            return ns.obj[i];
        }
    }

#ifdef DEBUG
    fprintf(stderr, "[D] object_find | object not found\n", i);
#endif

    return NULL;
}

int parse_id(char **cursor, uint16_t *line_remaining, uint8_t *id) {

    int ret = SUCCESS;
    char *delim = NULL;
    uint16_t consumed = 0;

    if (NULL == (delim = strnchr(*cursor, ' ', (uint32_t)(*line_remaining)))) { 
#ifdef DEBUG
        fprintf(stderr, "[E] parse_id | unable to find delim (or remaining exceeded)\n");
#endif 
        ret = ERRNO_MALFORMED_JSON;
        goto bail;
    }
    consumed = delim - *cursor;

    uint32_t tmp = 0;
    if (SUCCESS != (ret = str2unt32n(*cursor, consumed, MAX_UINT8, &tmp))) {
#ifdef DEBUG
        fprintf(stderr, "[E] parse_id | unable to convert ID; ret = %d\n", ret);
#endif 
        goto bail;
    }

    // Write out result.
    *id = (uint8_t)tmp;

#ifdef DEBUG
    fprintf(stderr, "[D] parse_id | ID = %d\n", *id);
#endif 

    // Advance cursor.
    *cursor += consumed + 1;
    *line_remaining -= (consumed + 1);

bail:
    return ret;
}


int parse_type(char **cursor, uint16_t *line_remaining, objtype_t *type) {
    
    int ret = SUCCESS;
    char *delim = NULL;
    uint16_t consumed = 0;

    if (NULL == (delim = strnchr(*cursor, ' ', (uint32_t)(*line_remaining)))) { 
#ifdef DEBUG
        fprintf(stderr, "[E] parse_type | unable to find delim (or remaining exceeded)\n");
#endif 
        ret = ERRNO_MALFORMED_JSON;
        goto bail;
    }
    consumed = delim - *cursor;

    // Convert TYPE string to objtype_t
    // Promotion doesn't happen here; it happens during VAL parsing.
    if (0 == memcmp("NUMBER", *cursor, SZ_INSN_TYPE)) {

        *type = TYPE_NUMBER;

    } else if (0 == memcmp("STRING", *cursor, SZ_INSN_TYPE)) {

        *type = TYPE_STRING;

    } else {
#ifdef DEBUG
        fprintf(stderr, "[E] parse_type | got an invalid type: %d\n", *type);
#endif 
        ret = ERRNO_MALFORMED_JSON;
        goto bail;
    }

#ifdef DEBUG
    fprintf(stderr, "[D] parse_type | parsed type: %d\n", *type);
#endif

    // Advance cursor.
    *cursor += consumed + 1;
    *line_remaining -= (consumed + 1);

bail:
    return ret;
}


int parse_number(char **cursor, uint16_t *line_remaining, uint32_t *number) {

    int ret = SUCCESS;
    char *delim = NULL;
    uint16_t consumed = 0;

    if (NULL == (delim = strnchr(*cursor, ' ', (uint32_t)(*line_remaining)))) { 
#ifdef DEBUG
        fprintf(stderr, "[E] parse_number | unable to find delim (or remaining exceeded)\n");
#endif 
        ret = ERRNO_MALFORMED_JSON;
        goto bail;
    }
    consumed = delim - *cursor;

    if (SUCCESS != (ret = str2unt32n(*cursor, consumed, MAX_UINT32, number))) {
#ifdef DEBUG
        fprintf(stderr, "[D] parse_number | non-SUCCESS from str2unt32n(), could be PROMOTION; ret = %d\n", ret);
#endif 
        // We don't goto bail here because then we'd miss cursor advancement.
    } else {
#ifdef DEBUG
        fprintf(stderr, "[D] parse_number | number = %u\n", *number);
#endif  
    }

    // Advance cursor.
    *cursor += consumed + 1;
    *line_remaining -= (consumed + 1);

bail:
    return ret;
}


int parse_string(char **cursor, uint16_t *line_remaining, char *string) {

    int ret = SUCCESS;
    char *delim = NULL;
    uint16_t consumed = 0;

    if (NULL == (delim = strnchr(*cursor, ' ', (uint32_t)(*line_remaining)))) { 
#ifdef DEBUG
        fprintf(stderr, "[E] parse_string | unable to find delim (or remaining exceeded)\n");
#endif 
        ret = ERRNO_MALFORMED_JSON;
        goto bail;
    }
    consumed = delim - *cursor;

    // NOTE: minus 1 because we don't want to copy the newline
    // XXXX: underflow?
    strncpy(string, *cursor, MIN(*line_remaining-1, MAX_SZ_STRING));

#ifdef DEBUG
    fprintf(stderr, "[D] parse_string | string = %s\n", string);
#endif 

    // Advance cursor.
    *cursor += consumed + 1;
    *line_remaining -= (consumed + 1);

bail:
    return ret;
}


// Check whether or not we have enough space for another object.
// If we have enough space, allocate backing memory, add object to namespace.
// allocates space for an object, points *object at it
int object_new(uint8_t id, objtype_t type, uint32_t number, char *string) {

    int ret = SUCCESS;

    object_t *object = NULL;

    if (SUCCESS != (ret = allocate(SZ_PAGE, FALSE, (void **)&object))) {
#ifdef DEBUG
        fprintf(stderr, "[E] object_new | allocate() failed\n");
#endif    
        goto bail;
    }

    // Reject duplicate IDs
    // This appears to be in agreement with machine.py design.
    if (NULL != object_find(id)) {
#ifdef DEBUG
        fprintf(stderr, "[D] object_new | dupe ID; silently rejecting\n", id);
#endif 
        goto bail;
    }
    
    // Initialize the object
    object->id = id;
    object->type = TYPE_UNKNOWN;
    object->number = NULL;
    object->string = NULL;

    // If the object type is known (specified as part of construction), 
    // then fill in appropriate values.  Type is trusted here; we check type
    // and NUMBER -> STRING promotion in calling functions.
    if (TYPE_NUMBER == type) {
        object->type = TYPE_NUMBER;
        object->number = (uint32_t *)(object + OFF_NUMBER);
        *(object->number) = number;
    } else if (TYPE_STRING == type) {
        object->type = TYPE_STRING;
        object->string = (char *)(object + OFF_STRING);
        // If a VAL isn't specified, don't try to copy from NULL.
        if (NULL != string) { strncpy(object->string, string, MAX_SZ_STRING); }
    } else {
#ifdef DEBUG
        fprintf(stderr, "[E] object_new | TYPE INVALID (shouldn't happen)\n", id);
#endif 
        ret = ERRNO_MALFORMED_JSON;
        goto bail;
    }

    // Add the object to the namespace.
    ns.obj[id] = object;

bail:
    return ret;
}


// Format:
// DEL <id>
int op_del(char **cursor, uint16_t *line_remaining) {

    int ret = SUCCESS;
    uint8_t id = 0;
    size_t i = 0;

    // Get ID to DEL.
    if (SUCCESS != (ret = parse_id(cursor, line_remaining, &id))) {
#ifdef DEBUG
        fprintf(stderr, "[E] op_del | non-SUCCESS from op_del()\n");
#endif 
        goto bail;
    }

    for (i=0; i<NUM_OBJS; i++) {
        if (NULL != ns.obj[i] && id == ns.obj[i]->id) {
#ifdef DEBUG
            fprintf(stderr, "[D] object_del | deleting %03d\n", id);
#endif
            if (SUCCESS != (ret = deallocate(ns.obj[i], SZ_PAGE))) {
#ifdef DEBUG
                fprintf(stderr, "[E] op_del | failed to deallocate backing memory for ID %03d\n", id);
#endif  
            }     
            ns.obj[i] = NULL;
            goto bail;
        }
    }

#ifdef DEBUG
    fprintf(stderr, "[D] op_del | attempted to DEL non-existant object %03d\n", id);
#endif   

bail:
    return ret;
}


// Format:
// SET <id> [<val>]
int op_set(char **cursor, uint16_t *line_remaining) {

    int ret = SUCCESS;
    uint8_t id = 0;
    object_t *object = NULL;
    char *bak_cursor = NULL;
    uint16_t bak_line_remaining = 0;

    ////
    // Get ID
    ////
    if (SUCCESS != (ret = parse_id(cursor, line_remaining, &id))) {
#ifdef DEBUG
        fprintf(stderr, "[E] op_set | non-SUCCESS from parse_id()\n");
#endif 
        goto bail;
    }

    // If ID doesn't exist, bail.
    if (NULL == (object = object_find(id))) {
#ifdef DEBUG
        fprintf(stderr, "[D] op_set | could not find object; skipping assignment\n");
#endif  
        
#ifdef DEBUG
        fprintf(stderr, "[D] op_set | DEBUG: prior to advancement: *cursor: '%s', *line_remaining: %d\n", *cursor, *line_remaining);
#endif 
        // NOTE: minus one because we don't want to skip the \n
        *cursor += (*line_remaining - 1);
        *line_remaining = 0;

#ifdef DEBUG
        fprintf(stderr, "[D] op_set | DEBUG: after advancement: *cursor: '%s', *line_remaining: %d\n", *cursor, *line_remaining);
#endif 
        goto bail;
    }

    ////
    // Get VAL (based on TYPE)
    ////
    if (TYPE_NUMBER == object->type) {
        // If promotion happens, we will attempt to parse bytes as NUMBER, 
        // which we'll need to re-parse as a STRING.  So we store the 
        // before-parse values here and restore them should we need to re-parse.
        bak_cursor = *cursor;
        bak_line_remaining = *line_remaining;

        ret = parse_number(cursor, line_remaining, object->number);

        if (SUCCESS == ret) {
#ifdef DEBUG
            fprintf(stderr, "[D] op_set | number update: %03d = %d\n", object->id, object->number);
#endif          
        } else if (ERRNO_NUMBER_TOO_LARGE == ret) {

            // Supress the "error" & conduct promotion.
            ret = SUCCESS;

            // Vulnerable promotion does not result in updating of type.
#ifdef PATCHED
            object->type = TYPE_STRING;
            object->string = (char *)(object + OFF_STRING);
#endif
            // We're now a string; set the number ptr to NULL.
            object->number = NULL;

            // The string pointer is set to the promoted string value.
            // Reset cursor and line_remaining and re-parse.
            *cursor = bak_cursor;
            *line_remaining = bak_line_remaining;
            if (SUCCESS != (ret = parse_string(cursor, line_remaining, object->string))) {
#ifdef DEBUG
                fprintf(stderr, "[E] op_set | something bad happened in parse_string()\n", object->id, object->string);
#endif 
                goto bail;
            }

#ifdef DEBUG
            fprintf(stderr, "[D] op_set | number->string promotion: %03d = %s\n", object->id, object->string);
#endif 
        } else {
#ifdef DEBUG
            fprintf(stderr, "[E] op_set | parse_number returned error\n");
#endif  
            goto bail;
        }
    } else if (TYPE_STRING == object->type) {
        if (SUCCESS != (ret = parse_string(cursor, line_remaining, object->string))) {
#ifdef DEBUG
            fprintf(stderr, "[E] op_set | something bad happened in parse_string()\n", object->id, object->string);
#endif 
            goto bail;
        }
    } else {
#ifdef DEBUG
        fprintf(stderr, "[E] op_new | INVALID TYPE (SHOULDN'T HAPPEN)\n");
#endif  
    }

bail:
    return ret;
}


// Format:
// NEW <id> <type> [<val>]
int op_new(char **cursor, uint16_t *line_remaining) {

    int ret = SUCCESS;
    char *delim = NULL;

#ifdef DEBUG
    fprintf(stderr, "[D] op_new | INIT\n");
#endif

    ////
    // Get ID
    ////
    uint8_t id = 0;
    if (SUCCESS != (ret = parse_id(cursor, line_remaining, &id))) {
#ifdef DEBUG
        fprintf(stderr, "[E] op_new | non-SUCCESS from parse_id()\n");
#endif 
        goto bail;
    }

    ////
    // Get TYPE
    ////
    objtype_t type = TYPE_UNKNOWN;
    if (SUCCESS != (ret = parse_type(cursor, line_remaining, &type))) {
#ifdef DEBUG
        fprintf(stderr, "[E] op_new | non-SUCCESS from parse_type()\n");
#endif 
        goto bail;
    }

    ////
    // Get (optional) VAL
    ////
    if (NULL == (delim = strnchr(*cursor, ' ', (uint32_t)(*line_remaining)))) { 
        
        // We didn't find a VAL; we have everything we need to make the object.
#ifdef DEBUG
        fprintf(stderr, "[D] op_new | didn't find a VAL argument\n");
#endif 

        if (SUCCESS != (ret = object_new(id, type, 0, NULL))) {
#ifdef DEBUG
            fprintf(stderr, "[E] op_new | non-SUCCESS from object_new()\n");
#endif 
            goto bail;
        }

    } else {

        // We *did* find another delim (presumably the optional [<val>]).

        if (TYPE_NUMBER == type) {
            // In case we need to re-parse as a STRING (due to PROMOTION).
            char *bak_cursor = *cursor;
            uint16_t bak_line_remaining = *line_remaining;

            // Type confusion doesn't happen here; promotion is done correctly. 
            // If the number cannot be represented as a uint32_t, the type is 
            // updated to STRING and parsed as such.  The type is *not* updated 
            // in the SET command, which is where the vulnerability is.
            uint32_t number;
            ret = parse_number(cursor, line_remaining, &number);

            if (SUCCESS == ret) {
                // We successfully converted the string into a uint32_t.
                // Now create the object.
#ifdef DEBUG
                fprintf(stderr, "[D] op_new | NUMBER = %u\n", number);
#endif 

                if (SUCCESS != (ret = object_new(id, TYPE_NUMBER, number, NULL))) {
#ifdef DEBUG
                    fprintf(stderr, "[E] op_new | non-SUCCESS from object_new()\n");
#endif 
                    goto bail;
                }

            } else if (ERRNO_NUMBER_TOO_LARGE == ret) {
                // PROMOTION: The value provided cannot be represented by a 
                // uint32_t, so we must store it as a string instead.
#ifdef DEBUG
                fprintf(stderr, "[D] op_new | im creating a new STRING via PROMOTION, VAL = '%s'\n", bak_cursor);
#endif 

                char string[MAX_SZ_STRING] = { 0 };
                if (SUCCESS != (ret = parse_string(&bak_cursor, &bak_line_remaining, (char *)&string))) {
#ifdef DEBUG
                    fprintf(stderr, "[E] op_set | something bad happened in parse_string()\n");
#endif 
                    goto bail;
                }

                if (SUCCESS != (ret = object_new(id, TYPE_STRING, 0, (char *)&string))) {
#ifdef DEBUG
                    fprintf(stderr, "[E] op_new | non-SUCCESS from object_new()\n");
#endif 
                    goto bail;
                }

            } else {
#ifdef DEBUG
                fprintf(stderr, "[E] op_new | something bad happeend during str2intn()\n");
#endif 
                ret = ERRNO_MALFORMED_JSON;
                goto bail;
            }

        } else if (TYPE_STRING == type) {
            // If the JSON says [<val>] is a STRING, we trust this and 
            // treat it as such.  There *shouldn't* be an issue with 
            // doing this.
            char string[MAX_SZ_STRING] = { 0 };
            if (SUCCESS != (ret = parse_string(cursor, line_remaining, (char *)&string))) {
#ifdef DEBUG
                fprintf(stderr, "[E] op_set | something bad happened in parse_string()\n");
#endif 
                goto bail;
            }

#ifdef DEBUG
                fprintf(stderr, "[D] op_new | im creating a new STRING (not via promo), VAL = '%s'\n", string);
#endif 

            if (SUCCESS != (ret = object_new(id, TYPE_STRING, 0, (char *)&string))) {
#ifdef DEBUG
                fprintf(stderr, "[E] op_new | non-SUCCESS from object_new()\n");
#endif 
                goto bail;
            }

        } else {
#ifdef DEBUG
            fprintf(stderr, "[D] op_new | TYPE invalid (SHOULD NEVER HAPPEN)\n");
#endif 
            ret = ERRNO_MALFORMED_JSON;
            goto bail;
        }
    }

bail:
    return ret;
}


int parse_json(uint16_t json_sz) {

    int ret = SUCCESS;
    char *cursor = json;
    char *op = NULL;
    char *line_start = NULL, *line_end = NULL, *delim = NULL;
    uint16_t remaining = json_sz;
    uint16_t line_remaining = 0;
    uint16_t consumed = 0;

    // There's nothing to do; just return.
    if (0 == json_sz) {
#ifdef DEBUG
        fprintf(stderr, "[D] parse_json | json_sz = 0x%04x; nothing to do\n", json_sz);
#endif 
        goto bail;
    }

    // For each INSN (1 per line)...
    while (NULL != (line_start = strnchr(cursor, '\n', (uint32_t)remaining))) {

#ifdef DEBUG
        fprintf(stderr, "[D] parse_json | top of loop; line_start = '%s'\n", line_start);
#endif 

        // Consume the newline.
        line_start += 1;
        remaining -= 1;

        // If there's nothing left, we've parse it all.
        if (0 == remaining) { 
#ifdef DEBUG
            fprintf(stderr, "[D] parse_json | consumed all JSON\n", remaining);
#endif
            goto bail;
        }

        // Find next newline (so we have bounds to this line).
        if (NULL == (line_end = strnchr(line_start, '\n', (uint32_t)remaining))) {
#ifdef DEBUG
            fprintf(stderr, "[E] parse_json | could not find next line ending; line_start is: '%s'\n", line_start);
#endif  
            ret = ERRNO_MALFORMED_JSON;
            goto bail;
        }
        line_remaining = line_end - line_start;
        cursor = line_start;

#ifdef DEBUG
        fprintf(stderr, "[D] parse_json | cursor = line_start = '%s'\n", cursor);
#endif

        // Decrement from global remaining now, since we'll be consuming this line.
        remaining -= line_remaining;

        ////
        // Get OP
        ////
        if (NULL == (delim = strnchr(cursor, ' ', (uint32_t)(line_remaining)))) { 
#ifdef DEBUG
            fprintf(stderr, "[E] parse_json | cannot find OP delim\n");
#endif   
            ret = ERRNO_MALFORMED_JSON;
            goto bail;
        }
        consumed = delim - cursor;
        line_remaining -= consumed;

        if (SZ_INSN_OP != consumed) {
#ifdef DEBUG
            fprintf(stderr, "[E] parse_json | invalid OP length: %d\n", consumed);
#endif
            ret = ERRNO_MALFORMED_JSON;
            goto bail;
        }

        ////
        // Dispatch OP
        ////
        op = cursor;
        cursor += SZ_INSN_OP+1;
        if (0 == memcmp("NEW", op, SZ_INSN_OP)) {
            if (SUCCESS != (ret = op_new(&cursor, &line_remaining))) {
#ifdef DEBUG
                fprintf(stderr, "[E] parse_json | NEW | non-SUCCESS from op_new()\n");
#endif         
                goto bail;       
            }
        } else if (0 == memcmp("SET", op, SZ_INSN_OP)) {
            if (SUCCESS != (ret = op_set(&cursor, &line_remaining))) {
#ifdef DEBUG
                fprintf(stderr, "[E] parse_json | NEW | non-SUCCESS from op_set()\n");
#endif         
                goto bail;       
            }
        } else if (0 == memcmp("DEL", op, SZ_INSN_OP)) {
            if (SUCCESS != (ret = op_del(&cursor, &line_remaining))) {
#ifdef DEBUG
                fprintf(stderr, "[E] parse_json | NEW | non-SUCCESS from op_del()\n");
#endif         
                goto bail;       
            }
        } else {
#ifdef DEBUG
            fprintf(stderr, "[E] parse_json | unknown OP: '%.3s'\n", cursor);
#endif
            ret = ERRNO_MALFORMED_JSON;
            goto bail;
        }
    }

bail:
    return ret;
}

// If we get DESERIALIZE command, then it should be followed by 2B of len + data.
int deserialize(void) {

    int ret = SUCCESS;
    size_t rx_bytes = 0;

    uint16_t json_sz = 0;

    // Get json_sz.
    rx_bytes = 0;
    if (SUCCESS != (ret = receive_all(STDIN, (void *)&json_sz, sizeof(json_sz), &rx_bytes)) || sizeof(json_sz) != rx_bytes) { 
#ifdef DEBUG
        fprintf(stderr, "[E] deserialize | during receive_all() of json_sz\n");
#endif
        ret = ERRNO_RECV;
        goto bail;
    }

#ifdef DEBUG
    fprintf(stderr, "[D] deserialize | json_sz = 0x%04x\n", json_sz);
#endif

    // Get json.
    rx_bytes = 0;
    if (SUCCESS != (ret = receive_all(STDIN, (void *)&json, json_sz, &rx_bytes)) || json_sz != rx_bytes) { 
#ifdef DEBUG
        fprintf(stderr, "[E] deserialize | during receive_all() of json\n");
#endif
        ret = ERRNO_RECV;
        goto bail;
    }

#ifdef DEBUG
    fprintf(stderr, "[D] deserialize | read 0x%04x bytes of json\n", rx_bytes);
#endif

    // Parse json.
    if (SUCCESS != (ret = parse_json(json_sz))) {
#ifdef DEBUG
        fprintf(stderr, "[E] deserialize | non-SUCCESS from parse_json(); bailing\n");
#endif
        goto bail;
    }

bail:
    return ret;
}


// Format: <id> <type> <val>
// Example: 333 NUMBER 42
int serialize(void) {

    int ret = SUCCESS;
    uint32_t consumed = 0;
    object_t *object = NULL;
    size_t i = 0;

#ifdef DEBUG
    fprintf(stderr, "[D] serialize | INIT\n");
#endif  

    // Just bail if we can't fit serialization in a buffer?
    // Or transmit one at a time?
    // I'm thinking transmit as we go...
    char tx_buf[MAX_SZ_LINE] = { 0 }; // buffer per object

    // Loop over the objects, spit them back.
    for (i=0; i<NUM_OBJS; i++) {

        // This *should* be sufficient to reset the buffer.
        tx_buf[0] = '\0';
        consumed = 0;

        if (NULL == (object = ns.obj[i])) { continue; }

#ifdef DEBUG
        fprintf(stderr, "[D] serialize | obj %03d INIT\n", i);
#endif  

        // Do the ID.
        consumed += uint2str32(tx_buf+consumed, MAX_SZ_LINE-consumed-1, object->id);

#ifdef DEBUG
        fprintf(stderr, "[D] serialize | +=ID: tx_buf = '%s'\n", tx_buf);
#endif 

        // Do the TYPE + VAL.
        if (TYPE_NUMBER == object->type) {
            consumed += strncpy(tx_buf+consumed, " NUMBER ", MAX_SZ_LINE-consumed-1);
#ifdef DEBUG
            fprintf(stderr, "[D] serialize | += TYPE: tx_buf = '%s'\n", tx_buf);
#endif

            // NOTE: This is where the vuln gets triggered.  We assume that if 
            // the type is NUMBER, than the number field points to non-NULL. 
            // This asumption is invalid in the case of buggy promotion.
#ifdef DEBUG
            fprintf(stderr, "[D] serialize | *object->number = %u\n", *object->number);
#endif
            consumed += uint2str32(tx_buf+consumed, MAX_SZ_LINE-consumed-1, *object->number);

        } else if (TYPE_STRING == object->type) {
            consumed += strncpy(tx_buf+consumed, " STRING ", MAX_SZ_LINE-consumed-1);
            consumed += strncpy(tx_buf+consumed, object->string, MAX_SZ_LINE-consumed-1);
        } else {
#ifdef DEBUG
            fprintf(stderr, "[E] serialize | INVALID TYPE (SHOULDN'T HAPPEN)\n");
#endif      
        }

        // CRS will read until here.
        tx_buf[consumed] = '\n';

        // We've built a line.
#ifdef DEBUG
        fprintf(stderr, "[D] serialize | obj %03d DONE: %s", i, tx_buf);
#endif

        // Send answer back to CRS.
        if (SUCCESS != (ret = transmit_all(STDOUT, &tx_buf, consumed+1, NULL))) { 
#ifdef DEBUG
            fprintf(stderr, "[E] serialize | during transmit_all()\n");
#endif
            ret = ERRNO_TRANSMIT;
            goto bail;
        }
    }

bail:
    return ret;
}


// Protocol:
// 1B: command
//  - deserialize
//  - serialize
//  - exit
// if command is deserialize, then JSON follows:
// 2B: length of JSON
// ?B: JSON data
int main(void) {

    int ret = SUCCESS;
    size_t rx_bytes = 0;
    size_t tx_bytes = 0;

    memset((void *)&ns, 0, sizeof(ns));

    // Keep processing commands until told to exit (or error occurs).
    while (TRUE) {

        // Keep trying to get a command byte.
        uint32_t got_command = FALSE;
        command_t command = CMD_UNKNOWN;

        while (FALSE == got_command) {

            // Get command (1B).
            if (SUCCESS != (ret = receive_all(STDIN, (void *)&command, sizeof(command), &rx_bytes))) { 
#ifdef DEBUG
                fprintf(stderr, "[E] during receive_all() of command\n");
#endif
                ret = ERRNO_RECV;
                goto bail;
            }

            if (0 != rx_bytes) { got_command = TRUE; }
        }

#ifdef DEBUG
        fprintf(stderr, "[D] got command: 0x%02x\n", command);
#endif

        // Dispatch command.
        if (CMD_DESERIALIZE == command) {
            if (SUCCESS != (ret = deserialize())) {
#ifdef DEBUG
                fprintf(stderr, "[E] non-SUCCESS from deserialize(); bailing...\n");
#endif
                goto bail;
            }
        } else if (CMD_SERIALIZE == command) {
            if (SUCCESS != (ret = serialize())) {
#ifdef DEBUG
                fprintf(stderr, "[E] non-SUCCESS from serialize(); bailing...\n");
#endif
                goto bail;
            }
        } else if (CMD_EXIT == command) {
#ifdef DEBUG
            fprintf(stderr, "[D] received EXIT command, shutting down...\n");
#endif
            goto bail;
        } else {
#ifdef DEBUG
            fprintf(stderr, "[D] received INVALID command: 0x%02x\n", command);
#endif
        }
    }

bail:
    return ret;
}

