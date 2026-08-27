#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint32_t fnv32_hash(const char *str, size_t len);

int main(void)
{
    char string[100];

    scanf("%99s", string);

    printf("String: %s\n", string);

    uint32_t hash = fnv32_hash(string, strlen(string));

    printf("Hash: %u\n", hash);

    return 0;
}

uint32_t fnv32_hash(const char *str, size_t len)
{
    const unsigned char *s = (const unsigned char *)str;

    const uint32_t FNV_32_PRIME = 0x01000193;

    uint32_t h = 0x811c9dc5;

    while (len--)
    {
        h ^= *s++;
        h *= FNV_32_PRIME;
    }

    return h;
}
