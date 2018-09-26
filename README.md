# HashMapImplementation

In this program you will use C++ linked lists to implement a data structure
we have studied in this class: a hash table. The hash table is in a class
called Table (what you know as a map). To make it more interesting, we're
going to test our class in two different programs: one is a command-based test
driver you will write (a program to maintain student names and scores), and the
other is a C++ version of the concordance program we wrote in lab 10. We
wrote the concordance program for you.


To be able to use a C++ class in multiple programs, but not end up with
multiple versions of our class code, these are going to be multi-file programs
that use separate compilation.
• The implementation file (suffix .cpp) contains the implementation of the
methods. That is, the complete method definitions for all the methods,
public and private. This file needs to #include the class header file
(i.e., Table.h). We started your Table.cpp, and put the necessary
 #include in it.
This program is also going to contain a second separately-compiled module,
although it's one that does not have a class in it. It's going to be a module with
our Nodestruct and all the functions for operating on a linked list of that node
type . This module is needed for the chaining in your hash table. That module
will also have a header file plus an implementation file. It is described in more
detail in the section on linked list functions. Since this module is only used in
the Tableimplementation the #include statement for its header file is only
in Table.cpp (and <listfuncs.cpp< kbd="" style="color: rgb(0, 0, 0); font-family: 
"Times New Roman"; font-size: medium; font-style: normal; font-variant-ligatures:
normal; font-variant-caps: normal; font-weight: normal; letter-spacing: normal; orphans:
2; text-align: start; text-indent: 0px; text-transform: none; white-space: normal; widows:
2; word-spacing: 0px; -webkit-text-stroke-width: 0px;">). In particular Table.h does not
depend on what is in the list module.
To make a complete program from the files that comprise the Table class, plus the linked
list module, we need another source code file with main in it (suffix .cpp ). This file
could also have other helper functions used by main. It needs to #include the header file
for any classes it uses. For the grades program we already put the necessary #include
statement in grades.cpp for you. See concord.cpp as an example of a completed Table
client program.


#Compiling the program

For this PROGRAM the Makefile we wrote for you takes care of creating the necessary
executables from the various source code files. The Makefile has comments that explain
how to use it for the various tasks it was made for. Repeated here is how you use it to
compile your programs (the following are Unix shell commands that will work when the
Makefile is in the same directory as your source code):
gmake grades
Makes the grades executable.
gmake concord
Makes the concord executable.
gmake pa5list
Makes the pa5list executable.(See milestone section for details.)
To clarify, you use one of the gmake commands above instead of using g++. Note: The
Makefile will also create some .o files in your directory, which are compiled versions of
the different program modules (roughly analogous to Java .class files).
The Table class
Table interface
The Table class is similar in functionality to the Java Map class. To simplify your
implementation, this one does not use C++ templates (= Java generics), but is fixed to use
a key type of string and a value type of int. Also to keep things simple, there is no
iterator interface: the only way to visit all the elements is via the printAll function.
The exact interface for the Table class is given in Table.h. You are not allowed to change
the interface (i.e., public section) for this class.
The concord program: Example of using the Table class We wrote a complete
program that uses the Table class, concord.cpp. This is a concordance program like the
one we did in an earlier Java lecture and that we enhanced in one of our labs, but that
uses the Table class we're implementing here. This version filters words, but it does not
sort the output. We wrote this whole program for you -- you will just need to complete
your Table class to be able to compile and run it successfully.
Please read the code in concord.cpp, to see examples of how to call the Table methods,
and what they do. In particular, you can see that, since lookup returns a pointer to the
value that goes with the given key, we can use lookup not only to access that value, but
also to update the value.
Info about hashStats parameter The hashStats() method is parameterized so you can
use it to print out to different output streams at different times. One of these streams
is cout and another is cerr (more about cerr in the comments at the top of concord.cpp).
You write the print statements in this function just as if you were writing to cout, but you
use the parameter instead. Here's an example of defining and calling a function with
an ostream parameter:
// Param "out" is the output stream to write to.
// (passed by reference, because "<<" updates the stream object)
void testOut(ostream &out) {
 out << "Hello there!" << endl;
}
. . .
// example calls:
 testOut(cout);
 testOut(cerr);
You can see an example call to hashStats in the main function in in concord.cpp.
Table implementation
You are required to implement your Table class using a hash table that you implement.
This hash table will use chaining via linked lists. For this assignment you may not use 
STL container classes or any other classes or functions not implemented by you (a few
exceptions: C++ string, the I/O library, and a hash function from the library that is
called in the starter code).
Since the key type is fixed for this hash table, we can fix what the hash function is too.
We wrote the hash function for you. It's defined in the private section of the Table class.
Note: to compare two C++ strings for equality, you use ==. By the way, the other
relational operators are also defined for strings as well.
Unlike the Java HashMap, our hash table will be a fixed size once it gets created. There
are two constructors for the Table class; one that uses a constant in Table to determine the
size, and another that gets the size to use in a parameter. The latter makes the class more
flexible; but we also included it to make it easy for you to test your code on very small
hash table sizes so you can force collisions to occur.
Dynamic arrays.
An implication of the client-specified hash size discussed in the previous paragraph is
that our representation has to involve a dynamic array, rather than a fixed size array.
Remember that with a fixed-size array in C++, the size is fixed at compile-time, so it's
impossible to use a value specified from the client/user. Once we create the dynamic
array in our table, however, its size won't change.
Creating a dynamic array looks a lot like creating a Java array, except we use a pointer
type. The pointer points to the first element in the array. However, once the array is
created we can use normal [] syntax to reference elements.
Here is some example code:
int * arr; // var decl for a dynamic array of integers
arr = new int[10]; // create an array of 10 ints
 // (unlike in java, array elements are not automatically
initialized)
arr[3] = 7; // put a 7 in a[3]
cout << arr[10]; // error: invalid array index (exact behavior
undefined)
delete [] arr; // reclaim memory for the array
 // (use [] form of delete with anything allocated with [] form
of new)
The syntax for declaring our array will be a little hairy, because the element type itself
will be a pointer. Each element is going to be a Node* for a linked list:
Node* * data; // decl for array of pointers to Node (yes, need two *'s)
data = new Node*[100]; // allocate an array of 100 pointers to Node
data[0]; // this expression is type Node*
This example should be helpful for you to get started with working with this type in the
Table class. We have defined the ListType typedef for you already to help abstract the
list part of things. Here's the code we just saw using ListType instead:
typedef Node * ListType;
ListType * data;
data = new ListType[100];
data[0]; // this expression is type ListType (= Node*)
Linked list functions.
One requirement for managing the complexity of the Table class representation, and
keeping different levels of abstraction straight is to write linked list routines that take
ListType as a parameter to do each of the necessary linked list operations for dealing with
a hash chain. For example, one such function might be:
bool listRemove(ListType & list, string target);
When your Table code calls listRemove, it would pass to it one element of the hash table
array (i.e., one chain, or one hash bucket).
You are required to define these functions as regular functions in listFuncs.cpp, rather
than trying to make them part of the Table class. Because we are writing them as a
separately compilable module, we will also need to put their prototypes in listFuncs.h.
 The advantage of a separate module is it makes it easy to test them
independently from the Table class, and then later use them directly the Table class
implementation. In a later section we discuss a plan for testing these functions
independently.
Copy semantics and reclaiming memory.
The Table class contains dynamic data, so we need to be concerned about how table
objects get copied. When we pass an object by value, the formal parameter is initialized
using something called the copy constructor. When we assign one object to another we
use the assignment (=) operator. C++ supplies built-in versions of these two methods;
however, the built-in versions only do a shallow copy, so do not work correctly for
objects that contain dynamic data. It's a little bit tricky to define these correctly to do
deep copy, so we are going opt for something simpler here: we are going
to disallow copying our Table objects. We do this by making the headers for those
methods private. We already put the code to disallow copies in your Table.h file; you do
not need to do anything else for this to work the way we want. Table objects can still be 
used as parameters passed by reference or const-reference, since that doesn't involve
copying the object.
[One note for future reference: even if you create a class that disallows copies, you
normally would define another method, called a destructor, that reclaims the dynamic
memory when a client is done with your object. We won't have time to discuss that topic
in detail, and not having it won't really matter for the way we are using Tables in our
client programs here, so our Table class is not going to define a destructor.]
Note: you should still reclaim the Node memory no longer needed in when you remove
an entry from the Table.
grades program
This is going to be a simple program to keep track of students and their scores in a class.
It's not meant to be ultra-realistic (for example, only one score per name, and no way to
save scores), but it's really a test driver for your Table implementation.
The program takes one optional command-line argument, the size for the hash table -- if
the argument is left off, the program uses the default hash size. We have already written
the code to deal with the command line argument (you can see the starter code here).
When the program starts up it creates a hash table, immediately prints out the hashStats()
for that empty table, and then should print the initial command prompt ("cmd> "). In the
following example of program startup % is the Unix shell prompt and user input is shown
in italics
% grades 7
number of buckets: 7
number of entries: 0
number of non-empty buckets: 0
longest chain: 0
cmd>
Once this start-up happens the program repeatedly reads and executes commands from
the user, printing out the command prompt (cmd>) after it finishes the previous command,
until the user enters the quit command.
Here are the commands for the program (in the following a name will always be a single
word):
insert name score
Insert this name and score in the grade table. If this name was already present,
print a message to that effect, and don't do the insert.
change name newscore
Change the score for name. Print an appropriate message if this name isn't
present.
lookup name
Lookup the name, and print out his or her score, or a message indicating that
student is not in the table.
remove name
Remove this student. If this student wasn't in the grade table, print a message to
that effect.
print
Prints out all names and scores in the table.
size
Prints out the number of entries in the table.
stats
Prints out statistics about the hash table at this point. (Calls hashStats() method)
help
Prints out a brief command summary.
quit
Exits the program.
The only error-checking required for this program is for you to print out "ERROR:
invalid command", and the command summary (see 'help' command) if a user give an
invalid command name. Once you print the message your program should then display
another command prompt.
So, for example, you do not have to check whether the user has entered the correct
number of arguments or the correct type of arguments for a command (i.e., the graders
will not test your program on those conditions).
Note: this program enables you to test all of the table methods.
Using the concord program to test Table
Once you are convinced your Table class works with the other test program, you should
use concord.cpp program along with the .txt files that came with the assignment to test
your Table class with a larger amount of data. This program does not use all of the Table
methods, so is not suitable as a complete test of your Table class. See comments
in concord.cpp for how to run it.


