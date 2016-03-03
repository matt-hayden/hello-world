#include <stdio.h>

#include "my_api.h"

int
excited_print(char * message)
{
	printf("***%s***\n", message);
	return 1;
}

my_api
plugin_init_function(my_api incoming, int argc, char * argv[])
{
my_api outgoing = incoming;

	printf("Initializing plugin 'excited_plugin.so'\n");
	outgoing.print = excited_print;
	return outgoing;
}
