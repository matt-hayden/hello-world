#include <apr.h>
#include <apr_hash.h>
#include <apr_time.h>
#define APR_WANT_STDIO
#include <apr_want.h>

struct userRecord
{
  apr_time_t creationDate; 
  char username[30];
  char password[30];
};

void print(struct userRecord *user)
{
  apr_pool_t *p = NULL;
  char *timeReadable = NULL;
  apr_pool_create(&p, NULL);
  int i = 0;

  timeReadable = apr_palloc(p, APR_RFC822_DATE_LEN);
  apr_rfc822_date(timeReadable, user->creationDate);

  printf("Username:\t\t %s\n", user->username);
  printf("Password:\t\t %s\n", user->password);
  printf("CreationDate:\t\t %s\n", timeReadable);
 
  apr_pool_destroy(p);
  return;
}

/* Compile with 
 * $> export APR_LIBS="`apr-1-config --cflags --cppflags --includes --ldflags --link-ld --libs`"
 * $> export APU_LIBS="`apu-1-config --includes --ldflags --link-ld --libs`"
 * $> gcc aprHashtable.c -o aprHashtable $APR_LIBS $APU_LIBS
 */
int main(int argc, const char* const* argv)
{
  apr_status_t rv;
  apr_pool_t *p = NULL;
  struct userRecord *cUser = NULL;
  struct userRecord *readUser = NULL;
  int i = 0;
  char countName[12];
  apr_hash_index_t *hidx = NULL;


  apr_app_initialize(&argc, &argv, NULL);
  atexit(apr_terminate);

  apr_pool_create(&p, NULL);

  apr_hash_t *ht = apr_hash_make(p);

  apr_cpystrn(countName, "Jens Frey  ", 12);

  for (i=0; i < 26; i++) {
    countName[10] = (char) i + 65;
    cUser = apr_palloc(p, sizeof(struct userRecord));
    apr_cpystrn(cUser->username, countName, strlen(countName) + 1);
    apr_cpystrn(cUser->password, "secret", strlen("secret") + 1); 
    cUser->creationDate = apr_time_now();

    apr_hash_set(ht, cUser->username, APR_HASH_KEY_STRING, cUser);

    print(cUser);
  }

  for (hidx = apr_hash_first(p, ht); hidx; hidx = apr_hash_next(hidx)) {
    apr_hash_this(hidx, NULL, NULL, (void*) &readUser);
    print(readUser);
  }

  readUser = apr_hash_get(ht, "Jens Frey G", APR_HASH_KEY_STRING);
  printf("\n\n");
  print(readUser);

  printf("Hashtable size: %d bytes\n", 
	 apr_hash_count(ht) * sizeof(struct userRecord)
	 + apr_hash_count(ht) * sizeof(readUser->username));

  apr_terminate();
  return rv;
}
