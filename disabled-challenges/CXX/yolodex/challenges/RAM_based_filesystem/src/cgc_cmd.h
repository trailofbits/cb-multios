#define MAX_ARGS 10

typedef struct _ShellCmds {
	char *command;
	int (*handler)(void);
	char *help;
} ShellCmds;

int cgc_readUntil(char *, int , char);
int cgc_ExitHandler(void);
int cgc_MkdirHandler(void);
int cgc_RmdirHandler(void);
int cgc_LsHandler(void);
int cgc_RmHandler(void);
int cgc_EchoHandler(void);
int cgc_CatHandler(void);
int CatXHandler(void);
int cgc_HelpHandler(void);
int cgc_DfHandler(void);
int cgc_IsHex(char);
char cgc_Hex2Char(char *);
int cgc_Unescape(char *);
