#include "ComplexPlane.h"

void ComplexPlane::draw_lines() const{
    fl_draw_image(buf, 0,y_pixel_offset, xPixels, yPixels);
}

void writePixel(unsigned char* buf, int xPixels, int row, int col, unsigned char r, unsigned char g, unsigned char b){
    *(buf + ((row*xPixels+col)*3)) = r;
    *(buf + ((row*xPixels+col)*3 + 1)) = g;
    *(buf + ((row*xPixels+col)*3 + 2)) = b;
}

int countIterations(double re, double im, int maxIterations){
    complex<double> c(re, im);
    complex<double> z(0,0);
    
    int i = 0;
    while((abs(z) < 2.0) && (i < maxIterations)){
        z=z*z+c;
        i++;
    }
    return i;
}

double mapRange(double n, double fromLow, double fromHigh, double toLow, double toHigh){
    return ((n-fromLow)/(fromHigh - fromLow)) *(toHigh - toLow) + toLow;
}

void ComplexPlane::createBuffer(){
    complex<double> c;
    for(int i = 0; i < yPixels; i++){
        
        c.imag(mapRange(i, yPixels, 0,(center.imag() -(imRange/2) * zoomLevel),(center.imag() +(imRange/2) * zoomLevel))); 
        
        for(int j = 0; j < xPixels; j++){
            int iter;
            
            c.real(mapRange(j, xPixels, 0, (center.real() +(reRange/2) * zoomLevel),(center.real() -(reRange/2) * zoomLevel)));
            
            iter = countIterations(c.real(), c.imag(), maxIterations);
            
            uchar r, g, b;
            if(iter >= maxIterations){
                Fl::get_color(maxIterations-iter, r, g, b);
            }
            else{
                Fl::get_color(iter, r, g, b);
            }
            
            writePixel(buf,xPixels,i,j, r, g, b);
        }
    }
    draw_lines();
}

