#include "Integer.h"
#include "Rational.h"
#include <iostream>
using namespace cosc326;
int main(){
    //Rational rat1 = Rational(Integer("1230920392039"),Integer("520392039209"));
    //Rational rat2 = Rational(Integer("4023920392039"),Integer("723092039203"));
    //rat1 /=rat2;
    //std::cout<<rat1<<"\n";
    cosc326::Integer ai("2452345345234123123178");
    cosc326::Integer bi("23459023850983290542");
    std::cout<<Rational(ai,bi)<<"\n";
    //std::cout<<(bi/Integer("2"))<<"\n";
    //    Integer a("500");
    //    Integer b("2");
    //    std::cout<<(a/b)<<"\n";
    Integer a("922337");
    Integer b("42949");
    std::cout << a * b << std::endl;
    //std::cout<<Rational(ai,bi)<<"\n";

}
