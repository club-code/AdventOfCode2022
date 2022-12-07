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

int part2(){
    ifstream infile("ressource/day3.txt");
    string line;
    string pack;
    string bag1;
    string bag2;
    string bag3;
    int size;
    int ctr=0;
    int teamctr=0;
    string team[]={"","",""};
    while (getline(infile, line))
    { 
        istringstream iss(line);
        iss >> pack;
        team[teamctr]=pack;
        teamctr+=1;
        if(teamctr==3){
            teamctr=0;
            for(int i = 0 ; i < team[0].length() ; i++){
                for(int j=0; j<team[1].length();j++){
                    if(team[0][i]==team[1][j]){
                        //found a match, check the last one
                        for(int k=0;k<team[2].length();k++){
                            if(team[0][i]==team[2][k]){
                                ctr+=priority(team[0][i]);
                                goto end2;
                            }
                        }
                        
                    }
                }
            }
        }
    end2:
        continue;
    }
    return ctr;
}

int main()
{
    int res = part1();
    cout << "The priority level is : " << res << "\n";
    int res2 = part2();
    cout << "The priority level for badges is : " << res2 << "\n";
    infile.close();
    return 0;
}