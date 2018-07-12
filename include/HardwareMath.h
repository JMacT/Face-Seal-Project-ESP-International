#ifndef HARDWAREMATH_H
#define HARDWAREMATH_H


class HardwareMath
{
    public:
        float getMaxVolume(float); //Pass the gland max from Parker reqs txt into this
        float getMinVolume(float); //Pass the gland min from Parker reqs txt into this
        int units;
        int p_direction;
        int media;
        float id;
        float id_tol;
        float od;
        float od_tol;
        float gland_max;
        float gland_tol;

    protected:

    private:
};

#endif // HARDWAREMATH_H
