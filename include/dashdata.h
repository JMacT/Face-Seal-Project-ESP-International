#ifndef DASHDATA_H
#define DASHDATA_H
#include <vector>
    //AS568 Format - used for hard coding all other functions using the as568 resource.
    //as568[0] : Dash Size Callout
    //as568[1] : CS inch
    //as568[2] : CS Tol inch
    //as568[3] : ID inch
    //as568[4] : ID Tol inch
    //as568[5] : CS mm
    //as568[6] : CS Tol mm
    //as568[7] : ID mm
    //as568[8] : ID Tol mm

class dashdata
{
    public:
        dashdata();
        float cs_in;
        float cs_tol_in;
        float id_in;
        float id_tol_in;
        float cs_mm;
        float cs_tol_mm;
        float id_mm;
        float id_tol_mm;
        int dashSize;
        virtual ~dashdata();

        void getdata(int, std::vector<float>&);

    protected:

    private:
};

#endif // DASHDATA_H
