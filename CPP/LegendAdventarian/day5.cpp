#include <fstream> //for reading file i think
#include <sstream> //idk maybe reading lines
#include <string>  //i need to include strings?
#include <iostream> //for cout
#include <vector>
using namespace std; //very useful
ifstream infile("ressource/day5.txt");

string split_piles(string pile){
    int pos;
    string stlist;
    for(int i=1;i<pile.length();i+=4){
        stlist.push_back(pile[i]);
    }
    return stlist;
}
vector<string> populate(string templist, vector<string> stack){
    for(int i=0; i<templist.size();i++){
        if(templist[i]!=' '){
            stack[i].insert(0,1,templist[i]);
        }
    }
    return stack;
}

string part1(){
    string line;
    string trash;
    string str;
    vector<string> stacklist(9,"");
    string tempstr;
    int first=0;
    int nbboxes;
    int initpile;
    int endpile;
    while (getline(infile, line))
    { 
        if(line.empty() || line[1]=='1'){first=1;}
        else{
            if(first==0){
                tempstr=split_piles(line);
                stacklist=populate(tempstr, stacklist);
            }
            else{
                istringstream iss(line);
                iss >>trash;
                iss >>nbboxes;
                iss >>trash;
                iss>>initpile;
                iss >> trash;
                iss>>endpile;
                for(int i=0;i<nbboxes;i++){
                    tempstr=stacklist[initpile-1].back();
                    stacklist[initpile-1].pop_back();
                    stacklist[endpile-1].append(tempstr);   
                }
            }         
        }
    }
    for(int i=0; i<stacklist.size(); i++){
        str+=stacklist[i].back();
    }
    return str;
}

string part2(){
    ifstream infile("ressource/day5.txt");
    string line;
    string trash;
    string str;
    vector<string> stacklist(9,"");
    string tempstr;
    int first=0;
    int nbboxes;
    int initpile;
    int endpile;
    while (getline(infile, line))
    { 
        if(line.empty() || line[1]=='1'){first=1;}
        else{
            if(first==0){
                tempstr=split_piles(line);
                stacklist=populate(tempstr, stacklist);
            }
            else{
                istringstream iss(line);
                iss >>trash;
                iss >>nbboxes;
                iss >>trash;
                iss>>initpile;
                iss >> trash;
                iss>>endpile;
                tempstr=stacklist[initpile-1].substr(stacklist[initpile-1].length()-nbboxes);
                stacklist[endpile-1]+=tempstr;
                for(int i=0;i<nbboxes;i++){
                    stacklist[initpile-1].pop_back(); 
                }
            }         
        }
    }
    for(int i=0; i<stacklist.size(); i++){
        str+=stacklist[i].back();
    }
    return str;
}

int main()
{
    string res = part1();
    cout << "The top of the piles are : " << res << "\n";
    string res2 = part2();
    cout << "The top of piles with the new crane is : " << res2 << "\n";
    infile.close();
    return 0;
}