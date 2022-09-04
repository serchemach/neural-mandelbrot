#include "neural_network_stuff.h"
#include "time.h"
#include "stdlib.h"
#include "mandelbrot.h"

void trainANN(genann* ann, double x_border, double y_border, double x_size, double y_size, unsigned number_of_samples){
    double *input = malloc(sizeof(double) * 2), *output = malloc(sizeof(double));

    for(int j = 0; j < number_of_samples; j++){
        input[0] = (double)(((rand() % 101351507) * 1735891) % 10000007) / 10000007;
        input[1] = (double)(((rand() % 101513507) * 1735891) % 10000007) / 10000007;

        int mandelbrot_iterations = 50;
        output[0] = (double)mandelbrot(input[0] * x_size + x_border, input[1] * y_size + y_border, mandelbrot_iterations) / mandelbrot_iterations;
        // output[0] = (input[0] + input[1]) / 2;
        // output[0] = 1;
        // if(input[0] > 0.5 && input[1] > 0.5){
        //     output[0] = 0;
        // }
        genann_train(ann, input, output, 3);
    }


    // input[0] = 1;
    // input[1] = 1;
    // double *result = genann_run(ann, input);
    // printf("result?? %lf, %lf, %lf\n", input[0], input[1], result[0]);

    // const double input[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    // const double output[4] = {0, 1, 1, 0};
    // int i;

    // /* Train on the four labeled data points many times. */
    // for (i = 0; i < 500; ++i) {
    //     genann_train(ann, input[0], output + 0, 3);
    //     genann_train(ann, input[1], output + 1, 3);
    //     genann_train(ann, input[2], output + 2, 3);
    //     genann_train(ann, input[3], output + 3, 3);
    // }

    // printf("Output for [%1.f, %1.f] is %1.f.\n", input[0][0], input[0][1], *genann_run(ann, input[0]));
    // printf("Output for [%1.f, %1.f] is %1.f.\n", input[1][0], input[1][1], *genann_run(ann, input[1]));
    // printf("Output for [%1.f, %1.f] is %1.f.\n", input[2][0], input[2][1], *genann_run(ann, input[2]));
    // printf("Output for [%1.f, %1.f] is %1.f.\n", input[3][0], input[3][1], *genann_run(ann, input[3]));
}

