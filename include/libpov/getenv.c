
#include <libcgc.h>
#include <pov/stdlib.h>
#include <pov/string.h>

typedef struct _entry {
   char *name;
   unsigned char *val;
   size_t val_len;
} entry;

static size_t env_size = 0;
static size_t env_cap = 0;
static entry **env = NULL;

static void *memdup(const unsigned char *buf, size_t len) {
   unsigned char *res = (unsigned char *)malloc(len);
   memcpy(res, buf, len);
   return res;
}

int putenv(const char *name, const unsigned char *val, size_t val_len) {
   size_t i;

   if (name == NULL || val == NULL) {
      return -1;
   }

   for (i = 0; i < env_size; i++) {
      if (strcmp(name, env[i]->name) == 0) {
         free(env[i]->val);
         env[i]->val = memdup(val, val_len);
         env[i]->val_len = val_len;
         return 0;
      }
   }
   if (env_size == env_cap) {
      entry **e = realloc(env, (env_cap + 1) * sizeof(char*));
      if (e == NULL) {
         return -1;
      }
      env = e;
      env_cap++;
   }
   env_size++;
   env[i] = (entry*)malloc(sizeof(entry));
   env[i]->name = memdup((const unsigned char*)name, strlen(name) + 1);
   env[i]->val = memdup(val, val_len);
   env[i]->val_len = val_len;
   return 0;
}

unsigned char *getenv(const char *name, size_t *len) {
   size_t i;
   for (i = 0; i < env_size; i++) {
      if (strcmp(name, env[i]->name) == 0) {
         *len = env[i]->val_len;
         return (unsigned char *)memdup(env[i]->val, env[i]->val_len);
      }
   }
   return NULL;
}
