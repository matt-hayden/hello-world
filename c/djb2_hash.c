
static
unsigned int djbh_text_hash(char const *str) {
unsigned int hash = 5381;
	char c;
	while ((c = *str++)) hash += hash<<5 + c;
return hash;
}

static
unsigned int djbh_list_hash(void const **in) {
unsigned int hash = 5381;
	void *c;
	while ((c = *in++)) hash += hash<<5 + (uintptr_t)c;
return hash;
}
