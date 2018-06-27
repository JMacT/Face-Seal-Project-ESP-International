#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string search;
    string line;
    ifstream referenceOne;
    referenceOne.open ("as568.txt");
    size_t pos;

    cout << "What dash size are you looking for?\n";
    cin >> search;

    if (referenceOne.is_open() ) {
        while( getline(referenceOne, line) ){ //pulls in one line from as568.txt
            pos = line.find(search); //search for
            if(pos!=string::npos){
                cout << line;
            }
        }
        referenceOne.close();
    }
    else cout << "unable to open file.\n";
    return 0;
}
