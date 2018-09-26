
// Name:Sarthak seth    
// USC NetID:sethsart@usc.edu
// CSCI 455 PA5
// Spring 2018

// Table.cpp  Table class implementation


#include "Table.h"

#include <iostream>
#include <string>
#include <cassert>


// listFuncs.h has the definition of Node and its methods.  -- when
// you complete it it will also have the function prototypes for your
// list functions.  With this #include, you can use Node type (and
// Node*, and ListType), and call those list functions from inside
// your Table methods, below.

#include "listFuncs.h"


//*************************************************************************


//Constructor function for table using default size
Table::Table() {
   

    hashSize = HASH_SIZE;
   
    table = new ListType[hashSize];
   
    numberOfEntries = 0;
   
    for (int i = 0; i < hashSize; i++) {
    
        table[i] = NULL;
    }

}

//Constructor to initialise size
Table::Table(unsigned int hasSize) {
    hashSize = hasSize;
   
    numberOfEntries = 0;
   
    table = new ListType[hashSize];
   
    for (int i = 0; i < hashSize; i++) {
   
        table[i] = NULL;
    }

}

//to print the elements in table
void Table::printAll() const {
    
    for (int i = 0; i < hashSize; i++) {
        
        listPrintItems(table[i]);
    }
}

//to remove element from table
bool Table::remove(const string &key) {
    
    int basket = hashCode(key);
    
    if (listRemoveItems(table[basket], key)) {
        numberOfEntries--;
       
        return true;
    } 
    else {
     
        return false;
    }


}

//to insert element to table
bool Table::insert(const string &key, int value) {
    
    int basket = hashCode(key);
    
    if (listInsertItems(table[basket], key, value)) {
    
        numberOfEntries++;
    
        return true;
    }
     else {
        return false;
    }
}

//to find the longest chain
int Table::numberOfLongestChain() const {
    int LongestChain = 0;

    for (int i = 0; i < hashSize; i++) {
      
        if (listSizeItems(table[i]) > LongestChain) {
      
            LongestChain = listSizeItems(table[i]);
        }
    }
    return LongestChain;
}

//to find number of buckets
int Table::numberOfBuckets() const {
    return hashSize;
}

//to find total number of entries
int Table::numEntries() const {
    return numberOfEntries;
}



//to find the number of non empty buckets
int Table::numberOfNonEmptyBuckets() const {
  
    int numberOfNonEmptyBuckets = 0;
  
    for (int i = 0; i < hashSize; i++) {
  
        if (table[i] != NULL) {
  
            numberOfNonEmptyBuckets++;
        }
    }
    return numberOfNonEmptyBuckets;
}



//to print out the initial information

void Table::hashStats(ostream &out) const {
    out << "number of buckets " << numberOfBuckets() << endl;
    
    out << "number of entries " << numEntries() << endl;
    
    out << "number of non-empty buckets " << numberOfNonEmptyBuckets() << endl;
    
    out << "longest chain " << numberOfLongestChain() << endl;

}

//to lookup element in the table
int *Table::lookup(const string &key) {
    int basket = hashCode(key);
  
  return listLookUpItems(table[basket], key);
}







// add definitions for your private methods here