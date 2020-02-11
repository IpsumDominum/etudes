#include "Integer.h"
#include <vector>
#include <sstream>
#include <string>
#include <stdexcept>
#include <ctype.h>
namespace cosc326 {

    Integer::Integer() {
        data.push_back(0);
        length = 1;
        sign = 1;
    }
    Integer::Integer(const Integer& i) {
        data = i.data;
        sign = i.sign;
        length = i.length;
        *this = +*this;
    }
    Integer::Integer(const std::string& s) {
        std::istringstream iss(s);
        char c;
        length = 0;
        iss>>c;
        if((c=='-')||(c=='+')){
            if(c=='-'){
                sign = -1;
            }else{
                sign = 1;
            }
        }else{
            sign = 1;
            length +=1;
            data.insert(data.begin(),c-'0');
        }
        while(iss>>c){
            if(isdigit(c)){
                length +=1;
                data.insert(data.begin(),c-'0');
            }else{
                std::cerr<<"Invalid Inputs for Integer Initialization : "<<s<<"\n";
                exit(EXIT_FAILURE);
            }
        }
        if(length==0){
            std::cerr<<"Invalid Inputs for Integer Initialization : "<<s<<"\n";
            exit(EXIT_FAILURE);
        }
        *this = +*this;
    }
    Integer::~Integer() {
    }
    Integer& Integer::operator=(const Integer& i) {
        data = i.data;
        sign = i.sign;
        length = i.length;
        return *this;
    }
    Integer& Integer::operator-() {
        sign *= -1;
        *this = +*this;
        return *this;
    }
    Integer& Integer::operator+()  {
        bool start = true;
        int newlength = length;
        for(int idx=length-1;idx>=0;idx--){
            if(start){
                if(data[idx]==0){
                    newlength-=1;
                }else{
                    start = false;
                }
            }
        }
        if(start){
            /*If no other numbers are found, the number is zero*/
            sign = 1;
            return *this;
        }else{
        length = newlength;
        }
        return *this;
    }
    Integer& Integer::operator+=(const Integer& i) {
        /*
            Four cases: 1 + -2  -> 1-=2
                        1 + 2  good
                        -1 + -2 -> good (sign=-1)
                        -1 + 2 -> 2-=1
        */
        if(sign==1 & i.sign==-1){
            Integer rhs = Integer(i);
            rhs.sign = 1;
            *this -=rhs;
            *this = +*this;
            return *this;
        }
        if(sign==-1 & i.sign==1){
            Integer rhs = Integer(i);
            sign = 1;
            return rhs -= *this;
        }
        if(sign==-1 & i.sign==-1){
            sign = -1;
        }
        if(sign==1 & i.sign==1){
            sign = 1;
        }
        int largerLength;
        int res;
        int carry = 0;
        std::vector<int> result;
        if(i.length > length){
            largerLength = i.length;
        }else{
            largerLength = length;
        }
        for(int idx=0;idx<largerLength;idx++){
            res = carry;
            carry = 0;
            if(idx< length){
                res += data[idx];
            }
            if(idx<i.length){
                res += i.data[idx];
                if(res >=10){
                    carry = std::to_string(res)[0] - '0';
                    res  = std::to_string(res)[1] -'0';
                }
            }
            result.push_back(res);
        }
        length = largerLength;
        if(carry!=0){
            result.push_back(carry);
            length +=1;
        }
        data = result;
        *this = +*this;
        return *this;
    }
    Integer& Integer::operator-=(const Integer& i) {
        /*
            Four cases: 1 - -2  -> 1+=2
                        1 - 2  good
                        -1 - -2 -> good (inverted, 2-1)
                        -1 - 2 -> -(1+=2)
        */
        if(sign==1 & i.sign==-1){
            Integer rhs = Integer(i);
            rhs.sign = 1;
            *this +=rhs;
            return *this;
        }
        if(sign ==-1 & i.sign==1){
            Integer rhs = Integer(i);
            sign = 1;
            *this +=rhs;
            sign = -1;
            return *this;
        }        
        int largerLength;
        int res = 0;
        int carry = 0;
        int next_carry = 0;       
        bool leftabove;
        std::vector<int> result;        
        Integer top = Integer();
        Integer bottom = Integer();         
        if(i.sign==-1 & sign ==-1){
            /*Inverted, rhs = this lhs = i*/
            if(Integer(*this)<i){
                /*this is larger numerically, if it is less, in the both
                negative case, this should then be on top*/
                top.data = data;
                top.length = length;
                top.sign = sign;
                bottom.length = i.length;
                bottom.data = i.data;
                bottom.sign = i.sign;
                sign = -1;
            }else{
                top.data = i.data;
                top.length = i.length;
                top.sign = i.sign;
                bottom.length = length;
                bottom.data = data;
                bottom.sign = sign;
                sign = 1;
            }
        }
        if(i.sign==1 & sign ==1){
            if(Integer(*this)>i){
                /*this is larger numerically, if it is less, in the both
                negative case, this should then be on top*/
                top.data = data;
                top.length = length;
                top.sign = sign;
                bottom.length = i.length;
                bottom.data = i.data;
                bottom.sign = i.sign;
                sign = 1;
            }else{
                top.data = i.data;
                top.length = i.length;
                top.sign = i.sign;
                bottom.length = length;
                bottom.data = data;
                bottom.sign = sign;
                sign = -1;
            }
        }
        largerLength = top.length;
        for(int idx=0;idx<top.length;idx++){
            res = 0;          
            next_carry = 0;              
            if(idx<top.length){
                /*if both length has not been exceeded*/
                if(idx<bottom.length){
                    /*set carry and borrow if top data is smaller*/
                    if((top.data[idx]+carry)<bottom.data[idx]){                        
                        res = (top.data[idx]+carry+10) - bottom.data[idx];
                        next_carry = -1;
                    }else{
                        /*Otherwise get result*/
                        res = top.data[idx]+carry - bottom.data[idx];
                    }
                }else{
                    /*otherwise drop down*/
                    res = top.data[idx]+carry;
                }
            }
            carry = next_carry;
            result.push_back(res);
        }
        length = largerLength;
        data = result;
        *this = +*this;
        return *this;
    }
    
    Integer& Integer::operator*=(const Integer& i) {
        int res = 0;
        int carry = 0;
        sign = sign * i.sign;
        std::vector<int> result;
        result.resize(length+i.length);
        std::fill(result.begin(),result.end(),0);
        for(int jdx=0;jdx<i.length;jdx++){
            for(int idx=0;idx<length;idx++){
                res = 0;
                res += data[idx] * i.data[jdx] + result[idx+jdx];
                result[idx+jdx] = res;
            }
        }
        for(int ids=0;ids<length+i.length;ids++){
            result[ids] += carry;
            if(result[ids]>=10){
                carry = std::to_string(result[ids])[0] - '0';
                res  = std::to_string(result[ids])[1] -'0';
                result[ids] = res;
            }else{
                carry = 0;
            }
        }
        data = result;
        length = length + i.length;
        *this = +*this;
        return *this;
    }
    
    Integer& Integer::operator/=(const Integer& i) {
        if(i==Integer("0")){
            std::cerr<<"Dvision by Zero"<<"\n";
            Integer error = Integer("-1");
            data = error.data;
            sign = error.sign;
            length = error.length;
            return *this;
        }
        Integer Q = Integer("0");
        Q.sign = 1;
        Integer R = Integer(*this);
        R.sign = 1;
        Integer D = Integer(i);
        D.sign = 1;

        while(true){
            Q = Q +Integer("1");
            R = R -D;
            if(R<=D){
                if(R==D){
                    Q = Q +Integer("1");
                    break;
                }
                break;
            }

        }
        sign = sign * i.sign;
        data = Q.data;
        length = Q.length;
        *this = +*this;
        return *this;
    }

    Integer& Integer::operator%=(const Integer& i) {
        if(i==Integer("0")){
            std::cerr<<"Dvision by Zero"<<"\n";
            Integer error = Integer("-1");
            data = error.data;
            sign = error.sign;
            length = error.length;
            return *this;
        }
        sign = sign * i.sign;
        Integer Q = Integer("0");
        Integer R = Integer(*this);
        Integer D = Integer(i);
        while(R>=D){
            Q = Q+Integer("1");
            R = R - D;
        }
        data = R.data;
        length = R.length;
        *this = +*this;
        return *this;
    }

    Integer operator+(const Integer& lhs,const Integer& rhs) {
        Integer res = Integer(lhs);
        Integer opthing = Integer(rhs);
        res += opthing;
        return res;
    }

    Integer operator-(const Integer& lhs, const Integer& rhs) {
        Integer res = Integer(lhs);
        Integer opthing = Integer(rhs);
        res -= opthing;
        return res;
    }

    Integer operator*(const Integer& lhs, const Integer& rhs) {
        Integer res = Integer(lhs);
        Integer opthing = Integer(rhs);
        res *= opthing;
        return res;
    }

    Integer operator/(const Integer& lhs, const Integer& rhs) {
        Integer res = Integer(lhs);
        Integer opthing = Integer(rhs);
        res /= opthing;
        return res;
    }

    Integer operator%(const Integer& lhs, const Integer& rhs) {
        Integer res = Integer(lhs);
        Integer opthing = Integer(rhs);
        res %= opthing;
        return res;
    }
    std::ostream& operator<<(std::ostream& os, const Integer& i) {
        if(i.sign<0){
            os<<"-";
        }
        for(int idx=i.length-1;idx>=0;idx--){
            os<<std::to_string(i.data[idx]);
        }
        return os;
    }

    std::istream& operator>>(std::istream& is, Integer& i) {
        char c;
        std::string inputString = "";
        while(is>>c){
            inputString += c;
        }
        i = Integer(inputString);
        return is;
    }

    bool operator<(const Integer& lhs, const Integer& rhs) {
        if(lhs.sign <rhs.sign){
            //first check sign cases
            return true;
        }else if(lhs.sign>rhs.sign){
            //first check sign cases
            return false;
        }else{
            if(lhs.length<rhs.length){
                if(lhs.sign>0){
                   return true;
                }else{
                    return false;
                }
            }else if(lhs.length>rhs.length){
                if(lhs.sign>0){
                   return false;
                }else{
                   return true;
                }
            }else{
                for(int idx = lhs.length-1;idx>=0;idx--){
                    if(lhs.data[idx]<rhs.data[idx]){
                        return true;
                    }else if(lhs.data[idx]>rhs.data[idx]){
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool operator> (const Integer& lhs, const Integer& rhs) {
        if(lhs<rhs){
            return false;
        }else{
            return true;
        }
    }
    bool operator<=(const Integer& lhs, const Integer& rhs) {
        if(lhs<rhs || lhs==rhs){
            return true;
        }else{
            return false;
        }
    }

    bool operator>=(const Integer& lhs, const Integer& rhs) {
        if(lhs>rhs || lhs==rhs){
            return true;
        }else{
            return false;
        }
    }

    bool operator==(const Integer& lhs, const Integer& rhs) {
        if(lhs.sign !=rhs.sign){
            return false;
        }else if(lhs.length!=rhs.length){
            return false;
        }else{
            for(int idx = lhs.length-1;idx>=0;idx--){
                if(lhs.data[idx]!=rhs.data[idx]){
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Integer& lhs, const Integer& rhs) {
        return !(lhs==rhs);
    }
    Integer gcd(const Integer& a, const Integer& b) {
        Integer t;
        Integer acopy = Integer(a);
        Integer bcopy = Integer(b);
        while (bcopy != Integer("0"))
            {
                t = bcopy;
                bcopy = acopy % bcopy;
                acopy = t;
            }
        return acopy;
    }

}
