#!/usr/bin/python
# -*- coding: latin-1 -*-

# A big dictionary to store the look up table
verbs = {
    "going":{
        "maori":"haere",
        "tense":"present",
        },
    "went":{
        "maori":"haere",
        "tense":"past"
    },
    "go":{
        "maori":"haere",
        "tense":"future"
    },
    "making":{
        "maori":"hanga",
        "tense":"present"
    },"made":{
        "maori":"hanga",
        "tense":"past"
    },"make":{
        "maori":"hanga",
        "tense":"future"
    },"seeing":{
        "maori":"kite",
        "tense":"present"
    },"saw":{
        "maori":"kite",
        "tense":"past"
    },"see":{
        "maori":"kite",
        "tense":"future"
    },"wanting":{
        "maori":"hiahia",
        "tense":"present"
    },"wanted":{
        "maori":"hiahia",
        "tense":"past"
    },"want":{
        "maori":"hiahia",
        "tense":"future"
    },"calling":{
        "maori":"karanga",
        "tense":"present"
    },"called":{
        "maori":"karanga",
        "tense":"past"
    },"call":{
        "maori":"karanga",
        "tense":"future"
    },"asking":{
        "maori":"pātai",
        "tense":"present"
    },"asked":{
        "maori":"pātai",
        "tense":"past"
    },"ask":{
        "maori":"pātai",
        "tense":"future"
    },"reading":{
        "maori":"pānui",
        "tense":"present"
    },"read":{
        "maori":"pānui",
        "tense":"past"
    },"read":{
        "maori":"pānui",
        "tense":"future"
    },"learning":{
        "maori":"ako",
        "tense":"present"
    },"learnt":{
        "maori":"ako",
        "tense":"past"
    },"learn":{
        "maori":"ako",
        "tense":"future"
    },
    }
to_be = {
    "is":"present",
    "are":"present",
    "am":"present",
    "will":"future"}
to_be_lookup = {
    "is":["she","he"],
    "are":["you","we","they"],
    "am":["i"],
    "will":["she","he","you","we","i","they"]
    }
#another one to lookup
english_map = {
    "i":{
        "default":"au",
        },
    "you":{
        "default":"koe",
        "2excl":"koe",
        "2excl":"kōrua",
        "3excl":"koutou",
        "2incl":"koe",
        "2incl":"kōrua",
        "3incl":"koutou",
    },
    "he":{
        "default":"ia",
        },
    "she":{
        "default":"ia",
        },
    "they":{
        "default":"rāua",
        "2excl":"rāua",
        "3excl":"rātou",
    },
    "we":{
        "default":"taua",
        "2incl":"tāua",
        "3incl":"tātou",
        "2excl":"māua",
        "3excl":"mātou"
        }
}
cases = {
    "present":"Kei te",
    "past":"I",
    "future":"Ka"
    }
import re
#----------Programme------------
if __name__ =="__main__":
    try:
        while(True):
            verb_maori = ""
            pronoun_maori= ""
            pronoun_case = "default"
            tense_maori= ""
            #Get the line input and split into tokens by whitespace
            line = raw_input().lower().strip(" ")
            #if there are special specifications
            things_in_bracket = re.findall("\(.+\)",line)
            if(len(things_in_bracket)>1):
                print("Error: invalid specifications, too many brackets:{}".format(line))
                continue
            elif(len(things_in_bracket)==1):
                nums = re.findall("[0-9]+",things_in_bracket[0])
                if(len(nums)==1):
                      whatsleft = things_in_bracket[0].replace("("+nums[0],"").replace(")","").replace(" ","")
                      if(int(nums[0])==1):
                          #if the num is 1, keep to default
                          pass
                      else:                          
                          if(whatsleft=="incl"):
                              num_c = "2" if int(nums[0])<=2 else "3"
                              pronoun_case = num_c +"incl"
                          elif(whatsleft=="excl"):
                              num_c = "2" if int(nums[0])<=2 else "3"
                              pronoun_case = num_c +"excl"
                          else:
                              print("Error: invalid specifications {}".format(things_in_the_bracket[0]))
                              continue
                      line = line.replace(things_in_bracket[0]+" ","")
                elif(len(nums)>1):
                    print("Error: invalid specifcations, too many numbers: {}".format(line))
                    continue
                
            #Get some tokens
            #Parse pronoun
            tokens = line.split(" ")
            if(len(tokens)>1):
                pronoun = tokens[0]
                if(pronoun in english_map.keys()):
                    if(pronoun_case in english_map[pronoun].keys()):
                        pronoun_maori = english_map[pronoun][pronoun_case]
                    else:
                        print("Error: pronoun {} incompatible with spec {}".format(pronoun,pronoun_case))
                        continue
                else:
                    print("Error: unknown pronoun: {}".format(pronoun))
                    continue
            else:
                print("Error: invalid input")
                continue
            #Get either a "tobe", or a verb
            to_be_or_not_to_be = "not_to_be"
            to_be_tense = ""
            if(len(tokens)>=2):
                #anticipating a to_be conjunction: "are, am, will"
                if(tokens[1] in to_be.keys()):
                    to_be_or_not_to_be = "to_be"
                    to_be_tense = tokens[1]
                    if(pronoun in to_be_lookup[to_be_tense]):
                        pass
                    else:
                        print("Error: Incompatible tobe with {} and {}".format(pronoun,to_be_tense))
                        continue
                #if no to_be conjunction is found, move on to check if a verb is found
                if(to_be_or_not_to_be == "not_to_be"):
                    verb = tokens[1]
                    if(verb in verbs.keys()):
                        verb_maori = verbs[verb]["maori"]
                        tense_maori = verbs[verb]["tense"]
                        if(verb=="read"):
                            tense_maori = "past"
                    else:
                        print("Error: Invalid verb {}".format(verb))
                        continue
            #Get the verbs
            if(to_be_or_not_to_be=="to_be"):
                if(len(tokens)==3):
                    verb = tokens[2]
                    if(verb in verbs):
                        if(to_be[to_be_tense] ==verbs[verb]["tense"]):
                            verb_maori = verbs[verb]["maori"]
                            tense_maori = verbs[verb]["tense"]
                            if(verb=="read"):
                                tense_maori = "future"
                        else:
                            print("Error: invalid combination of {0} and verb {1}".format(to_be_tense,verb))
                            continue
                    else:
                        print("Error: invalid verb {}".format(verb))
                        continue
                elif(len(tokens)<3):
                    print("Error: expecting a verb")
                    continue
                elif(len(tokens)>3):
                    print("Error: Unknown: {}".format("".join(tokens[3:])))
                    continue
            if(tense_maori==""):
                continue
            print(cases[tense_maori]+" "+verb_maori+" "+pronoun_maori)
    except EOFError:
        exit()
