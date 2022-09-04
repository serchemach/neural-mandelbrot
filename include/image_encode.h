#pragma once

void encodeWithState(const char* filename, const unsigned char* image, unsigned width, unsigned height);

unsigned char* makeFractalImageBuffer(unsigned char* fractal_value_buffer, unsigned width, unsigned height);

