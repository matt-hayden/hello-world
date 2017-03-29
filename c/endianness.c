#include <stdint.h>
#include <stdio.h>

uint32_t change_endianness(uint32_t value)
{
    /*
    union {
        uint32_t i;
        char cs[sizeof(uint32_t)];
    } in, out;
    in = value;
    out.cs[0] = in.cs[3];
    out.cs[1] = in.cs[2];
    out.cs[2] = in.cs[1];
    out.cs[3] = in.cs[0];
    return out.i;
    */
    uint32_t result = 0;
    result |= (value & 0x000000FF) << 3*8;
    result |= (value & 0x0000FF00) <<   8;
    result |= (value & 0x00FF0000) >>   8;
    result |= (value & 0xFF000000) >> 3*8;
    return result;
}

int is_big_endian(void)
{
    union {
        uint32_t i;
        char cs[sizeof(uint32_t)];
    } ber = {0x01020304};

    return ber.cs[0] == 1; 
}

int is_big_endian64(void)
{
    union {
        uint64_t i;
        char cs[sizeof(uint64_t)];
    } ber = {0x0102030405060708};

    return ber.cs[0] == 1; 
}

int
main(int argc, char **argv) {
  printf("32-bit endianness: %s\n", is_big_endian() ? "Big" : "Little");
  printf("64-bit endianness: %s\n", is_big_endian64() ? "Big" : "Little");
}
