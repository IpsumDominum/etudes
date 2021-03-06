import os
import sys
from sys import argv
from floating import *
if sys.version_info >= (3,0):
    version = 3
else:
    version = 2
if __name__ =="__main__":
    if(len(argv)>=2):
        outputhex = True if(argv[1].lower()=="true")else False
    else:
        outputhex = True
    if(version==3):
        print("Python 3 not supported, please use python 2")
        exit()
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
        writeIEEE(outputpath,ieee,outputprecision,outputhex)
    except EOFError:
        exit()


    

