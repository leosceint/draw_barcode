#ifndef MINISOIL_H
#define MINISOIL_H

#ifdef __cplusplus
extern "C"{
#endif

/**
	The format of images that may be loaded (force_channels).
	SOIL_LOAD_AUTO leaves the image in whatever format it was found.
	SOIL_LOAD_L forces the image to load as Luminous (greyscale)
	SOIL_LOAD_LA forces the image to load as Luminous with Alpha
	SOIL_LOAD_RGB forces the image to load as Red Green Blue
	SOIL_LOAD_RGBA forces the image to load as Red Green Blue Alpha
**/
enum
{
	SOIL_LOAD_AUTO = 0,
	SOIL_LOAD_L = 1,
	SOIL_LOAD_LA = 2,
	SOIL_LOAD_RGB = 3,
	SOIL_LOAD_RGBA = 4
};


/**
	The types of images that may be saved.
	(TGA supports uncompressed RGB / RGBA)
	(BMP supports uncompressed RGB)
	(DDS supports DXT1 and DXT5)
**/
enum
{
	SOIL_SAVE_TYPE_TGA = 0,
	SOIL_SAVE_TYPE_BMP = 1,
	SOIL_SAVE_TYPE_DDS = 2
};


/**
	Loads an image from disk into an array of unsigned chars.
	Note that *channels return the original channel count of the
	image.  If force_channels was other than SOIL_LOAD_AUTO,
	the resulting image has force_channels, but *channels may be
	different (if the original image had a different channel
	count).
	\return 0 if failed, otherwise returns 1
**/
unsigned char*
	miniSOIL_load_image
	(
		const char *filename,
		int *width, int *height, int *channels,
		int force_channels
	);


/**
	Saves an image from an array of unsigned chars (RGBA) to disk
	\return 0 if failed, otherwise returns 1
**/
int
	miniSOIL_save_image
	(
		const char *filename,
		int image_type,
		int width, int height, int channels,
		const unsigned char *const data
	);

#ifdef __cplusplus
}
#endif

#endif