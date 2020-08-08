#include <iostream>
#include <iterator>

#include "Barcode.h"
#include "miniSOIL.h"

using namespace std;


// Set bit in pixel
unsigned char* SetPixelBit(
							unsigned char* pixel,	// Pointer to pixel
							int pixel_channels,		// Count of color components in pixel
							unsigned char char_bit	// Bit to write in pixel
							)
{
	unsigned char* temp_pixel = pixel;
	int channel = 0;
	while(channel < pixel_channels)
	{
		temp_pixel[channel] = char_bit;
		++channel;
	}

	return temp_pixel;
}

// There we only draw barcode. To make barcode use Barcode::MakeBarcode (Barcode class -> blueprints in Unreal)
unsigned char* DrawBarcode(
							unsigned char* img,			// Pointer to image
							int* img_dimensions,		// Image dimension = [width, height, count of color components] 
							int pixels_per_bit,			// Width of barcode bit in pixels
							std::vector<bool> barcode,	// Barcode that we make in Barcode::MakeBarcode
							int thickness = 1			// Thickness of Barcode (count of image lines)
							)
{
	unsigned char* temp_img = img;

	int img_width		= img_dimensions[0];
	int img_height		= img_dimensions[1];
	int img_channels	= img_dimensions[2];

	int row_position = img_channels * (img_width * img_height - thickness * img_width);
	unsigned char* row = temp_img;
	row += row_position;

	unsigned char* pixel = row;
	unsigned char* pixel_in_bit;

while(thickness)
	{
		for( unsigned int bit_index = 0, pixel_index = 0;
				bit_index < barcode.size();
			++bit_index, pixel_index += pixels_per_bit )
		
		{
			if(pixel_index > img_width)
				break;
			unsigned char bit_color = barcode[bit_index] ? 255 : 0;
			pixel = row + pixel_index * img_channels;
			
			unsigned char* pixel_in_bit;
			
			int index_pixel_in_bit = 0;
			while(index_pixel_in_bit < pixels_per_bit)
			{
				pixel_in_bit = pixel + index_pixel_in_bit * img_channels;
				SetPixelBit(pixel_in_bit, img_channels, bit_color);
				++index_pixel_in_bit;
			}
		
		}
		row += img_channels*img_width;
		--thickness;
	}

	return temp_img;
}

int main()
{
	int img_number		= 996;
	int distance		= 1544;
	int object_class	= 5;

	cout << endl;
	cout << "== BARCODE ==" << endl;
	cout << endl;
	cout << "|x| INPUT |x|" << endl;
	cout << "<IMG NUMBER>	:" << img_number << endl;
	cout << "<DISTANCE>	:" << distance << endl;
	cout << "<OBJECT CLASS>	:" << object_class << endl;

    Barcode barcode(
					32,	//	Bits to image number
					16,	//	Bits to distance to target (in meters)
					16	//	Bits to class of tracked object
					);
    std::vector<bool> barcode_result = barcode.MakeBarcode(
														   img_number,	// Image number
														   distance,	// Distance in meters
														   object_class	// Object class
														   );

    cout << endl;
	cout << "|x| RESULT |x|" << endl; 
	copy(barcode_result.begin(), barcode_result.end(), ostream_iterator<bool>(cout, ""));
    cout << endl;

	const char* img_name = "9996.png";
	int img_width;
	int img_height;
	int img_channels;

	unsigned char* img = miniSOIL_load_image(img_name, &img_width, &img_height, &img_channels, SOIL_LOAD_RGB);
	
	cout << endl;
	cout << "== IMG PARAMETERS ==" << endl;
	cout << endl;
	cout << "<IMG NAME>     :" << img_name << endl;
	cout << "<IMG WIDTH>    :" << img_width << endl;
	cout << "<IMG HEIGHT>   :" << img_height << endl;
	cout << "<IMG CHANNELS> :" << img_channels << endl;
    
	int img_dimensions[] = {img_width, img_height, img_channels};

	img = DrawBarcode(
					  img,				// Image that was loaded
					  img_dimensions,	// Image dimensions = [width, height, count of colors] 
					  10,				// Width of barcode bit in pixels
					  barcode_result,	// Barcode that we make in Barcode::MakeBarcode
					  3					// Thickness of Barcode (count of image lines)
					  );

	const char* result_name = "9996.bmp";
	miniSOIL_save_image(result_name, SOIL_SAVE_TYPE_BMP, img_width, img_height, img_channels, img);

	cout << endl;
	cout << "== IMG SAVED ==" << endl;
    getchar();
    return 0;
}
