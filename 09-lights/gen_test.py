import random
from sys import argv
import os
import time

def exec_test(filePath):
    os.system("sh build.sh")
    file_path = filePath
    if(os.path.isfile(file_path)):
        while(True):
            expectingNum = True
            temp_nums = ""
            temp_combs = ""
            with open(file_path,"r") as file:
                lines = file.readlines()
            problem_num = 0
            for idx,line in enumerate(lines):
                if(expectingNum):
                    temp_nums = line
                    expectingNum = False
                else:
                    temp_combs = line
                    with open("temp.txt","w") as file:
                        file.write(temp_nums+temp_combs)
                        temp_nums = ""
                        temp_combs = ""
                        problem_num +=1
                    print("=====================")
                    print(problem_num)
                    os.system("cat temp.txt | ./lights")
                    expectingNum = True
            break
    else:
        print("invalid file path")
def write_test(filePath):
    alphabets = "abcdefghijklmn"
    num_tests = 20
    with open(filePath,"w") as file:
        """Generate some random alphabet combinations"""
        for i in range(num_tests):
            combs = ""
            alphas = ""
            for alpha in alphabets:
                alphas += alpha +" "
            alphas = alphas.strip(" ")
            alphas += "\n"
            for alpha in alphabets:
                if(alpha in alphas):
                    for otheralpha in alphabets:
                        if(otheralpha in alphas and otheralpha!=alpha):
                            if(random.randint(0,1)>0.5):
                                combs += alpha + otheralpha + " "
            combs = combs.strip(" ")
            combs +="\n"
            file.write(alphas+combs)
if __name__ =="__main__":
    if(len(argv)>=3):
        filePath = argv[2]
        if(argv[1] =="write"):
            write_test(filePath)
        elif(argv[1]=="exec"):
            exec_test(filePath)
    else:
        print("""
usage:
    -python gen_test.py write/exec --filePath
exec:
    read and runs every line of --filePath, and feeds them as test cases for ./lights
write:
    write some randomly generated test cases to --filePath
 """)
