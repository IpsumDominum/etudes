#include <iostream>
#include <vector>
#include <sstream>
/*gcd is implemented a iterative euclidean algorithm,code inspired by 
https://www.geeksforgeeks.org/c-program-find-gcd-hcf-two-numbers/*/
uint64_t gcd(uint64_t a, uint64_t b) ;
int main(int argc,const char* argv[]){

    std::uint64_t k;
    std::uint64_t n;
    std::string line;
    std::getline(std::cin, line);
    char* cha;
    std::istringstream iss(line);
    iss>>cha;
    n =std::atol(cha);
    iss>>cha;
    k = std::atol(cha);
    std::uint64_t remain_factor; // set the value for n-k
    std::vector<uint64_t> arrayk;
    std::vector<uint64_t> arrayn;
    std::uint64_t result = 1;
    std::uint64_t temptemp;
    std::uint64_t gcd_temp;
    if(k  >  n){
        std::cout<<"k is larger then n! not valid";
        return EXIT_FAILURE;
    }
    /*choose which ever one is alrger to factorise out, in the first step*/
    if(k>=(n-k)){
        remain_factor = (n-k);
    }else{
        remain_factor = k;
    }
    for(int i =0;i<remain_factor;i++){
        arrayk.push_back(remain_factor-i);
        arrayn.push_back(n-i);
    }

    for(int i=0;i<remain_factor;i++){
        /*for each in the remain Ns,
          we see if it can be factored by the arrayks*/
        for(int j=0;j<remain_factor;j++){
            gcd_temp = gcd(arrayn[i],arrayk[j]);
            if(gcd_temp!=1){
                arrayk[j] = arrayk[j] /gcd_temp;
                arrayn[i] = arrayn[i] /gcd_temp;
            }
        }
        result *= arrayn[i];
    }
    std::cout<<result<<"\n";
    exit(0);
}
uint64_t gcd(uint64_t a, uint64_t b) 
{
    uint64_t t;
    while (b != 0)
        {
            t = b;
            b = a % b;
            a = t;
        }
    return a;
}
