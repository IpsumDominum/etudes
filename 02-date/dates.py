import re
import sys

odd_months = ['Jan','Mar','May','Jul','Aug','Oct','Dec']
even_months = ['Apr','Jun','Sep','Nov']
months = ['Jan','Feb','Mar','Apr','May','Jun','Jul','Aug',
          'Sep','Oct','Nov','Dec']

def get_tokens(input):
    tokens = []
    if " " in input:
        tokens = input.split(" ")
    elif "/" in input:
        tokens = input.split("/")
    elif "-" in input:
        tokens = input.split("-")
    else:
        print(input,"INVALID: separation error")
        return -1
    if(len(tokens)!=3):
        print(input,"INVALID:input error: not enough tokens or Invalid separator usage")
        return -1
    else:
        return tokens

def parse_day(token,month,year):
    if len(token)>2:
        print(token,"INVALID: day does not follow format dd d 0d")
        return -1
    try:
        day_num = int(token)
    except Exception:
        print(token,"INVALID: day contains invalid characters")
        return -1
    if(month=="Feb"):
        if(year%4==0):
            if(year%100==0):
                if(year%400==0):
                    max_day = 29
                else:
                    max_day = 28
            else:
                max_day = 29
        else:
            max_day = 28
    elif(month in odd_months):
        max_day = 31
    else:
        max_day = 30
    if(day_num>max_day or day_num<=0):
        print(token,"INVALID: Day out of range")
        return -1
    else:
        return day_num
def parse_month(token):
    #check if month is number
    if token.isdigit():
        if(len(token)>2):
            print(token,"INVALID: month formatting error, only m and mm is valid!")
        if(int(token)<1 or int(token)>12):
            print(token,"INVALID: not a valid month!")
        else:
            token = months[int(token)-1]
    else:
        if(len(token)!=3):
            print(token,"INVALID: not a valid month!")
            return -1
        else:
            pass
        if(token[0].isupper()):
            #Filter out cases like  ApR or APr
            if(token[1].isupper() and token[2].isupper()
               or token[1].islower() and token[2].islower()):
                pass
            else:
                print(token,"INVALID: not a valid month!")
                return -1
        else:
            #Filter out cases like aPr or aPR and apR
            if(token[1].isupper() or token[2].isupper()):
                print(token,"INVALID: not a valid month!")
                return -1
            else:
                pass
        if((token[0].upper() + token[1:].lower()) in months):
            pass
        else:
            print(token,"INVALID: not a valid month!")
            return -1
    return token
def parse_year(token):
    if(len(token)!=2 and len(token)!=4):
        print(token,"INVALID: Year does not follow format yy or yyyy")
        return -1
    try:
        if(len(token)!=2):
            year_num = int(token)
            if(year_num<1753 or year_num>3000):
                print(token,"INVALID: Year out of range")
                return -1
        else:
            year_num = int(token)
            if(year_num<0):
                print(token,"INVALID: Year out of range")
                return -1
            if(year_num>=50):
                return "19"+ token
            else:
                return "20"+token
    except Exception:
        print(token,"INVALID: year")
        return -1
    return token
if __name__ =="__main__":
    try:
        while(True):
            if sys.version_info >= (3,0):
                date = input()
            else:
                date = raw_input()
            tokens = get_tokens(date)
            if(tokens==-1):
                continue
            year = parse_year(tokens[2])
            if(year==-1):
                continue
            month = parse_month(tokens[1])
            if(month==-1):
                continue
            day = parse_day(tokens[0],month,int(year))
            if(day==-1):
                continue
            print(str(day)+" "+str(month)+" "+str(year))
    except EOFError:
        exit()
