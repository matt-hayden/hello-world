#include <dlfcn.h>
#include <stdio.h>

#include "my_api.h"

#define PLUGIN_LIB_NAME "./bubble_plugin.so"
#define PLUGIN_INIT_NAME "plugin_init_function"

int
main(int argc, char * argv[])
{

	void * plugin_lib = dlopen(PLUGIN_LIB_NAME, RTLD_LAZY);
	if (plugin_lib == NULL) {
		printf("%s\n", dlerror());
		return 1;
	}

	plugin_init_function_t plugin_init_function = dlsym(plugin_lib, PLUGIN_INIT_NAME);
	if (plugin_init_function == NULL) {
		printf("Did not find %s function in %s: %s\n", PLUGIN_INIT_NAME, PLUGIN_LIB_NAME, dlerror());
		return 2;
	}

	my_api plugin_routines = plugin_init_function(plugin_routines, argc, argv);
	
	/*
	 * Main part of program
	 */
	plugin_routines.print("Hello World!");
	/*
	 * End of Hello World
	 */


	if (dlclose(plugin_lib) != 0) {
		printf("Failed to close %s\n", PLUGIN_LIB_NAME);
		return 3;
	}
	return 0;
}
