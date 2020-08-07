#ifndef BITSET_H
#define BITSET_H
#include <vector>

class Bitset
{
private:
    std::vector<bool> vBitset;

public:
    
    Bitset(int size);
    std::vector<bool> Bits(int number);

private:
    Bitset();
};

#endif