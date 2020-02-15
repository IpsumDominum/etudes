git ad#include "Integer.h"
#include <vector>
#include <sstream>
#include <string>
#include <stdexcept>
#include <ctype.h>

namespace cosc326 {
    
    Integer::Integer() {
        /*Create default integer*/
        data.push_back(0);
        length = 1;
        sign = 1;
    }
    Integer::Integer(const Integer& i) {
        /*Copy the Integer in the parameter*/
        data = i.data;
        sign = i.sign;
        length = i.length;
        *this = +*this;
    }
    Integer::Integer(const std::string& s) {
        /*Create an Integer through parameter string
          check first if first character is "-" or "+"
         */
        std::istringstream iss(s);
        char c;
        length = 0;
        iss>>c;
        /*check if first character is - or +*/
        if((c=='-')||(c=='+')){
            /*if so, set the sign accordingly*/
            if(c=='-'){
                sign = -1;
            }else{
                sign = 1;
            }
        }else{
            /*other wise it is a number*/
            sign = 1;
            length +=1;
            data.insert(data.begin(),c-'0');
        }
        /*Pass in the rest of the numbers*/
        while(iss>>c){
            if(isdigit(c)){
                /*add the number if it is number*/
                length +=1;
                data.insert(data.begin(),c-'0');
            }else{
                //Check for invalid inputs
                std::cerr<<"Invalid Inputs for Integer Initialization : "<<s<<"\n";
                exit(EXIT_FAILURE);
            }
        }
        if(length==0){
            //Check for invalid inputs
            std::cerr<<"Invalid Inputs for Integer Initialization : "<<s<<"\n";
            exit(EXIT_FAILURE);
        }
        *this = +*this;
    }
    Integer::~Integer() {
        /*destructor not needed */
    }
    Integer& Integer::operator=(const Integer& i) {
        /*assignment operator, copies data */
        data = i.data;
        sign = i.sign;
        length = i.length;
        return *this;
    }
    Integer& Integer::operator-() {
        /*negation operator, negates sign*/
        sign *= -1;
        *this = +*this;
        return *this;
    }
    Integer& Integer::operator+()  {
        /*normalization operator, normalizes the integer, gets rid of leading zeros*/
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
            Integer zero = Integer();
            *this = zero;
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
        /*Addition operation:
          add top and bottom numbers,
          based on intuitive addition

          123
          123
          ---
          246
          add numbers, if over 10 , add carry to next digit
         */
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

        /*Subtraction operation
          intuitive subtraction

          123
          123
          ---
          000
          find the larger on top, and then minus each digit,
          set carry to -1 if top is smaller than bottom
          add carry to next top.
          If top is longer than bottom, drop down top, added by carry
         */
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
                    if(top.data[idx]+carry<0){
                        res = (top.data[idx]+10)+carry;
                        next_carry = -1;
                    }else{
                        res = top.data[idx]+carry;
                    }
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
        /*
          intuitive multiplication

          multiply each digit,
          sets the carry to be the overflow of the multiplication
          Add the final results;
         */
        int res = 0;
        int carry = 0;
        int doublecarry = 0;
        sign = sign * i.sign;
        std::vector<int> result;
        result.resize(length+i.length+1);
        std::fill(result.begin(),result.end(),0);
        /*
          First build up a result array
         */
        for(int jdx=0;jdx<i.length;jdx++){
            for(int idx=0;idx<length;idx++){
                res = 0;
                res += data[idx] * i.data[jdx] + result[idx+jdx];
                result[idx+jdx] = res;
            }
        }

        /*
          Handle all carries, in the result array
         */
        for(int ids=0;ids<length+i.length;ids++){
            //result[ids] += carry;
            //result[ids+1] += doublecarry;
            if(result[ids]>=100){
                doublecarry = std::to_string(result[ids])[0] - '0';
                carry = std::to_string(result[ids])[1] - '0';
                res  = std::to_string(result[ids])[2] -'0';
                result[ids] = res;
                result[ids+1] += carry;
                result[ids+2] += doublecarry;
            }else if(result[ids]>=10){
                carry = std::to_string(result[ids])[0] - '0';
                res  = std::to_string(result[ids])[1] -'0';
                result[ids] = res;
                result[ids+1] += carry;
            }
        }
        data = result;
        length = length + i.length;
        *this = +*this;
        return *this;
    }
    
    Integer& Integer::operator/=(const Integer& i) {
        //Refers to the other function
        std::pair<Integer,Integer> result= divide(*this,i);
        *this = result.first;
        return *this;
    }

    Integer& Integer::operator%=(const Integer& i) {
        //Refers to the other function
        std::pair<Integer,Integer> result= divide(*this,i);
        *this = result.second;
        return *this;
    }

    Integer operator+(const Integer& lhs,const Integer& rhs) {
        //Refers to the other function
        Integer res = Integer(lhs);
        Integer opthing = Integer(rhs);
        res += opthing;
        return res;
    }

    Integer operator-(const Integer& lhs, const Integer& rhs) {
        //Refers to the other function
        Integer res = Integer(lhs);
        Integer opthing = Integer(rhs);
        res -= opthing;
        return res;
    }

    Integer operator*(const Integer& lhs, const Integer& rhs) {
        //Refers to the other function
        Integer res = Integer(lhs);
        Integer opthing = Integer(rhs);
        res *= opthing;
        return res;
    }

    Integer operator/(const Integer& lhs, const Integer& rhs) {
        //Refers to the other function
        Integer res = Integer(lhs);
        Integer opthing = Integer(rhs);
        res /= opthing;
        return res;
    }

    Integer operator%(const Integer& lhs, const Integer& rhs) {
        //Refers to the other function
        Integer res = Integer(lhs);
        Integer opthing = Integer(rhs);
        res %= opthing;
        return res;
    }
    std::ostream& operator<<(std::ostream& os, const Integer& i) {
        //Streaming operator
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
                /*
                  Then check on the case of whether any of the digits are
                  larger or smaller
                 */
                for(int idx = lhs.length-1;idx>=0;idx--){
                    if(lhs.data[idx]<rhs.data[idx]){
                        return true;
                    }else if(lhs.data[idx]>rhs.data[idx]){
                        return false;
                    }
                }
            }
        }
        return false;
    }

    bool operator> (const Integer& lhs, const Integer& rhs) {
        //Refer to other functions
        if(lhs<rhs){
            return false;
        }else{
            return true;
        }
    }
    bool operator<=(const Integer& lhs, const Integer& rhs) {
        //Refer to other functions
        if(lhs<rhs || lhs==rhs){
            return true;
        }else{
            return false;
        }
    }

    bool operator>=(const Integer& lhs, const Integer& rhs) {
        //Refer to other function
        if(lhs>rhs || lhs==rhs){
            return true;
        }else{
            return false;
        }
    }

    bool operator==(const Integer& lhs, const Integer& rhs) {
        /* Check if equal, by checking sign, length and each digit */
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
        //oposition to equal
        return !(lhs==rhs);
    }

    Integer gcd(const Integer& a, const Integer& b) {
        /*Euclidean algorithm*/
        Integer t;
        Integer acopy = Integer(a);
        Integer bcopy = Integer(b);
        if(bcopy==Integer("1")){
            return bcopy;
        }
        while (bcopy != Integer("0"))
            {
                t = bcopy;
                bcopy = acopy % bcopy;
                acopy = t;
            }
        return acopy;
    }  
    std::pair<Integer,Integer> divide(const Integer& a,const Integer& b){
        std::pair <Integer,Integer> result;        
        Integer lhs = Integer(a);
        Integer rhs = Integer(b);
        //Check if lhs is smaller or equal to rhs
        if(lhs<rhs){
            result.first = Integer("0");
            result.second = lhs;
            return result;
        }else if(lhs==rhs){
            result.first = Integer("1");
            result.second = Integer("0");
            return result;
        }
        //Otherwise we assume lhs is larger than rhs
        if(rhs==Integer("0")){
            std::cerr<<"Dvision by Zero"<<"\n";
            Integer error = Integer("-1");
            result.first =error;
            result.second = error;
            return result;
        }
        Integer Q = Integer("0");
        Q.sign = 1;
        Integer R = Integer(lhs);
        R.sign = 1;
        Integer D = Integer("0");
        D.sign = 1;
        Integer INC = Integer(rhs);
        INC.sign = 1;
        Integer M = Integer("1");
        while(true){
            /*Start from 0,
              start adding by increments of divisor*/
            Q += M;
            D += INC *M;
            if(D>=R){
                if(D==R){
                    /*When it is equal, return*/
                    result.first = Q;
                    result.second = Integer("0");
                    return result;
                }
                else if(M==Integer("1")){                    
                    Q-= M;
                    result.first = Q;
                    result.second = R-(Q*INC);
                    return result;
                }else{
                    //If over shoots, go back until we are lower than that.
                    while(D>R){
                        D -= INC *M;
                        Q -= M;
                        if(D==R){
                            /*When it is equal, return*/
                            result.first = Q;
                            result.second = Integer("0");
                            return result;
                        }
                    }
                    M = Integer("1");
                }
            }else{
                /*Each round build up momentum */
                M *= Integer("10");
            }
        }
    }
}
