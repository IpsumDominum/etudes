import os
import struct
import re
import binascii
def parseIBMfloating(inputpath,inputprecision):

    """
    parseIBMfloating:
         @inputpath - input file path, input file should contain
                      hex representations of IBM 360 floating point
                      numbers, separated by line.
         @inputprecision - precision can be "single" or "double"
         
         How it works:
                After checking format validity,
                get sign bit
                get exponents
                get mantissa
                add offset to exponents
                convert the floating point into digital
        returns digital form of IBM360 floating point number
    """
    results = []
    #Check for precision 
    expectedLength = 32 if inputprecision=="single" else 64
    with open(inputpath,"rb" if inputpath.endswith(".bin") else "r") as file:
        if(inputpath.endswith(".bin")):
            stringthing = ""
            byte = file.read(1)
            while byte!="":
                byte = file.read(1)
                stringthing +=byte
            stringthing = binascii.hexlify(stringthing)
            stringerthings = []
            idx = 0
            incresize = 8 if(inputprecision=="single") else 16
            while(not (idx+incresize>len(stringthing))):
                stringerthings.append(stringthing[idx:idx+incresize])
                idx = idx +incresize
            stringerthings.append(stringthing[idx:])
        else:
            stringerthings = file.readlines()
        for linenum,oneNum in enumerate(stringerthings):
            oneNum = oneNum.strip("\n").replace(" ","")
            #Check if oneNum is hex            
            if(len(oneNum)!=8):
                print("line: {} | Ignored: {}".format(linenum,oneNum))
                continue
            try:
                oneNum = "{0:08b}".format(int(oneNum,16))
            except ValueError:
                print("line: {} | Ignored: {}".format(linenum,oneNum))
                continue
            if(len(oneNum)==expectedLength):
                pass
            else:
               if(len(oneNum)<expectedLength):
                   oneNum = "0"* (expectedLength -len(oneNum))+oneNum
               else:
                   print("Conversion issue")
                   continue
            if(oneNum[0]=="1"):
                sign = -1
            elif(oneNum[0]=="0"):
                sign = 1
            exponent = oneNum[1:8]
            fraction = oneNum[8:]
            expodigit = bin_to_digit(exponent) - 64
            afterdigit = bin_to_digit_after(fraction)
            result = (afterdigit*(16**expodigit)) * sign
            results.append(result)
    return results

def writeIEEE(outputpath,results,outputprecision):
    """
    writeIEEE
         @outputpath - output file path, output file will be
                       written line by line, each line is a
                       binary representation, of the 
                       corresponding IBM360 floating point
                       in the input file
         @outputprecision - precision can be "single" or "double"
         How it works:
                   Since the default python double representation,
                   is already IEEE floating point format,
                   we convert the IBM360 floating point format
                   into python double() or float() data types.
                   And write out the result to outputfile.
    """
    writetype = "wb" if(outputpath.endswith(".bin")) else "w"
    with open(outputpath,writetype) as out_file:
        for data in results:
            if(outputprecision=="single"):
                try:
                    packed = struct.pack('>f',data).encode('hex')
                except OverflowError:
                    if(outputhex):
                        if(data>=0):
                            packed = "7F800000"
                        elif(data<0):
                            packed = "FF800000"
                    if(data>=0):
                        packed = "01111111100000000000000000000000"
                    elif(data<0):
                        packed = "01111111100000000000000000000000"
                bin = "{0:08b}".format(int(packed,16))
                if(bin[0]=="0"):
                    if(int(bin)==0):
                        bin = "0"*32
                elif(bin[0]=="1"):
                    if(int(bin[1:])==0):
                        bin = "1"+"0"*31
                if(len(bin)==31):
                    out_file.write("0"+bin)
                else:
                    out_file.write(bin)
            elif(outputprecision=="double"):
                try:
                    packed = struct.pack('>d',data).encode('hex')
                except OverflowError:
                    """
                    if(outputhex):
                        if(data>=0):
                            packed = "7F80000000000000"
                        elif(data<0):
                            packed = "FF80000000000000"
                    """
                    if(data>=0):
                        packed = "01111111100000000000000000000000" + "0"*32
                    elif(data<0):
                        packed = "11111111100000000000000000000000" + "0"*32
                bin = "{0:08b}".format(int(packed,16))
                if(bin[0]=="0"):
                    if(int(bin)==0):
                        bin = "0"*64
                elif(bin[0]=="1"):
                    if(int(bin[1:])==0):
                        bin = "1"+"0"*63
                if(len(bin)==63):
                    out_file.write("0"+bin+"\n")
                else:
                    out_file.write(bin+"\n")

"""
Helper functions:
"""
def bin_to_digit(binary):
    #converts binary to digital
    digit = 0
    for i,num in enumerate(reversed(binary)):
        digit += 2**(i) * int(num)
    return digit
def bin_to_digit_after(binary):
    #converts binary to digital, after the decimal place
    digit = 0
    for i,num in enumerate(binary):
        digit += 2**(-(i+1)) * int(num)
    return digit

def insert_dot(fraction,pos):
    #inserts the dot, and treat before and after separately.
    return fraction[:pos], fraction[pos:].strip("0")
"""
#Testing
if __name__ =="__main__":
    def test():
        inputpath = "testibm_single.bin"
        inputprecision = "single"
        parseIBMfloating(inputpath,inputprecision)
    test()
"""
