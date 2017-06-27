#include "libcgc.h"

#include "cgc_libc.h"
#include "cgc_lib_funcs.h"

#ifdef PIPEIT
#define PIPEFD_IN 0
#else
#define PIPEFD_IN 6
#endif

//#define DEBUG 1

enum OPCODE {ADD = 1, SUB, PUSH, EXC, MUL, SWP, POP, OUT, DIV, SHR, MOD, SHL, MOV };

//sizeof == 32
typedef struct _inst_t {
   int opcode;
   int i2;
   int opvals[2];
   int optypes[2];
   int i7;
   int i8;
} inst_t;

typedef struct _cpu_t {
   int regs[4];
   int stack[256];
   int memory[256];
   int esp;
} cpu_t;

int cgc_read_op_value(cpu_t *cpu, inst_t *inst, int opnum) {
   int result = -1;
#ifdef DEBUG
   fprintf(cgc_stderr, "read_op_value hitting illegal inst\n");
#endif
#ifdef DEBUG
   fprintf(cgc_stderr, "read_op_value resuming\n");
#endif
   if (inst->optypes[opnum] == 1) {
      result = cpu->memory[inst->opvals[opnum]];
   }
   else if (inst->optypes[opnum] == 0) {
      result = cpu->regs[inst->opvals[opnum]];
   }
   else if (inst->optypes[opnum] == 2) {
      result = inst->opvals[opnum];
   }
   return result;
}

int cgc_write_op_value(cpu_t *cpu, inst_t *inst, int opnum, int val) {
   int result = 0;
#ifdef DEBUG
   fprintf(cgc_stderr, "write_op_value hitting illegal inst\n");
#endif
#ifdef DEBUG
   fprintf(cgc_stderr, "write_op_value resuming from illegal inst\n");
#endif
   if (inst->optypes[opnum] == 1) {
      cpu->memory[inst->opvals[opnum]] = val;
   }
   else if (inst->optypes[opnum] == 0) {
      cpu->regs[inst->opvals[opnum]] = val;
   }
   else {
      result = -1;
   }
   return result;
}

int cgc_run_program(inst_t *program, int size) {
   cpu_t cpu;
   int PC;
   inst_t *current;
   int op0;
   int op1;
   int result;
   cgc_memset(&cpu, 0, sizeof(cpu));
   PC = 0;
   current = NULL;
   op0 = 0;
   op1 = 0;
#ifdef DEBUG
   fprintf(cgc_stderr, "run_program hitting illegal inst\n");
#endif
#ifdef DEBUG
   fprintf(cgc_stderr, "child 3 entering instruction loop\n");
#endif
   while (PC < size) {
      current = program + PC;
      switch (current->opcode) {
         case PUSH:
            if (cpu.esp == 255) {
               result = -23;
               goto done;
            }
            cpu.esp++;
            cpu.stack[cpu.esp] = cgc_read_op_value(&cpu, current, 0);
            break;
         case POP:
            if (cpu.esp == 0) {
               result = -23;
               goto done;
            }
            op1 = cpu.stack[cpu.esp];
            cgc_write_op_value(&cpu, current, 0, op1);
            cpu.esp--;
            break;
         case MOV:
            op1 = cgc_read_op_value(&cpu, current, 1);
            cgc_write_op_value(&cpu, current, 0, op1);
            break;
         case OUT:
            op0 = cgc_read_op_value(&cpu, current, 0);
            cgc_printf("OUT: 0x%.8x\n", op0);
#ifdef DEBUG
            fprintf(cgc_stderr, "OUT: %d (%x)\n", op0, op0);
#endif
            break;
         case ADD:
            op0 = cgc_read_op_value(&cpu, current, 0);
            op1 = cgc_read_op_value(&cpu, current, 1);
            cgc_write_op_value(&cpu, current, 0, op0 + op1);
#ifdef DEBUG
            fprintf(cgc_stderr, "add %d + %d = %d (%x)\n", op0, op1, op0 + op1, op0 + op1);
#endif
            break;
         case SUB:
            op0 = cgc_read_op_value(&cpu, current, 0);
            op1 = cgc_read_op_value(&cpu, current, 1);
            cgc_write_op_value(&cpu, current, 0, op0 - op1);
#ifdef DEBUG
            fprintf(cgc_stderr, "sub %d - %d = %d (%x)\n", op0, op1, op0 - op1, op0 - op1);
#endif
            break;
         case MUL:
            op0 = cgc_read_op_value(&cpu, current, 0);
            op1 = cgc_read_op_value(&cpu, current, 1);
            cgc_write_op_value(&cpu, current, 0, op0 * op1);
#ifdef DEBUG
            fprintf(cgc_stderr, "mul %d * %d = %d (%x)\n", op0, op1, op0 * op1, op0 * op1);
#endif
            break;
         case DIV:
            op0 = cgc_read_op_value(&cpu, current, 0);
            op1 = cgc_read_op_value(&cpu, current, 1);
            cgc_write_op_value(&cpu, current, 0, op0 / op1);
#ifdef DEBUG
            fprintf(cgc_stderr, "div %d / %d = %d (%x)\n", op0, op1, op0 / op1, op0 / op1);
#endif
            break;
         case MOD:
            op0 = cgc_read_op_value(&cpu, current, 0);
            op1 = cgc_read_op_value(&cpu, current, 1);
            cgc_write_op_value(&cpu, current, 0, op0 % op1);
#ifdef DEBUG
            fprintf(cgc_stderr, "mod %d %% %d = %d (%x)\n", op0, op1, op0 % op1, op0 % op1);
#endif
            break;
         case SHL:
            op0 = cgc_read_op_value(&cpu, current, 0);
            op1 = cgc_read_op_value(&cpu, current, 1);
            cgc_write_op_value(&cpu, current, 0, op0 << op1);
#ifdef DEBUG
            fprintf(cgc_stderr, "shl %d << %d = %d (%x)\n", op0, op1, op0 << op1, op0 << op1);
#endif
            break;
         case SHR:
            op0 = cgc_read_op_value(&cpu, current, 0);
            op1 = cgc_read_op_value(&cpu, current, 1);
            cgc_write_op_value(&cpu, current, 0, op0 >> op1);
#ifdef DEBUG
            fprintf(cgc_stderr, "shr %d >> %d = %d (%x)\n", op0, op1, op0 >> op1, op0 >> op1);
#endif
            break;
         case EXC:
            op0 = cgc_read_op_value(&cpu, current, 0);
            op1 = cgc_read_op_value(&cpu, current, 1);
            cgc_write_op_value(&cpu, current, 1, op0);
            cgc_write_op_value(&cpu, current, 0, op1);
            break;
         case SWP:
            op0 = cgc_read_op_value(&cpu, current, 0);
            cgc_write_op_value(&cpu, current, 0, cgc_htonl(op0));
#ifdef DEBUG
            fprintf(cgc_stderr, "swp %d = %d (%x)\n", op0, htonl(op0), htonl(op0));
#endif
            break;
         default:
            result = -20;
            goto done;
      }
      PC++;
   }
#ifdef DEBUG
   fprintf(cgc_stderr, "child 3 leaving instruction loop\n");
#endif
   result = 0;
done:
   return result;
}

int cgc_execute() {
   int var_C = 0;
   int rx;
   unsigned int nbytes = 0;
   int result = 0;
   inst_t program[0x200];
   int PC;

   cgc_memset(program, 0, sizeof(program));
   PC = 0;
#ifdef DEBUG
   fprintf(cgc_stderr, "execute hitting illegal inst\n");
#endif

#ifdef DEBUG
   fprintf(cgc_stderr, "child 3 entering read program loop\n");
#endif
   do {
      nbytes = cgc_read_all(PIPEFD_IN, (char*)(program + PC), sizeof(inst_t));
      if (nbytes != sizeof(inst_t) || program[PC].opcode == -1) {
         break;
      }
      if (program[PC].opcode == -2) {
          result = -1;
          goto done;
      }
#ifdef DEBUG
      fprintf(cgc_stderr, "read %d bytes from pipe 12\n", sizeof(inst_t));
#endif
   } while (++PC < 512);
#ifdef DEBUG
   fprintf(cgc_stderr, "child 3 leaving read program loop\n");
#endif
   if (nbytes != sizeof(inst_t) && nbytes != 0) {
      result = -1;
   }
   else {
      result = cgc_run_program(program, PC);
      cgc_printf("COMPLETE\n");
   }
done:
   return result;
}

int main(int cgc_argc, char *cgc_argv[]) {
   cgc__terminate(cgc_execute());
}
