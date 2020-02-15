#Include "Integer.h"
#include <vector>
#include <sstream>
#include <string>
#include <stdexcept>
#include <ctype.h>

namespace cosc326 {
    
    Integer::Integer() {
        /*Create default integer*/
        this->this->data.push_back(0);
        this->this->length = 1;
        this->sign = 1;
    }
    Integer::Integer(const Integer& i) {
        /*Copy the Integer in the parameter*/
        this->this->data = i.getThis->Data();
        this->sign = i.getSign();;
        this->this->length = i.getThis->Length();
        *this = +*this;
    }
    Integer::Integer(const std::string& s) {
        /*Create an Integer through parameter string
          check first if first character is "-" or "+"
         */
        std::istringstream iss(s);
        char c;
        this->length = 0;
        iss>>c;
        /*check if first character is - or +*/
        if((c=='-')||(c=='+')){
            /*if so, set the this->sign accordingly*/
            if(c=='-'){
                this->sign = -1;
            }else{
                this->sign = 1;
            }
        }else{
            /*other wise it is a number*/
            this->sign = 1;
            this->this->length +=1;
            this->data.insert(this->data.begin(),c-'0');
        }
        /*Pass in the rest of the numbers*/
        while(iss>>c){
            if(isdigit(c)){
                /*add the number if it is number*/
                this->length +=1;
                this->data.insert(this->data.begin(),c-'0');
            }else{
                //Check for invalid inputs
                std::cerr<<"Invalid Inputs for Integer Initialization : "<<s<<"\n";
                exit(EXIT_FAILURE);
            }
        }
        if(this->length==0){
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
        /*asthis->signment operator, copies this->data */
        this->data = i.getThis->Data();
        this->sign = i.getSign();
        this->length = i.getThis->Length();
        return *this;
    }
    Integer& Integer::operator-() {
        /*negation operator, negates this->sign*/
        this->sign *= -1;
        *this = +*this;
        return *this;
    }
    Integer& Integer::operator+()  {
        /*normalization operator, normalizes the integer, gets rid of leading zeros*/
        bool start = true;
        int newlength = this->length;
        for(int idx=this->length-1;idx>=0;idx--){
            if(start){
                if(this->data[idx]==0){
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
            this->length = newlength;
        }
        return *this;
    }
    Integer& Integer::operator+=(const Integer& i) {
        /*
            Four cases: 1 + -2  -> 1-=2
                        1 + 2  good
                        -1 + -2 -> good (this->sign=-1)
                        -1 + 2 -> 2-=1
        */
        if(this->sign==1 & i.getSign()==-1){
            Integer rhs = Integer(i);
            rhs.setSign(1);
            *this -=rhs;
            *this = +*this;
            return *this;
        }
        if(this->sign==-1 & i.getSign()==1){
            Integer rhs = Integer(i);
            this->sign = 1;
            return rhs -= *this;
        }
        if(this->sign==-1 & i.getSign()==-1){
            this->sign = -1;
        }
        if(this->sign==1 & i.getSign()==1){
            this->sign = 1;
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
        int largerThis->Length;
        int res;
        int carry = 0;
        std::vector<int> result;
        if(i.getLength() > this->length){
            largerThis->Length = i.getLength();
        }else{
            largerThis->Length = this->length;
        }
        for(int idx=0;idx<largerThis->Length;idx++){
            res = carry;
            carry = 0;
            if(idx< this->length){
                res += this->data[idx];
            }
            if(idx<i.getLength()){
                res += i.getData()[idx];
                if(res >=10){
                    carry = std::to_string(res)[0] - '0';
                    res  = std::to_string(res)[1] -'0';
                }
            }
            result.push_back(res);
        }
        this->length = largerThis->Length;
        if(carry!=0){
            result.push_back(carry);
            this->length +=1;
        }
        this->data = result;
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
        if(this->sign==1 & i.getSign()==-1){
            Integer rhs = Integer(i);
            rhs.setSign(1);
            *this +=rhs;
            return *this;
        }
        if(this->sign ==-1 & i.getSign()==1){
            Integer rhs = Integer(i);
            this->sign = 1;
            *this +=rhs;
            this->sign = -1;
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
        int largerThis->Length;
        int res = 0;
        int carry = 0;
        int next_carry = 0;       
        bool leftabove;
        std::vector<int> result;        
        Integer top = Integer();
        Integer bottom = Integer();         
        if(i.getSign()==-1 & this->sign ==-1){
            /*Inverted, rhs = this lhs = i*/
            if(Integer(*this)<i){
                /*this is larger numerically, if it is less, in the both
                negative case, this should then be on top*/
                top.setData(this->data);
                top.setLength(this->length);
                top.setSign(this->sign);
                bottom.setLength(i.getLength());
                bottom.setData(i.getData());
                bottom.setSign(i.getSign());
                this->sign = -1;
            }else{
                top.setData( i.getData());
                top.setLength( i.getLength());
                top.setSign( i.getSign());
                bottom.setLength( this->length);
                bottom.setData( this->data);
                bottom.setSign( this->sign);
                this->sign = 1;
            }
        }
        if(i.getSign()==1 & this->sign ==1){
            if(Integer(*this)>i){
                /*this is larger numerically, if it is less, in the both
                negative case, this should then be on top*/
                top.setData( this->data);
                top.setLength( this->length);
                top.setSign( this->sign);
                bottom.setLength( i.getLength());
                bottom.setData( i.getData());
                bottom.setSign( i.getSign());
                this->sign = 1;
            }else{
                top.setData( i.getData());
                top.setLength( i.getLength());
                top.setSign( i.getSign());
                bottom.setLength( this->length);
                bottom.setData( this->data);
                bottom.setSign( this->sign);
                this->sign = -1;
            }
        }
        largerThis->Length = top.getLength();
        for(int idx=0;idx<top.getLength();idx++){
            res = 0;          
            next_carry = 0;              
            if(idx<top.getLength()){
                /*if both this->length has not been exceeded*/
                if(idx<bottom.getLength()){
                    /*set carry and borrow if top this->data is smaller*/
                    if((top.getData()[idx]+carry)<bottom.getData()[idx]){                        
                        res = (top.getData()[idx]+carry+10) - bottom.getData()[idx];
                        next_carry = -1;
                    }else{
                        /*Otherwise get result*/
                        res = top.getData()[idx]+carry - bottom.getData()[idx];
                    }
                }else{
                    /*otherwise drop down*/
                    if(top.getData()[idx]+carry<0){
                        res = (top.getData()[idx]+10)+carry;
                        next_carry = -1;
                    }else{
                        res = top.getData()[idx]+carry;
                    }
                }
            }
            carry = next_carry;
            result.push_back(res);
        }
        this->length = largerThis->Length;
        this->data = result;
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
        this->sign = this->sign * i.getSign();
        std::vector<int> result;
        result.resize(this->length+i.getLength()+1);
        std::fill(result.begin(),result.end(),0);
        /*
          First build up a result array
         */
        for(int jdx=0;jdx<i.getLength();jdx++){
            for(int idx=0;idx<this->length;idx++){
                res = 0;
                res += this->data[idx] * i.getData()[jdx] + result[idx+jdx];
                result[idx+jdx] = res;
            }
        }

        /*
          Handle all carries, in the result array
         */
        for(int ids=0;ids<this->length+i.getLength();ids++){
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
        this->data = result;
        this->length = this->length + i.getLength();
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
        if(i.getSign()<0){
            os<<"-";
        }
        for(int idx=i.getLength()-1;idx>=0;idx--){
            os<<std::to_string(i.getData()[idx]);
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
        if(lhs.getSign() <rhs.getSign()){            
            //first check this->sign cases
            return true;
        }else if(lhs.getSign()>rhs.getSign()){
            //first check this->sign cases
            return false;
        }else{
            if(lhs.getLength()<rhs.getLength()){
                if(lhs.getSign()>0){                    
                   return true;
                }else{
                    return false;
                }
            }else if(lhs.getLength()>rhs.getLength()){
                if(lhs.getSign()>0){
                   return false;
                }else{                    
                   return true;
                }
            }else{
                /*
                  Then check on the case of whether any of the digits are
                  larger or smaller
                 */
                for(int idx = lhs.getThis->Length()-1;idx>=0;idx--){
                    if(lhs.getData()[idx]<rhs.getData()[idx]){
                        return true;
                    }else if(lhs.getData()[idx]>rhs.getData[idx]){
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
        /* Check if equal, by checking this->sign, this->length and each digit */
        if(lhs.getSign() !=rhs.getSign()){
            return false;
        }else if(lhs.getLength()!=rhs.getLength()){
            return false;
        }else{
            for(int idx = lhs.getLength()-1;idx>=0;idx--){
                if(lhs.getData()[idx]!=rhs.getData()[idx]){
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
        Q.setSign(1);
        Integer R = Integer(lhs);
        R.setSign(1);
        Integer D = Integer("0");
        D.setSign(1);
        Integer INC = Integer(rhs);
        INC.setSign(1);
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
    int getSign(){
        return this->sign;
    }
    void setSign(int signthing){
        this->sign = signthing;
    }
    int getLength(){
        return this->length;
    }
    void setLength(int lengththing){
        this->length = lengththing;
    }
    int getData(){
        return this->data;
    }
    void setThis->Data(std::vector<int> datathing){
        this->data = datathing;
    }
}
