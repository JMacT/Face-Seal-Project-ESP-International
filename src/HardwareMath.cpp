#include "..\includes\HardwareMath.h"

HardwareMath::getMaxVolume(float gland_max)
{
    float volume;
    float area;

    od += od_tol;
    id -= id_tol;
    double pi = 3.14159265358979323846;

    area = (pi*(od*od)/4) - (pi*(id*id)/4); // area of the gland to integrate to G

    volume = area * gland_max; //gland max is taken from the parker recommendations txt file. CS_test has already identified it is an option.

    return volume;
}

HardwareMath::getMinVolume(float gland_Min)
{
    float volume;
    float area;

    od -= od_tol;
    id += id_tol;
    double pi = 3.14159265358979323846;

    area = (pi*(od*od)/4) - (pi*(id*id)/4); // area of the gland to integrate to G

    volume = area * gland_Min; //gland max is taken from the parker recommendations txt file. CS_test has already identified it is an option.

    return volume;
}
