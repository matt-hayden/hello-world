
struct my_api {
	int (* print)(char * message);
	//struct my_api (* exit)(void);
};

typedef struct my_api my_api;

typedef my_api (* plugin_init_function_t)(my_api, int, char **);
