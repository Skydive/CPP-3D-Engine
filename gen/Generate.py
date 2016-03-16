from glob import glob
from os.path import splitext, split
from os import system

    
def DLLDependencies():
    Dependencies = [];
    for path in glob("..\\bin\\*.dll"):
        Dependencies.append(path.split("\\")[2]);

    DependencyString = "";
    for dep in Dependencies:
        DependencyString += "- "+dep+"\n";
    
    return DependencyString;

def FindToDos(FindPath, FileTypes):
    TODOS = [];
    for path in glob(FindPath):
        for filetype in FileTypes:
            if(splitext(path)[1][1:] == filetype):
                LineNumber=1;
                for line in open(path, "r").read().split("\n"):    
                    Status = line.find("TODO:");
                    if(Status != -1):
                        TODOS.append("  - {}: Line {}: {}\n".format(split(path)[1], LineNumber, line[Status+len("TODO:"):].strip()));
                    LineNumber += 1;

    return TODOS;


def ToDoList():
    List = "";
    EngineTODOS = ["- Engine (Major and Significant):"+"\n"]
    EngineTODOS += FindToDos("..\src\Engine\*", ["h", "cpp"]);
    GameTODOS = ["- Game (Minor and virtually pointless):"+"\n"]
    GameTODOS += FindToDos("..\src\Game\*", ["h", "cpp"]);
    for i in (EngineTODOS+GameTODOS):
        List += i;
    
    
    return List;

def ChangeLog():
    return open("changelog.md", "r").read();

def Main():
    print("Started!");
    ReplaceControllers = dict();
    ReplaceControllers["$DLL_DEPENDENCIES"] = DLLDependencies;
    ReplaceControllers["$TODO_LIST"] = ToDoList;
    ReplaceControllers["$CHANGE_LOG"] = ChangeLog;
    
    Template = open("template.md", "r").read();
    for replacestring in ReplaceControllers.keys():
        Status = Template.find(replacestring);
        if(Status != -1):
            Result = ReplaceControllers[replacestring]();
            Template = Template.replace(replacestring, Result);
    open("../readme.md", "w").write(Template);

    print("Done!");
    system("PAUSE");


Main();
