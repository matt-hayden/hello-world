#include <apr.h>
#include <apr_general.h>
#include <apr_pools.h>
#include <stdlib.h>
#include <stdio.h>
#include <apr_strings.h>
#include <apr_time.h>

/* Compile this beast with 
 * $> export APR_LIBS="`apr-1-config --cflags --cppflags --includes --ldflags --link-ld --libs`"
 * $> gcc simple_apr.c -o simple_apr $APR_LIBS
 */
typedef struct user
{
  apr_time_t *creationDate;
  char *username;
  char *password;
} user;

int main(int argc, char **argv)
{

  apr_pool_t *pool = NULL;
  user *user = NULL;
  char *time = NULL;

  /* Initialize APR at the program start */
  apr_initialize(&argc, &argv, NULL);

  /* atexit(apr_terminate()); gives 
   * error: invalid use of void expression 
   */
  atexit(apr_terminate);

  /* create a managed memory pool with APR */
  apr_pool_create(&pool, NULL);

  /* Init the struct */
  user = apr_palloc(pool, sizeof(struct user));

  /* Assign strings via the pool */
  user->username = apr_pstrdup(pool, "Jens Frey");
  user->password = apr_pstrdup(pool, "secret");

  /* Assign binary mem */
  apr_time_t now = apr_time_now();
  user->creationDate = apr_pmemdup(pool, &now, sizeof(apr_time_t));

  printf("Username: %s\n", user->username);
  printf("Password: %s\n", user->password);
  printf("Time: %" APR_TIME_T_FMT "\n", *user->creationDate);

  time = apr_palloc(pool, APR_RFC822_DATE_LEN);
  apr_rfc822_date(time, *user->creationDate);
  printf("Time readable: %s\n", time);

  apr_pool_destroy(pool);

  return 0;
}

