
// Name:Sarthak Seth
// USC NetID:sethsart@usc.edu
// CSCI 455 PA5
// Spring 2018

/*
 * grades.cpp
 * A program to test the Table class.
 * How to run it:
 *      grades [hashSize]
 * 
 * the optional argument hashSize is the size of hash table to use.
 * if it's not given, the program uses default size (Table::HASH_SIZE)
 *
 */

#include "Table.h"

// cstdlib needed for call to atoi
#include <cstdlib>
void allCommands();
int main(int argc, char * argv[]) {

  // gets the hash table size from the command line

  int hashSize = Table::HASH_SIZE;

  Table * grades;  // Table is dynamically allocated below, so we can call
                   // different constructors depending on input from the user.

  if (argc > 1) {
    hashSize = atoi(argv[1]);  // atoi converts c-string to int

    if (hashSize < 1) {
      cout << "Command line argument (hashSize) must be a positive number" 
	   << endl;
      return 1;
    }

    grades = new Table(hashSize);

  }
  else {   // no command line args given -- use default table size
    grades = new Table();
  }


  grades->hashStats(cout);

  // add more code here
  // Reminder: use -> when calling Table methods, since grades is type Table*

 int tester=1;
  
    int score;

    string name;
    
  string command;


    cout << "cmd>";


    while (tester) {
       

        cin >> command;


    if (command == "quit") {
         
            tester = 0;
         
            continue;
        }

       
   if (command == "print") {
          
            grades->printAll();
          
            cout << "cmd>";
          
            continue;
        }


        if (command == "lookup") {

            cin >> name;

            if (grades->lookup(name) != NULL) {
              
                cout  << name << " : " << *(grades->

                lookup(name)) << endl;
            } else {
                cout << "The student is not existed" << endl;
            }
            cout << "cmd>";

            continue;
        }


        if (command == "remove") {
      
            cin >> name;
      
            if (!grades->remove(name)) {
      
                cout << "The key value doesn't exist" << endl;
            }

            cout << "cmd>";
            continue;
        }

   if (command == "stats") {
         
            grades->hashStats(cout);
         
            cout << "cmd>";
         
            continue;
        }


     
        if (command == "size") {
           
            cout << grades->numEntries() << endl;
           
            cout << "cmd>";
           
            continue;
        }


       

        if (command == "change") {
            cin >> name;

            
            cin >> score;

            if (grades->remove(name)) {
              
                grades->insert(name, score);
            } 
            else {
                cout << "Change can't be made since no such student exists" << endl;
            }

            cout << "cmd>";
            
            continue;
        }


     

        if (command == "help") {
            
            allCommands();
            
            cout << "cmd>";
            
            continue;

        }

    

         if (command == "insert") {
              

            cin >> name;

              cin >> score;

       

            if (grades->lookup(name) == NULL) {

                grades->insert(name, score);
            } else {

                cout << "Student already present" << endl;

            }
           
            cout << "cmd>";
            
            continue;
        }



        
        cout << "ERROR: invalid command" << endl;
        
        allCommands();
        
        cout << "cmd>";

    }

    return 0;
}

//print all the commands available to the client
void allCommands() {
    cout << "All the commands for this Program" << endl;
  
    cout << "insert name score" << endl;
  
    cout << "change name newscore" << endl;
  
    cout << "lookup name" << endl;
  
    cout << "remove name" << endl;
  
    cout << "print" << endl;
  
    cout << "size" << endl;
  
    cout << "stats" << endl;
  
    cout << "help" << endl;
  
    cout << "quit" << endl;
}
