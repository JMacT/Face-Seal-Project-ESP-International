#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void Variable_Assigner(string source, char matrix[][]);




int main()
{
    string search;
    string line;
    char var_Matrix[9][5];


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

                Variable_Assigner(line, var_Matrix); //sort information into the matrix

            }
        }

        referenceOne.close();
    }
    else cout << "unable to open file.\n";
    return 0;
}

void Variable_Assigner(string source, char matrix[][]){ //matrix is set up FOR 9 DIMENSIONS TYPES with 5 characters for DATA.DATA [9][5]
    int i,j = 0;
    int k = -1;
    for(i=0;i<70;i++){
        k++;

        if(source[i]=='\t'){
            k++;
        }
        else{
            matrix[j][k] = source [i];
        }
    }
};
