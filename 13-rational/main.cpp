#include "Integer.h"
#include "Rational.h"
#include <iostream>
using namespace cosc326;
int main(){
    Integer thing = Integer("19");    
    Integer thingn = Integer("-203");
    Integer thing3 = Integer("1");
    Integer res = thing /thing3;
    /* addition cases
    300 + 300
    300 + -300
    -300 + 300
    -300 +-300*/
        std::cout<<res<<"\n";

}
