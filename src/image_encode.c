#include "image_encode.h"
#include "lodepng.h"
#include "malloc.h"
#include "mandelbrot.h"

void encodeWithState(const char* filename, const unsigned char* image, unsigned width, unsigned height) {
  unsigned error;
  unsigned char* png;
  size_t pngsize;
  LodePNGState state;

  lodepng_state_init(&state);
  /*optionally customize the state*/

  error = lodepng_encode(&png, &pngsize, image, width, height, &state);
  if(!error) lodepng_save_file(png, pngsize, filename);

  /*if there's an error, display it*/
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));

  lodepng_state_cleanup(&state);
  free(png);
}

unsigned char* makeFractalImageBuffer(unsigned char* fractal_value_buffer, unsigned width, unsigned height){
    unsigned char* image = malloc(width * height * sizeof(unsigned char) * 4);

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            image[(i * width + j) * 4] = fractal_value_buffer[i * width + j];
            image[(i * width + j) * 4 + 1] = 0;
            image[(i * width + j) * 4 + 2] = fractal_value_buffer[i * width + j];
            image[(i * width + j) * 4 + 3] = 255;
        }
    }

    return image;
}

