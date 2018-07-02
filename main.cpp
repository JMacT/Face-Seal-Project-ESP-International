#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <math.h> //pow

using namespace std;

void hardware_specs(float input_arr [] ); //cin customer hardeware specs. Output an array of those specs
float dash_Query(string as568); //search as568.txt for an oring size and output an array of those specs


int main()
{
    string search; //Holds dash size required for the search
    float hardware[9]={0}; //Customer input: Units, P_direction, Media, ID, ID_tol, OD, OD_tol, Gland_Max, Gland_tol, '\0'


    hardware_specs(hardware);

    cout << "What dash size do you THINK will work?\n"; //choose a dash size
    cin >> search;
    search = "-" + search; //Adds the dash in order to search as568.txt

    cout << "The dash size to be analyzed is : " << dash_Query(search) << endl; //uses dash size to search as568.txt and get an array of floats containing dim/tols for that size

    return 0;
}

//cin customer hardeware specs. Output an array of those specs
/*
0. Metric (0) or Imperial Measurements (1)
1. Pressure Direction: Internal pressure (0) or External Pressure (1)
2. Media: Liquid (0) or Gas (1)
3. ID
4. ID Tolerance
5. OD
6. OD Tolerance
7. Maximum gland depth allowable
8. Gland cut tolerance
*/
void hardware_specs(float input_arr []){
    //defaults to metric dimensions
    //defaults to liquid sealing
    //defaults to internal pressure

    cout << "In order to calculate your AS568 seal size, please enter your hardware dimensions : \n";

    cout << "Enter 0 for METRIC measurements or enter 1 for IMERIAL measurements" << endl;
    cin >> input_arr[0];
    if((input_arr[0]!=0) || (input_arr[0]!=0)){
        cout << "Illegal entry, defaulting to METRIC\n";
        input_arr[0]=0;
    }

    cout << "Enter 0 for sealing a LIQUID, enter 1 for sealing a GAS" << endl;
    cin >> input_arr[1];
    if((input_arr[1]!=0) || (input_arr[1]!=0)){
        cout << "Illegal entry, defaulting to LIQUID MEDIA\n";
        input_arr[0]=0;
    }

    cout << "Enter 0 for INTERNAL PRESSURE or enter 1 for EXTERNAL PRESSURE " << endl;
    cin >> input_arr[2];
    if((input_arr[2]!=0) || (input_arr[2]!=0)){
        cout << "Illegal entry, defaulting to INTERNAL PRESSURE\n";
        input_arr[0]=0;
    }
    cout << "Enter your gland INNER DIAMETER" << endl;
    cin >> input_arr[3];

    cout << "Enter your INNER DIAMETER TOLERANCE" << endl;
    cin >> input_arr[4];

    cout << "Enter your gland OUTER DIAMETER" << endl;
    cin >> input_arr[5];

    cout << "Enter you OUTER DIAMETER TOLERANCE" << endl;
    cin >> input_arr[6];

    cout << "Enter your MAXIMUM ALLOWABLE GLAND DEPTH" << endl;
    cin >> input_arr[7];

    cout << "Enter your GLAND DEPTH TOLERANCE" << endl;
    cin >> input_arr[8];

    return;
};


float dash_Query(string as568){

    string storage[9]={}; //Holds only pertinent characters read from string "line"
    string temp; //Used to fill storage and exit loop in case of \t in string "line"
    string line; //Holds info from as568.txt
    float dimTol[8] = {0}; //stof directly from the string "storage" indexed by i
    size_t pos;
    int i, j=0; //counters

    ifstream refOne;
    refOne.open ("as568.txt"); //Opening as568.txt as reference one

    //Opens as568.txt and copies relevant dash size line to "line" string
    while( getline(refOne, line) ){ //line.string = (entire) as568.txt
        pos = line.find(as568); //line.string now = the correct dash size entry

        if(pos!=string::npos){

            cout << line << endl; //Debug -- look at data is in "line" string.


                //Fill 1D string array "storage" with string data from the dash size line, breaking at '\t' character
                for(i=0;i<9;i++){

                    if (line[i]=='\t'){

                        dimTol[j] = stof(temp);
                        //cout << "this is dimTol at index " << j << " : " << dimTol[j] << endl;
                        temp.clear();
                        j++;

                        if(j==8){
                            i=500; //exit if all the dimensions are full
                        }

                    }

                    else{
                        temp = temp + line[i];
                    }

                }
                //END

    /*
                //Clean up data in 1D string array "storage"
                //Also, copy that data as a float into dimTol locations 0-8 (mirrors format of storage string)
                for(i=0;i<9;i++){ //0-8 slots for all 8 possible dimensions of the array
                    dimTol[i]= stof(storage[i]);
                }
                //END
    */

        }
    }

    refOne.close(); //close as568.txt

    return dimTol[0];
};

