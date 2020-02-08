#include "Integer.h"
#include "Rational.h"
#include <iostream>
using namespace cosc326;
int main(){
    Integer thing = Integer("4023");
    Integer thing2 = Integer("6028");
    thing += thing2;
    std::cout<<thing<<"\n";
}
