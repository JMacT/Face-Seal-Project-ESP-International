#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <cstring> //strlen
#include <math.h> //pow
#define SIZE 9

using namespace std;

void Variable_Assigner(string source);

/*
float stof(const char* s){
  float rez = 0, fact = 1;
  if (*s == '-'){
    s++;
    fact = -1;
  };
  for (int point_seen = 0; *s; s++){
    if (*s == '.'){
      point_seen = 1;
      continue;
    };
    int d = *s - '0';
    if (d >= 0 && d <= 9){
      if (point_seen) fact /= 10.0f;
      rez = rez * 10.0f + (float)d;
    };
  };
  return rez * fact;
};
*/


float str2float(char){
};


int main()
{
    string search;
    string storage[9]={};
    string temp;
    string line;
    float dim_tols[9]={0};
    char var;
    int i, j=0;


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

                for(i=0;i<9;i++){
                    //temp = storage[i];
                    float holder=0; // this is where the float goes
                    char temp2[10]; //this is the array that passses to str2float
                    for (j=0;j<7;j++){
                        temp2[j]=storage[i][j];
                    }
                    int k=0;
                    holder = str2float (temp2[i+1]); //Not Tested, need WINGC 2011 for ATOF.
                    for(k=0;k<5;k++){
                        cout << temp2[k];
                    }
                    cout << holder << "this is holder\n";

                }

            }
        }

        referenceOne.close();
    }
    else cout << "unable to open file.\n";
    return 0;
}


float str2float(char* s){
// solve for special cases where s begins with 0's or nun numeric values, or if s is NULL
  float result = 0;
  int decimalCount = 0, i = 0, decimalPointLoc = strlen(s);
  for (; s[i] != '\0'; i++){
    if (s[i] == '.') decimalPointLoc = i;
    if (i < decimalPointLoc) { result *= 10; result += (int)(s[i] + '0'); }
    else { result += (float)(s[i] + '0')/(pow(i-decimalPointLoc,10)); }
  }
  return result;
}


/*
void Variable_Assigner(string source){ //matrix is set up FOR 9 DIMENSIONS TYPES with 5 characters for DATA.DATA [9][5]
    int i,j = 0;
    string storage[9]={0};
    string temp;

    cout << source;
/*
    for(i=0;i<50;i++){
        if (source[i]=='\t'){
            storage[j]=temp;
            j++;

            if(j==8){
                i=50; //exit if all the dimensions are full
            }

        }

        else{
            //temp = temp + source[i];
            cout << temp <<endl;
        }

    }*/

   /* for(i=0;storage[i][0]!='\0'; i++){
        for(j=0;storage[i][j]!='\0';j++){
            cout << storage[i][j];
        }
    }*/
//};
