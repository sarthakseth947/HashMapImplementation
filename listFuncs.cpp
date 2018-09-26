// Name:Sarthak seth    
// USC NetID:sethsart@usc.edu
// CSCI 455 PA5
// Spring 2018


#include <iostream>

#include <cassert>

#include "listFuncs.h"

using namespace std;

Node::Node(const string &theKey, int theValue) {
  key = theKey;
  value = theValue;
  next = NULL;
}

Node::Node(const string &theKey, int theValue, Node *n) {
  key = theKey;
  value = theValue;
  next = n;
}




//*************************************************************************
// put the function definitions for your list functions below

//check if the key is present in the list
bool listContainsKeyItems(ListType list, string key1) {
    ListType n = list;

    while (n != NULL) {
      
        if (n->key == key1) {
           
            return true;

        }
        n = n->next;
    }
    return false;
}


//check the size of list items
int listSizeItems(ListType list) {
   
    ListType n = list;
    
    int size = 0;
    
    while (n != NULL) {
        
        size++;
        
        n = n->next;
    }
    return size;
}


//lookup items in a list
int *listLookUpItems(ListType list, string key1) {
   
    ListType n = list;
    
    while (n != NULL) {
       
        if (n->key == key1) {
           
            return &(n->value);
        }
        n = n->next;
    }

    return NULL;


}
//remove items from a list
bool listRemoveItems(ListType &list, string key1) {
 
    ListType current = list;
    
    ListType previous = current;

   

    if (current->key == key1) {
        
        list = current->next;
        
        return true;
    }

     if (!listContainsKeyItems(list, key1)) {
        
        return false;
    }


    while (current != NULL) {
        if (current->key == key1) {
            
            previous->next = current->next;
            
            return true;
        }
        
        previous = current;
        
        current = current->next;
    }

    return false;


}


//insert items in the list
bool listInsertItems(ListType &list, string key1, int value) {
       ListType n = list;

    if (list == NULL) {
        list = new Node(key1, value);
        return true;
    }
 if (listContainsKeyItems(list, key1)) {
        return false;
    }



    while (n->next != NULL) {
        n = n->next;
    }
    ListType newnod = new Node(key1, value);
    
    n->next = newnod;
    
    return true;
}

// print items in a list
void listPrintItems(ListType list) {
    ListType n = list;
    
    while (n != NULL) {
      
        cout << n->key << " " << n->value << endl;
      
        n = n->next;
    }
}

