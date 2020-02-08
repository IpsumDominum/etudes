#include <iostream>
#include <sstream>
#include <map>
#include <queue>
void print_matrix(int **adj_matrix,int count);
void try_combs(int n, int row_keep[], int i,int **adj_matrix,std::map<int,char> reverseKeyLookup) ;
int main(){    
    std::string line;
    bool expectingNums = true;
    std::getline(std::cin, line);
    std::map<char,int> keyLookup;
    std::map<int,char> reverseKeyLookup;
    char cha;
    int count=0;
    std::istringstream iss(line);
    while (iss >> cha){
        keyLookup[cha] = count;
        reverseKeyLookup[count] = cha;
        count+=1;
    }
    /*build adjacancy matrix */
    int **adj_matrix = new int*[count];
    int *row_keep = static_cast<int*>(calloc(count,sizeof(int)));
    for (int i=0; i<count; i++) {
        adj_matrix[i] = new int[count];
    }
    
    int i,j;
    for(i = 0;i<count;i++){
        for(j=0;j<count;j++){
            if(i==j){
                adj_matrix[i][j] = 1;
            }else{
                adj_matrix[i][j] = 0;
            }
        }
    }
    /*Still building the adjacancy matrix */
    std::getline(std::cin, line);
    std::istringstream iss_two(line);
    std::string connection;
    while (iss_two>> connection){
        adj_matrix[keyLookup[connection[1]]][keyLookup[connection[0]]] =1;
    }
    /*Chen's Algorithm
      Naively, try all the combinations
      Check if column is odd or even,
      if even, combination has failed.
      Otherwise continue, if all odd,
      then solution is found.
      If all combinations has checked,
      then no solutions is to be found.
    */
    try_combs(count,row_keep,0,adj_matrix,reverseKeyLookup);
    std::cout<<"No Solutions!"<<"\n";
    exit(1);
}


void print_matrix(int **adj_matrix,int count){
    std::cout<<"\n";
    for(int i = 0;i<count;i++){
        for(int j=0;j<count;j++){
            std::cout<<adj_matrix[i][j]<<" ";
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
}
void try_combs(int n, int row_keep[], int i,int **adj_matrix,std::map<int,char> reverseKeyLookup) 
{

    /*End case, check if the column sums are odd or even*/
    if (i == n) {
        int row_sum;
        for(int i = 0;i<n;i++){
            row_sum=0;
            for(int j=0;j<n;j++){
                if(row_keep[j]==1){
                   row_sum+= adj_matrix[i][j];
                }
            }
            if(row_sum%2==0){
                return;
            }
        }
        /*Found a solution, if all columns are odd*/
        std::cout<<"found! Here are the steps: 0 means off, 1 means on"<<"\n";
        for(int i=0;i<n;i++){
            std::cout<<row_keep[i]<<" ";
        }
        std::cout<<"\n";
        std::cout<<"solution is:";
        for(int i=0;i<n;i++){
            if(row_keep[i]==1){
                std::cout<<reverseKeyLookup[i];
            }
        }
        std::cout<<"\n";
        exit(1);
    }
    /*Build the combination tree recursively*/
    /*branch one*/
    row_keep[i] = 0; 
    try_combs(n, row_keep, i + 1,adj_matrix,reverseKeyLookup); 
    /*branch two*/  
    row_keep[i] = 1; 
    try_combs(n, row_keep, i + 1,adj_matrix,reverseKeyLookup); 
} 
