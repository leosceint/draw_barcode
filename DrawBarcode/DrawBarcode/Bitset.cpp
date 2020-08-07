#include "Bitset.h"

Bitset::Bitset(int size):
vBitset(size, 0)
{

}

std::vector<bool> Bitset::Bits(int number)
{
    int index = vBitset.size() - 1;
    while(number)
    {
        if (index < 0)
            break;
        vBitset[index--] = number%2;
        number >>= 1;
    }

    return vBitset;
}
