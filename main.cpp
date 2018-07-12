#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector> //for dynamic storage of acceptable o-rings
#include <math.h> //pow
#include <DashMath.h>
#include <HardwareMath.h>
#include <dashdata.h>

using namespace std;

void hardware_specs(float input_arr [] ); //cin customer hardeware specs. Output an array of those specs
void hardware_specs_2(HardwareMath& gland);

void dash_Query(string as568, vector<int> &oring_Fits); //search as568.txt for an oring size and output an array of those specs
void CS_Test(float*, float*);
void string_to_float_array(string, float*, int, int);
void convert_To_Metric(float*);

int main()
{
    int i=0;
    int iterate_ctr = 0;
    DashMath dash(.239, .005, .070, .003);
    HardwareMath gland;
    dashdata asobj;


    string search; //Holds dash size required for the search.
    vector<int> oring_Fits; //Holds list of recommended dash sizes
    vector<float> dimtols;
    float *as568; //a pointer to the array holding all info on a dash size. See below:
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

    float hardware[9]={1,0,0,1.0,.00,1.370,.00,1,.05}; //Customer input: Units, P_direction, Media, ID, ID_tol, OD, OD_tol, Gland_Max, Gland_tol, '\0'
    float CS_array[]={0.07, 0.103, 0.139, 0.21, 0.275};//lists all AS568 CSs available for fitment. Because of -0xx and -9xx c/s variance, hard coding may be better option
                //NOTE: Cannot judge the following CS sizes -001 through -003, all 2-9xxs because they are not covered by Parker recommendations: 0.056, 0.064, 0.072, 0.078, 0.082, 0.087, 0.097, 0.116, 0.118

    //hardware_specs_2(gland);//temporarily hard-coding

    CS_Test(hardware, CS_array);

    //Cycle through the cross sections possible. If CS_array[i] has been turned to NULL for mis-fit C/S it is ignored
    for(i=0; i <=4 ; i++){
        search = to_string(CS_array[i]); //Adds the dash in order to search as568.txt

        if(CS_array[i] > 0){
            dash_Query(search, oring_Fits); //oring_Fits is a vector that holds all dash sizes currently fitting
        }
    }

    //cout << "The volume of this o-ring is : " << dash.getVolume() << endl;

    //go through the approved dash sizes and analyze for fit

    for(vector<int>::const_iterator i = oring_Fits.begin(); i != oring_Fits.end(); ++i){
        iterate_ctr++;

        cout << "now checking dash size: " << *i << endl;
        asobj.getdata(*i, dimtols);
    }

    return 0;
}

/*
string_to_float_array
Inputs: a string, a float array, an integer width, a loop escape value
Function: Fill each index of the float array with one snip of the string separating by \t
*/
void string_to_float_array(string line, float arr[], int w, int escape){
    //string line;
    string temp;
    int i, j=0;

    for(i=0;i<w;i++){
        //data is separated by '\t'.
        //This splits data and then copies it as a float into arr[].
        while( (line[(j+i)]!= '\t' ) && (line[(j+i)]!= '\0' ) ){
            temp = temp + line[(j+i)];
            j++;
        }
        arr[i] = stof(temp);

        temp.clear();

        //If you have filled all of the dimensions...
        if( (j+i) == line.length()){
            i=w;
        }
    }
    //END

    //cout << "This is a test of sting_to_float function. This is arr[5] : " << arr[5] << endl;

    return;
};

//cin customer hardeware specs. Output an array of those specs
/*
Input:
-1. an empty array from main()
0. Metric (0) or Imperial Measurements (1)
1. Pressure Direction: Internal pressure (0) or External Pressure (1)
2. Media: Liquid (0) or Gas (1)
3. ID
4. ID Tolerance
5. OD
6. OD Tolerance
7. Maximum gland depth allowable
8. Gland cut tolerance
Working? YES 7/3/18
*/
void hardware_specs_2(HardwareMath& gland){
    //defaults to metric dimensions
    //defaults to liquid sealing
    //defaults to internal pressure
    cout << "In order to calculate your AS568 seal size, please enter your hardware dimensions : \n";

    cout << "Enter 0 for METRIC measurements or enter 1 for IMERIAL measurements" << endl;
    cin >> gland.units;
    if( (gland.units!=1) && (gland.units!=0)){
        cout << "Illegal entry, defaulting to METRIC\n";
        gland.units=0;
    }

    cout << "Enter 0 for sealing a LIQUID, enter 1 for sealing a GAS" << endl;
    cin >> gland.media;
    if((gland.media!=0) && (gland.media!=1)){
        cout << "Illegal entry, defaulting to LIQUID MEDIA\n";
       gland.media=0;
    }

    cout << "Enter 0 for INTERNAL PRESSURE or enter 1 for EXTERNAL PRESSURE " << endl;
    cin >> gland.p_direction;
    if((gland.p_direction!=0) && (gland.p_direction!=1)){
        cout << "Illegal entry, defaulting to INTERNAL PRESSURE\n";
        gland.p_direction=0;
    }
    cout << "Enter your gland INNER DIAMETER" << endl;
    cin >> gland.id;

    cout << "Enter your INNER DIAMETER TOLERANCE" << endl;
    cin >> gland.id_tol;

    cout << "Enter your gland OUTER DIAMETER" << endl;
    cin >> gland.od;

    cout << "Enter you OUTER DIAMETER TOLERANCE" << endl;
    cin >> gland.od_tol;

    cout << "Enter your MAXIMUM ALLOWABLE GLAND DEPTH" << endl;
    cin >> gland.gland_max;

    cout << "Enter your GLAND DEPTH TOLERANCE" << endl;
    cin >> gland.gland_tol;

    return;

}

void hardware_specs(float input_arr []){
    //defaults to metric dimensions
    //defaults to liquid sealing
    //defaults to internal pressure

    cout << "In order to calculate your AS568 seal size, please enter your hardware dimensions : \n";

    cout << "Enter 0 for METRIC measurements or enter 1 for IMERIAL measurements" << endl;
    cin >> input_arr[0];
    if( (input_arr[0]!=1) && (input_arr[0]!=0)){
        cout << "Illegal entry, defaulting to METRIC\n";
        input_arr[0]=0;
    }

    cout << "Enter 0 for sealing a LIQUID, enter 1 for sealing a GAS" << endl;
    cin >> input_arr[1];
    if((input_arr[1]!=0) && (input_arr[1]!=1)){
        cout << "Illegal entry, defaulting to LIQUID MEDIA\n";
        input_arr[0]=0;
    }

    cout << "Enter 0 for INTERNAL PRESSURE or enter 1 for EXTERNAL PRESSURE " << endl;
    cin >> input_arr[2];
    if((input_arr[2]!=0) && (input_arr[2]!=1)){
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

/*
CS_Test
Inputs: the customer's hardware in array format, the array of available cross-sections (hard-coded from as568 reference material)
Function: Test the available cross-sections in the customer's hardware and see which are viable options
Results: The array of available cross sections is left without those that will not work
Working? So far, parker_Recs is filling up correctly
*/
void CS_Test(float hardware[], float CS_array[]){
    /*Format of hardware[]:
    0. Metric (0) or Imperial Measurements (1)
    1. Pressure Direction: Internal pressure (0) or External Pressure (1)
    2. Media: Liquid (0) or Gas (1)
    3. ID
    4. ID Tolerance
    5. OD
    6. OD Tolerance
    7. Maximum gland depth allowable
    8. Gland cut tolerance*/

    //Gameplan:
    //Basically, get gland depth min and max from hardware
    //get groove width min and max from hardware
    //get the recommendations min and max using hardware metric/imperial, internal/external_p, liquid/gas
    //If a cross section fails, change its address in CS_array[] to a NULL so it is ignored


    float G_Recommended_min, G_Recommended_max, G_hardware_max,G_hardware_min, L_hardware_max = 0;
    string line;
    float squeeze[2]={0}; //squeeze[0] = min, squeeze[1]=max;
    int width=10;
    int exit_var=5; //Only check the 5 existing cross sections
    int CS_Counter = 0;
    static float parker_Recs[10];
    float report = 0; //saves the cross section size for the cout report.
    int i, j =0;
    size_t pos;

    //error catcher
    if(hardware[3] >= hardware[5]){
        cout << "There was an error in your entry. Make sure your OD is larger than your ID" << endl;
        return;
    }

    //Gland width, G_max [(maximum OD)-(minimum ID)]/2
    G_hardware_max = ((hardware[5]+hardware[6])-(hardware[3]-hardware[4]))/2;
    G_hardware_min = ((hardware[5]-hardware[6])-(hardware[3]+hardware[4]))/2;
    L_hardware_max = hardware[7]+hardware[8]; //This is the absolute deepest the customer can cut. Compare to parker_Recs[2]
    //Minimum gland depths are dealt with in the analysis ??? CHECK THIS


   /* 0. Metric (0) or Imperial Measurements (1)
1. Pressure Direction: Internal pressure (0) or External Pressure (1)
2. Media: Liquid (0) or Gas (1)
3. ID
4. ID Tolerance
5. OD
6. OD Tolerance
7. Maximum gland depth allowable
8. Gland cut tolerance*/

    ifstream refTwo;
    refTwo.open("Parker Oring Face Seal Design Chart 4-3.txt"); // opens the face seal design recommendations .txt file

    //Looping through the CSs available
    for(i=0; i < width; i++ ){

        //refTwo.open("Parker Oring Face Seal Design Chart 4-3.txt");
        refTwo.clear();
        refTwo.seekg(0,ios::beg);

            while( getline(refTwo, line) ){ //line string = (entire) parker recommendations .txt

                //search for the seven sigfig float version of CS_array[i]
                pos = line.find(to_string(CS_array[i])); //position, pos is equal to where CS_array[0] (the cross section) was found in line.

                refTwo.clear(); //start searching again from the beginning of the file next time

                if(pos!=string::npos){ //execute if the string is not-not found

                    string_to_float_array(line, parker_Recs, width, exit_var); //fill parker_Recs with floats of all the dash data

                    if(hardware[0] == 0){
                        convert_To_Metric(parker_Recs); //convert the inch recommendations to mm if necessary
                    }

                    if(hardware[2]==0){ //use gland widths for liquids
                        G_Recommended_min = parker_Recs[6];
                        G_Recommended_max = parker_Recs[7];
                    }
                    else{ //use gland widths for gases
                        G_Recommended_min = parker_Recs[8];
                        G_Recommended_max = parker_Recs[9];
                    }

                    report = CS_array[i];
                    //Checking hardware vs recommendations
                    if( L_hardware_max < parker_Recs[2] ){ //If the hardware is not jiving with the recommendations
                        CS_array[i] = NULL; //Get rid of the C/S that did not fit
                        CS_Counter++; //if all available cross sections are exhausted, recommend a custom size.
                        cout << "The problem with the " << report << " cross section was the maximum groove depth.\n";
                    }
                    else if( (G_hardware_min < G_Recommended_min) ){ //If the hardware is not jiving with the recommendations
                        CS_array[i] = NULL; //Get rid of the C/S that did not fit
                        CS_Counter++; //if all available cross sections are exhausted, recommend a custom size.
                        cout << "The problem with the " << report << " cross section was the gland diameter was too big\n";
                    }
                    else if( (G_hardware_max > G_Recommended_max) ){ //If the hardware is not jiving with the recommendations
                        CS_array[i] = NULL; //Get rid of the C/S that did not fit
                        CS_Counter++; //if all available cross sections are exhausted, recommend a custom size.
                        cout << "The problem with the " << report << " cross section was the gland diameter was too small\n";
                    }
                    else{
                        cout << "The correct cross section is : " << CS_array[i] << endl;
                    }

                }
            }

            if(CS_Counter > 4){
                cout << "There is no recommended match in the AS568 O-ring sizes for this hardware.\n";
                break;
            }
    }

    return;
};
;
/*
dash_Query:
Input: an as568 dash size
Function: to pull size's line from as568.txt and copy the values to an array in float form. Then, take that dash size and copy it into a growing vector of potential fits.

//IMPORTANT CHANGE ***Took away the return::float and now pass a vector of correct sizes to dash_Query(). No longer need all the conversion to float as that will occur later.***
Working? YES 7/3/18
*/
void dash_Query(string as568, vector<int> &oring_Fits){

    string temp; //Used to fill storage and exit loop in case of \t in string "line"
    string line; //Holds info from as568.txt
    static float dimTol[9] = {0}; //stof directly from the string "storage" indexed by i
    size_t pos;
    int i, j=0; //counters
    int width = 9; //Exit the loop when all 9 dimensions are filled
    int exit_var = 8; //Exit the loop when data is 8 bits long

    ifstream refOne;
    refOne.open ("as568.txt"); //Opening as568.txt as reference one

    //Opens as568.txt and copies relevant dash size line to "line" string
    while( getline(refOne, line) ){ //line.string = (entire) as568.txt

        pos = line.find(as568); //line.string now = the correct dash size entry

        if(pos!=string::npos){

            string_to_float_array(line, dimTol, width, exit_var); //fill dimTol with floats of all the dash data

            j = (dimTol[8]); //copying float::(dash size) to int::j in order to drop of extra zeros

            //Add that dash size to the growing vector of acceptable dash sizes
            oring_Fits.push_back(j);

            //***oring_Fits is now vector holding all dash sizes of the proper cross section for the hardware.****
        }
    }

    refOne.close(); //close as568.txt

    return;
};

void convert_To_Metric(float* arr){
    int i;
    for(i=0; i < sizeof(arr); i++){
        arr[i] = arr[i] * 25.4; //convert inches to mm
    }

    return;
}
