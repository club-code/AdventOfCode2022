#include <fstream> //for reading file i think
#include <sstream> //idk maybe reading lines
#include <string>  //i need to include strings?
#include <iostream> //for cout
#include <vector>
#include <algorithm>
using namespace std; //very useful
ifstream infile("ressource/day9.txt");



int part1(){
    string line;
    vector<string> position;
    int head[2]={0,0};
    int tail[2]={0,0};
    int ctr=0;
    char dir;
    int steps;
    while (getline(infile, line))
    { 
        istringstream iss(line);   
        iss >> dir;
        iss >> steps;
        cout << dir << " and " << steps << "\n";
        for(int i=0; i<steps;i++){
            switch(dir){
                case 'R':
                    head[0]++;
                    break;
                case 'L':
                    head[0]--;
                    break;
                case 'U':
                    head[1]++;
                    break;
                case 'D':
                    head[1]--;
                    break;
                default:
                    break;        
            }
            if(abs(head[0]-tail[0])>1){ 
                if(head[0]>tail[0]){
                    tail[0]++;
                }
                else{
                    tail[0]--;
                }
                if(head[1]!=tail[1]){//far diagonal
                    if(head[1]>tail[1]){
                        tail[1]++;
                    }
                    else{
                        tail[1]--;
                    }
                }
            }
            else if(abs(head[1]-tail[1]>1)){
                if(head[1]>tail[1]){
                    tail[1]++;
                }
                else{
                    
                    tail[1]--;
                }
                if(head[0]!=tail[0]){//far diagonal
                    if(head[0]>tail[0]){
                        tail[0]++;
                    }
                    else{
                        tail[0]--;
                    }
                }
            } 
            string pos= to_string(tail[0]) + to_string(tail[1]);
            if(find(position.begin(),position.end(),pos)==position.end()){
                position.push_back(pos);
            }
            cout << "tail at " << tail[0] <<","<< tail[1] << "\n";
            cout << position.size() << "\n";
        } 
    }
    return position.size();
}

int part2(){
    ifstream infile("ressource/day8.txt");
    string line;
    vector<string> treelist;
    int ctr=0;
    return ctr;
}

int main()
{
    int res = part1();
    cout << "The number of used spaces is : " << res << "\n";
    //int res2 = part2();
    //cout << "The scenic view has a value of : " << res2 << "\n";
    infile.close();
    return 0;
}