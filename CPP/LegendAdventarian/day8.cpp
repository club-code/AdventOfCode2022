#include <fstream> //for reading file i think
#include <sstream> //idk maybe reading lines
#include <string>  //i need to include strings?
#include <iostream> //for cout
#include <vector>
using namespace std; //very useful
ifstream infile("ressource/day8.txt");

int checkiftaller(string line, int pos){
    int ctr=1;
    for(int i=pos-1;i>=0;i--){
        if(line[pos]<=line[i]){
            ctr=0;
            break;//not visible from this side
        }
    }
    if(ctr==1){
        return 1;//visible!
    }
    ctr=1;
    for(int i=pos+1;i<line.size();i++){
        if(line[pos]<=line[i]){
            ctr=0;
            break;
        }
    }
    return ctr;
}

int checkincolumn(vector<string> treelist,int i,int j){
    int ctr=1;
    for(int k=i-1; k>=0; k--){
        if(treelist.at(i)[j]<=treelist.at(k)[j]){
            ctr=0;
            break;
        }
    }
    if(ctr==1){
        return 1;//visible!
    }
    ctr=1;
    for(int k=i+1;k<treelist.size();k++){
        if(treelist.at(i)[j]<=treelist.at(k)[j]){
            ctr=0;
            break;
        }
    }
    return ctr;
}

int counttrees(vector<string> treelist,int pos1,int pos2){
    string line=treelist.at(pos1);
    int right=0;
    int left=0;
    int bottom=0;
    int top=0;
    for(int i=pos2-1;i>=0;i--){//left side
        left+=1;
        if(line[pos2]<=line[i]){
            break;//bigger tree
        }
    }
    for(int i=pos2+1;i<line.size();i++){//right side
        right+=1;
        if(line[pos2]<=line[i]){
            break;
        }
    }
    for(int k=pos1-1; k>=0; k--){
        top+=1;
        if(treelist.at(pos1)[pos2]<=treelist.at(k)[pos2]){//top
            break;
        }
    }
    for(int k=pos1+1;k<treelist.size();k++){
        bottom+=1;
        if(treelist.at(pos1)[pos2]<=treelist.at(k)[pos2]){//bottom
            break;
        }
    }
    return left * right * top * bottom;
}



int part1(){
    string line;
    vector<string> treelist;
    int ctr=0;
    while (getline(infile, line))
    { 
        treelist.push_back(line);//populate the map       
    }
    ctr=2*treelist.at(1).size()+2*treelist.size()-4; //border trees are visible
    for(int i=1; i<treelist.size()-1; i++){
        for(int j=1; j<treelist.at(1).size()-1; j++){
            int check=checkiftaller(treelist.at(i), j);
            if(check==0){//check in column
                check=checkincolumn(treelist,i,j);
            }
            ctr+=check;//adds 1 if tree is visible
        }
    }
    return ctr;
}

int part2(){
    ifstream infile("ressource/day8.txt");
    string line;
    vector<string> treelist;
    int ctr=0;
    while (getline(infile, line))
    { 
        treelist.push_back(line);//populate the map       
    }
    for(int i=1; i<treelist.size()-1; i++){
        for(int j=1; j<treelist.at(1).size()-1; j++){
            int val=counttrees(treelist,i,j);
            if(val>=ctr){
                ctr=val;
            }
        }
    }
    return ctr;
}

int main()
{
    int res = part1();
    cout << "The number of visible trees are : " << res << "\n";
    int res2 = part2();
    cout << "The scenic view has a value of : " << res2 << "\n";
    infile.close();
    return 0;
}