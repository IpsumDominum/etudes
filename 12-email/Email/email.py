import sys
import re
if sys.version_info >= (3,0):
    version = 3
else:
    version = 2
#list of valid_domains
valid_domains = ['.co.nz','.com.au','.co.ca','.com','.co.us','.co.uk']

def get_tokens(email,full):
    """
    The get_tokens method gets all the tokens
    it first checks for whether the @ symbol
    exists in the email.
    If it does not, it goes through the email, finding
    the first _at_ it can find, and replaces it with @
    This is in case there are emails which are formatted
    as   hi_at_the_beach_at_gmail.com
    which should be valid.(as my assumption)
    If neither way finds the @ symbol or _at_ 
    the email is invalid
"""
    if(len(email)<1):
        print("INVALID: no entry")
        return 0
    email = email.lower()
    whitespace = re.findall("\s",email)
    if(len(whitespace)>0):
        print(full + "----> " +"INVALID: should not include whitespace! ")
        return 0
    email_list = list(email)

    if("@" not in email):
        at_loc = 0 
        for i in reversed(range(len(email_list))):
            if(i>3):
                if((email[i]+email[i-1]+email[i-2]+email[i-3])=="_ta_"):
                    at_loc = i
                    break
            else:
                print(full + "----> " +"INVALID: no @ or _at_ found")
                return 0
        email_list[at_loc] = ""
        email_list[at_loc-1] = ""
        email_list[at_loc-2] = ""
        email_list[at_loc-3] = "@"
        email = "".join(email_list)
    email = email.replace("_dot_",".")
    tokens = email.split("@")
    if(len(tokens)!=2):
        print(email+"---->INVALID: formatting incorrect")
        return 0
    if(len(tokens[0])<1 or len(tokens[1])<1):
        print(email + "---->INVALID: mailbox name or domain missing")
        return 0
    return tokens
def parse_front(token,full):
    """
    Here we parse the front part, before the @ symbol,
    should it be the only @ symbol, which is found in 
    the string.
    We first check for invalid characters,
    then check for invalid usage of separators,
    that is:
    two or more separators conjoint
    start and end with separators
"""
    invalid = re.findall(r'([^A-Z a-z 0-9 \- \. \_]+)',token)    
    if(len(invalid)>0):
        print(full + "----> " +"INVALID: invalid characters exist in mailbox")
        return 0
    more_seps = re.findall(r'[ \. \- \_]{2,}',token)
    start_sep = re.findall(r'^[\. \- \_]',token)
    end_sep = re.findall(r'[\. \- \_]$',token)
    if(len(more_seps)>0):
        print(full + "----> " +"INVALID: inproper separator or usage in mailbox")
        return 0
    if(len(start_sep)>0):
        print(full + "----> " +"INVALID: cannot start with separator in mailbox")
        return 0
    if(len(end_sep)>0):
        print(full + "----> " +"INVALID: cannot end with separator in mailbox")
        return 0
    return token
def parse_domain(token,full):
    """
    Here we parse the domain part, after the @ symbol.
    We first check if the domain is a properly formatted
    numeric domain.
    Otherwise, check for invalid characters,
    then separator rules same as the front.
    And as well as that the domain ends with one of the
    valid alphabetical domains such as .co.nz
"""
    if(token.startswith("[") and token.endswith("]")):
       numerical_tokens = token[1:-1].split(".")
       print(token[1:-1])
       if(token[1:-1]=="0.0.0.0" or token[1:-1] =="127.0.0.1"):
           print(full + "----> " +"INVALID: invalid numeric domain, local host is not a valid email domain ip")
           return 0
       if(len(numerical_tokens)!=4):
           print(full + "----> " +"INVALID: invalid numeric domain")
           return 0
       else:
           for num_tok in numerical_tokens:
               if(not num_tok.isdigit()):
                   print(full + "----> " +"INVALID: invalid numeric domain")
                   return 0
               elif(len(num_tok)>3 or int(num_tok)>255):
                   print(full + "----> " +"INVALID: invalid numeric domain")
                   return 0
           return token
    invalid = re.findall(r'([^A-Z a-z 0-9 \.]+)',token)
    if(len(invalid)>0):
        print(full + "----> " +"INVALID: invalid characters exist in domain")
        return 0
    more_seps = re.findall(r'[ \.]{2,}',token)
    end_sep = re.findall(r'[\.]$',token)
    start_sep = re.findall(r'^[\.]',token)
    if(len(start_sep)>0):
        print(full + "----> " +"INVALID: cannot start with separator in domain")
        return 0
    if(len(more_seps)>0):
        print(full + "----> " +"INVALID: inproper separator usage in domain")
        return 0
    if(len(end_sep)>0):
        print(full + "----> " +"INVALID: cannot end with separator in domain")
        return 0
    for domain in valid_domains:
        if(token.endswith(domain)):
            return token
    print(full + "----> " +"INVALID: not a valid domain")
    return 0


if __name__=="__main__":
    try:
        while(True):
            ###############################
            # Programme structure:
            #   input -> tokenizer -> front checking -> domain checking -> output
            # If Invalidity is encountered, break from pipe.
            ###############################
            if(version==3):
                email = input()
            elif(version==2):
                email = raw_input()
            tokens = get_tokens(email,email)
            if(tokens==0):
                continue
            front = parse_front(tokens[0],email)
            if(front==0):
                continue
            domain = parse_domain(tokens[1],email)
            if(domain ==0):
                continue
            final =  front+"@" + domain
            print(final)
    except Exception:
        pass


    
