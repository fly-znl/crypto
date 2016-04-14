import os

def decode(filename):
    cmd = "encode_tank.exe %s" % (filename)
    os.system(cmd)
    
def decodeDir(dir):
    for parent,dirnames,filenames in os.walk(dir):
        for filename in filenames:
            fullname = os.path.join(parent, filename)
            decode(fullname)
            

if __name__ == "__main__":
    dir = "./Config"
    decodeDir(dir)