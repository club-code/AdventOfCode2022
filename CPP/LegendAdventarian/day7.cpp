#include <fstream> //for reading file i think
#include <sstream> //idk maybe reading lines
#include <string>  //i need to include strings?
#include <iostream> //for cout
#include <vector>
#include <memory>
using namespace std; //very useful

struct tree{
    struct tree *father;
    string name;
    int fileweight;
    vector<unique_ptr<tree>> children;
};


struct tree* setup(struct tree* t, string name){
    auto newtree=make_unique<tree>();
    newtree->name=name;
    newtree->father=t;
    newtree->fileweight=0;
    t->children.push_back(move(newtree));
    return t;
}

struct tree* search_child(struct tree* my, string name){
    for(auto &child : my->children){
        if(child->name==name){
            return child.get();
        }
    }
    throw("Child not found");
    return my;
}

int recursive_weighcount(tree* curdir){
    if(!curdir->children.empty()){//im taking the bet that it works
        for(auto &child : curdir->children){//after getting the weight from all children...
            curdir->fileweight+=recursive_weighcount(child.get());
        }
    }
    return curdir->fileweight;//...give weight to parent
}

int recursive_sum(tree* curdir){
    int sum=0;
    if(!curdir->children.empty()){//im taking the bet that it works
        for(auto &child : curdir->children){//add the sum from children
            sum+=recursive_sum(child.get());
        }
    }
    if(curdir->fileweight<100000){//add our weight if it respects specifications
        sum+=curdir->fileweight;
    }
    return sum;
}

int recursive_searchfree(tree* curdir, int neededspace){
    int val=0;
    int tempval;
    if(curdir->fileweight>neededspace){//add our weight if it respects specifications
        val=curdir->fileweight;
        if(!curdir->children.empty()){
            for(auto &child : curdir->children){//check in the children
                tempval=recursive_searchfree(child.get(),neededspace);
                if(tempval<val && tempval>=neededspace){
                    val=tempval;
                }
            }
        }
    }
    else{//not big, enough dont check children
        return 0;
    }
    return val;
}

unique_ptr<tree> init(){
    ifstream infile("ressource/day7.txt");
    struct tree* curdir;
    string line;
    string trash;
    string cmd;
    string dir;
    int weight=0;
    auto root=make_unique<tree>();
    root->father=NULL;
    root->name="root";
    root->fileweight=0;
    curdir=root.get();
    int sum=0;
    while (getline(infile, line))
    { 
        //cout << line << " currently in " << curdir->name << "\n";
        istringstream iss(line);
        if(line[0]=='$'){//process command
            iss >>trash;
            iss >>cmd;
            if(cmd=="cd"){
                iss>>dir;
                if(dir=="/"){
                    curdir=root.get();
                }
                else if(dir==".."){
                    curdir=curdir->father;
                    //cout << curdir->name << " the curdir name\n";
                }
                else{
                    curdir=search_child(curdir,dir);
                }
            }
        }
        else if(line[0]=='d'){//dir
            iss>>trash;
            iss>>dir;
            //cout << "added dir " << dir << "\n";
            curdir=setup(curdir,dir);//mmake child and add it
        }
        else{//file
            iss>>weight;
            curdir->fileweight+=weight;
            //cout << curdir->fileweight << " current weight for dir " << curdir->name <<"\n";
        }
    }
    infile.close();
    return root;
}

int part1(){
    unique_ptr<tree> root=init();
    root->fileweight= recursive_weighcount(root.get());
    int sum=recursive_sum(root.get());
    return sum;
}

int part2(){
    unique_ptr<tree> root=init();
    root->fileweight=recursive_weighcount(root.get());
    int neededspace=30000000-(70000000-root->fileweight);
    int size=recursive_searchfree(root.get(), neededspace);
    return size;
}

int main()
{
    int res = part1();
    cout << "The sum of files weighs " << res << "\n";
    int res2 = part2();
    cout << "The smallest file to delete weighs : " << res2 << "\n";
    return 0;
}