#include "Integer.h"
#include "Rational.h"
#include <iostream>
using namespace cosc326;
int main(){
    Integer thing = Integer("2039");    
    Integer thingn = Integer("-203");
    Integer thing3 = Integer("-200");
    Integer res;
    /* addition cases
    300 + 300
    300 + -300
    -300 + 300
    -300 +-300*/
    thing -= thing3;
    std::cout<<thing<<"\n";

}
