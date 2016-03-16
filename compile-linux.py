from subprocess import Popen, PIPE, call
from os.path import dirname, realpath, join
from os import system, remove, walk, chdir
from multiprocessing import cpu_count
BASE_PATH = dirname(realpath(__file__));

print(BASE_PATH);
LAUNCH_COMMANDLINE = ["."+join(BASE_PATH, "bin", "linux","Game")];

def CleanAndCompile():
    Clean();
    cores = cpu_count();
    print("Compiling with {} threads...".format(cores));
    FORBIDDEN_PRINTS = ["\n", "\r"];

    def fixline(s):
        for char in FORBIDDEN_PRINTS:
            s = s.replace(char, "");
        return s;

    p = Popen(["make", "-j"+str(int(cores*1.5)), "-fmakefile-linux"], cwd=BASE_PATH , stdout=PIPE, bufsize=1)


    FinalLine = None;

    FILE = open("log", "w");

    for line in iter(p.stdout.readline, ''):
        FILE.write(line.decode("utf-8"));
        if(line != b''):
            fixedline = fixline(line.decode("utf-8"));
            print(fixedline);
            FinalLine = fixedline;
        else:
            break;

    p.stdout.close();

    if p.wait() != 0:
        print("Failure!");
        return False;

    FILE.close();
    print("Completed!");
    print("Status: {}".format(FinalLine));
    return True;

def Clean():
    print("Cleaning...");

    for root, dirs, files in walk(join(BASE_PATH, "obj")):
        for file in files:
            if(file.find(".o") != -1):
                remove(join(root, file));
    print("Completed.")
    return False;

OPTIONS = [CleanAndCompile, Clean];
def Main():
    system("clear");
    Index = None;

    for k, v in enumerate(OPTIONS):
        print("{} - {}".format(k, v.__name__));

    try:
        Index = int(input("Enter Number: "));
    except:
        print("Please enter a valid integer!");
        return;

    if(Index > len(OPTIONS)):
        print("Please enter a valid integer!");
        return;

    Result = OPTIONS[abs(Index)]();

    if(Result):
        print("Launching...");
        chdir(join(BASE_PATH, "bin/linux"));
        system("./Game"); system("read -rsp $'Press any key to continue...\n' -n 1 key");
        return;

    try:
        input();
    except:
        system("clear");
        return;


while True:
    Main();
