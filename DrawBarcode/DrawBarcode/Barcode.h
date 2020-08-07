#ifndef BARCODE_H
#define BARCODE_H
#include <vector>

#include "Bitset.h"

class Barcode
{

private:
    int img_number_width;
    int distance_width;
    int classes_width;
    int barcode_width;

    Bitset bs_img_number;
    Bitset bs_distance;
    Bitset bs_object;

public:

    Barcode(int img_number_width, int distance_width, int classes_width);

    std::vector<bool> MakeBarcode(int img_number, int distance, int object);

private:
    Barcode();

};

#endif