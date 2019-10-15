/*
 * Copyright (c) 2015 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#include "libcgc.h"

#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_commands.h"
#include "cgc_io.h"

int cgc_parse_args(char* args, cgc_size_t len, char** argv, cgc_size_t max_args)
{
  int in_double_quote_flag = 0;
  int in_escape_flag = 0;
  int arg_num = 0;

  for (cgc_size_t i = 0; i < len; i++)
  {
    if (args[i] == '\\')
    {
      in_escape_flag = 1;
    }
    else if (args[i] == '"' && !in_escape_flag)
    {
      in_double_quote_flag = !in_double_quote_flag;
      args[i] = '\0';
    }
    else if (args[i] == ' ' && !in_double_quote_flag)
    {
      args[i] = '\0';
    }
    else if (args[i] == '"' && in_escape_flag)
    {
      in_escape_flag = 0;
    }
  }

  if (in_escape_flag || in_double_quote_flag)
    return -1;

  for (cgc_size_t i = 0; i < len && arg_num < max_args;)
  {
    if (args[i] != '\0') {
      argv[arg_num++] = &args[i];
      i += cgc_strlen(&args[i]);
    }
    else
    {
      i++;
    }
  }

  return arg_num;
}

#define MAX_ARGS 10
command_t* cgc_parse_command(char* line)
{
  char** argv = cgc_calloc(sizeof(char*), MAX_ARGS);
  command_t* cmd = cgc_calloc(sizeof(command_t), 1);
  if (!cmd || !argv)
    err("bad calloc");

  int num_args = cgc_parse_args(line, cgc_strlen(line), argv, MAX_ARGS);

  if (num_args < 0)
    goto error;

  for (cgc_size_t i = 0; i < NUM_CMDS; i++)
  {
    if (argv[0] && cgc_strcasecmp(commands[i].symbol, argv[0]) == 0 &&
        num_args - 1 == commands[i].arity)
    {
      cgc_memcpy(cmd, &commands[i], sizeof(command_t));
      cmd->argv = argv + 1;
      goto done;
    }
  }

error:
  if (argv)
    cgc_free(argv);
  if (cmd)
    cgc_free(cmd);
  return NULL;
done:
  for (cgc_size_t i = 0; i < cmd->arity; i ++)
    if (cgc_strlen(cmd->argv[i]) > 512)
      goto error;

  return cmd;
}

int cgc_serialize_command(command_t* command, unsigned char** serialized)
{
  cgc_size_t size = sizeof(int) * 2;
  for (cgc_size_t i = 0; command->argv[i]; i++)
  {
    size += cgc_strlen(command->argv[i]) + 1;
  }

  *serialized = cgc_calloc(sizeof(unsigned char), size);
  if (!*serialized)
    err("bad calloc");

  unsigned char* cur = *serialized;

  cgc_memcpy(cur, (void *)&command->type, sizeof(command->type));
  cur += sizeof(command->type);

  cgc_memcpy(cur, (void *)&command->arity, sizeof(command->arity));
  cur += sizeof(command->arity);

  for (cgc_size_t i = 0; i < command->arity; i++)
  {
    cgc_strcpy((char *)cur, command->argv[i]);
    cur += cgc_strlen((char *)cur) + 1;
  }

  return size;
}

int main(int cgc_argc, char *cgc_argv[])
{
#define LINE_SIZE (8 * 1024)

  int rx = SERVER_TO_CLIENT_OUT;
  int tx = CLIENT_TO_SERVER_IN;

  char line[LINE_SIZE];
  char resp[LINE_SIZE];
  int failed_cnt = 0;

  for (;;)
  {
    cgc_memset(line, 0, LINE_SIZE);
    cgc_transmit_string(STDOUT, "hackdis> ");
    if (cgc_read_until(STDIN, LINE_SIZE, '\n', line) < 0)
    {
      if (++failed_cnt > 10)
        cgc_exit(0);
      if (cgc_transmit_string(STDOUT, "\n") != 0)
        err("send failed");
      continue;
    }
    failed_cnt = 0;
    dbg("read line: %s", line);

    if (cgc_strncmp("quit", line, cgc_strlen("quit")) == 0)
    {
      cgc_send_n_bytes(tx, 4, "quit");
      if (cgc_transmit_string(STDOUT, "bye\n") != 0)
        err("send failed");
      cgc_exit(0);
    }

    command_t* command = cgc_parse_command(line);
    if (!command)
      continue;

    unsigned char *serialized_command;
    int ssize;
    if ((ssize = cgc_serialize_command(command, &serialized_command)) < 0)
      continue;

    dbg("sending command of type: %x", command->type);
    cgc_send_n_bytes(tx, sizeof(ssize), (char* )&ssize);
    cgc_send_n_bytes(tx, ssize, (char *)serialized_command);
    dbg("done sending");
    cgc_memset(resp, 0, LINE_SIZE);
    if (cgc_read_until(rx, LINE_SIZE, '\n', resp) < 0)
    {
      dbg("bad response");
      continue;
    }

    dbg("got response: %s", resp);
    if (cgc_transmit_string(STDOUT, resp) != 0)
      err("send failed");
    if (cgc_transmit_string(STDOUT, "\n") != 0)
      err("send failed");

    cgc_free(command);
    cgc_free(cgc_serialize_command);
  }

  return 0;
}
