#include "DashMath.h"
#include <iostream>
#include <math.h> // power

using namespace std;

DashMath::DashMath(float a, float b, float c, float d)
{
    id = a;
    id_tol = b;
    cs = c;
    cs_tol = d;
    std::cout << "this is a func";
    //ctor
}

//add tolerance detail?
//confirmed works
float DashMath::getVolume(){
    float od = 0;
    float ic, oc, big_R, little_R; //inner and outer circumference
    double pi = 3.14159265358979323846;

    little_R = cs/2;
    big_R = little_R + id/2;

    ic = pi*id;
    oc = 2*pi*(big_R+little_R);
    ic = 2*pi*little_R;

    volume = ((ic*ic)*(oc-ic))/(4*pi);
    return volume;
}
