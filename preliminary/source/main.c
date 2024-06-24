#include <stdio.h>
#include <stdint.h>

uint8_t makeBitmask(uint8_t width, uint8_t shift)
{
    uint8_t bitMask = (1 << width) - 1;
    return bitMask << shift;
}

uint8_t countOnes(uint8_t value)
{
    uint8_t count = 0;
    for (int i = 0; i < 8; i++)
    {
        if (value & (1 << i))
            count++;
    }

    return count;
}

int main()
{
    int w = 1;
    printf("they are %d 1s in the binary form of %d\n", countOnes(w), w);
    return 0;
} 