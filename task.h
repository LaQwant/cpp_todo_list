/*
Author : Quentin GUITET
Date : 6/02/2020
Part of the "todo_app" project. Implements a Task class (and a Date class, used in the first one).
*/


#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std ;

class Date { //implements a date with comparison operators
private :
    int day ;
    int month ;
    int year ;
public :
    Date () : day(0),month(0),year(0){}
    Date (const int& day, const int& month, const int& year) : day(day),month(month),year(year) {} //from numbers
    Date (const string& str_date) {
        stringstream ss(str_date);
        string element ;
        bool ok = true ;
        try {
            ok = (getline(ss, element, '/') && ok) ;
            day = stoi(element) ;
            ok = (getline(ss, element, '/') && ok) ;
            month = stoi(element) ;
            ok = (getline(ss, element, '/') && ok) ;
            year = stoi(element) ;
        }
        catch (invalid_argument const &e) //doesn't work and I don't know why !! impossible to catch the exceptions...
        {
            ok = false ;
        }
        catch (out_of_range const &e)
        {
            ok = false ;
        }
        if (not ok) {
                throw "A date must be dd/mm/yyyy : " + str_date ;
        }
    }
    string show() { //returns a string representing the date
        return to_string(day)+"/"+to_string(month)+"/"+to_string(year) ;
    }
    bool operator< (const Date& b) {
        if (year<b.year) {
            return true ;
        }
        else if (year==b.year) {
            if (month<b.month) {
                return true ;
            }
            else if (month==b.month) {
                if (day<b.day) {
                    return true ;
                }
                else {
                    return false ;
                }
            }
            else {return false ;}
        }
        else {return false ;}
    }
    bool operator== (const Date& b) {
        return (year==b.year && month==b.month && day==b.day) ;
    }

};


class Task {
public :
    int id ;
    string full_id ="" ;
    string title  ="";
    string desc ;
    Date begin ;
    Date end ;
    string status ;
    int progress ;
    string priority ;
    vector<string> commentaries ;

    int counter {1} ;
    vector<Task*> daughters ;
    bool root = false ;
    Task* mother ;

    Task (const string& title, const string& desc, const Date& begin, const Date& end, const string& status, const int& progress, const string& priority,Task* mother) :
                    title(title), desc(desc), begin(begin),end(end),
                    status(status),progress(progress), priority(priority), mother(mother) { //constructor for any task having a mother
        id = mother->counter ;
        mother->counter++ ;
        if (mother->root) {
            full_id = to_string(id) ;
        }
        else {
            full_id = mother->full_id + "." + to_string(id) ;
        }
    }
    Task () {// constructor for root
        root = true ;
    } 
    Task* addDaughter (const string& title, const string& desc, const Date& begin, const Date& end, const string& status, const int& progress, const string& priority) {
        Task* ptr = new Task (title,desc,begin,end,status,progress,priority,this) ;
        daughters.push_back( ptr ) ;
        return ptr ;
    }
    
    ~Task () { //must delete reference in its mother's daugthers vector, and delete the daughters
        if (not root) {
            //remove the daughters
            for (int i {0} ; i<daughters.size() ; i++) {
                delete daughters[i] ;
            }
            //remove the good object from the mother's list
            for (int i {0} ; i<mother->daughters.size() ; i++) {
                if (mother->daughters[i]==this) {
                    mother->daughters.erase(mother->daughters.begin()+i) ;
                }
            }
        }
    }

    Task* find_by_id(const string& identity) { // finds a task using its ID
        stringstream ident {identity} ;
        return find_by_id(ident) ;
    }

    bool operator== (const Task& b) {
        return (this==&b) ;
    }

    void show() { // shows the task and its subtasks (simplified)
        if (not root) {
            cout << title << " (" << full_id << ")" << endl ;
            cout << " " <<begin.show() << " to " << end.show() << " - Progress : " << progress << "%" << endl ;
            cout << " Priority : " << priority << "   Status : " << status << endl ;
            cout << " Description : " << desc << endl ;
            cout << " Commentaries :" << endl ;
            for (int i = 0; i<commentaries.size(); i++) {
                cout << "  " <<i << ") "<< commentaries[i] << endl ;
            }
            cout << " Subtasks :" << endl ;
            for (int i = 0; i<daughters.size(); i++) {
                Task* d = daughters[i] ;
                cout << "  "<<d->full_id << " : " << d->title  << endl ;
            }
        }
    }

    void tree (const string& title,const string& desc, Date& begin, Date& end,const string& status,
            const int &progress,const string& priority,const bool& title_, const bool& desc_,const bool& begin_, const bool& end_,
            const bool& status_,const bool& progress_, const bool& priority_) { //show a tree, public function
        tree_(0,title,desc,begin,end,status,progress,priority,title_,desc_,begin_,end_,status_,progress_,priority_);
    }

    void add_commentary(const string& commentary) {
        commentaries.push_back(commentary) ;
    }

private :
    Task* find_by_id(stringstream& ident) { //recursively finds a task using its id
        string element ;
        if (getline(ident, element, '.')) {
            int n = stoi(element) ;
            int s = daughters.size() ;
            int i {0} ;
            for (int i {0} ; i<s ; i++) {
                if (daughters[i]->id == n) {
                    return daughters[i]->find_by_id(ident) ;
                }
            }
            throw "No task corresponding to this id" ;
        }
        else { // base case (this is the object)
            return this ;
        }
        
    }

    void tree_ (int depth,const string& title,const string& desc, Date& begin, Date& end,const string& status,const int &progress,const string& priority,const bool& title_, const bool& desc_,const bool& begin_, const bool& end_, const bool& status_,const bool& progress_, const bool& priority_) { //show a tree, private function
        string sep = "" ;

        bool ok ;

        ok = (depth==0 or ((!title_ or title==this->title) and (!desc_ or desc==this->desc) and (!begin_ or begin==this->begin) and (!end_ or end==this->end) and (!status_ or status==this->status) and (!progress_ or progress==this->progress) and (!priority_ or priority==this->priority) ));

        if (ok) { // displays only if repects the constraints
            for (int i = 0 ; i<depth ; i++) {
                sep +="    ";
            }

            if (root) { cout << "Tree of all tasks"<<endl ; }
            else { cout << sep << this->title << " (" << full_id << ")" << endl ; }

            for (int i = 0; i<daughters.size(); i++) {
                    daughters[i]->tree_(depth+1, title,desc,begin,end,status,progress,priority,title_,desc_,begin_,end_,status_,progress_,priority_) ;
            }
        }
    }

};