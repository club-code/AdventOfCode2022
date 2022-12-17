#include <fstream> //for reading file i think
#include <sstream> //idk maybe reading lines
#include <string>  //i need to include strings?
#include <iostream> //for cout
#include <map>
#include <list>
using namespace std; //very useful
ifstream infile("ressource/day6.txt");

int part1(){
    string line;
    getline(infile, line);
    string tmp;
    int pos;
    int ctr=0;
    for(int j=0; j<line.length(); j++){
        char ch = line[j];
        ctr+=1; //this is the nth char
        pos=tmp.find(ch);
        if(pos!=string::npos){
            int rmnb=tmp.size()-pos;
            for(int i=0; i<rmnb; i++){ //remove all until duplicate char
                tmp.pop_back();
            }
            tmp.insert(0,1,ch); //insert our char
        }
        else{
            tmp.insert(0,1,ch);
            if(tmp.size()==4){
                return ctr;
            }
        }
    }
    return ctr;
}

int part2(){
    ifstream infile("ressource/day6.txt");
    string line;
    getline(infile, line);
    string tmp;
    int pos;
    int ctr=0;
    for(int j=0; j<line.length(); j++){
        char ch = line[j];
        pos=tmp.find(ch);
        if(pos!=string::npos){//if char is found in string
            int rmnb=tmp.size()-pos;
            for(int i=0; i<rmnb; i++){ //remove all until duplicate char
                tmp.pop_back();
            }
            tmp.insert(0,1,ch); //insert our char
        }
        else{
            tmp.insert(0,1,ch);
            if(tmp.size()==14){
                return j+1;
            }
        }
    }
    return ctr;
}

int main()
{
    int res = part1();
    cout << "The beginning is at : " << res << "\n";
    int res2 = part2();
    cout << "The beggining of the message  is at : " << res2 << "\n";
    infile.close();
    return 0;
}