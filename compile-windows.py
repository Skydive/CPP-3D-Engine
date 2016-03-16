from subprocess import Popen, PIPE, call
from os.path import dirname, realpath, join
from os import system, remove, walk
from multiprocessing import cpu_count
BASE_PATH = dirname(realpath(__file__));

print(BASE_PATH);
LAUNCH_COMMANDLINE = [join(BASE_PATH, "bin", "Game.exe")];

def Compile():
    cores = cpu_count();
    print("Compiling with {} threads...".format(cores));
    FORBIDDEN_PRINTS = ["\n", "\r"];

    def fixline(s):
        for char in FORBIDDEN_PRINTS:
            s = s.replace(char, "");
        return s;

    p = Popen(["mingw32-make", "-j"+str(int(cores*1.5))], cwd=BASE_PATH , stdout=PIPE, bufsize=1)


    FinalLine = None;

    FILE = open("log", "w");

    for line in iter(p.stdout.readline, ''):
        FILE.write(line.decode("utf-8"));dw
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

OPTIONS = [Compile, Clean];
def Main():
    system("cls");
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
        call(LAUNCH_COMMANDLINE, cwd=join(BASE_PATH, "bin"));
        return;

    try:
        input();
    except:
        system("cls");
        return;


while True:
    Main();
