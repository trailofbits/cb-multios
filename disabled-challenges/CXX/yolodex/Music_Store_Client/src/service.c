#include "libcgc.h"
#include "cgc_libc.h"
#include "cgc_service.h"

char* cgc_setValue(char* buffer, char* value) {
    char* ptr =NULL;
    int count =0;
    int i =0;
    char* delim = PARAM_DELIM;

    ptr = buffer;
    while(*ptr && (*ptr!=*delim) && count < RESULT_VALUE_SIZE)
        ptr++, count++;

    cgc_memcpy(value, buffer, count);

    return ++ptr;

}

int cgc_parseResultSize(char* buffer)
{
    char* start =NULL;
    char* end =NULL;
    char key[KEY_SIZE] = {0};
    char value[RESULT_VALUE_SIZE] = {0};
    int count =0;
    int i =0;
    char* delim = KEYVAL_DELIM;
    int ret =0;
    int num_results =0;

    start = buffer;
    end = start;
    count = 0;
    while(*end && (*end!=*delim) && count < KEY_SIZE)
            end++, count++;

    cgc_memcpy(key, start, count);
    if(cgc_strcmp(key, NUM_STR) == 0) {
        cgc_setValue(++end, value);
        num_results = cgc_str2int(value);
        return num_results;
    }

    return 0;

}

int cgc_parseBalanceResult(char* buffer)
{
    char* start =NULL;
    char* end =NULL;
    char key[KEY_SIZE] ={0};
    char value[RESULT_VALUE_SIZE] ={0};
    int count =0;
    int i =0;
    char* delim = KEYVAL_DELIM;
    int ret =0;
    int balance =0;

    start = buffer;
    end = start;
    count = 0;
    while(*end && (*end!=*delim) && count < KEY_SIZE)
            end++, count++;

    cgc_memcpy(key, start, count);
    if(cgc_strcmp(key, BAL_STR) == 0) {
        cgc_setValue(++end, value);
        balance = cgc_str2int(value);
        if (balance < 0 || balance > 255)
            return 0;
        return balance;
    }

    return 0;

}

int cgc_parseSearchResult(char* buffer, Song* song)
{
    char* start =NULL;
    char* end =NULL;
    char key[KEY_SIZE] ={0};
    int count =0;
    int i =0;
    char* delim = KEYVAL_DELIM;
    int ret =0;

    cgc_memset(song, 0, SONG_SIZE);

    start = buffer;
    while(1) {
        end = start;
        count = 0;
        while(*end && (*end!=*delim) && count < KEY_SIZE)
            end++, count++;
        
        cgc_memcpy(key, start, count);
        if(cgc_strcmp(key, SONG_ID_STR) == 0)
            start = cgc_setValue(++end, song->id);
        else if(cgc_strcmp(key, PRICE_STR) == 0)
            start = cgc_setValue(++end, song->price);
        else if(cgc_strcmp(key, ARTIST_STR) == 0)
            start = cgc_setValue(++end, song->artist);
        else if (cgc_strcmp(key, ALBUM_STR) == 0)
            start = cgc_setValue(++end, song->album);
        else if (cgc_strcmp(key, SONG_STR) == 0) {
            cgc_setValue(++end, song->song);

            return 0;
        } 
        else
            return 0;

        cgc_memset(key, 0, KEY_SIZE);
    }

    return 0;

}

int cgc_receiveBalance(int socket)
{
    char buf[1024] ={0};
    int bytes_read =0;
    int balance =0;

    bytes_read = cgc_recvline(socket, buf, sizeof(buf)-1);
    if (bytes_read < 0)
        cgc__terminate(2);

    if (bytes_read == 0)
        return 0;

    balance = cgc_parseBalanceResult(buf);

    return balance;
}

int cgc_receiveNumResults(int socket)
{
    char buf[1024] ={0};
    int bytes_read =0;
    int num_results =0;

    bytes_read = cgc_recvline(socket, buf, sizeof(buf)-1);
    if (bytes_read < 0)
        cgc__terminate(2);

    if (bytes_read == 0)
        return 0;

    num_results = cgc_parseResultSize(buf);
    if (num_results > 0)
        return num_results;
    
    return 0;
}

int cgc_receiveSearchResults(int socket, SongList* songList, int limit)
{
    char buf[1024] ={0};
    int ret =0;
    int bytes_read =0;
    int num_results =0;

    num_results = cgc_receiveNumResults(socket);
    while(num_results) 
    {
        bytes_read = cgc_recvline(socket, buf, sizeof(buf)-1);
        if (bytes_read < 0)
            cgc__terminate(2);

        if (bytes_read == 0)
            return 0;

        if(songList->size < limit) {
            ret = cgc_parseSearchResult(buf, &songList->songs[songList->size]);
            if (ret != 0)
                cgc__terminate(10);

            songList->size++;
        }

        num_results--;

    }

    return 0;
}

char * cgc_createSearchString(Request request)
{
    char* buffer =NULL;
    int ret =0;

    ret = cgc_allocate(sizeof(request)+cgc_MIN_REQ_LEN, 0, (void **) &buffer);
    if (ret != 0)
        cgc__terminate(3);

    cgc_memset(buffer, 0, sizeof(request)+cgc_MIN_REQ_LEN);
    cgc_strcat(buffer, TERM_STR);
    cgc_strcat(buffer, KEYVAL_DELIM);
    cgc_strcat(buffer, request.term);
    cgc_strcat(buffer, PARAM_DELIM);
    cgc_strcat(buffer, ATTRIBUTE_STR);
    cgc_strcat(buffer, KEYVAL_DELIM);
    cgc_strcat(buffer, request.attribute);
    cgc_strcat(buffer, PARAM_DELIM);
    cgc_strcat(buffer, LIMIT_STR);
    cgc_strcat(buffer, KEYVAL_DELIM);
    cgc_strcat(buffer, request.limit);
    cgc_strcat(buffer, EOL_STR);

    return buffer;
}

unsigned int cgc_getRandomNumber(unsigned int max)
{
    cgc_size_t bytes_written =0;
    unsigned int index =0;
    int ret =0;

    ret = cgc_random(&index, sizeof(index), &bytes_written);
    if (ret != 0)
        cgc__terminate(1);

    if (bytes_written != sizeof(index))
        cgc__terminate(2);

    index = index % max;

    return index;
}

void cgc_getRandomAttribute(Request* request)
{
    int index =0;

    index = cgc_getRandomNumber(ATTR_NUM);
    cgc_memcpy(request->attribute, attributes[index], cgc_strlen(attributes[index]));
}

void cgc_getRandomTerm(Request* request)
{
    unsigned int size =0;
    unsigned int charset_size =0;
    int index =0;

    while(size == 0) {
        size = cgc_getRandomNumber(RESULT_VALUE_SIZE);
    }

    charset_size = cgc_strlen(cgc_charset);
    for(index = 0; index < size; index++) {
        int letter = cgc_getRandomNumber(charset_size);
        request->term[index] = cgc_charset[letter];
    }

    request->term[size] = '\0';

}

void cgc_createRandomRequest(Request *request) {

    cgc_memset(request, 0, REQUEST_SIZE);

    cgc_getRandomTerm(request);
    cgc_getRandomAttribute(request);
    cgc_memcpy(request->limit, RESULT_LIMIT_STR, sizeof(RESULT_LIMIT_STR));

}

cgc_size_t cgc_getRandomGiftCard(char** gift_card) {

    unsigned int charset_size =0;
    int index =0;
    int section =0;
    int ret =0;

    ret = cgc_allocate(GIFT_CARD_LEN+1, 0, (void **) gift_card);
    if (ret != 0)
        cgc__terminate(3);

    cgc_memset(*gift_card, 0, GIFT_CARD_LEN);
    charset_size = cgc_strlen(cgc_charset);

    for(index = 0; index < GIFT_CARD_LEN; index++) {
        int letter = cgc_getRandomNumber(charset_size);
        (*gift_card)[index] =  cgc_charset[letter];
    }

    (*gift_card)[GIFT_CARD_LEN] = '\0';

    return GIFT_CARD_LEN+1;
}

int cgc_purchaseSong(int socket, Song* selectedSong, SongList* mySongList) {
    int ret=0;
    char price=0; 

    price = cgc_str2int(selectedSong->price);

#ifdef PATCHED
    if(price < 0) {
        ret = cgc_transmit_all(socket, INVALID_PRICE_MSG, sizeof(INVALID_PRICE_MSG)-1);
        if (ret != 0)
            cgc__terminate(10);
        return INVALID_PRICE;
    }
#else
#endif

    if(mySongList->balance >= price) {

        mySongList->balance -= price;
        mySongList->size++;
        cgc_memcpy(&mySongList->songs[mySongList->size-1], selectedSong, RESULT_VALUE_SIZE*3);

        ret = cgc_transmit_all(socket, mySongList->songs[mySongList->size-1].id, cgc_strlen(mySongList->songs[mySongList->size-1].id));
        if (ret != 0)
            cgc__terminate(10);
        ret = cgc_transmit_all(socket, "\n", cgc_strlen("\n"));
        if (ret != 0)
            cgc__terminate(10);

        return SUCCESS;

    }

    return LOW_BALANCE;
}

int cgc_sendSearchString(int socket, Request request) {
    int ret =0;
    char *search_string =NULL;

    search_string = cgc_createSearchString(request);

    ret = cgc_transmit_all(socket, search_string, cgc_strlen(search_string));
    if (ret != 0)
        cgc__terminate(4);

    return 0;
}

int cgc_getBalance(SongList* mySongList) {
    cgc_size_t size =0;
    char* gift_card =NULL;
    char *buffer =NULL;
    int ret =0;

    size = cgc_getRandomGiftCard(&gift_card);

    ret = cgc_allocate(size+sizeof("ID=")+sizeof("\n")+1, 0, (void **) &buffer);
    if (ret != 0)
        cgc__terminate(3);

    cgc_memset(buffer, 0, size+sizeof("ID=")+sizeof("\n")+1);

    cgc_strcat(buffer,"ID=");
    cgc_strcat(buffer,gift_card);
    cgc_strcat(buffer,"\n");

    ret = cgc_deallocate(gift_card, size);
    if (ret != 0)
        cgc__terminate(3);

    ret = cgc_transmit_all(STDOUT, buffer, cgc_strlen(buffer));
    if (ret != 0)
        cgc__terminate(10);

    ret = cgc_deallocate(buffer, size+sizeof("ID=")+sizeof("\n")+1);
    if (ret != 0)
        cgc__terminate(3);

    mySongList->balance = cgc_receiveBalance(STDIN);
#ifdef PATCHED
    mySongList->maxSize = mySongList->balance;
#else
#endif
    ret = cgc_allocate(sizeof(Song)*mySongList->balance, 0, (void**) &mySongList->songs);
    if (ret != 0)
        cgc__terminate(3);

    return 0;
}

Song* cgc_selectSong(SongList results, Request request)
{
    return &results.songs[0];
}

int main(int cgc_argc, char *cgc_argv[]) {
    int ret =0;
    int starting_balance =0;
#ifdef PATCHED
    SongList mySongList ={0, 0, NULL, 0};
    SongList results ={0, 0, NULL, 0};
#else
    SongList mySongList ={0, NULL, 0};
    SongList results ={0, NULL, 0};
#endif
    Request request ={0,0,0};
    Song songs[RESULT_LIMIT] ={0};
    Song* selectedSong =NULL;
    results.songs = songs;

    cgc_getBalance(&mySongList);

    starting_balance = mySongList.balance;
#ifdef PATCHED
    while(mySongList.balance > 0 && mySongList.maxSize > mySongList.size) {
#else
    while(mySongList.balance > 0) {
#endif
        results.size = 0;

        cgc_createRandomRequest(&request);
        cgc_sendSearchString(STDOUT, request);
        cgc_receiveSearchResults(STDIN, &results, RESULT_LIMIT);

        selectedSong = cgc_selectSong(results, request);

        ret = cgc_purchaseSong(STDOUT, selectedSong, &mySongList);
        if (ret == LOW_BALANCE)
            break;

        cgc_receiveBalance(STDIN);
    }

    ret = cgc_deallocate(mySongList.songs, sizeof(Song)*starting_balance);
    if (ret != 0)
        cgc__terminate(3);
    return ret;

}
