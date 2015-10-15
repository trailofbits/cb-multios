#include <libcgc.h>
#include "libc.h"
#include "service.h"

char* setValue(char* buffer, char* value) {
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

int parseResultSize(char* buffer)
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
        setValue(++end, value);
        num_results = str2int(value);
        return num_results;
    }

    return 0;

}

int parseBalanceResult(char* buffer)
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
        setValue(++end, value);
        balance = str2int(value);
        if (balance < 0 || balance > 255)
            return 0;
        return balance;
    }

    return 0;

}

int parseSearchResult(char* buffer, Song* song)
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
            start = setValue(++end, song->id);
        else if(cgc_strcmp(key, PRICE_STR) == 0)
            start = setValue(++end, song->price);
        else if(cgc_strcmp(key, ARTIST_STR) == 0)
            start = setValue(++end, song->artist);
        else if (cgc_strcmp(key, ALBUM_STR) == 0)
            start = setValue(++end, song->album);
        else if (cgc_strcmp(key, SONG_STR) == 0) {
            setValue(++end, song->song);

            return 0;
        } 
        else
            return 0;

        cgc_memset(key, 0, KEY_SIZE);
    }

    return 0;

}

int receiveBalance(int socket)
{
    char buf[1024] ={0};
    int bytes_read =0;
    int balance =0;

    bytes_read = recvline(socket, buf, sizeof(buf)-1);
    if (bytes_read < 0)
        _terminate(2);

    if (bytes_read == 0)
        return 0;

    balance = parseBalanceResult(buf);

    return balance;
}

int receiveNumResults(int socket)
{
    char buf[1024] ={0};
    int bytes_read =0;
    int num_results =0;

    bytes_read = recvline(socket, buf, sizeof(buf)-1);
    if (bytes_read < 0)
        _terminate(2);

    if (bytes_read == 0)
        return 0;

    num_results = parseResultSize(buf);
    if (num_results > 0)
        return num_results;
    
    return 0;
}

int receiveSearchResults(int socket, SongList* songList, int limit)
{
    char buf[1024] ={0};
    int ret =0;
    int bytes_read =0;
    int num_results =0;

    num_results = receiveNumResults(socket);
    while(num_results) 
    {
        bytes_read = recvline(socket, buf, sizeof(buf)-1);
        if (bytes_read < 0)
            _terminate(2);

        if (bytes_read == 0)
            return 0;

        if(songList->size < limit) {
            ret = parseSearchResult(buf, &songList->songs[songList->size]);
            if (ret != 0)
                _terminate(10);

            songList->size++;
        }

        num_results--;

    }

    return 0;
}

char * createSearchString(Request request)
{
    char* buffer =NULL;
    int ret =0;

    ret = allocate(sizeof(request)+MIN_REQ_LEN, 0, (void **) &buffer);
    if (ret != 0)
        _terminate(3);

    cgc_memset(buffer, 0, sizeof(request)+MIN_REQ_LEN);
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

unsigned int getRandomNumber(unsigned int max)
{
    size_t bytes_written =0;
    unsigned int cgc_index =0;
    int ret =0;

    ret = random(&cgc_index, sizeof(cgc_index), &bytes_written);
    if (ret != 0)
        _terminate(1);

    if (bytes_written != sizeof(cgc_index))
        _terminate(2);

    cgc_index = cgc_index % max;

    return cgc_index;
}

void getRandomAttribute(Request* request)
{
    int cgc_index =0;

    cgc_index = getRandomNumber(ATTR_NUM);
    cgc_memcpy(request->attribute, attributes[cgc_index], cgc_strlen(attributes[cgc_index]));
}

void getRandomTerm(Request* request)
{
    unsigned int size =0;
    unsigned int charset_size =0;
    int cgc_index =0;

    while(size == 0) {
        size = getRandomNumber(RESULT_VALUE_SIZE);
    }

    charset_size = cgc_strlen(charset);
    for(cgc_index = 0; cgc_index < size; cgc_index++) {
        int letter = getRandomNumber(charset_size);
        request->term[cgc_index] = charset[letter];
    }

    request->term[size] = '\0';

}

void createRandomRequest(Request *request) {

    cgc_memset(request, 0, REQUEST_SIZE);

    getRandomTerm(request);
    getRandomAttribute(request);
    cgc_memcpy(request->limit, RESULT_LIMIT_STR, sizeof(RESULT_LIMIT_STR));

}

size_t getRandomGiftCard(char** gift_card) {

    unsigned int charset_size =0;
    int cgc_index =0;
    int section =0;
    int ret =0;

    ret = allocate(GIFT_CARD_LEN+1, 0, (void **) gift_card);
    if (ret != 0)
        _terminate(3);

    cgc_memset(*gift_card, 0, GIFT_CARD_LEN);
    charset_size = cgc_strlen(charset);

    for(cgc_index = 0; cgc_index < GIFT_CARD_LEN; cgc_index++) {
        int letter = getRandomNumber(charset_size);
        (*gift_card)[cgc_index] =  charset[letter];
    }

    (*gift_card)[GIFT_CARD_LEN] = '\0';

    return GIFT_CARD_LEN+1;
}

int purchaseSong(int socket, Song* selectedSong, SongList* mySongList) {
    int ret=0;
    char price=0; 

    price = str2int(selectedSong->price);

#ifdef PATCHED
    if(price < 0) {
        ret = transmit_all(socket, INVALID_PRICE_MSG, sizeof(INVALID_PRICE_MSG)-1);
        if (ret != 0)
            _terminate(10);
        return INVALID_PRICE;
    }
#else
#endif

    if(mySongList->balance >= price) {

        mySongList->balance -= price;
        mySongList->size++;
        cgc_memcpy(&mySongList->songs[mySongList->size-1], selectedSong, RESULT_VALUE_SIZE*3);

        ret = transmit_all(socket, mySongList->songs[mySongList->size-1].id, cgc_strlen(mySongList->songs[mySongList->size-1].id));
        if (ret != 0)
            _terminate(10);
        ret = transmit_all(socket, "\n", cgc_strlen("\n"));
        if (ret != 0)
            _terminate(10);

        return SUCCESS;

    }

    return LOW_BALANCE;
}

int sendSearchString(int socket, Request request) {
    int ret =0;
    char *search_string =NULL;

    search_string = createSearchString(request);

    ret = transmit_all(socket, search_string, cgc_strlen(search_string));
    if (ret != 0)
        _terminate(4);

    return 0;
}

int getBalance(SongList* mySongList) {
    size_t size =0;
    char* gift_card =NULL;
    char *buffer =NULL;
    int ret =0;

    size = getRandomGiftCard(&gift_card);

    ret = allocate(size+sizeof("ID=")+sizeof("\n")+1, 0, (void **) &buffer);
    if (ret != 0)
        _terminate(3);

    cgc_memset(buffer, 0, size+sizeof("ID=")+sizeof("\n")+1);

    cgc_strcat(buffer,"ID=");
    cgc_strcat(buffer,gift_card);
    cgc_strcat(buffer,"\n");

    ret = deallocate(gift_card, size);
    if (ret != 0)
        _terminate(3);

    ret = transmit_all(STDOUT, buffer, cgc_strlen(buffer));
    if (ret != 0)
        _terminate(10);

    ret = deallocate(buffer, size+sizeof("ID=")+sizeof("\n")+1);
    if (ret != 0)
        _terminate(3);

    mySongList->balance = receiveBalance(STDIN);
#ifdef PATCHED
    mySongList->maxSize = mySongList->balance;
#else
#endif
    ret = allocate(sizeof(Song)*mySongList->balance, 0, (void**) &mySongList->songs);
    if (ret != 0)
        _terminate(3);

    return 0;
}

Song* selectSong(SongList results, Request request)
{
    return &results.songs[0];
}

int main(void) {
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

    getBalance(&mySongList);

    starting_balance = mySongList.balance;
#ifdef PATCHED
    while(mySongList.balance > 0 && mySongList.maxSize > mySongList.size) {
#else
    while(mySongList.balance > 0) {
#endif
        results.size = 0;

        createRandomRequest(&request);
        sendSearchString(STDOUT, request);
        receiveSearchResults(STDIN, &results, RESULT_LIMIT);

        selectedSong = selectSong(results, request);

        ret = purchaseSong(STDOUT, selectedSong, &mySongList);
        if (ret == LOW_BALANCE)
            break;

        receiveBalance(STDIN);
    }

    ret = deallocate(mySongList.songs, sizeof(Song)*starting_balance);
    if (ret != 0)
        _terminate(3);
    return ret;

}
