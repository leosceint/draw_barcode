#include "Barcode.h"

Barcode::Barcode(int img_number_width, int distance_width, int classes_width):
    img_number_width(img_number_width), 
    distance_width(distance_width),
    classes_width(classes_width),
    barcode_width(img_number_width + distance_width + classes_width),
    bs_img_number(img_number_width),
    bs_distance(distance_width),
    bs_object(classes_width)

{

}

std::vector<bool> Barcode::MakeBarcode(int img_number, int distance, int object)
{
    std::vector<bool> bitset_img_number = bs_img_number.Bits(img_number);
    std::vector<bool> bitset_distance = bs_distance.Bits(distance);
    std::vector<bool> bitset_object = bs_object.Bits(object);

    std::vector<bool> Barcode(barcode_width, 0);

    for(std::size_t index = 0; index < barcode_width; ++index)
    {
        if(index < img_number_width)
        {
            Barcode[index] = bitset_img_number[index];
            continue;
        }
        if(index < img_number_width + distance_width)
        {
            Barcode[index] = bitset_distance[index-img_number_width];
            continue;
        }
        if(index < barcode_width)
        {
            Barcode[index] = bitset_object[index-img_number_width-distance_width];
        }
    }

    return Barcode;
}
