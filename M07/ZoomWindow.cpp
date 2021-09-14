#include "ZoomWindow.h"

ZoomWindow::ZoomWindow(Point xy, int w, int h, const string& title) :
        Simple_window{xy,w,h,title},
        plane{PLANE_Y_OFFSET,complex<double> (0,0),1.0,w,h-PLANE_Y_OFFSET},
        next_i{Point(x_max()-250,0), 80, 20, "Center i"},
        next_r{Point(x_max()-400,0), 80, 20, "Center r"},
        next_zoom{Point(x_max()-550,0), 80, 20, "Zoom Level"}
{   

    attach(next_i);
    attach(next_r);
    attach(next_zoom); 
    next_i.hide();
    next_r.hide();
    next_zoom.hide();
    
    Simple_window::wait_for_button();
    attach(plane);
    plane.createBuffer();

    next_i.show();
    next_r.show();
    next_zoom.show();
    
}

bool ZoomWindow::wait_for_button(){

    Simple_window::wait_for_button();

    double center_r, center_i, zoom;   
    istringstream ss(next_i.get_string() + " " + 
    next_r.get_string() + " " + next_zoom.get_string());
    
    ss >> center_i;
    ss >> center_r;
    ss >> zoom;
    ss.clear();
    
    complex<double> c(center_r,center_i);
    plane.setCenter(c);
    plane.setZoomLevel(zoom);
    plane.createBuffer();
    
    return true;
}


double ZoomWindow::getCenter_r() const{return plane.getCenter().real();}
double ZoomWindow::getCenter_i() const{return plane.getCenter().imag();}
double ZoomWindow::getZoom() const{return plane.getZoomLevel();}