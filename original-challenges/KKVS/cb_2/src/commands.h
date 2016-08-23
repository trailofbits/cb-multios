#ifndef _COMMAND_H
#define _COMMAND_H
typedef struct command_t command_t;
struct command_t
{
  unsigned arity;
  char **argv;
  char *symbol;
  enum {
    CMD_APPEND = 0xdead0001,
    CMD_AUTH   = 0xdead0002,
    CMD_BITCOUNT = 0xdead0003,
    CMD_BITOP = 0xdead0004,
    CMD_DECR = 0xdead0005,
    CMD_DEL = 0xdead0006,
    CMD_EXISTS  = 0xdead0007,
    CMD_GET = 0xdead0009,
    CMD_INCR = 0xdead000a,
    CMD_KEYS = 0xdead000b,
    CMD_RENAME = 0xdead000d,
    CMD_SET = 0xdead000e,
  } type;
};

#define NUM_CMDS 12
#define DECL_CMD(__type, __sym, __arity) \
{ \
  .arity = __arity, \
  .symbol = __sym, \
  .type = __type, \
  .argv = NULL \
}

command_t commands[NUM_CMDS] = {
    DECL_CMD(CMD_APPEND, "append", 2),
    DECL_CMD(CMD_AUTH, "auth", 1),
    DECL_CMD(CMD_BITCOUNT, "bitcount", 1),
    DECL_CMD(CMD_BITOP, "bitop", 3),
    DECL_CMD(CMD_DECR, "decr", 1),
    DECL_CMD(CMD_DEL, "del", 1),
    DECL_CMD(CMD_EXISTS, "exists", 1),
    DECL_CMD(CMD_GET, "get", 1),
    DECL_CMD(CMD_INCR, "incr", 1),
    DECL_CMD(CMD_KEYS, "keys", 0),
    DECL_CMD(CMD_RENAME, "rename", 2),
    DECL_CMD(CMD_SET, "set", 2),
};

#define MAX_COMMAND_SIZE (16 * 1024)

void free_command(command_t* cmd)
{
  if (!cmd)
    return;

  if (cmd->argv)
  {
    for (size_t i = 0; i < cmd->arity; i++)
      if (cmd->argv[i])
        free(cmd->argv[i]);
    free(cmd->argv);
  }

  free(cmd);
}

#endif /* _COMMAND _H */
