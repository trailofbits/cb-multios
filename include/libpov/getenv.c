
#include <libcgc.h>
#include <pov/cgc_stdlib.h>
#include <pov/cgc_string.h>

typedef struct _entry {
   char *name;
   unsigned char *val;
   cgc_size_t val_len;
} entry;

static cgc_size_t env_size = 0;
static cgc_size_t env_cap = 0;
static entry **env = NULL;

static void *cgc_memdup(const unsigned char *buf, cgc_size_t len) {
   unsigned char *res = (unsigned char *)cgc_malloc(len);
   cgc_memcpy(res, buf, len);
   return res;
}

int cgc_putenv(const char *name, const unsigned char *val, cgc_size_t val_len) {
   cgc_size_t i;

   if (name == NULL || val == NULL) {
      return -1;
   }

   for (i = 0; i < env_size; i++) {
      if (cgc_strcmp(name, env[i]->name) == 0) {
         cgc_free(env[i]->val);
         env[i]->val = cgc_memdup(val, val_len);
         env[i]->val_len = val_len;
         return 0;
      }
   }
   if (env_size == env_cap) {
      entry **e = cgc_realloc(env, (env_cap + 1) * sizeof(char*));
      if (e == NULL) {
         return -1;
      }
      env = e;
      env_cap++;
   }
   env_size++;
   env[i] = (entry*)cgc_malloc(sizeof(entry));
   env[i]->name = cgc_memdup((const unsigned char*)name, cgc_strlen(name) + 1);
   env[i]->val = cgc_memdup(val, val_len);
   env[i]->val_len = val_len;
   return 0;
}

unsigned char *cgc_getenv(const char *name, cgc_size_t *len) {
   cgc_size_t i;
   for (i = 0; i < env_size; i++) {
      if (cgc_strcmp(name, env[i]->name) == 0) {
         *len = env[i]->val_len;
         return (unsigned char *)cgc_memdup(env[i]->val, env[i]->val_len);
      }
   }
   return NULL;
}
