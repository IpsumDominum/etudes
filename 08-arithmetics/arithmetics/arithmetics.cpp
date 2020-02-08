#include <iostream>
#include <sstream>
#include <vector>
#include <string>
void left_traverse(std::vector<int> nums,int target,int cur_res,int depth,int max_depth,std::string opstring);
void norm_traverse(std::vector<int> nums,int target,int cur_res,int buffer,int depth,int max_depth,std::string opstring);
int main(){
    //Read programme inputs
    std::string line;
    bool expectingNums = true;
    std::vector<int> nums;
    std::getline(std::cin, line);
    char* cha;
    int count=0;
    std::istringstream iss(line);
    while (iss >> cha){
        count +=1;
        nums.push_back(atoi(cha));
    }
    std::getline(std::cin, line);
    std::istringstream iss_two(line);
    int target;
    char* mode;
    iss_two>> cha;
    target = atoi(cha);
    iss_two>> cha;
    mode = cha;
    //According to inputs, check the combs, either left or normal
    if(strcmp(mode,"L")==0){
        left_traverse(nums,target,nums[0],0,count,"");
        std::cout<<"L " + std::to_string(target) +" impossible"<<"\n";
    }else if(strcmp(mode,"N")==0){
        norm_traverse(nums,target,0,1,0,count,"");
        std::cout<<"N " + std::to_string(target) +" impossible"<<"\n";
    }
}
void left_traverse(std::vector<int> nums,int target, int cur_res,int depth,int max_depth,std::string opstring){
    if(depth==max_depth-1){
        left_traverse(nums,target,cur_res,depth+1,max_depth,opstring + std::to_string(nums[depth]));    
    }else if(depth==max_depth){
        if(cur_res==target){
            std::cout<<"L " + std::to_string(target) +" "+ opstring<<"\n";
            exit(0);
        }
        return;
    }else{
        if(cur_res>=target){
            return;
        }
    //traverse left branch
    left_traverse(nums,target,cur_res +nums[depth+1],depth+1,max_depth,opstring + std::to_string(nums[depth])+" + ");    
    //traverse right branch
    left_traverse(nums,target,cur_res * nums[depth+1],depth+1,max_depth,opstring+std::to_string(nums[depth])+" * ");
    }
}

void norm_traverse(std::vector<int> nums,int target,int cur_res,int buffer,int depth,int max_depth,std::string opstring){
    if(depth==max_depth-1){
        norm_traverse(nums,target,cur_res+(buffer*nums[depth]),1,depth+1,max_depth,opstring +std::to_string(nums[depth]));    
    }else if(depth==max_depth){
        if(cur_res==target){
            std::cout<<"N " + std::to_string(target) +" "+ opstring<<"\n";
            exit(0);
        }
        return;
    }else{
        if(cur_res>=target){
            return;
        }
    //traverse left branch,if the next operation is +, evaluate buffer
    norm_traverse(nums,target,cur_res+(buffer*nums[depth]),1,depth+1,max_depth,opstring +std::to_string(nums[depth])+ " + ");    
    //traverse right branch,if the next operation is *, put in buffer
    norm_traverse(nums,target,cur_res,buffer*nums[depth],depth+1,max_depth,opstring+std::to_string(nums[depth])+" * ");
    }
}






