/*
Author : Quentin GUITET
Date : 6/02/2020
Part of the "todo_app" project. Main file.
Implements the command line, loads the backups and translates the commands into the objects defined in task.h.
*/


#include <fstream>
#include <iostream>
#include "task.h"

using namespace std;

const string SAVE_FILE {".taskssave.txt"} ;

int command(int argc, string argv [], Task& root, const int& start = 0) { // applies a command and returns 0 if no problem and need to save, 1 if problem, 2 if no problem and no need to save /!\ "start"=1 if file name in the list 
    if (argv[start] == "create" ) {
        string title ;
        string desc = "" ;
        Date begin ;
        Date end ;
        int progress = 0 ;
        string status = "" ;
        string mother_id = "";
        string priority = "normal";

        bool title_ = false ;
        bool desc_ = false ;
        bool begin_ = false ;
        bool end_ = false ;
        bool status_ = false ;
        bool mother_id_ = false ;
        bool priority_ = false ;
        bool progress_ = false ;
        
        for (int i=start+1 ; i<argc ; i++) { // translates arguments into variables
            if (argv[i]=="--title" or argv[i]=="-t") {
                i++ ;
                if (i==argc or argv[i][0]=='-') {
                    cout << "Error" << endl ;
                    cout << "--title expects one argument." << endl ;
                    return 1;
                }
                title = argv[i] ;
                title_ = true ;
                }
            else if (argv[i]=="--description" or argv[i]=="--desc" or argv[i]=="-d") {
                i++ ;
                if (i==argc or argv[i][0]=='-') {
                    cout << "Error" << endl ;
                    cout << "--description expects one argument." << endl ;
                    return 1;
                }
                desc = argv[i] ;
                desc_ = true ;
            }
            else if (argv[i]=="--progress") {
                i++ ;
                if (i==argc or argv[i][0]=='-') {
                    cout << "Error" << endl ;
                    cout << "--progress expects one argument." << endl ;
                    return 1;
                }
                try {
                    progress = stoi(argv[i]) ;
                    progress_ = true ;
                }
                catch (invalid_argument const &e)
                {
                    cout << "Error" << endl ;
                    cout << "--progress argument must be a number" << endl ;
                    return 1;
                }
                catch (out_of_range const &e)
                {
                    cout << "Error" << endl ;
                    cout << "--progress number out_of_range" << endl ;
                    return 1;
                }
                if (progress<0 or progress>100) {
                    cout << "Error"<< endl<< "progress should be between 0 and 100%." << endl ;
                    return 1 ;
                }
            }
            else if (argv[i]=="--begin" or argv[i]=="-b") {
            i++ ;
            if (i==argc or argv[i][0]=='-') {
                cout << "Error" << endl ;
                cout << "--begin expects one argument." << endl ;
                return 1;
            }
            begin = Date(argv[i]) ;
            begin_ = true ;
            }
            else if (argv[i]=="--end" or argv[i]=="-e") {
                i++ ;
                if (i==argc or argv[i][0]=='-') {
                    cout << "Error" << endl ;
                    cout << "--end expects one argument." << endl ;
                    return 1;
                }
                end = Date(argv[i]) ;
                end_ = true ;
            }
            else if (argv[i]=="--status" or argv[i]=="-s") {
                i++ ;
                if (i==argc or argv[i][0]=='-') {
                    cout << "Error" << endl ;
                    cout << "--status expects one argument." << endl ;
                    return 1;
                }
                status = argv[i] ;
                status_ = true ;
            }
            else if (argv[i]=="--mother_id" or argv[i]=="--mother" or argv[i]=="-m") {
                i++ ;
                if (i==argc or argv[i][0]=='-') {
                    cout << "Error" << endl ;
                    cout << "--mother_id expects one argument." << endl ;
                    return 1;
                }
                mother_id = argv[i] ;
                mother_id_ = true ;
            }
            else if (argv[i]=="--priority") {
                i++ ;
                if (i==argc or argv[i][0]=='-') {
                    cout << "Error" << endl ;
                    cout << "--priority expects one argument." << endl ;
                    return 1;
                }
                priority = argv[i] ;
                priority_ = true ;
            }
            else {
                cout << "Syntax error" << endl ;
                return 1;
            }
        }
        if (not (title_)) {
            cout << "Error" << endl ;
            cout << "\"create\" needs at least a title : create --title [title]" << endl ;
            return 1;
        }
        try {
            Task* mother = root.find_by_id(mother_id) ;
            mother->addDaughter(title,desc,begin,end,status,progress,priority) ;
            return 0 ;
        }
        catch (char const* &e) {
            cout << "Error : "<< e << endl ;
            return 1 ;
        }    
    }
    else if (argv[start] == "list") { // prints a tree
        string title ;
        string desc = "" ;
        Date begin ;
        Date end ;
        int progress = 0 ;
        string status = "" ;
        string mother_id = "";
        string priority = "normal";
        bool title_ = false ;
        bool desc_ = false ;
        bool begin_ = false ;
        bool end_ = false ;
        bool status_ = false ;
        bool mother_id_ = false ;
        bool priority_ = false ;
        bool progress_ = false ;
            
        for (int i=start+1 ; i<argc ; i++) { // translates arguments into variables
            if (argv[i]=="--title" or argv[i]=="-t") {
                i++ ;
                if (i==argc or argv[i][0]=='-') {
                    cout << "Error" << endl ;
                    cout << "--title expects one argument." << endl ;
                    return 1;
                }
                title = argv[i] ;
                title_ = true ;
            }
            else if (argv[i]=="--progress") {
                i++ ;
                if (i==argc or argv[i][0]=='-') {
                    cout << "Error" << endl ;
                    cout << "--progress expects one argument." << endl ;
                    return 1;
                }
                try {
                    progress = stoi(argv[i]) ;
                    progress_ = true ;
                }
                catch (invalid_argument const &e)
                {
                    cout << "Error" << endl ;
                    cout << "--progress argument must be a number" << endl ;
                    return 1;
                }
                catch (out_of_range const &e)
                {
                    cout << "Error" << endl ;
                    cout << "--progress number out_of_range" << endl ;
                    return 1;
                }
                if (progress<0 or progress>100) {
                    cout << "Error"<< endl<< "progress should be between 0 and 100%." << endl ;
                    return 1 ;
                }
            }
            else if (argv[i]=="--status" or argv[i]=="-s") {
                i++ ;
                if (i==argc or argv[i][0]=='-') {
                    cout << "Error" << endl ;
                    cout << "--status expects one argument." << endl ;
                    return 1;
                }
                status = argv[i] ;
                status_ = true ;
            }
            else if (argv[i]=="--begin" or argv[i]=="-b") {
                i++ ;
                if (i==argc or argv[i][0]=='-') {
                    cout << "Error" << endl ;
                    cout << "--begin expects one argument." << endl ;
                    return 1;
                }
                begin = Date(argv[i]) ;
                begin_ = true ;
            }
            else if (argv[i]=="--end" or argv[i]=="-e") {
                i++ ;
                if (i==argc or argv[i][0]=='-') {
                    cout << "Error" << endl ;
                    cout << "--end expects one argument." << endl ;
                    return 1;
                }
                end = Date(argv[i]) ;
                end_ = true ;
            }
            else if (argv[i]=="--mother_id" or argv[i]=="--mother" or argv[i]=="-m") {
                i++ ;
                if (i==argc or argv[i][0]=='-') {
                    cout << "Error" << endl ;
                    cout << "--mother_id expects one argument." << endl ;
                    return 1;
                }
                mother_id = argv[i] ;
                mother_id_ = true ;
            }
            else if (argv[i]=="--priority") {
                i++ ;
                if (i==argc or argv[i][0]=='-') { 
                    cout << "Error" << endl ;
                    cout << "--priority expects one argument." << endl ;
                    return 1;
                }
                priority = argv[i] ;
                priority_ = true ;
            }
            else {
                    cout << "Syntax error" << endl ;
                    return 1;
            }
        }
        try {
            Task* mother = root.find_by_id(mother_id) ;
            mother->tree(title,desc,begin,end,status,progress,priority,title_,desc_,begin_,end_,status_,progress_,priority_) ;
            return 2 ;
        }
        catch (char const* &e) {
            cout << "Error : "<< e << endl ;
            return 1 ;
        }
    }

    else if (argv[start] == "edit") { // edit a task
        string title ;
        string desc = "" ;
        Date begin ;
        Date end ;
        int progress = 0 ;
        string status = "" ;
        string priority = "normal";
        bool title_ = false ;
        bool desc_ = false ;
        bool begin_ = false ;
        bool end_ = false ;
        bool status_ = false ;
        bool priority_ = false ;
        bool progress_ = false ;
        Task* task {nullptr} ;
        if (start+2>argc) { // no id given
            cout << "Error" << endl ;
            cout << "edit expects at least one argument (id) : edit [id] [--argument [argument]]." << endl ;
            return 1;
        }
        try {
            task = root.find_by_id(argv[start+1]) ;
        }
        catch (char const* &e) {
            cout << "Error : "<< e << endl ;
            return 1 ;
        }
            
        for (int i=start+2 ; i<argc ; i++) { // translates arguments into variables
            if (argv[i]=="--title" or argv[i]=="-t") {
                i++ ;
                if (i==argc or argv[i][0]=='-') {
                    cout << "Error" << endl ;
                    cout << "--title expects one argument." << endl ;
                    return 1;
                }
                title = argv[i] ;
                title_ = true ;
            }
            else if (argv[i]=="--progress") {
                i++ ;
                if (i==argc or argv[i][0]=='-') {
                    cout << "Error" << endl ;
                    cout << "--progress expects one argument." << endl ;
                    return 1;
                }
                try {
                    progress = stoi(argv[i]) ;
                    progress_ = true ;
                }
                catch (invalid_argument const &e)
                {
                    cout << "Error" << endl ;
                    cout << "--progress argument must be a number" << endl ;
                    return 1;
                }
                catch (out_of_range const &e)
                {
                    cout << "Error" << endl ;
                    cout << "--progress number out_of_range" << endl ;
                    return 1;
                }
                if (progress<0 or progress>100) {
                    cout << "Error"<< endl<< "progress should be between 0 and 100%." << endl ;
                    return 1 ;
                }
            }
            else if (argv[i]=="--status" or argv[i]=="-s") {
                i++ ;
                if (i==argc or argv[i][0]=='-') {
                    cout << "Error" << endl ;
                    cout << "--status expects one argument." << endl ;
                    return 1;
                }
                status = argv[i] ;
                status_ = true ;
            }
            else if (argv[i]=="--begin" or argv[i]=="-b") {
                i++ ;
                if (i==argc or argv[i][0]=='-') {
                    cout << "Error" << endl ;
                    cout << "--begin expects one argument." << endl ;
                    return 1;
                }
                begin = Date(argv[i]) ;
                begin_ = true ;
            }
            else if (argv[i]=="--end" or argv[i]=="-e") {
                i++ ;
                if (i==argc or argv[i][0]=='-') {
                    cout << "Error" << endl ;
                    cout << "--end expects one argument." << endl ;
                    return 1;
                }
                end = Date(argv[i]) ;
                end_ = true ;
            }
            else if (argv[i]=="--priority") {
                i++ ;
                if (i==argc or argv[i][0]=='-') { 
                    cout << "Error" << endl ;
                    cout << "--priority expects one argument." << endl ;
                    return 1;
                }
                priority = argv[i] ;
                priority_ = true ;
            }
            else {
                    cout << "Syntax error" << endl ;
                    return 1;
            }
        }
        if (title_) { task->title = title ; }
        if (desc_) { task->desc = desc ; }
        if (begin_) { task->begin = begin ; }
        if (end_) { task->end = end ; }
        if (status_) { task->status = status ; }
        if (priority_) { task->priority = priority ; }
        if (progress_) { task->progress = progress ; }
    }

    else if (argv[start] == "show") { // prints a task

        string id = "";
        if (argc!=start+2) {// afficher une erreur : demande une id
            cout << "Error : show expects exactly one argument (the id of the task)" << endl ;
            return 1 ;
        }
        else {
            id = argv[start+1] ;
        }
        try {
            Task* task = root.find_by_id(id) ;
            task->show() ;
            return 2 ; //doesn't deserve to be saved
        }
        catch (char const* &e) {
            cout << "Error : "<< e << endl ;
            return 1 ;
        }
    }

    else if (argv[start] == "del") { // deletes a task

        string id = "";
        if (argc!=start+2) {// afficher une erreur : demande une id
            cout << "Error : show expects exactly one argument (the id of the task)" << endl ;
            return 1 ;
        }
        else {
            id = argv[start+1] ;
        }
        try {
            Task* task = root.find_by_id(id) ;
            delete task ;
            return 0 ;
        }
        catch (char const* &e) {
            cout << "Error : "<< e << endl ;
            return 1 ;
        }
    }

    else if (argv[start] == "comment") { // add a commentary

        if (argc!=start+3) {// afficher une erreur : demande une id
            cout << "Error : show expects exactly two arguments (the id of the task and a comment)" << endl ;
            return 1 ;
        }

        try {
            Task* task = root.find_by_id(argv[start+1]) ;
            task->add_commentary(argv[start+2]) ;
            return 0 ;
        }
        catch (char const* &e) {
            cout << "Error : " << e << endl ;
            return 1 ;
        }
    } 
    else {
        cout << "Error" << endl ;
        cout << '"' << argv[start] << "\" : unknown command" << endl ;
        return 1;
    }
}



int main (int argc, char* argv []) {
    Task root ;

    // 1) loading of the backup
    ifstream loadstream(SAVE_FILE.c_str()) ;

    string cmd ;
    int argc2 ;
    if (loadstream) {
    while (getline(loadstream, cmd)) {
        string element = "" ;
        string argv2 [50] ; //it should be enough for any command
        stringstream ss (cmd) ;
        argc2 = 0 ;
        bool quote = false ;
            while (getline(ss, element, ' ')) {
                if (not quote) {
                    if (element[0]=='"') {
                        if (element[element.size()-1]=='"') {
                            argv2[argc2] = element.substr(1,element.size()-2) ;
                            argc2++ ;
                        }
                        else {
                            quote = true ;
                            argv2[argc2] = element.substr(1) ;
                        }
                    }
                    else {
                        argv2[argc2] = element ;
                        argc2++ ;
                    }
                }
                else {
                    if (element[element.size()-1]=='"') {
                        quote = false ;
                        argv2[argc2] += " " + element.substr(0,element.size()-1) ;
                        argc2++ ;
                        }
                    else {
                        argv2[argc2] += " " + element ;
                    }
                }
            }

            if (quote) {
                cout << "Error : corrupted backup" << endl ;
                return 1 ;
            }
            if (command(argc2,argv2,root,0)!=0) {
                cout << "Error : corrupted backup" << endl ;
                return 1 ;
            }
        }
    }
    else {
        cout << "Warning : could not load the backup, starting a new one." << endl ;
    }

    // 2) execution of the command (if [program_name] is followed by a command)

    string argv_str [argc] ; // converts argv into an string array (easier for equality tests)
    for (int i = 0 ; i<argc ; i++) {
        argv_str[i] = argv[i];
    }

    ofstream savestream(SAVE_FILE.c_str(), ios::app) ; // opens the saving stream

    if (argc>1) { // executes the line if [program_name] is followed by a command
        int code = command(argc,argv_str,root,1) ;
        if (savestream and code==0) {
            for (int i = 1 ; i<argc ; i++) {
                auto it = std::find(argv_str[i].begin(), argv_str[i].end(), ' ');
                if (it == argv_str[i].end()) { // no space found -> don't need ""
                    savestream << argv_str[i] << " ";
                }
                else { // space in string need ""
                    savestream <<'"' << argv_str[i] << "\" ";
                }
            }
            savestream<<endl;
        }
        else if (code==1) {
            cout << "Warning : couldn't save your changes." << endl ;
        }
    }
    // 2) bis) or starts a command line if no command given
    else { 
        string cmd = "" ;
        string element = "" ;
        string argv2 [50] ; //it should be enough for any command
        while (true) {
            cout << ">>> " ;
            getline(cin,cmd) ;
            stringstream ss (cmd) ;
            argc = 0 ;
            bool quote = false ;
            while (getline(ss, element, ' ')) {
                if (not quote) {
                    if (element[0]=='"') {
                        if (element[element.size()-1]=='"') {
                            argv2[argc] = element.substr(1,element.size()-2) ;
                            argc++ ;
                        }
                        else {
                            quote = true ;
                            argv2[argc] = element.substr(1) ;
                        }
                    }
                    else {
                        argv2[argc] = element ;
                        argc++ ;
                    }
                }
                else {
                    if (element[element.size()-1]=='"') {
                        quote = false ;
                        argv2[argc] += " " + element.substr(0,element.size()-1) ;
                        argc++ ;
                        }
                    else {
                        argv2[argc] += " " + element ;
                    }

                }
            }

            if (quote) {
                cout << "Error : quoting problem" << endl ;
                continue ;
            }
            if (cmd!="exit") {
                if (argc>0) { // executes the line
                    int code = command(argc,argv2,root,0) ;
                    if (savestream and code==0) {
                        savestream<<cmd<<endl;
                    }
                    else if (code==1) {
                        cout << "Warning : couldn't save your changes." << endl ;
                    }
                }
                else {break ;}
            }
        }
    }
    return 0 ;
}