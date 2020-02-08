import os
import sys
from floating import *
if sys.version_info >= (3,0):
    version = 3
else:
    version = 2
if __name__ =="__main__":
    try:
        print("Please enter an input file path")
        inputpath = raw_input() if version==2 else input()
        print("And the precision?")
        inputprecision = raw_input() if version==2 else input()
        print("Please enter an output file path")
        outputpath = raw_input() if version==2 else input()
        print("And the precision?")
        outputprecision = raw_input() if version==2 else input()

        ieee = parseIBMfloating(inputpath,inputprecision)
        writeIEEE(outputpath,ieee,outputprecision)
    except EOFError:
        exit()


    

