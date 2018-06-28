#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void Variable_Assigner(string source);




int main()
{
    string search;
    string storage[9]={};
    string temp;
    string line;
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

                    for(i=0;i<9; i++){
                        cout<<storage[i];
                        cout << endl;
                    }

                //Variable_Assigner(line); //sort information into the matrix

            }
        }

        referenceOne.close();
    }
    else cout << "unable to open file.\n";
    return 0;
}

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
};
