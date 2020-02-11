#include "Rational.h"
#include "Integer.h"
#include <sstream>
namespace cosc326 {
	Rational::Rational() {
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
						a = Integer(buffer);
						expectingFirst = false;
						buffer = "";
					}else{
						buffer += c;
					}
				}else{
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
			*this = r;
	}
	Rational::Rational(const Integer& a) {
            num = Integer(a);
            denom = Integer("1");			
			ratsign = num.sign;
			num.sign = 1;
			denom.sign = 1;
			*this = +*this;
	}
	Rational::Rational(const Integer& a, const Integer& b) {
            num = Integer(a);
            denom = Integer(b);
			ratsign = num.sign * denom.sign;
			num.sign = 1;
			denom.sign = 1;
			*this = +*this;
	}
    Rational::Rational(const Integer& a, const Integer& b, const Integer& c) {
        num = Integer(a) + Integer(b);		
        denom = Integer(c);		
		ratsign = num.sign * denom.sign;
		num.sign = 1;
		denom.sign = 1;
		*this = +*this;
    }
    Rational::~Rational() {
	}
    Rational& Rational::operator=(const Rational& r) {		
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
		Integer gcdres;
		/*Normalize Rational Number here */
		if(num==Integer("0")){
			//denom = Integer("0");
			ratsign = 1;
			return Rational(*this);
		}
		while((gcd(num,denom))!= Integer("1")){
			gcdres = gcd(num,denom);
			num /= gcdres;
			denom /= gcdres;
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
		ratsign = ratsign * r.ratsign;
		num *= r.num;
		denom *=r.denom;
		*this = +*this;
		return *this;
	}
	Rational& Rational::operator/=(const Rational& r) {
		ratsign = ratsign * r.ratsign;
		num *= r.denom;
		denom *= r.num;
		return *this;
	}
	Rational operator+(const Rational& lhs, const Rational& rhs) {
		Rational res = Rational(lhs);
        Rational opthing = Rational(rhs);		
        res += opthing;
		return res;
	}
	Rational operator-(const Rational& lhs, const Rational& rhs) {
		Rational res = Rational(lhs);
        Rational opthing = Rational(rhs);
        res -= opthing;
		return res;
	}
	Rational operator*(const Rational& lhs, const Rational& rhs) {
		Rational res = Rational(lhs);
        Rational opthing = Rational(rhs);
        res *= opthing;
		return res;
	}
	Rational operator/(const Rational& lhs, const Rational& rhs) {
		Rational res = Rational(lhs);
        Rational opthing = Rational(rhs);
        res /= opthing;
		return res;
	}
	std::ostream& operator<<(std::ostream& os, const Rational& i) {
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
		char c;
		std::string result = "";
		while(is>>c){
			result +=c;
		}
		i = Rational(result);
		return is;
	}
	bool operator<(const Rational& lhs, const Rational& rhs) {
		Integer compA = lhs.num * rhs.denom;
		Integer compB = rhs.num * lhs.denom;
		if(compA <compB){
			return true;
		}else{
			return false;
		}
	}
	bool operator> (const Rational& lhs, const Rational& rhs) {
		return !(lhs<rhs);
	}
	bool operator<=(const Rational& lhs, const Rational& rhs) {
		return (lhs<rhs || lhs==rhs);
	}
	bool operator>=(const Rational& lhs, const Rational& rhs) {
		return (lhs>rhs || lhs==rhs);
	}

	bool operator==(const Rational& lhs, const Rational& rhs) {
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
		return !(lhs==rhs);
	}
}
