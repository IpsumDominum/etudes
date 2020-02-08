import os
if __name__ =="__main__":
    if(os.path.isfile("test.txt")):
        pass
    else:
        print("test.txt not found in current directory {}".format(os.getcwd()))
        exit()
    os.system("sh build.sh")
    with open("test.txt","r") as file:
        for line in file.readlines():
            line = line.strip("\n")
            with open("test.temp","w") as file:
                file.write(line)
            os.system("cat test.temp | ./countit") 
