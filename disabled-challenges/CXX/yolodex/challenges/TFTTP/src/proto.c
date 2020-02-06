#include "cgc_libc.h"
#include "cgc_proto.h"

//Describes a simple size-length packet format

int cgc_recvmsg(int fd, uint8_t *data, cgc_size_t maxsize, cgc_size_t minsize) {
    int res = 0;
    cgc_size_t size = 0;
    if (maxsize < sizeof(tfttp_hdr))
        return -3;
    if ((res = cgc_recv(fd, (char *)data, sizeof(tfttp_hdr))) != sizeof(tfttp_hdr))
        return res;
    size = *(cgc_size_t*)data;
    if (size > maxsize || size < minsize)
        return -1;
    if ((res = cgc_recv(fd, (char *)data+sizeof(tfttp_hdr), size)) != size)
        return -2;

    return size;
}

int cgc_senddgram(int fd, tfttp_pkt *msg, cgc_size_t size) {
    int res;
    if ((res=cgc_sendall(fd, (char *)msg, sizeof(tfttp_hdr))) != sizeof(tfttp_hdr)){
        return res;
    }
    return cgc_sendall(fd, (char *)msg->data, msg->hdr.size);
}

int cgc_recvdgram(int fd) {
    /*
     * Handles receiving of TFTTP datagrams, including defrag if necessary
     * Retransmits are allowed
     * Last received fragment is one used
     * Maxmimum allowed retransmitted packets is 5
     *
     * In case anyone's wondering why we allow frags,
     * fragmentation is provided to clobber stack enough to hit vulnerable
     * uninitialized memory usage.
    */

    uint16_t outstanding = 0;
    uint16_t totalfrag = 0;
    uint16_t curfragid = 0;
    enum pkttype fragcode = UNKNOWN;
    int i;
    tfttp_frag *f = NULL;
    char curfrag[MAX_FRAG][MAX_FRAG_DATA_LEN] = {0};

    cgc_memset(curpkt,'\0', TFTTP_STRUCT_SIZE); 

    while(1) {
        RECVM((uint8_t*)curpkt, MAX_DATA_LEN, 0) 
        if (curpkt->hdr.code != FRAG && !outstanding)
            return 0;
        else if (curpkt->hdr.code != FRAG)
            return -1;
        //we ensure this value is correct in recvmsg
        else if (curpkt->hdr.size != MAX_DATA_LEN) 
            return -2;

        f = (tfttp_frag*)curpkt->data;

        //like standardized TFTP, we do not allow out-of-order packets
        if(f->seqid != curfragid) {
            return -3;
        }

        if (f->seqid == 0) {
            outstanding = totalfrag = f->numfrag+1;
            if (totalfrag <= 1)
                //must be at least two fragments
                return -4;
            fragcode = f->code;
        }
        
        //some sanity checks
        if (!outstanding) {
            //should never get here
            return -5;
        } else if (totalfrag != f->numfrag+1) {
            //if we've already seen a fragment, numfrag and code should stay the same
            return -6;
        }

        cgc_memcpy(&curfrag[f->seqid], f->data, MAX_FRAG_DATA_LEN);
        outstanding--;
        curfragid++;

        if (!outstanding) {
            //reassemble and return
            //curpkt is large enough to hold MAX_DATA_LEN*256
            curpkt->hdr.code = fragcode;
            cgc_memcpy(curpkt->data, (char *)curfrag, MAX_PKT_SIZE);
            curpkt->hdr.size = totalfrag*MAX_DATA_LEN;
            return 0;
        }
    }
}

void cgc_create_resp_pkt(tfttp_pkt* pkt, char *resp) {
    cgc_memset(pkt,'\0', TFTTP_STRUCT_SIZE); 
    cgc_strcpy((char *)pkt->data, resp);
    pkt->hdr.code = RESP;
    //for now, fixed length responses until pollers can support otherwise
    //pkt->size = sizeof(enum pkttype)+cgc_strlen(resp)+1; 
    pkt->hdr.size = 256; //-_-
}
