#include <fstream> //for reading file i think
#include <sstream> //idk maybe reading lines
#include <string>  //i need to include strings?
#include <iostream> //for cout
#include <map>
using namespace std; //very useful
ifstream infile("ressource/day2.txt");

int part1(){
    map<string,int> rpsmap={{"A",1},{"B",2},{"C",3},{"X",1},{"Y",2},{"Z",3}};
    string line;
    string elf;
    string me;
    int ctr=0;
    while (getline(infile, line)){
        istringstream iss(line);
        iss >> elf;
        iss >> me;
        ctr+=rpsmap[me];
        if(rpsmap[me]==rpsmap[elf]){
            //egalité
            ctr+=3;
        }
        if(rpsmap[me]-rpsmap[elf]==1 || rpsmap[me]-rpsmap[elf]==-2){//trust me this works
            //gagné
            ctr+=6;
        }
    }
    return ctr;
}

int part2(){
    ifstream infile("ressource/day2.txt"); //reopen
    map<string,int> rpsmap={{"A",1},{"B",2},{"C",3},{"X",0},{"Y",3},{"Z",6}};
    //Rock, paper, scissors, lose, tie, win
    string line;
    string elf;
    string me;
    int ctr=0;
    while (getline(infile, line)){
        istringstream iss(line);
        iss >> elf;
        iss >> me;
        ctr+=rpsmap[me]; //win lose counter
        
        if(rpsmap[me]==3){
            //egaliser => faire pareil
            ctr+=rpsmap[elf];
        }
        else if(rpsmap[me]==0){
            //gagner
            if(rpsmap[elf]==1){
                ctr+=3;
            }
            else{
                ctr+=rpsmap[elf]-1;
            }
        }
        else{
            //perdre
            if(rpsmap[elf]==3){
                ctr+=1;
            }
            else{
                ctr+=rpsmap[elf]+1;
            }
        }
    }
    return ctr;
}


int main()
{
    int result = part1();
    cout << "Part 1 result : " << result << "\n";
    result = part2();
    cout << "Part 2 result : " << result << "\n";
    infile.close();
    return 0;
}