#include "stdio.h"
#include "image_encode.h"
#include "time.h"
#include "genann.h"
#include "neural_network_stuff.h"
#include "mandelbrot.h"
#include "string.h"

unsigned char* makeFractalValueBuffer(unsigned width, unsigned height, double x_border, double y_border, double x_size, double y_size){
    unsigned char* buffer = malloc(width * height * sizeof(unsigned char));

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            buffer[i * width + j] = 1/mandelbrotDE(j * x_size / width + x_border, i * y_size / height + y_border, 128);
        }
    }

    return buffer;
}

void savePerfectMandelbrot(unsigned width, unsigned height){
    double starting_time = time(NULL);
    printf("Making sample image\n");
    printf("Rendering...\n");
    unsigned char* fractal_value_buffer = makeFractalValueBuffer(width, height, -1.5, -1, 2, 2);
    unsigned char* img = makeFractalImageBuffer(fractal_value_buffer, width, height);
    free(fractal_value_buffer);

    printf("Encoding...\n");
    encodeWithState("example.png", img, width, height);
    printf("Done in %lf seconds\n", time(NULL) - starting_time);

    free(img);
}

int round(double x){
    if(x > 0.5){
        return 1;
    }
    return 0;
}

unsigned char* makeFractalNeuralValueBuffer(genann* ann, unsigned width, unsigned height, double x_border, double y_border, double x_size, double y_size){
    unsigned char* buffer = malloc(width * height * sizeof(unsigned char));    
    double *temp = malloc(sizeof(double) * 3);
    temp[2] = 1;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            temp[0] = (double)j / width;
            temp[1] = (double)i / height;
            double *result = genann_run(ann, temp);
            buffer[i * width + j] = result[0] * 255;
        }
    }

    free(temp);

    return buffer;
}

void saveNeuralMandelbrot(genann* ann, unsigned char* filename, unsigned width, unsigned height){
    double starting_time = time(NULL);
    printf("Making neural image\n");
    printf("Rendering...\n");
    unsigned char* fractal_value_buffer = makeFractalNeuralValueBuffer(ann, width, height, -1.5, -1, 2, 2);
    unsigned char* img = makeFractalImageBuffer(fractal_value_buffer, width, height);
    free(fractal_value_buffer);

    printf("Encoding...\n");
    encodeWithState(filename, img, width, height);
    printf("Done in %lf seconds\n", time(NULL) - starting_time);

    free(img);
}

int main(){
    unsigned width = 10000, height = 10000;

    savePerfectMandelbrot(width, height);
    
    // srand(time(NULL));
    // genann* ann = genann_init(2, 5, 4, 1);
    // printf("Training nn...\n");
    // for(int i = 0; i < 100000; i++){
    //     trainANN(ann, -1.5, -1, 2, 2, 10000);
    //     if(i % 100 == 0){
    //         printf("%lf%%\n", (double)(i + 1) * 100 / 100000);
    //         char str[100];
    //         sprintf(str, "neural%d.png", i / 100);
    //         saveNeuralMandelbrot(ann, str, 300, 300);
    //     }
    // }

    // saveNeuralMandelbrot(ann, "example+neural.png", width, height);
    // genann_free(ann);

    return 0;
}

