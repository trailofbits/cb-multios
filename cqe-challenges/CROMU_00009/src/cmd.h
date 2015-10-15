#define MAX_ARGS 10

typedef struct _ShellCmds {
	char *command;
	int (*handler)(void);
	char *help;
} ShellCmds;

int readUntil(char *, int , char);
int ExitHandler(void);
int MkdirHandler(void);
int RmdirHandler(void);
int LsHandler(void);
int RmHandler(void);
int EchoHandler(void);
int CatHandler(void);
int CatXHandler(void);
int HelpHandler(void);
int DfHandler(void);
int IsHex(char);
char Hex2Char(char *);
int Unescape(char *);
