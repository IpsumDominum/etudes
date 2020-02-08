#include "Integer.h"
#include "Rational.h"
#include <iostream>
using namespace cosc326;
int main(){
    Integer thing = Integer("300");    
    Integer thingn = Integer("-300");
    Integer res;
    /* addition cases
    300 + 300
    300 + -300
    -300 + 300
    -300 +-300*/
    thing +=thing;
    std::cout<<thing<<"\n";

}
