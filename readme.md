# Mounds: Array-Based Priority Queues

### About the project:

This project talks about the Mound data structure. Mounds are trees of sorted lists where the time complexity of insert() function which inserts a new value in the mound is O(log(log n)) and the time complexity of extractMin() function which extracts the least value present in the mound is O(log n), ‘n’ being the number of nodes in the tree.
The list present at each node of the tree is sorted, the first value being the least, and so are the nodes. The children of each node are greater in value than the parent. This is the mound property. 

## Getting Started

### Prerequisites:

A gcc compiler available with Ubuntu 20.04 OS

### Running the Code:

* Create a .txt file that contains the data set that is going to be used as input for our project. In this file, each new line should contain a new instance of the object. 
* Open this folder in the terminal and compile the DSA_assignment_group_15.c file using the command :

     ` gcc DSA_assignment_group_15.c `

* The executable 'a.out' is executed along with the data set file by running the command 

    ` ./a.out file_name.txt `

 where file_name.txt is the absolute path of the .txt file that contains the data set to be tested. 
* This will create an output.txt file which will contain the output of the extractAllValues() function which prints the result of extractMin() operation until the Mound is exhausted. This file is present in the current folder.
*In the output.txt file, each new line will contain an instance of the object.  


### Built With:
This project is built using C Programming Language. 

