/*
 * Copyright (c) 2014 Kaprica Security, Inc.
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

#include <libcgc.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "vm.h"

int read_n_bytes(int fd, size_t n, uint8_t *buf)
{
  if (!n || !buf)
    return -1;

  size_t rx = 0, total_read = 0;

  while (total_read < n) {
    if (receive(fd, buf + total_read, n - total_read, &rx) != 0) {
      return -1;
    } else if (rx == 0) {
      break;
    } else {
      total_read += rx;
    }
  }

  return total_read;
}

int read_header(int fd)
{
#define HEADER_LENGTH 4
  uint8_t header[HEADER_LENGTH] = { 0, 'M', 'V', 'i' };
  uint8_t buf[HEADER_LENGTH] = { 0, 0, 0, 0 };

  if (read_n_bytes(fd, HEADER_LENGTH, buf) != HEADER_LENGTH)
    return -1;

  return !memcmp(header, buf, HEADER_LENGTH);
}

uint32_t read_flags(int fd, int *err)
{
  uint32_t flags = 0;
  if (read_n_bytes(fd, sizeof(flags), (uint8_t *)&flags) != sizeof(flags))
    *err = 1;

  return flags;
}

state *init_state(int fd, uint32_t flags)
{
  int read_regs = flags & REG_FLAG;
  size_t read_mem_sz = flags & MEM_FLAG;

  state *new = calloc(1, sizeof(state));
  if (!new)
    goto err;

  if (read_regs)
    if (read_n_bytes(fd, sizeof(new->registers), (uint8_t *)new->registers) != sizeof(new->registers))
      goto err;

  if (read_mem_sz)
    if (read_n_bytes(fd, read_mem_sz, new->memory) != read_mem_sz)
      goto err;

  return new;

err:
  if (free) free(new);
  return NULL;
}

int dump_regs(int fd, state *machine)
{
  return transmit(fd, machine->registers, sizeof(machine->registers), NULL) == 0;
}

int process_load(state *machine, uint8_t dst, uint8_t src, uint16_t val)
{
  if (src)
    val += machine->registers[src];
  val &= 0xFFFF;
  machine->registers[dst] = machine->memory[val];
  return 0;
}

int process_str(state *machine, uint8_t dst, uint8_t src, uint16_t val)
{
  if (dst)
    val += machine->registers[dst];
  val &= 0xFFFF;
  machine->memory[val] = src == 0 ? 0 : machine->registers[src];
  return 0;
}

int frob(int fd, void *mem_start, size_t len, size_t *un2)
{
  for (size_t i = 0; i < len; i++)
    ((uint8_t *)mem_start)[i] ^= 0x42;
  return 0;
}

int process_sys(state *machine)
{
  struct {
    int fd;
    int (*fp)(int, void *, size_t, size_t *);
    char pad[0x100];
  } sv;

  if (machine->registers[1] == 0) {
    sv.fd = STDOUT;
    sv.fp = (int (*)(int, void *, size_t, size_t *))transmit;
  } else if (machine->registers[1] == 1) {
    sv.fd = STDIN;
    sv.fp = receive;
  }

  size_t start, len;
  if ((sv.fp == transmit && machine->registers[1] == 0) ||
      (sv.fp == receive && machine->registers[1] == 1)) {
    start = machine->registers[2] & 0xFFFF;
    len = machine->registers[3] & 0xFFFF;
    if (start + len > MEMORY_SIZE || len == 0)
      return 0;
  } else if (sv.fp == frob) {
    start = 0;
#ifdef PATCHED
    len = machine->registers[8] & 0xFFFF;
#else
    len = machine->registers[8];
#endif
  } else {
    return 0;
  }

  sv.fp(sv.fd, &(machine->memory[start]), len, NULL);
  return 0;
}

int process_add(state *machine, uint8_t dst, uint8_t src, int16_t val)
{
  if (src)
    machine->registers[dst] += machine->registers[src] + val;
  else
    machine->registers[dst] += val;
  return 0;
}

int process_sub(state *machine, uint8_t dst, uint8_t src, int16_t val)
{
  if (src)
    machine->registers[dst] -= machine->registers[src] + val;
  else
    machine->registers[dst] -= val;
  return 0;
}

int process_mul(state *machine, uint8_t dst, uint8_t src, int16_t val)
{
  if (src)
    machine->registers[dst] *= machine->registers[src] + val;
  else
    machine->registers[dst] *= val;
  return 0;
}

int process_div(state *machine, uint8_t dst, uint8_t src, int16_t val)
{
  if (src) {
    if (machine->registers[src] + val == 0)
      return -1;
    else
      machine->registers[dst] /= machine->registers[src] + val;
  } else {
    if (val == 0)
      return -1;
    else
      machine->registers[dst] /= val;
  }
  return 0;
}

int process_or(state *machine, uint8_t dst, uint8_t src, int16_t val)
{
  if (src)
    machine->registers[dst] |= machine->registers[src] | val;
  else
    machine->registers[dst] |= val;
  return 0;
}

int process_and(state *machine, uint8_t dst, uint8_t src, int16_t val)
{
  if (src)
    machine->registers[dst] &= machine->registers[src] | val;
  else
    machine->registers[dst] &= val;
  return 0;
}

int process_xor(state *machine, uint8_t dst, uint8_t src, int16_t val)
{
  struct {
    uint32_t old_val;
    uint32_t new_val;
    char pad[0x100];
  } sv;

  sv.old_val = machine->registers[dst];
  sv.new_val = sv.old_val ^ (src ? machine->registers[src] | val : val);
  machine->registers[dst] = sv.new_val;
  return 0;
}

int process_slt(state *machine, uint8_t dst, uint8_t src2, uint16_t src1)
{
  machine->registers[dst] = (src1 == 0 ? 0 : machine->registers[src1 & 0xF]) >
    (src2 == 0 ? 0 : machine->registers[src2]);
  return 0;
}

int process_slte(state *machine, uint8_t dst, uint8_t src2, uint16_t src1)
{
  machine->registers[dst] = (src1 == 0 ? 0 : machine->registers[src1 & 0xF]) >=
    (src2 == 0 ? 0 : machine->registers[src2]);
  return 0;
}

int handle_inst(state *machine, inst *cur)
{
  switch (cur->op) {
    case LOAD:
      return process_load(machine, DST(cur), SRC(cur), cur->val);
    case STR:
      return process_str(machine, DST(cur), SRC(cur), cur->val);
    case SYS:
      return process_sys(machine);
    case ADD:
      return process_add(machine, DST(cur), SRC(cur), cur->val);
    case SUB:
      return process_sub(machine, DST(cur), SRC(cur), cur->val);
    case MUL:
      return process_mul(machine, DST(cur), SRC(cur), cur->val);
    case DIV:
      return process_div(machine, DST(cur), SRC(cur), cur->val);
    case OR:
      return process_or(machine, DST(cur), SRC(cur), cur->val);
    case AND:
      return process_and(machine, DST(cur), SRC(cur), cur->val);
    case XOR:
      return process_xor(machine, DST(cur), SRC(cur), cur->val);
    case SLT:
      return process_slt(machine, DST(cur), SRC(cur), cur->val);
    case SLTE:
      return process_slte(machine, DST(cur), SRC(cur), cur->val);
    default:
      return -1;
  }
}

int read_inst(int fd, state *machine, inst *cur)
{
  int ret = -1;
  if (!read_n_bytes(fd, sizeof(inst), (uint8_t *)cur) == sizeof(inst))
    return -1;

  ret = handle_inst(machine, cur);
  return ret;
}

int main(void)
{
  void *x = frob;
  transmit(STDOUT, &x, sizeof(void *), NULL);
  if (!read_header(STDIN))
    return -1;

  int err = 0;
  int flags = read_flags(STDIN, &err);
  if (err)
    return -1;

  inst cur;
  state *machine = init_state(STDIN, flags);
  int ret;

  while (1) {
    if (read_inst(STDIN, machine, &cur) < 0)
      break;

    if (!dump_regs(STDOUT, machine))
      break;
  }

  transmit(STDOUT, "DONE", 5, NULL);
}
