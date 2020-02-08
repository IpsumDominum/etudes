#include "Integer.h"
#include <vector>
#include <sstream>
#include <string>
namespace cosc326 {

    Integer::Integer() {
        data.push_back(0);
    }
    Integer::Integer(const Integer& i) {
        data = i.data;
        sign = i.sign;
        length = i.length;
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
            length +=1;
            data.insert(data.begin(),c-'0');
        }
    }
    Integer::~Integer() {
    }
    Integer& Integer::operator=(const Integer& i) {
        return *this;
    }
    Integer& Integer::operator-() {
        sign *= -1;
        return *this;
    }
    Integer& Integer::operator+()  {
        return *this;
    }
    Integer& Integer::operator+=(const Integer& i) {
        /*
            Four cases: 1 + -2  -> 1-=2
                        1 + 2  good
                        -1 + -2 -> good (sign=-1)
                        -1 + 2 -> 2-=1
        */
        if(sign==1 & sign==-1){
            Integer rhs = Integer(i);
            rhs.sign = 1;
            *this -=rhs;
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
        return *this;
    }
    
    Integer& Integer::operator*=(const Integer& i) {
        return *this;
    }
    
    Integer& Integer::operator/=(const Integer& i) {
        return *this;
    }

    Integer& Integer::operator%=(const Integer& i) {
        return *this;
    }

    Integer operator+(const Integer& lhs,const Integer& rhs) {
        Integer(lhs) += Integer(rhs);
        return lhs;
    }

    Integer operator-(const Integer& lhs, const Integer& rhs) {
        Integer(lhs) -= Integer(rhs);
        return lhs;
    }

    Integer operator*(const Integer& lhs, const Integer& rhs) {
        return lhs;
    }

    Integer operator/(const Integer& lhs, const Integer& rhs) {
        return lhs;
    }

    Integer operator%(const Integer& lhs, const Integer& rhs) {
        return lhs;
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
        return true;
    }

    bool operator>=(const Integer& lhs, const Integer& rhs) {
        return true;
    }

    bool operator==(const Integer& lhs, const Integer& rhs) {
        return true;
    }

    bool operator!=(const Integer& lhs, const Integer& rhs) {
        return true;
    }


    Integer gcd(const Integer& a, const Integer& b) {
        return a;
    }

}
