#include "Rational.h"
#include "Integer.h"
#include <sstream>
namespace cosc326 {
	Rational::Rational() {
        /*default integer
         */
            num = Integer();
            denom = Integer();
			ratsign = 1;
	}
        Rational::Rational(const std::string& str) {
            /* Three cases :
               a
               a/b
               w.a/b
            */
            std::istringstream iss(str);
            bool expectingFirst = true;			
            bool founddot = false;
            Integer w = Integer("0");
            Integer a = Integer("1");
            Integer b = Integer("1");
            std::string buffer =  "";
            char c;			
            while(iss>>c){							
                if(expectingFirst){
                    if(c=='.'){
                        /*if a dot is found*/
                        w = Integer(buffer);
                        expectingFirst = false;
                        founddot = true;
                        buffer = "";
                    }else if(c=='/'){
                        /*otherwise if separator is found*/
                        a = Integer(buffer);
                        expectingFirst = false;
                        buffer = "";
                    }else{
                        buffer += c;
                    }
                }else{
                    /*otherwise if separator is found*/
                    if(c=='/'){
                        a = Integer(buffer);
                        buffer = "";						
                    }else{
                        buffer +=c;
                    }
                }
            }
            b = Integer(buffer);
            ratsign = w.sign * b.sign * a.sign;
            if(founddot){
                a += w *b;				
            }			
            num = a;
            denom = b;			
            num.sign = 1;
            denom.sign = 1;
            *this = +*this;
	}
    Rational::Rational(const Rational& r) {
        /*copies*/
        *this = r;
    }
    Rational::Rational(const Integer& a) {
        /*Becomes a*/
        num = Integer(a);
        denom = Integer("1");			
        ratsign = num.sign;
        num.sign = 1;
        denom.sign = 1;
        *this = +*this;
    }
    Rational::Rational(const Integer& a, const Integer& b) {
        /*Becomes a/b*/
        num = Integer(a);
        denom = Integer(b);
        ratsign = num.sign * denom.sign;
        num.sign = 1;
        denom.sign = 1;        
        *this = +*this;
    }
    Rational::Rational(const Integer& a, const Integer& b, const Integer& c) {
        /*Becomes a+b/c*/
        num = Integer(a) + Integer(b);		
        denom = Integer(c);		
        ratsign = num.sign * denom.sign;
        num.sign = 1;
        denom.sign = 1;
        *this = +*this;
    }
    Rational::~Rational() {
        /*destructor skipped*/
    }
    Rational& Rational::operator=(const Rational& r) {
        /*assignment operator*/
        num = r.num;
        denom = r.denom;
        ratsign = r.ratsign;
        return *this;
    }
    Rational Rational::operator-(){
        ratsign = -1 *ratsign;
        return Rational(*this);
    }
    Rational Rational::operator+(){
        Integer gcdres = Integer("0");
        num.sign = 1;
        denom.sign = 1;
        /*Normalize Rational Number here */
        if(num==Integer("0")){
            //denom = Integer("0");
            ratsign = 1;
            return Rational(*this);
        }
        /*Normalize the numerators and denomenators*/
        while(true){
            gcdres = gcd(num,denom);
            if(gcdres==Integer("1")){
                break;
            }
            num = num/gcdres;
            denom = denom/ gcdres;
        }
        return Rational(*this);
    }
    Rational& Rational::operator+=(const Rational& r) {
            /* 4 cases:
               a + b = a +b 
               a + -b = a -b
               -a + b = b -a
               -a + -b = -(a+b)
            */
            if(ratsign==1 ){			
                if(r.ratsign ==1){
                    /*pass, a+b=a+b*/
                }else if(r.ratsign==-1){
                    /*send to a-=b*/
                    Rational rhs = Rational(r);
                    rhs.ratsign = 1;				
                    *this -= rhs;
                    return *this;
                }
            }else if(ratsign==-1){
                if(r.ratsign ==1){
                    /*send to b-=a*/
                    Rational rhs = Rational(r);
                    ratsign = 1;				
                    rhs -= *this;
                    *this = Rational(rhs);
                    return *this;
                }else if(r.ratsign==-1){
                    Rational rhs = Rational(r);
                    rhs.ratsign = 1;
                    *this = -(*this + rhs);
                    return *this;
                }
            }
            Rational rhs = Rational(r);
            denom *= rhs.denom;
            /*normalize denom*/
            num *= rhs.denom;
            rhs.num *= rhs.denom;
            num += rhs.num;
            *this = +*this;
            return *this;
	}
    Rational& Rational::operator-=(const Rational& r) {
        /* 4 cases:
           a - b  =  a -b 
           a - -b = a + b
           -a - b = -(a + b)
           -a - -b = b-a
        */
        if(ratsign==1 ){			
            if(r.ratsign ==1){
                /*pass, a-b*/
            }else if(r.ratsign==-1){
                /*send to a + b*/
                *this = *this + r;
                return *this;
            }
        }else if(ratsign==-1){
            if(r.ratsign ==1){
                /*send -(a+b)*/
                *this = -(*this + r);
                return *this;
            }else if(r.ratsign==-1){
                /*send to b-a*/
                Rational rhs = Rational(r);
                ratsign = 1;				
                rhs -= *this;
                *this = Rational(rhs);
                return *this;
            }
        }		
		Rational rhs = Rational(r);
		denom *= rhs.denom;
		/*normalize denom*/
		num *= rhs.denom;
		rhs.num *= rhs.denom;
		num -= rhs.num;		
		*this = +*this;
		return *this;
    }
    Rational& Rational::operator*=(const Rational& r) {
        /*multiply numerators and denomenators*/
        ratsign = ratsign * r.ratsign;
        num *= r.num;
        denom *=r.denom;
        *this = +*this;
        return *this;
    }
    Rational& Rational::operator/=(const Rational& r) {
        /*multiply the inverse of the second number, by numerator->denomenator, denomenator->numerator*/
        ratsign = ratsign * r.ratsign;
        num *= r.denom;
        denom *= r.num;
        return *this;
    }
    Rational operator+(const Rational& lhs, const Rational& rhs) {
        /*refer to other function*/
        Rational res = Rational(lhs);
        Rational opthing = Rational(rhs);		
        res += opthing;
        return res;
    }
    Rational operator-(const Rational& lhs, const Rational& rhs) {
        /*refer to other function*/
        Rational res = Rational(lhs);
        Rational opthing = Rational(rhs);
        res -= opthing;
        return res;
    }
    Rational operator*(const Rational& lhs, const Rational& rhs) {
        /*refer to other function*/
        Rational res = Rational(lhs);
        Rational opthing = Rational(rhs);
        res *= opthing;
        return res;
    }
    Rational operator/(const Rational& lhs, const Rational& rhs) {
        /*refer to other function*/
        Rational res = Rational(lhs);
        Rational opthing = Rational(rhs);
        res /= opthing;
        return res;
    }
    std::ostream& operator<<(std::ostream& os, const Rational& i) {
        //Streaming operator
        if(i.num==Integer("0")){
            os<<"0";
            return os;
        }else if(i.num==i.denom){
            os<<"1";
            return os;
        }
        if(i.ratsign<0){
            os<<"-";
        }
        if(i.denom==Integer("1")){
            os<<i.num;
            return os;
        }
        if(i.num>i.denom){
            os<<i.num/i.denom<<"."<<i.num%i.denom<<"/"<<i.denom;
        }else if(i.num==i.denom){
            os<<"1";
        }else{
            os<<i.num<<"/"<<i.denom;
        }
        return os;
    }
    std::istream& operator>>(std::istream& is, Rational& i) {
        //assignment through string stream
        char c;
        std::string result = "";
        while(is>>c){
            result +=c;
        }
        i = Rational(result);
        return is;
    }
    bool operator<(const Rational& lhs, const Rational& rhs) {
        //Compares denomenator and numerator
        Integer compA = lhs.num * rhs.denom;
        Integer compB = rhs.num * lhs.denom;
        if(compA <compB){
            return true;
        }else{
            return false;
        }
    }
    bool operator> (const Rational& lhs, const Rational& rhs) {
        //refer to other function
        return !(lhs<rhs);
    }
    bool operator<=(const Rational& lhs, const Rational& rhs) {
        //refer to other function
        return (lhs<rhs || lhs==rhs);
    }
    bool operator>=(const Rational& lhs, const Rational& rhs) {
        //refer to other function
        return (lhs>rhs || lhs==rhs);
    }
    
    bool operator==(const Rational& lhs, const Rational& rhs) {
        //Check for both things
        if(lhs.num ==Integer("0") & rhs.num==Integer("0")){
            return true;
        }
        if(lhs.num== rhs.num & lhs.denom == rhs.denom){
            return true;
        }else{
            return false;
        }
    }
    
    bool operator!=(const Rational& lhs, const Rational& rhs) {
        //refer to other
        return !(lhs==rhs);
    }
}
