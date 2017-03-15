/*
 * https://sqlite.org/quickstart.html
 */
#include <stdio.h>
#include <stdlib.h>

#include <sqlite3.h>

enum { QUERY_MAX_SIZE = 1024*1024 };

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  for(i=0; i<argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

int run_file(sqlite3 *db, char *filename) {
  char query_text[QUERY_MAX_SIZE];
  FILE *fp_in = fopen(filename, "r");
  char *zErrMsg = 0;
  int rc;

  if (!fp_in) {
    perror("Error opening");
    rc = 1;
    goto cleanup;
  }
  size_t rl = fread(query_text, sizeof *query_text, QUERY_MAX_SIZE, fp_in);
  if (sqlite3_exec(db, query_text, callback, 0, &zErrMsg) != SQLITE_OK) {
    perror("SQL error");
    fprintf(stderr, "%s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
cleanup:
  return rc;
}


int main(int argc, char **argv){
  sqlite3 *db;
  int rc;
  rc = sqlite3_open(argv[1], &db);
  if (rc) {
    perror("Can't open database");
    fprintf(stderr, "%s\n", sqlite3_errmsg(db));
    goto cleanup;
  }
  rc = run_file(db, argv[2]);
  goto cleanup;
cleanup:
  sqlite3_close(db);
  return rc;
}
