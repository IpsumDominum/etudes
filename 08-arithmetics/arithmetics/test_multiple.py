import os
from sys import argv
if __name__=="__main__":
    os.system("sh build.sh")
    if(len(argv)<2):
        print("usage: python test_multiple --testfilePath")
        exit()
    if(os.path.isfile(argv[1])):
        pass
    else:
        print("invalid file path {}".format(argv[1]))
        exit()
    expectingNums = True
    with open(argv[1],'r') as file:
        to_write = ""
        for line in file.readlines():
            if(expectingNums):
                to_write += line
                expectingNums = False
            else:
                with open("test.temp","w") as filetemp:
                    filetemp.write(to_write+line)
                os.system("cat test.temp | ./arithmetics")
                to_write = ""
                expectingNums = True
