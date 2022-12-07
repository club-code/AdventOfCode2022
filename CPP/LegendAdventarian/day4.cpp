#include <fstream> //for reading file i think
#include <sstream> //idk maybe reading lines
#include <string>  //i need to include strings?
#include <iostream> //for cout
#include <map>
#include <list>
using namespace std; //very useful
ifstream infile("ressource/day4.txt");

int part1(){
    string line;
    string elf1;
    string elf2;
    int elf1_low;
    int elf1_high;
    int elf2_low;
    int elf2_high;
    string trash;
    int size;
    int ctr=0;
    int pos;
    while (getline(infile, line))
    { 
        istringstream iss(line);
        iss >>trash;
        pos=trash.find(',');
        elf1=trash.substr(0,pos);
        elf2=trash.substr(pos+1,trash.length());
        //elf1
        pos=elf1.find('-');
        elf1_low=stoi(elf1.substr(0, pos));
        elf1_high=stoi(elf1.substr(pos+1,elf1.length()));
        //elf2
        pos=elf2.find('-');
        elf2_low=stoi(elf2.substr(0, pos));
        elf2_high=stoi(elf2.substr(pos+1,elf2.length()));
        if(elf1_low==elf2_low || elf1_high == elf2_high){
            ctr+=1;
        }
        else if(elf1_low<elf2_low){
            if(elf1_high>=elf2_high){
                ctr+=1;
            }
        }
        else if(elf2_high>=elf1_high){//elf2 has lower low value, check higher high val
            ctr+=1;    
        }
    }
    return ctr;
}

int part2(){
    ifstream infile("ressource/day4.txt");
    string line;
    string elf1;
    string elf2;
    int elf1_low;
    int elf1_high;
    int elf2_low;
    int elf2_high;
    string trash;
    int size;
    int ctr=0;
    int pos;
    while (getline(infile, line))
    { 
        istringstream iss(line);
        iss >>trash;
        pos=trash.find(',');
        elf1=trash.substr(0,pos);
        elf2=trash.substr(pos+1,trash.length());
        //elf1
        pos=elf1.find('-');
        elf1_low=stoi(elf1.substr(0, pos));
        elf1_high=stoi(elf1.substr(pos+1,elf1.length()));
        //elf2
        pos=elf2.find('-');
        elf2_low=stoi(elf2.substr(0, pos));
        elf2_high=stoi(elf2.substr(pos+1,elf2.length()));
        if(elf1_low==elf2_low || elf1_high == elf2_high){
            ctr+=1;
        }
        else if(elf1_low<elf2_low){
            if(elf1_high>=elf2_low){
                ctr+=1;
            }
        }
        else if(elf2_high>=elf1_low){
            ctr+=1;    
        }
    }
    return ctr;
}

int main()
{
    int res = part1();
    cout << "The number of embedded zones is : " << res << "\n";
    int res2 = part2();
    cout << "The number of covered zones is : " << res2 << "\n";
    infile.close();
    return 0;
}