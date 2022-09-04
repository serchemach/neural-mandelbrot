#include "mandelbrot.h"
#include "math.h"
#include "complex.h"

unsigned int mandelbrot(double x, double y, unsigned int max_iteration){
    unsigned int current_iteration = 0;
    double initial_x = x, initial_y = y;
    while(x * x + y * y < 16 && current_iteration < max_iteration){
        double temp = x;
        x = x * x - y * y + initial_x;
        y = y * 2 * temp + initial_y;
    
        current_iteration++;
    }

    return current_iteration;
}

double mandelbrotDE(double x, double y, unsigned int max_iteration){
    unsigned int current_iteration = 0;
    double initial_x = x, initial_y = y, derivative_x = 1, derivative_y = 0;
    while(x * x + y * y < 16 && current_iteration < max_iteration){
        double temp_der = derivative_x;
        derivative_x = 2*derivative_x * x - 2*y * derivative_y + 1;
        derivative_y = 2*temp_der * y + 2*x * derivative_y;
        
        double temp = x;
        x = x * x - y * y + initial_x;
        y = y * 2 * temp + initial_y;
    
        current_iteration++;
    }

    // return current_iteration;
    double point_abs = sqrt(x * x + y * y);
    
    return point_abs*abs(log(point_abs))/sqrt(derivative_x*derivative_x + derivative_y*derivative_y);
}

