#include <apr.h>
#include <apr_file_io.h>
#include <apr_getopt.h>

/* Compile with 
 * $> export APR_LIBS="`apr-1-config --cflags --cppflags --includes --ldflags --link-ld --libs`"
 * $> export APU_LIBS="`apu-1-config --includes --ldflags --link-ld --libs`"
 * $> gcc aprGetopt.c -o aprGetopt $APR_LIBS $APU_LIBS
 */
int main(int argc, const char * const *argv)
{
  apr_pool_t *p = NULL;
  apr_getopt_t *cmdLineArgs = NULL;
  apr_status_t rv;
  char optChar;
  const char *optArg = NULL;

  /* Will hold the position for the non optional 
   * args in the APR parsed argv  
   */
  int processedOptions = 0;

  /* cleanly handle fileIO this time */
  apr_file_t *out = NULL;
  apr_file_t *err = NULL;

  /* init APR, create memory pool */
  apr_app_initialize(&argc, &argv, NULL);
  atexit(apr_terminate);
  apr_pool_create(&p, NULL);

  /* Open stdin, stderr */
  apr_file_open_stdout(&out, p);
  apr_file_open_stderr(&err, p);

  /* init APRs getopt */
  apr_getopt_init(&cmdLineArgs, p, argc, argv);

  /* If not using the getopt_long version, this
   * this is ignored
   */
  //cmdLineArgs->interleave = 1;

  /* Now step through the options given */
  while ((rv = apr_getopt(cmdLineArgs, "hc:", &optChar, &optArg)) == APR_SUCCESS) {
    switch(optChar) {
    case 'h':
      apr_file_printf(out, "Read option h ...\n");
      break;
    case 'c':
      apr_file_printf(out, "Read option c with argument %s\n", optArg);
      break;
    default:
      apr_file_printf(out, "Default reached ...\n");
    }
  }

  if (APR_STATUS_IS_BADCH(rv)) {
    apr_file_printf(err, "Read bad option ...\n");
  }

  processedOptions = cmdLineArgs->ind;
  /* Now spit out non options */
  while (processedOptions < argc) {
    apr_file_printf(out, "Non opt arg: %s\n", cmdLineArgs->argv[processedOptions++]);
  }
 

  apr_pool_destroy(p);
  return 0;
}
