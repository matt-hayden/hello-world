#include <stdlib.h>
#include <stdio.h>

#include <apr.h>
#include <apr_pools.h>
#include <apr_random.h>

/* Compile this beast with 
 * $> export APR_LIBS="`apr-1-config --cflags --cppflags --includes --ldflags --link-ld --libs`"
 * $> gcc simple_apr.c -o simple_apr $APR_LIBS
 */

int main(int argc, char * argv[])
{
	apr_pool_t *pool = NULL;
	apr_random_t *prng_state = NULL;

	/* Initialize APR at the program start */
	apr_app_initialize(&argc, &argv, NULL);
	atexit(apr_terminate);

	/* create a managed memory pool with APR */
	apr_pool_create(&pool, NULL);
	prng_state = apr_random_standard_new(pool);
	if (!prng_state)
		printf("apr_random_standard_new failed\n");

	unsigned char * buffer;
	buffer = apr_palloc(pool, 8);

	if (apr_random_secure_ready(prng_state) == APR_SUCCESS) {
		if (apr_random_secure_bytes(prng_state, buffer, 8) == APR_SUCCESS) {
			printf("apr_random_secure_bytes:\n");
			for (int i = 0; i<8; i++)
				printf("%x ", buffer[i]);
			printf("\n");
		}
	} else {
		printf("Not enough entropy for apr_random_secure_ready\n");
	}

	if (apr_random_insecure_ready(prng_state) == APR_SUCCESS) {
		if (apr_random_insecure_bytes(prng_state, buffer, 8) == APR_SUCCESS) {
			printf("apr_random_insecure_bytes:\n");
			for (int i = 0; i<8; i++)
				printf("%x ", buffer[i]);
			printf("\n");
		}
	} else {
		printf("Not enough entropy for apr_random_insecure_ready\n");
	}

	if (apr_generate_random_bytes(buffer, 8) == APR_SUCCESS) {
		printf("apr_generate_random_bytes:\n");
		for (size_t i = 0; i<8; i++)
			printf("%02x ", buffer[i]);
		printf("\n");
	}
	
	apr_pool_destroy(pool);
}
