#include <iostream>
#include <iterator>

#include "Barcode.h"
#include "miniSOIL.h"

using namespace std;


// ������������� ��� � �������
unsigned char* SetPixelBit(
							unsigned char* pixel,	// ��������� �� �������
							int pixel_channels,		// ����������� �������
							unsigned char char_bit	// ���, ������� �����
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

// ������ ������ �����-���. ������ ��� � Barcode::MakeBarcode (�����, ������� ������ � �������� Unreal)
unsigned char* DrawBarcode(
							unsigned char* img,			// ��������� �� ��������
							int* img_dimensions,		// ����������� = [������, ������, �����������] 
							int pixels_per_bit,			// ������� �� ��� (������ ����� �����-����)
							std::vector<bool> barcode,	// �����-���
							int thickness = 1			// ������� ����� �����-����
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
					32,	//	����� ��� �� ����� �������� 
					16,	//	����� ��� �� ��������� (� ������)
					16	//	����� ��� �� ��������� (������������� �����)
					);
    std::vector<bool> barcode_result = barcode.MakeBarcode(
														   img_number,	// ����� ��������
														   distance,	// ��������� � ������
														   object_class	// ����� �������
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
					  img,				// ��������
					  img_dimensions,	// ����������� = [������, ������, �����������] 
					  10,				// ������� �� ��� (������ ����� �����-����)
					  barcode_result,	// �����-���
					  7					// ������� ����� �����-����
					  );

	const char* result_name = "9996.bmp";
	miniSOIL_save_image(result_name, SOIL_SAVE_TYPE_BMP, img_width, img_height, img_channels, img);

	cout << endl;
	cout << "== IMG SAVED ==" << endl;
    getchar();
    return 0;
}
