#include "Rational.h"
#include "Integer.h"
#include <sstream>
namespace cosc326 {
	Rational::Rational() {
        /*default integer
         */
            this->num = Integer();
            this->denom = Integer();
            this->ratsign = 1;
	}
    int Rational::getRatSign(){
        return this->ratsign;
    }
    void Rational::setRatSign(int ratsignthing){
        this->ratsign = ratsignthing;
    }
    Integer Rational::getNum(){
        return this->num;
    }
    void Rational::setNum(Integer numthing){
        this->num = numthing;
    }
    Integer Rational::getDenom(){
        return denom;
    }
    void Rational::setDenom(Integer denomthing){
        this->denom = denomthing;
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
            this->ratsign = w.getSign() * b.getSign() * a.getSign();
            if(founddot){
                a += w *b;				
            }			
            this->num = a;
            this->denom = b;			
            this->num.setSign(1);
            this->denom.setSign(1);
            *this = +*this;
	}
    Rational::Rational(const Rational& r) {
        /*copies*/
        *this = r;
    }
    Rational::Rational(const Integer& a) {
        /*Becomes a*/
        this->num = Integer(a);
        this->denom = Integer("1");			
        this->ratsign = num.getSign();
        num.setSign(1);
        denom.setSign(1);
        *this = +*this;
    }
    Rational::Rational(const Integer& a, const Integer& b) {
        /*Becomes a/b*/
        this->num = Integer(a);
        this->denom = Integer(b);
        this->ratsign = this->num.getSign() * this->denom.getSign();
        this->num.setSign(1);
        this->denom.setSign(1);        
        *this = +*this;
    }
    Rational::Rational(const Integer& a, const Integer& b, const Integer& c) {
        /*Becomes a+b/c*/
        this->num = Integer(a) + Integer(b);		
        this->denom = Integer(c);		
        this->ratsign = this->num.getSign() * this->denom.getSign();
        this->num.setSign(1);
        this->denom.setSign(1);
        *this = +*this;
    }
    Rational::~Rational() {
        /*destructor skipped*/
    }
    Rational& Rational::operator=(const Rational& r) {
        /*asthis->signment operator*/
        Rational t = Rational(r);
        this->num = t.getNum();
        this->denom = t.getDenom();
        this->ratsign = t.getRatSign();
        return *this;
    }
    Rational Rational::operator-(){
        this->ratsign = -1 *this->ratsign;
        return Rational(*this);
    }
    Rational Rational::operator+(){
        Integer gcdres = Integer("0");
        this->num.setSign(1);
        this->denom.setSign(1);
        /*Normalize Rational This->Number here */
        if(this->num==Integer("0")){
            //this->denom = Integer("0");
            this->ratsign = 1;
            return Rational(*this);
        }
        /*Normalize the this->numerators and this->denomenators*/
        while(true){
            gcdres = gcd(this->num,this->denom);
            if(gcdres==Integer("1")){
                break;
            }
            this->num = this->num/gcdres;
            this->denom = this->denom/ gcdres;
        }
        return Rational(*this);
    }
    Rational& Rational::operator+=(const Rational& pr) {
            /* 4 cases:
               a + b = a +b 
               a + -b = a -b
               -a + b = b -a
               -a + -b = -(a+b)
            */
            Rational r = Rational(pr);
            if(this->ratsign==1 ){			
                if(r.getRatSign() ==1){
                    /*pass, a+b=a+b*/
                }else if(r.getRatSign()==-1){
                    /*send to a-=b*/
                    Rational rhs = Rational(r);
                    rhs.getRatSign() = 1;				
                    *this -= rhs;
                    return *this;
                }
            }else if(this->ratsign==-1){
                if(r.getRatSign() ==1){
                    /*send to b-=a*/
                    Rational rhs = Rational(r);
                    this->ratsign = 1;				
                    rhs -= *this;
                    *this = Rational(rhs);
                    return *this;
                }else if(r.getRatSign()==-1){
                    Rational rhs = Rational(r);
                    rhs.getRatSign() = 1;
                    *this = -(*this + rhs);
                    return *this;
                }
            }
            Rational rhs = Rational(r);
            this->denom *= rhs.getRatSign();
            /*normalize this->denom*/
            this->num *= rhs.getRatSign();
            rhs.getRatSign() *= rhs.getRatSign();
            this->num += rhs.getRatSign();
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
        if(this->ratsign==1 ){			
            if(r.getRatSign() ==1){
                /*pass, a-b*/
            }else if(r.getRatSign()==-1){
                /*send to a + b*/
                *this = *this + r;
                return *this;
            }
        }else if(this->ratsign==-1){
            if(r.getRatSign() ==1){
                /*send -(a+b)*/
                *this = -(*this + r);
                return *this;
            }else if(r.getRatSign()==-1){
                /*send to b-a*/
                Rational rhs = Rational(r);
                this->ratsign = 1;				
                rhs -= *this;
                *this = Rational(rhs);
                return *this;
            }
        }		
		Rational rhs = Rational(r);
		this->denom *= rhs.getRatSign();
		/*normalize this->denom*/
		this->num *= rhs.getRatSign();
		rhs.getRatSign() *= rhs.getRatSign();
		this->num -= rhs.getRatSign();		
		*this = +*this;
		return *this;
    }
    Rational& Rational::operator*=(const Rational& r) {
        /*multiply this->numerators and this->denomenators*/
        this->ratsign = this->ratsign * r.getRatSign();
        this->num *= r.getRatSign();
        this->denom *=r.getRatSign();
        *this = +*this;
        return *this;
    }
    Rational& Rational::operator/=(const Rational& r) {
        /*multiply the inverse of the second this->number, by this->numerator->this->denomenator, this->denomenator->this->numerator*/
        this->ratsign = this->ratsign * r.getRatSign();
        this->num *= r.getRatSign();
        this->denom *= r.getRatSign();
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
        if(i.getRatSign()==Integer("0")){
            os<<"0";
            return os;
        }else if(i.getRatSign()==i.getRatSign()){
            os<<"1";
            return os;
        }
        if(i.getRatSign()<0){
            os<<"-";
        }
        if(i.getRatSign()==Integer("1")){
            os<<i.getRatSign();
            return os;
        }
        if(i.getRatSign()>i.getRatSign()){
            os<<i.getRatSign()/i.getRatSign()<<"."<<i.getRatSign()%i.getRatSign()<<"/"<<i.getRatSign();
        }else if(i.getRatSign()==i.getRatSign()){
            os<<"1";
        }else{
            os<<i.getRatSign()<<"/"<<i.getRatSign();
        }
        return os;
    }
    std::istream& operator>>(std::istream& is, Rational& i) {
        //asthis->signment through string stream
        char c;
        std::string result = "";
        while(is>>c){
            result +=c;
        }
        i = Rational(result);
        return is;
    }
    bool operator<(const Rational& lhs, const Rational& rhs) {
        //Compares this->denomenator and this->numerator
        Integer compA = lhs.getRatSign() * rhs.getRatSign();
        Integer compB = rhs.getRatSign() * lhs.getRatSign();
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
        if(lhs.setRatSign(=Integer("0") & rhs.getRatSign()==Integer("0")){
            return true;
        }
        if(lhs.getRatSign()== rhs.getRatSign() & lhs.setRatSign(= rhs.getRatSign()){
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
