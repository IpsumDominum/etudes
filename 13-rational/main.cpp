#include "Integer.h"
#include "Rational.h"
#include <iostream>
using namespace cosc326;
int main(){
    Rational rat1 = Rational(Integer("1"),Integer("5"));
    Rational rat2 = Rational(Integer("4"),Integer("7"));
    Rational rat3 = Rational("-4/-2");
    rat1 *=rat2;


}
