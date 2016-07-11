#define RESULT_VALUE_SIZE 50
#define TERM_SIZE 50
#define ARTIST_STR "artist"
#define ALBUM_STR "album"
#define SONG_STR "song"
#define KEYVAL_DELIM "="
#define PARAM_DELIM "&"
#define TERM_STR "term"
#define ENTITY_STR "entity"
#define ATTRIBUTE_STR "attribute"
#define LIMIT_STR "limit"
#define MAX_LIMIT 4
#define EOL_STR "\n"
#define ATTR_NUM 3
#define BAL_STR "BALANCE"
#define GIFT_CARD_LEN 32
#define NUM_STR "NUMBER"
#define RESULT_LIMIT 10
#define RESULT_LIMIT_STR "10"
#define KEY_SIZE 20
#define SONG_ID_STR "sid"
#define PRICE_STR "price"
#define MAX_PRICE 2
#define SUCCESS 0
#define LOW_BALANCE 1
#define INVALID_PRICE 2
#define SONG_SIZE RESULT_VALUE_SIZE*5
#define REQUEST_SIZE RESULT_VALUE_SIZE*2 + MAX_LIMIT
#define INVALID_PRICE_MSG "Invalid Price\n"

const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char *attributes[] = {"artistTerm", "albumTerm", "songTerm"};

const unsigned int MIN_REQ_LEN = sizeof(TERM_STR) 
								+ sizeof(ATTRIBUTE_STR)
								+ sizeof(LIMIT_STR)
								+ sizeof(KEYVAL_DELIM)*3
								+ sizeof(PARAM_DELIM)*2
								+ sizeof(EOL_STR);

typedef struct Request {
	char term[RESULT_VALUE_SIZE];
	char attribute[RESULT_VALUE_SIZE];
	char limit[MAX_LIMIT];
} Request;

typedef struct Song {
	char id[RESULT_VALUE_SIZE];
	char artist[RESULT_VALUE_SIZE];
	char album[RESULT_VALUE_SIZE];
	char song[RESULT_VALUE_SIZE];
	char price[RESULT_VALUE_SIZE];
} Song;

typedef struct SongList {
	unsigned int size;
#ifdef PATCHED
	unsigned int maxSize;
#else
#endif
	Song* songs;
	unsigned char balance;
} SongList;