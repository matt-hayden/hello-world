#include <apr.h>
#include <apu.h>
#include <apr_dbm.h>
#include <apr_time.h>
#include <apr_strings.h>
#define APR_WANT_STDIO
#define APR_WANT_MEMFUNC
#include <apr_want.h>


#define DBM_TYPE "SDBM"
#define DEBUG 
#ifdef DEBUG
#define PDEBUG(message, arguments) printf("[DEBUG] " message "\n", arguments)
#define PDEBUG_NA(message) printf("[DEBUG] " message "\n")
#else
#define PDEBUG(message, arguments) /* empty */
#define PDEBUG_NA(message) /* empty */
#endif

/* Compile with 
 * $> export APR_LIBS="`apr-1-config --cflags --cppflags --includes --ldflags --link-ld --libs`"
 * $> export APU_LIBS="`apu-1-config --includes --ldflags --link-ld --libs`"
 * $> gcc aprWithSdbm.c -o aprWithSdbm $APR_LIBS $APU_LIBS
 */

struct userRecord 
{
  apr_time_t creationDate;
  char *username;
  char *password;
};

void print(struct userRecord *user);
/* since apr_datum_t* results in a nested structure
 * this allocates the memory on the nested 
 * char* onto the given pool.
 */
apr_datum_t* string2datum(apr_pool_t *p, 
			  char *toDatum);
apr_datum_t* time2datum(apr_pool_t *p, 
			apr_time_t *toDatum);

apr_status_t persistDatum(unsigned int *key, 
			  apr_dbm_t *database, 
			  apr_datum_t *toDump);

apr_status_t persistUserRecord(unsigned int *key, 
			       apr_dbm_t *database, 
			       struct userRecord *user);

void persistUserRecords(apr_table_t *userRecords);
struct userRecord *readUserRecord(apr_pool_t *resultPool, 
				  apr_dbm_t *db, 
				  apr_datum_t *lastReadKey);
apr_table_t *readUserRecords(apr_pool_t *resultPool);
void checkError(apr_status_t rv);


int main(int argc, char **argv)
{
  
  struct userRecord *user, *user2 = NULL;
  struct userRecord *userReadBack, *userReadBack2 = NULL;
  apr_pool_t *mainPool = NULL;
  apr_dbm_t *db;
  unsigned int counter = 0;
  apr_datum_t readKey;
  apr_status_t rv;


  /* Always init at program start */
  apr_app_initialize(&argc, &argv, NULL);

  /* Register cleanup */
  atexit(apr_terminate);

  /* create our main memory pool,
   * which will be valid during the programs lifetime
   */
  apr_pool_create(&mainPool, NULL);

  /* Allocate memory for a user on the main pool */
  user = apr_palloc(mainPool, sizeof(struct userRecord));
  
  user->username = apr_pstrdup(mainPool, "Jens Frey");
  user->password = apr_pstrdup(mainPool, "secret");
  user->creationDate = apr_time_now();

  user2 = apr_palloc(mainPool, sizeof(struct userRecord));
  
  user2->username = apr_pstrdup(mainPool, "Master Frey");
  user2->password = apr_pstrdup(mainPool, "more secret password");
  user2->creationDate = apr_time_now();

  print(user);
  print(user2);
  apr_dbm_open_ex(&db, DBM_TYPE, "/tmp/testDatabase", APR_DBM_RWTRUNC, 
	       APR_FPROT_OS_DEFAULT, mainPool);
  
  PDEBUG("Counter value: %u", counter);
  persistUserRecord(&counter, db, user);
  persistUserRecord(&counter, db, user2);
  PDEBUG("Counter value: %u", counter);

  //Query the first Key, the rest are subsequently queried alone
  rv =  apr_dbm_firstkey(db, &readKey);
  checkError(rv);
  userReadBack = readUserRecord(mainPool, db, &readKey);
  userReadBack2 = readUserRecord(mainPool, db, &readKey);

  print(userReadBack);
  print(userReadBack2);

  apr_dbm_close(db);
  apr_pool_destroy(mainPool);
  return 0;
}

void checkError(apr_status_t rv)
{
  if (rv != APR_SUCCESS) {
    printf("An error happened while operating with the database (code %d)\n", rv);
  }
}

struct userRecord *readUserRecord(apr_pool_t *p, apr_dbm_t *db, apr_datum_t *lastReadKey)
{
  apr_datum_t tmp;
  apr_status_t rv;

  struct userRecord *user = apr_palloc(p, sizeof(struct userRecord));
  
  PDEBUG_NA("enter readUserRecord()");

  /* Read username */
  rv = apr_dbm_fetch(db, *lastReadKey, &tmp);
  checkError(rv);
  user->username = apr_pstrndup(p, tmp.dptr, tmp.dsize);

  /* Advance to next key and read password */
  rv = apr_dbm_nextkey(db, lastReadKey);
  checkError(rv);
  rv = apr_dbm_fetch(db, *lastReadKey, &tmp);
  checkError(rv);
  user->password = apr_pstrndup(p, tmp.dptr, tmp.dsize);
  
  /* Timestamp */
  rv = apr_dbm_nextkey(db, lastReadKey);
  checkError(rv);
  rv = apr_dbm_fetch(db, *lastReadKey, &tmp);
  checkError(rv);
  /* Memcpy that, that part of the structure is already alloced */
  memcpy(&user->creationDate, tmp.dptr, sizeof(apr_time_t));


  /* Set the key to the next element, so a subsequent call will
     be correct again
  */
  rv = apr_dbm_nextkey(db, lastReadKey);
  checkError(rv);

  PDEBUG_NA("leave readUserRecord()");
  return user;
}

/* Converts an apr_time_t into a
 * persistable apr_datum_t
 */
apr_datum_t* time2datum(apr_pool_t *p, apr_time_t *toDatum)
{
  apr_size_t size = 0;
  apr_datum_t *dt = apr_palloc(p, sizeof(apr_datum_t));
  
  size = sizeof(apr_time_t);
  dt->dptr = apr_pmemdup(p, toDatum, size);
  dt->dsize = size;

  return dt;
}

/* 
 * Converts the given char* into a apr_datum_t with lengths set correctly
 * depending on the database type. The memory required for the string
 * to be held is saved in the given memory pool.
 *
 */
apr_datum_t* string2datum(apr_pool_t *p, char *toDatum)
{
  apr_datum_t *dt = apr_palloc(p, sizeof(apr_datum_t));

  dt->dptr = apr_pstrdup(p, toDatum);

#ifndef NETSCAPE_DBM_COMPAT
  dt->dsize = strlen(dt->dptr);
#else
  dt->dsize = strlen(dt->dptr) + 1;
#endif

    return dt;
}


/* This function persists the whole struct userRecord
 * into the SDBM database. You have to check if this implementation
 * is still correct if you change your struct.
 *
 * There should however be no problem if you are just adding transient
 * parameters that should not be persisted at all.
 */
apr_status_t persistUserRecord(unsigned int *key, apr_dbm_t *database, struct userRecord *user)
{
  apr_status_t rv;
  apr_datum_t *dumpKey;
  apr_pool_t *p;
  PDEBUG_NA("enter persistUserRecord()");

  apr_pool_create(&p, NULL);

  /* Now fill in every field of the record */
  dumpKey = string2datum(p, user->username);
  persistDatum(key, database, dumpKey);
  
  dumpKey = string2datum(p, user->password);
  persistDatum(key, database, dumpKey);

  dumpKey = time2datum(p, &user->creationDate);
  persistDatum(key, database, dumpKey);
  
  apr_pool_destroy(p);
  PDEBUG_NA("leave persistUserRecord()");
  return rv;
}


/*
  Assumes an open database.
 */
apr_status_t persistDatum(unsigned int *key, apr_dbm_t *database, apr_datum_t *toDump)
{
  apr_status_t rv;
  apr_datum_t datumKey;
  datumKey.dptr = (char *) key;
  datumKey.dsize = sizeof(unsigned int);
  


  PDEBUG_NA("enter persistDatum()");
  rv = apr_dbm_store(database, datumKey, *toDump);
  if (rv != APR_SUCCESS) {
    printf("Error saving datum in database (returned %d)", rv);
  }
  
  //Increment count for every written datum
  (*key)++;
  PDEBUG("Key is %u", *key);
  PDEBUG_NA("leave persistDatum()");
  return rv;
}

void print(struct userRecord *user)
{
  apr_pool_t *p = NULL;
  char *timeReadable = NULL;
  apr_pool_create(&p, NULL);

  timeReadable = apr_palloc(p, APR_RFC822_DATE_LEN);
  apr_rfc822_date(timeReadable, user->creationDate);

  PDEBUG("Username: %s", user->username);
  PDEBUG("Password: %s", user->password);
  PDEBUG("CreationDate (long): %" APR_TIME_T_FMT, user->creationDate);
  PDEBUG("CreationDate (read): %s", timeReadable);
  
  apr_pool_destroy(p);
}
