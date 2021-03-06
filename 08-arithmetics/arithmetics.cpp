#include <iostream>
#include <sstream>
#include <vector>
#include <string>
void left_traverse(std::vector<int> nums,int64_t target,int cur_res,int depth,int max_depth,std::string opstring);
void norm_traverse(std::vector<int> nums,int64_t target,int cur_res,int buffer,int depth,int max_depth,std::string opstring);
void checkmax(std::vector<int> nums,int64_t target, std::string mode,int depth);
void checkmin(std::vector<int> nums,int64_t target, std::string mode,int depth);
int main(){
    //Read programme inputs
    /*Programme input format should be:

      numbers, separated by white space, \n
      target mode
      Example:
      1 1 2 3 1 3 2 1 4 1 2
      14 N
    */
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
    int64_t target;
    char mode;
    iss_two>> cha;
    target = atol(cha);
    iss_two>> cha;
    mode = *cha;
    //According to inputs, check the combs, either left or normal
    if(mode=='L'){
        /*Check minimum and maximum*/
        checkmin(nums,target,"L",count);
        checkmax(nums,target,"L",count);
        /*Traverse*/
        left_traverse(nums,target,nums[0],0,count,"");
        std::cout<<"L " + std::to_string(target) +" impossible"<<"\n";
    }else if(mode=='N'){
        /*Check minimum and maximum*/
        checkmin(nums,target,"N",count);
        checkmax(nums,target,"N",count);
         /*Traverse*/
        norm_traverse(nums,target,0,1,0,count,"");
        std::cout<<"N " + std::to_string(target) +" impossible"<<"\n";
    }
}
void left_traverse(std::vector<int> nums,int64_t target, int cur_res,int depth,int max_depth,std::string opstring){
    /*Norm traverse:

      @nums ->the values of the numbers, in a vector
      @cur_res ->keep track of current result
      @depth ->current depth
      @maxdepth ->size of the nums
      @opstring ->a string we build up, of all the operations operated.
      How it works:
      if depth ==max depth-1, we don't branch, and just evaluate the buffer.
      if depth ==max depth, we check if the result is == target, if so, output result and opstring
      otherise we branch down two different operations.
      The + operator means to add the next number to the current result,
      The * operator means to multiply the next number to the current result.
    */
    if(depth==max_depth-1){
        left_traverse(nums,target,cur_res,depth+1,max_depth,opstring + std::to_string(nums[depth]));    
    }else if(depth==max_depth){
        if(cur_res==target){
            std::cout<<"L " + std::to_string(target) +" "+ opstring<<"\n";
            exit(0);
        }
        return;
    }else{
        if(cur_res>target || cur_res <0){
            return;
        }
    //traverse left branch
    left_traverse(nums,target,cur_res +nums[depth+1],depth+1,max_depth,opstring + std::to_string(nums[depth])+" + ");    
    //traverse right branch
    left_traverse(nums,target,cur_res *nums[depth+1],depth+1,max_depth,opstring+std::to_string(nums[depth])+" * ");
    }
}
void norm_traverse(std::vector<int> nums,int64_t target,int cur_res,int buffer,int depth,int max_depth,std::string opstring){
    /*Norm traverse:

      @nums ->the values of the numbers, in a vector
      @cur_res ->keep track of current result
      @buffer ->buffer used to track multiplication
      @depth ->current depth
      @maxdepth ->size of the nums
      @opstring ->a string we build up, of all the operations operated.
      How it works:
      if depth ==max depth-1, we don't branch, and just evaluate the buffer.
      if depth ==max depth, we check if the result is == target, if so, output result and opstring
      otherise we branch down two different operations.
      The + operation means to evaluate the buffer, and set buffer to 0
      otherwise the * operation means to multiply the next item to the buffer.
    */
    if(depth==max_depth-1){
        norm_traverse(nums,target,cur_res+(buffer*nums[depth]),1,depth+1,max_depth,opstring +std::to_string(nums[depth]));
    }else if(depth==max_depth){
        if(cur_res==target){
            std::cout<<"N " + std::to_string(target) +" "+ opstring<<"\n";
            exit(0);
        }
        return;
    }else{
        if(cur_res>target || cur_res <0){
            return;
        }
    //traverse left branch,if the next operation is +, evaluate buffer
    norm_traverse(nums,target,cur_res+(buffer*nums[depth]),1,depth+1,max_depth,opstring +std::to_string(nums[depth])+ " + ");    
    //traverse right branch,if the next operation is *, put in buffer
    norm_traverse(nums,target,cur_res,buffer*nums[depth],depth+1,max_depth,opstring+std::to_string(nums[depth])+" * ");
    }
}
void checkmin(std::vector<int> nums,int64_t target, std::string mode,int depth){
    /*Checkmin
      @nums ->the values of the numbers, in a vector
      @target ->target
      @mode ->mode of operation
      @depth ->current depth
      @opstring ->a string we build up, of all the operations operated.
      How it works:
      L:
          Add all numbers, except for one, multiply ones.
      N:
          same as L
    */
      
    int min = 0;
    for(int idx=0;idx<depth;idx++){
        /*if find a one, multiply by it, otherwise add numbers*/
        if(nums[idx]==1){
            /*pass*/
        }else{
            if(min==0){
                min = nums[idx];
            }else{
                min += nums[idx];
            }
        }
    }
    //If min < target, the target is unreachable, exit
    if(target < min){
        std::cout<<mode+" " + std::to_string(target) +" impossible"<<"\n";
        exit(EXIT_FAILURE);
    }
}
void checkmax(std::vector<int> nums,int64_t target, std::string mode,int depth){
    /*Checkmin
      @nums ->the values of the numbers, in a vector
      @target ->target
      @mode ->mode of operation
      @depth ->current depth
      @opstring ->a string we build up, of all the operations operated.
      How it works:
      L:
          Multiply all numbers, except for one, add ones.
      N:
          First create buffers
          mbuffer ->buffer of multiples of numbers which are not one
          onebuffer ->buffers of numbers of ones, in between chunks of numbers which are not one
          Then evaluate, for each in the one buffer,
          if it has a neighbour, (corresponding mbuffer[ids] and mbuffer[ids+1]
          check if it's neighbours multiplied together is larger than it(the number of ones in this interval)
          if so, then multiply those ones, otherwise add.
    */
    int64_t max;
    bool lastisone;
    if(mode=="L"){
        /*Left check,
          if one,add,
          otherwise multiply
        */
        max = 0;
        for(int idx=0;idx<depth;idx++){
            //if one, add
            if(nums[idx]==1){
                max +=1;
            }else{
                if(max==0){
                    max = nums[idx];
                }else{
                    if(max==1){
                        max += nums[idx];
                    }
                    max *= nums[idx];
                }
            }
        }
    }else if(mode=="N"){
        /*
          Checks by chunks

          first build arrays of buffers.
          example 1 1 1 4 1 1 2 1 1
              ->    3 , 2 , 2  (onebuffer)
              ->    4 , 2      (mbuffer)
              Where one buffer documents the numbers of ones
              and mbuffer documents the mulitplication results, of clusters of non-'1' numbers
          Then iterate through onebuffer
          each time checking, if neighbours exist (mbuffer[ids] and mbuffer[ids]), then
          check, if everything on the right and everything on the left multiplied together is
          larger than the numbers of ones, if so, multiply those ones together,
          otherwise add them.
        */
        max = 0;
        std::vector<int64_t> mbuffer;
        std::vector<int64_t> onebuffer;
        char state = 'm';/*either waiting for a "1" or some other number  'o' == waiting for one, 'm' waiting for multiplication*/
        int64_t tempbuffer = 0;
        int64_t temponecount = 0;
        int64_t mbuffercount = 0;
        int64_t onebuffercount = 0;
        bool started = false;
        for(int idx=0;idx<depth;idx++){
            if(!started){
                if(nums[idx]!=1){
                    /*start putting things in buffers,
                      once the first non-1 number is found
                    */
                    if(tempbuffer==0){
                        tempbuffer = nums[idx];
                    }else{
                        tempbuffer *= nums[idx];
                    }
                    started = true;
                }else{
                    /*Otherwise just keep adding these ones*/
                    max +=1;
                }
            }else{
                if(nums[idx]!=1){
                    if(state=='o'){
                        onebuffer.push_back(temponecount);
                        onebuffercount +=1;
                        temponecount = 0;
                        state = 'm';
                    }
                    if(tempbuffer==0){
                        tempbuffer = nums[idx];
                    }else{
                        tempbuffer *= nums[idx];
                    }
                }else{
                    if(state=='m'){
                        mbuffer.push_back(tempbuffer);
                        mbuffercount +=1;
                        tempbuffer = 0;
                        state = 'o';
                    }
                    temponecount +=1;
                }
            }
        }
        if(state=='o'){
            /*if in the end, we are looking at ones,add the remaining ones*/
            onebuffer.push_back(temponecount);
            onebuffercount +=1;
        }else if(state=='m'){
            mbuffer.push_back(tempbuffer);
            mbuffercount +=1;
        }
        int64_t left = 1;
        int64_t right = 1;
        int64_t tempmax = 0;
        int64_t seriouslyanotherbufferhowmanyconfusingbuffernamesdoyouneed = 0;
        if(mbuffercount >=1){
            tempmax = mbuffer[0];
            for(int ids=0;ids<onebuffercount;ids++){
                /*for each in one buffer, look at it's neighbours*/
                /*look left*/
                if(seriouslyanotherbufferhowmanyconfusingbuffernamesdoyouneed==0){
                    seriouslyanotherbufferhowmanyconfusingbuffernamesdoyouneed = mbuffer[ids];
                }else{
                    seriouslyanotherbufferhowmanyconfusingbuffernamesdoyouneed *= mbuffer[ids];
                }
                left = seriouslyanotherbufferhowmanyconfusingbuffernamesdoyouneed;
                /*look right*/
                if(mbuffercount> ids+1){
                    for(int idm=ids+1;idm<mbuffercount;idm++){
                        right *= mbuffer[idm];
                    }
                }else{
                    /*other wise we have trailing ones, add all of those ones and terminate*/
                    tempmax += onebuffer[ids];
                    break;
                }
                /*if left * right is smaller or equal to those ones, we add those ones */
                if((left * right)<=onebuffer[ids]){
                    /*we add*/
                    tempmax += mbuffer[ids+1];
                    tempmax += onebuffer[ids];
                    /*we set the seriouslyanotherbufferhowmanyconfusingbuffernamesdoyouneed value to
                      0*/
                    seriouslyanotherbufferhowmanyconfusingbuffernamesdoyouneed = 0;
                }else{
                    /*we multiply */
                    tempmax *= mbuffer[ids+1];
                }
            }
            max += tempmax;
        }else{
            /*pass, the max is all those added ones */   
        }
    }
    //If min < target, the target is unreachable, exit
        if(target > max & max>=0){
            std::cout<<mode+" " + std::to_string(target) +" impossible"<<"\n";
            exit(EXIT_FAILURE);
        }
}
