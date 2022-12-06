#include <fstream> //for reading file i think
#include <sstream> //idk maybe reading lines
#include <string>  //i need to include strings?
#include <iostream> //for cout
#include <map>
#include <list>
using namespace std; //very useful
ifstream infile("ressource/day3.txt");
int priority(char c){
    //if lowercase -96
    //if uppercase -38
    if(c<'a'){
        //c is uppercase
        return c-38;
    }
    else{
        return c-96;
    }
    return 0;
}
int part1(){
    string line;
    string pack;
    string pouch1;
    string pouch2;
    int size;
    int ctr=0;
    while (getline(infile, line))
    { 
        istringstream iss(line);
        iss >> pack;
        size = pack.size();
        pouch1=pack.substr(0,size/2);
        pouch2=pack.substr((size/2),size);
        //got the two pouches
        for(int i = 0 ; i < pouch1.length() ; i++){
            for(int j=0; j<pouch2.length();j++){
                if(pouch1[i]==pouch2[j]){
                    ctr+=priority(pouch1[i]);
                    goto end;
                }
            }
        }
    end:
        continue;
    }
    return ctr;
}

int main()
{
    int res = part1();
    cout << "The priority level is : " << res << "\n";
    //part2(); 3by3
    return 0;
}