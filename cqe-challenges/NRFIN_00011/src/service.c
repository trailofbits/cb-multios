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

#include "service.h"

////
// Globals
////
char buf_recv_tmp[SZ_BUF_RECV] = { STRING_TERMINATOR };

////
// Functions
////

// Populate a buf with len random lowercase alpha characters.
void random_alpha_lower(char *buf, size_t len) {

    int ret = SUCCESS;
    size_t rnd_bytes = 0;
    unsigned char rnd[len];

    while ((0 != random(rnd, len, &rnd_bytes)) && (len != rnd_bytes)) {}

    for (int i = 0; i < len; i++) {
        buf[i] = (rnd[i] % NUM_CHARS_ALPHA) + 'a';
    }
}


// Takes a rp ("raw path") and turns it into a cp ("canonicalized path").
// Vulnerability is in this function, emulates MS08-067 (Conficker).
// Canonicalization process:
    // CANON_TOKEN -> empty string
    //  for each CANON_TOKEN, advance beyond the token and strncat() until the 
    //  next CANON_TOKEN
// Case A:
    // aaaaaaaaaaaaaaaa
    // 0000000000000000
    // Section 0 occupies the entire rp.
// Case B:
    // aaaa()bbbb()cccc
    // 0000  1111  2222
    // Section 0 is bound by rp and the first token.
    // Section 1 is bound by the first token and the second token.
    // Section 2 is bound by the last token and the end of rp (rp + rp_len).
int canonicalize_path(char * cp, char * rp, size_t rp_len) {

    int ret = SUCCESS;
    char * sec_start = NULL;
    char * sec_end = NULL;
    size_t sz_copy = 0;
    char *pos = rp; // A parsing index into the rp.

#ifdef PATCHED
    size_t sz_consumed = 0;
#endif

    // The first section is a special case.
    // Rather than starting at a token, sec_start will be rp.
    // sec_end will be either the location of the first token, or if not 
    // present, rp + rp_len.
    sec_start = rp;
    if (NULL != (pos = strpos(rp, CANON_TOKEN))) {
        sec_end = pos;
    } else {
        sec_end = rp + rp_len;
    }

    // Initial ecurity check (this one should actually work without patch).
    sz_copy = sec_end - sec_start;
#ifdef PATCHED
    sz_consumed += sz_copy;
    if (sz_consumed > SZ_MAX_FILEPATH)
#else
    if (sz_copy > SZ_MAX_FILEPATH)
#endif
    {
#ifdef DEBUG
        fprintf(stderr, "[D] 1st section: %d > SZ_MAX_FILEPATH; rejecting\n", (sec_end - sec_start));
#endif
        ret = ERRNO_CANON;
        goto _bail_canon;
    }

    // If we pass the security check, we do the strncat.
    strncat(cp, sec_start, sz_copy);

    // If pos is NULL, meaning we just strncat()ed the entire rp into the cp, 
    // then there's no more to process.  We've handled Case A.
    if (NULL == pos) { goto _bail_canon; }

    // If, however, pos is non-NULL, then there may be additional sections we 
    // need to handle.  We advance pos beyond the token and start looking for 
    // more tokens.
    pos += (sizeof(CANON_TOKEN)-sizeof(STRING_TERMINATOR_STR));
    sec_start = pos;

    while (NULL != (pos = strpos(pos, CANON_TOKEN))) {

        // We found a token.  This token signifies the end of a section.
        sec_end = pos;

        // We do our security check and then strncat().
        sz_copy = sec_end - sec_start;
#ifdef PATCHED
        sz_consumed += sz_copy;
        if (sz_consumed > SZ_MAX_FILEPATH)
#else
        if (sz_copy > SZ_MAX_FILEPATH)
#endif 
        {
#ifdef DEBUG
            fprintf(stderr, "[D] within while(); rejecting overly-long path\n");
#endif
            ret = ERRNO_CANON;
            goto _bail_canon; 
        }

        strncat(cp, sec_start, sz_copy);

        // We advance pos beyond the token and update sec_start.
        pos += (sizeof(CANON_TOKEN)-sizeof(STRING_TERMINATOR_STR));
        sec_start = pos;
    }

    // We have another edge case, illustrated by Case B.
    // If the final section doesn't end in a token, then it ends at rp + rp_len.
    sec_end = rp + rp_len;
    if (sec_start < sec_end) {
        // If sec_start is before the end of the rp, then there's more we need 
        // to strncat().

        // We do our (buggy) security check and then strncat().
        sz_copy = sec_end - sec_start;
#ifdef PATCHED
        sz_consumed += sz_copy;
        if (sz_consumed > SZ_MAX_FILEPATH)
#else
        if (sz_copy > SZ_MAX_FILEPATH)
#endif 
        {
#ifdef DEBUG
            fprintf(stderr, "[D] after while(); rejecting overly-long path\n");
#endif
            ret = ERRNO_CANON;
            goto _bail_canon; 
        }

        strncat(cp, sec_start, sz_copy);
    }

_bail_canon:
    return ret;
}


// This is recursive, depth-first.
int request_document(char * path, size_t recusion_depth) {

    int ret = SUCCESS;
    size_t sz_recv = 0;

    // Place some arbitrary upper limit on recursion so that SEGFAULTs cannot 
    // be caused via recursion.
    if (recusion_depth > MAX_RECURSION_DEPTH) {
#ifdef DEBUG
        fprintf(stderr, "[E] exceeded recursion depth; ignoring request\n");
#endif 
        return ERRNO_RECUSION;
    }

#ifdef DEBUG
    fprintf(stderr, "[D] *** REQUEST: '%s' ***\n", path);
#endif    

    // Send request to the CRS
    if (SUCCESS != (ret = transmit_with_term(STDOUT, path, strlen(path), NULL))) { 
#ifdef DEBUG
        fprintf(stderr, "[E] during request for '%s'\n", path);
#endif
        return ret; 
    }

    // Parse the response for document length, name and contents.

    // First, get the size of the document.
    // (Specified as an unsigned short, assumed to be first 2 bytes).
    unsigned short doc_len = 0;
    if (SUCCESS != (ret = receive_all(STDIN, (void *)&doc_len, sizeof(doc_len), NULL))) {
#ifdef DEBUG
        fprintf(stderr, "[E] during doc_len receive ()\n");
#endif
        return ret; 
    }

    // Our poller won't hit this edge case.
    if (doc_len + 1 < doc_len) {
#ifdef DEBUG
        fprintf(stderr, "[D] overflow in doc_len; rejecting", doc_len);
#endif
        return ret;
    }

    // Next, get the name of the document.
    if (0 > recv_until_delim(STDIN, buf_recv_tmp, SZ_BUF_RECV)) {
#ifdef DEBUG
        fprintf(stderr, "[E] during doc name receive ()\n");
#endif
        return ret; 
    }

    // Check the name of the document against the expected name.
    if (0 != strcmp(path, buf_recv_tmp)) {
#ifdef DEBUG
        fprintf(stderr, "[E] doc name mismatch: got: %s, expected: %s\n", buf_recv_tmp, path);
#endif
        return ret;    
    }

#ifdef DEBUG
    fprintf(stderr, "[D] doc name matches\n");
#endif 

    // Finally, get the document contents.
    char * doc_contents = NULL;
    if (SUCCESS != (ret = allocate(doc_len+1, 0, (void **)&doc_contents))) {
#ifdef DEBUG
        fprintf(stderr, "[E] allocate(); length = 0x%04x", doc_len);
#endif
        return ret;
    }

#ifdef DEBUG
        fprintf(stderr, "[D] allocate()d buffer; doc_contents @ %p, doc_len+1 = %d\n", doc_contents, doc_len+1);
#endif 

    if (SUCCESS != (ret = receive_with_term(STDIN, doc_contents, doc_len, &sz_recv)) ||
        sz_recv != doc_len) {

#ifdef DEBUG
        fprintf(stderr, "[E] doc_contents: receive ()d %d bytes, expected %d\n", sz_recv, doc_len);
#endif
        goto _bail_request;
    }

#ifdef DEBUG
        fprintf(stderr, "[D] receive ()d %d bytes into allocate()d buffer @ %p; contents:\n", sz_recv, doc_contents);
        size_t i = 0;
        for (i=0; i<sz_recv; i++) {
            fprintf(stderr, "%02x ", doc_contents[i]);
            if (!((i+1)% 32)) { fprintf(stderr, "\n"); }
        }
        fprintf(stderr, "\n[D] (end contents)\n");
#endif 

    // Find all the path references in the document and request those as well.

    // Documents are _kinda_ HTML.  They reference other files like:
    // ...
    // $SRC$<filename>$!SRC$
    char * open = doc_contents;
    char * clse = NULL;

    while (NULL != (open = strpos(open, TAG_SRC_OPEN))) {

        // Advance open beyond the tag.
        open += strlen(TAG_SRC_OPEN);

        // We found the opening tag, now find the closing tag.
        clse = strpos(open, TAG_SRC_CLSE);

        if (NULL != clse) {

            // Now that we have a SRC open & close tag combination, we copy the 
            // rp between them into a temporary buffer and allocate our cp.
            size_t rp_len = clse - open + 1;
            char rp[rp_len];
            strncpy(rp, open, rp_len-1);
            rp[rp_len-1] = STRING_TERMINATOR;

            char cp[SZ_MAX_FILEPATH] = { STRING_TERMINATOR };

            // We canonicalize from rp to cp.
            if (SUCCESS != (ret = canonicalize_path(cp, rp, rp_len))) {
                goto _bail_request;
            }

            // Finally, we have a canonicalized path.  Request it and recurse.
            if (SUCCESS != (ret = request_document(cp, ++recusion_depth))) {
                goto _bail_request;
            }      
        }
    }

_bail_request:
    deallocate(doc_contents, doc_len+1);
    return ret;
}

int main(void) {

    int ret = SUCCESS;

    // Request the "index" document from the CRS.
    char index_path[SZ_INDEX_PATH];
    random_alpha_lower(index_path, SZ_INDEX_PATH);
    index_path[SZ_INDEX_PATH-1] = STRING_TERMINATOR;

#ifdef DEBUG
    fprintf(stderr, "\n\n\n\n[D] index_path: %s\n", index_path);
#endif

    return request_document(index_path, 0);
}  






