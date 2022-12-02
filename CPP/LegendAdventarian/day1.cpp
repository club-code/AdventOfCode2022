#include <fstream> //for reading file i think
#include <sstream> //idk maybe reading lines
#include <string>  //i need to include strings?
#include <iostream> //for cout
using namespace std; //very useful
ifstream infile("input.txt");

int part1(){
    string line;
    int a;
    int ctr=0;
    int max_ctr=0;
    while (getline(infile, line))
    {
        if(line.empty()){
            if(ctr>max_ctr){
                max_ctr=ctr;
            }
            ctr=0;
        }
        else{
            istringstream iss(line); //read input string lineth line
            iss >> a;//put the line in a (as an int)
            ctr+=a;
        }
    }
    cout << max_ctr << " is the max calorie number\n";
    return 0;
}

int part2(){
    ifstream infile("input.txt");
    string line;
    int a;
    int ctr=0;
    int top1=0;
    int top2=0;
    int top3=0;
    while (getline(infile, line))
    {
        if(line.empty()){
            if(ctr>top1){//this is ugly, should maybe do a list idk
                top3=top2;
                top2=top1;
                top1=ctr;
            }
            else if(ctr>top2){
                top3=top2;
                top2=ctr;
            }
            else if(ctr>top3){
                top3=ctr;
            }
            ctr=0;
        }
        else{
            istringstream iss(line);
            iss >> a;
            ctr+=a;
        }
    }
    cout << top1 + top2 + top3 << " is the  sum of top3's calorie number\n";
    return 0;
}

int main()
{
    part1();
    part2();
    return 0;
}