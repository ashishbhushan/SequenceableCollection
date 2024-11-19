# SequenceableCollection Project

This project implements a `SequenceableCollection` class in C++ with dynamic memory management, element insertion, deletion, iteration, and deep copying. The class supports efficient resizing and contiguity of elements, and handles shifting of elements based on insertion location.

## Files Included

- `SequenceableCollection.h`: Header file containing the `SequenceableCollection` class declaration.
- `SequenceableCollection.cpp`: Implementation file for the `SequenceableCollection` class.
- `main.cpp`: Contains test cases for verifying the functionality of the `SequenceableCollection` class.
- `.vscode/settings.json` and `.vscode/tasks.json`: VS Code configuration files to assist with project setup and build.

## Requirements

- C++ compiler with C++11 support
- Compatible with `g++` for compilation

## Class Overview

The `SequenceableCollection` class manages a dynamically sized collection of integers. Key features include:

- **Dynamic Resizing**: Automatically doubles capacity when full.
- **Contiguous Memory Management**: Ensures all elements are stored contiguously.
- **Insert and Remove**: Allows insertion at specific indices with proper shifting, and removal of elements.
- **Deep Copy**: Supports deep copying through a custom copy constructor and assignment operator.
- **Iteration**: Allows application of a function to each element in the collection.
  
## Compilation and Execution

### Compile

To compile the project, navigate to the project directory and run the following command:

${folderLocation} is the location of the folder where all the files are present.
I am using Visual Studio Code for developing and running this project.

```bash
g++ -std=c++11 -o ${folderLocation}/main.exe ${folderLocation}/main.cpp ${folderLocation}/SequenceableCollection.cpp

Example:
g++ -std=c++11 -o C:/ashish/vscode/cs474mp3/main.exe C:/ashish/vscode/cs474mp3/main.cpp C:/ashish/vscode/cs474mp3/SequenceableCollection.cpp
```

Run
After successful compilation, execute the following command to run the compiled program:

```bash
./main.exe
```

Test Cases
The main.cpp file includes a series of test cases that cover the following functionalities:

Initialization and Basic Properties: Verifies the initial state of an empty collection.
Single Element Insertion: Tests insertion of a single element.
Multiple Insertions without Resizing: Inserts elements to fill the initial capacity.
Automatic Resizing: Validates resizing by inserting beyond initial capacity.
Inserting at Specific Index: Checks shifting logic for inserting at a specific index.
Removing Elements: Ensures correct behavior when removing elements.
Iterating with a Function: Applies a function to each element and verifies results.
Deep Copy Verification: Confirms that the copy constructor and assignment operator perform deep copies.
Edge Case Handling: Tests inserting out-of-bounds and removing from an empty collection.

Notes
The SequenceableCollection class handles memory management with new and delete[] to avoid memory leaks.
Ensure that all assertions pass to verify that the SequenceableCollection class functions as expected.
