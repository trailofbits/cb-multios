#include "libcgc.h"

#include "cgc_libc.h"
#include "cgc_lib_funcs.h"

#ifdef PIPEIT
#define PIPEFD_IN 0
#define PIPEFD_OUT 1
#else
#define PIPEFD_IN 4
#define PIPEFD_OUT 5
#endif

typedef struct _asm_t {
   int opcode;
   const char *mnem;
   int i2;
   int i3;
} asm_t;

enum OPCODE {ADD = 1, SUB, PUSH, EXC, MUL, SWP, POP, OUT, DIV, SHR, MOD, SHL, MOV };

asm_t iset[] = {
   {PUSH, "push", 3, 0},
   {POP, "pop", 1, 0},
   {MOV, "mov", 1, 3},
   {ADD, "add", 1, 3},
   {SUB, "sub", 1, 3},
   {MUL, "mul", 1, 3},
   {DIV, "div", 1, 3},
   {OUT, "out", 3, 0},
   {MOD, "mod", 1, 3},
   {SHL, "shl", 1, 3},
   {SHR, "shr", 1, 3},
   {EXC, "exc", 1, 1},
   {SWP, "swp", 1, 0},
   {0, NULL, 0, 0}
};

//sizeof == 32
typedef struct _inst_t {
   int opcode;
   int i2;
   int opvals[2];
   int optypes[2];
   int i7;
   int i8;
} inst_t;

int cgc_parse_op(char *opstr, inst_t *inst, int opnum) {
   int result;
#ifdef DEBUG
   fprintf(cgc_stderr, "parse_op hitting illegal inst\n");
#endif
#ifdef DEBUG
   fprintf(cgc_stderr, "child %d parsing op '%s'\n", child_num, opstr);
#endif
   if (*opstr == 'r') {
      inst->optypes[opnum] = 0;
      errno = 0;
      inst->opvals[opnum] = cgc_strtol(opstr + 1, NULL, 0);
      if (errno) {
#ifdef DEBUG
         fprintf(cgc_stderr, "strtol error  in reg parsing\n");
#endif
         result = -22;
         goto done;
      }
#ifdef PATCHED
      if (inst->opvals[opnum] < 0 || inst->opvals[opnum] > 3) {
#else
      if (inst->opvals[opnum] > 3) {
#endif
#ifdef DEBUG
         fprintf(cgc_stderr, "reg out of bounds\n");
#endif
         result = -22;
         goto done;
      }
#ifdef DEBUG
      fprintf(cgc_stderr, "regsister %d selected\n", inst->opvals[opnum]);
#endif
   }
   else if (*opstr == 'm') {
      inst->optypes[opnum] = 1;
      errno = 0;
      inst->opvals[opnum] = cgc_strtol(opstr + 1, NULL, 0);
      if (errno) {
#ifdef DEBUG
         fprintf(cgc_stderr, "strtol error  in mem parsing\n");
#endif
         result = -22;
         goto done;
      }
      if (inst->opvals[opnum] > 255 || inst->opvals[opnum] < 0) {
#ifdef DEBUG
         fprintf(cgc_stderr, "mem out of bounds\n");
#endif
         result = -22;
         goto done;
      }
#ifdef DEBUG
      fprintf(cgc_stderr, "memory %d selected\n", inst->opvals[opnum]);
#endif
   }
   else {
      inst->optypes[opnum] = 2;
      errno = 0;
      inst->opvals[opnum] = cgc_strtol(opstr, NULL, 0);
      if (errno) {
#ifdef DEBUG
         fprintf(cgc_stderr, "strtol error  in imm parsing\n");
#endif
         result = -22;
         goto done;
      }
#ifdef DEBUG
      fprintf(cgc_stderr, "immediate %d selected\n", inst->opvals[opnum]);
#endif
   }
   result = 0;
done:
   return result;
}

int cgc_parse_inst(char *inbuf, inst_t *inst) {
   int count = 0;
   char *part1 = 0;
   char *part2 = 0;
   char *part3 = 0;
   int result;
#ifdef DEBUG
   fprintf(cgc_stderr, "parse_inst hitting illegal inst\n");
#endif
   part1 = cgc_strsep(&inbuf, " ");
   part2 = cgc_strsep(&inbuf, ",");
   part3 = cgc_strsep(&inbuf, ",");
#ifdef DEBUG
   fprintf(cgc_stderr, "child %d %s | %s | %s\n", child_num, part1, part2, part3);
#endif
   for (count = 0; iset[count].mnem; count++) {
      if (cgc_strcmp(iset[count].mnem, part1) == 0) {
         inst->opcode = iset[count].opcode;
         break;
      }
   }
   if (inst->opcode == 0) {
#ifdef DEBUG
      fprintf(cgc_stderr, "failed opcode lookup\n");
#endif
      result = -20;
      goto done;
   }
   if (part2) {
      if (iset[count].i2 == 0) {
#ifdef DEBUG
         fprintf(cgc_stderr, "opcode missing i2\n");
#endif
         return -22;
         goto done;
      }
      if (cgc_parse_op(part2, inst, 0)) {
#ifdef DEBUG
         fprintf(cgc_stderr, "parse_op(1) failed\n");
#endif
         return -22;
         goto done;
      }
      if (iset[count].i2 == 0 && (inst->optypes[0] & 1)) {
#ifdef DEBUG
         fprintf(cgc_stderr, "opcode bad optype(1)\n");
#endif
         return -22;
         goto done;
      }
   }
   if (part3) {
      if (iset[count].i3 == 0) {
#ifdef DEBUG
         fprintf(cgc_stderr, "opcode missing i3\n");
#endif
         return -22;
         goto done;
      }
      if (cgc_parse_op(part3, inst, 1)) {
#ifdef DEBUG
         fprintf(cgc_stderr, "parse_op(2) failed\n");
#endif
         return -22;
         goto done;
      }
      if (iset[count].i3 == 0 && (inst->optypes[1] & 1)) {
#ifdef DEBUG
         fprintf(cgc_stderr, "opcode bad optype(2)\n");
#endif
         return -22;
         goto done;
      }
   }
   result = 0;
done:
   return result;
}

int cgc_parse_instructions() {
   int i1 = 0;
   int i2 = 0;
   cgc_size_t tlen;
   char buf[256];
   inst_t inst;
   int result;
   cgc_memset(buf, 0, sizeof(buf));
   cgc_memset(&inst, 0, sizeof(inst));
#ifdef DEBUG
   fprintf(cgc_stderr, "parse_instructions hitting illegal inst\n");
#endif

#ifdef DEBUG
   fprintf(cgc_stderr, "child 2 resuming in parse_instructions\n");
#endif
   while ((i1 = cgc_read_until_delim(PIPEFD_IN, buf, 255, '\n')) > 0) {
#ifdef DEBUG
      fprintf(cgc_stderr, "read %d bytes from pipe 01\n", i1);
#endif
      buf[i1] = 0;
      if (cgc_memcmp(buf, "END", 3) == 0) {
         cgc_memset(&inst, 0xff, sizeof(inst));
         //make the effort to cgc_write all, but we are quitting anyway so nothing
         //we can do it this comes back short
         cgc_write_all(PIPEFD_OUT, (void *) &inst, sizeof(inst));
         break;
      }
      if (cgc_parse_inst(buf, &inst)) {
         cgc_printf("ERROR: Invalid Instruction Source (%s)\n", buf);
         result = -1;
         goto done;
      }
      if (cgc_write_all(PIPEFD_OUT, (void *) &inst, sizeof(inst)) != sizeof(inst)) {
         cgc_printf("ERROR: transmit to runner failed!\n");
         result = -1;
         goto done;
      }
#ifdef DEBUG
      fprintf(cgc_stderr, "wrote %d bytes to pipe 12\n", sizeof(inst));
#endif
      cgc_memset(buf, 0, sizeof(buf));
   }
#ifdef DEBUG
   fprintf(cgc_stderr, "child 2 done in parse_instructions\n");
#endif
   result = 0;
done:
   if (result == -1) {
      cgc_memset(&inst, 0xff, sizeof(inst));
      inst.opcode = -2;
      //make the effort to cgc_write all, but we are quitting anyway
      //so nothing we can do if this is short
      cgc_write_all(PIPEFD_OUT, (void *) &inst, sizeof(inst)); 
   }
   return result;
}

int main(int cgc_argc, char *cgc_argv[]) {
   cgc__terminate(cgc_parse_instructions());
}
