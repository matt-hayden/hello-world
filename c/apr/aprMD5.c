#include <apr.h>
#include <apr_base64.h>
#include <apr_general.h>
#include <apr_md5.h>
#define APR_WANT_STDIO
#include <apr_want.h>

/* This is neccessary since there seems to be
 * no real information to gather how long the actual
 * result string will be when the encoder finishes it's
 * work.
 *
 * Using another contellation, this should not be a problem,
 * since we would of course allocate the final result memory
 * from an APR pool. Where memory is managed, and the final length
 * of the result is known. 
 *
 * During several trial and error phases I observed the result string
 * to be no longer than 37 characters. But that might change if the 
 * e.g. change the apr id, where the "custom algorithm" is detected.
 */
#define MAX_STRING_LEN 256
#define SALT_LEN 9

void randomizeSalt(char *resultSalt)
{
  apr_status_t rv;
  char salt[SALT_LEN];
  char b64Salt[apr_base64_encode_len(SALT_LEN)];

  apr_base64_encode(b64Salt, salt, SALT_LEN);
  printf("Salt array before randomization:\t%s\n", b64Salt);
  rv = apr_generate_random_bytes(salt, SALT_LEN - 1);
  salt[SALT_LEN -1] = '\0';

  apr_base64_encode(b64Salt, salt, SALT_LEN);
  printf("Salt array  after randomization:\t%s\n", b64Salt);
  /* As we do just need 8 random characters, we just 
   * copy them (remember the 9th char is set to '\0' earlier
   */
  apr_cpystrn(resultSalt, b64Salt, SALT_LEN);
  return;
}

/* Compile with 
 * $> export APR_LIBS="`apr-1-config --cflags --cppflags --includes --ldflags --link-ld --libs`"
 * $> export APU_LIBS="`apu-1-config --includes --ldflags --link-ld --libs`"
 * $> gcc aprMd5.c -o aprMd5 $APR_LIBS $APU_LIBS
 */
int main(int argc, const char * const *argv)
{

  unsigned char md5Digest[APR_MD5_DIGESTSIZE];
  const char passwordToHash[] = "This is my very secure extrme 1337 pa55w0r)";

  /* This gives us the salt, so the same password
   * will not produce the same hash, given the assumption,
   * that the salt of course changes. 
   * Using this static string is, of course not any safer 
   * then just using the standard MD5 hashing.
   *
   * This MD5 version uses an APR specific salting.
   */
  //char salt[] = "12345678";
  char salt[9];
  apr_status_t rv;

  /* Actually use the app_initialize funciton if you are
   * not writing a library.
   *
   * This function is defined in apr_general.h
   */
  apr_app_initialize(&argc, &argv, NULL);
  atexit(apr_terminate);

  randomizeSalt(salt);

  unsigned char md5DigestSalted[MAX_STRING_LEN];

  /* This actually hashes the password into a final 
   * already in ASCII printable characters encoded 
   * string
   */
  apr_md5_encode(passwordToHash,
		 salt,
		 md5DigestSalted,
		 sizeof(md5DigestSalted));

  printf("The MD5 digest salted of:\n%s\nlooks like:\n%s\n"
	 "and is %d characters long\n",
	 passwordToHash,
	 md5DigestSalted,
	 strlen(md5DigestSalted));

  /* Now see if we can validate our "normal" password against the
   * hashed version.
   */
  rv = apr_password_validate(passwordToHash, md5DigestSalted);
  printf("Testing password: %s\n", passwordToHash);
  if (rv == APR_SUCCESS) {
    printf("[SUCCESS] The supplied password validated correctly against the hash\n");
  } else {
    printf("[FAILURE] The supplied password did not validate\n");
  }

  /* Offset the original password by one character, so this should not
   * be valid anymore.
   */
  rv = apr_password_validate(&passwordToHash[1], md5DigestSalted);
  printf("Testing password: %s\n", &passwordToHash[1]);
  if (rv == APR_SUCCESS) {
    printf("[SUCCESS] The supplied password validated correctly against the hash\n");
  } else {
    printf("[FAILURE] The supplied password did not validate\n");
  }

  apr_terminate();
  return 0;
}

