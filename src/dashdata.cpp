#include "dashdata.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

dashdata::dashdata()
{

}

//Inputs a dash size from the vector of approved dash sizes.
//Inputs a reference to the dashdata object to fill with data.
//Function: searches as568.txt for the missing data and organizes it into dashtata::asobj
void dashdata::getdata(int dashSize, vector<float> &data){
    char jt [4]  {"210"};
    string line; //holds the dash line entry from as568.txt
    vector <string> holder;

    size_t pos;

    for(int j; j<5;j++){
        jt[j]=to_string(dashSize)[j];
    }

    ifstream refOne;
    refOne.open("as568.txt");
    //cout << "this is dashSize : " << dashSize << endl;
    while (getline(refOne, line)){

        pos = line.find(jt);

        if(pos!=string::npos){
            cout << dashSize << " found in this line : " << line << endl;
            holder.push_back(line);
        }

        /*for(std::vector<string>::const_iterator i = holder.begin(); i != holder.end(); ++i){
            //cout << "this is vector contents : " << *i << endl;

        }*/
    }
}

dashdata::~dashdata()
{
    //dtor
}
