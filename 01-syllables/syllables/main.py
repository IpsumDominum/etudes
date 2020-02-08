
import cmudict

vowels = ["A","E","I","O","U"]
the_dict = cmudict.dict()
def get_syllables(word):

    """Get the syllables from looking up the CMU dict"""
    try:
        phonems = the_dict[word]
        count = 0
        for p in phonems[0]:
            if(p[0] in vowels):
                count +=1
        return count
    except Exception:
        count = _syllables(word)
        return count
def _syllables(word):

    """Otherwise, if the CMU dict does not contain the entries, manually check
    the syllables, this is not completely correct, however,
    since there are no true standards beyond the standard dictionary,this is
    our assumption that the general factoring rules apply simply on several
    rules"""
    vowels = 'aeiouAEIOU'
    count = 0
    word = line.rstrip()
    if len(word) <= 3:
        """if the word is small, if the word ends with y and starts with a vowel
        there are to be counted two vowels if it ends with y, otherwise
        1 vowels"""
        if word[0] in vowels and word[-1] == 'y':
            count += 2
        else:
            count += 1
    else:
        """
        Otherwise, count 1 up for each vowels encountered.

        """
        for char in word:
            if char in vowels:
                count += 1
        #If the word ends with a e, the e is considered silent.
        if word[-1] == 'e':
            count -= 1

        #If the word ends with a y, the e is considered silent.
        if word[-1] == 'y':
            count += 1
            
        w = 0
        x = 1
        #Check for vowel combinations, and remove one count for each
        #combined vowel. ie: oe ae ie etc
        while x < len(word): 
            if word[w] in vowels and word[x] in vowels:
                count -= 1
            w += 1
            x += 1

        """
        check for configurations such as:
              lyb
        where y is surrounded by not vowels,
        add one to count if one is found
        """
            
        a = 0
        b = 1
        c = 2

        while c < len(word):
            if word[a] not in vowels and word[b] == 'y' and word[c] not in vowels:
                count += 1
            a += 1
            b += 1
            c += 1
        #check for other remaining cases:
        #ending with "le", "ee" and "y"
        #and handle accordingly
        if word.endswith('le') and word[-3] not in vowels:
            count += 1

        if word.endswith('ee'):
            count += 1

        if word.endswith('y') and word[-2] in vowels:
            count -= 1
    return count


if __name__ =="__main__":
    from sys import argv
    while(True):
        try:
            line = raw_input()
            if(len(line.split(" "))>1):
                print("Hey it's supposed to be one word or whatever..")
                continue
            print(get_syllables(line))
        except EOFError:
            exit()
            
                  


    

        


    
