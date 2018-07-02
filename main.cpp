#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <cstring> //strlen
#include <math.h> //pow
#define SIZE 9

using namespace std;



int main()
{
    string search;
    string storage[9]={};
    string temp;
    string line;
    float dim_tols[9]={0};
    char var;
    int i, j=0;

    float holder=0; // this is where the float goes
    char temp2[6]; //this is the array that passes to str2float

    ifstream referenceOne;
    referenceOne.open ("as568.txt");
    size_t pos;

    cout << "What dash size are you looking for?\n";
    cin >> search;
    search = "-"+search;

    if (referenceOne.is_open() ) {
        while( getline(referenceOne, line) ){ //line.string = (entire) as568.txt
            pos = line.find(search); //line.string now = the correct dash size entry

            if(pos!=string::npos){

                cout << line << endl;

                    for(i=0;i<500;i++){

                        if (line[i]=='\t'){

                            storage[j]=temp;
                            temp.clear();
                            j++;

                            if(j==9){
                                i=500; //exit if all the dimensions are full
                            }

                        }

                        else{
                            temp = temp + line[i];
                            //cout << temp <<endl;
                        }

                    }
                    /*debug only
                    for(i=0;i<9; i++){
                        cout<<storage[i];
                        cout << endl;
                    }
                    */

                for(i=0;i<9;i++){ //0-8 slots for all 8 possible dimensions of the array
                    //temp = storage[i];
                    for (j=0;j<6;j++){
                        if((i==0 && j==4) ||(i==0 && j==5) ){
                            temp2[4] = ' '; // doesn't put nonsense after the dash number
                            temp2[5] = ' ';
                        }
                        else {
                            temp2[j]=storage[i][j]; //Note: forced space or '0' for unused slots
                        }
                    }
                    holder = atof(temp2);
                    cout << "this is dimensions times 4 : " << (holder*4)  << endl;


                }

            }
        }

        referenceOne.close();
    }
    else cout << "unable to open file.\n";
    return 0;
}
