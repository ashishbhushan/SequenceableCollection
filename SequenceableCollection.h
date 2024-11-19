#ifndef SEQUENCEABLE_COLLECTION_H
#define SEQUENCEABLE_COLLECTION_H

#include <stdexcept>  // For handling exceptions if needed

class SequenceableCollection {
private:
    int* _data;       // Pointer to dynamically allocated array
    int _start;       // Start index of the active region
    int _physicalIndex;
    int _end;         // End index of the active region
    int _capacity;    // Total allocated size of the array

    void grow();      // Method to double the array size when needed

public:
    SequenceableCollection();                        // Default constructor
    SequenceableCollection(int initialElem);         // Constructor with initial element
    SequenceableCollection(const SequenceableCollection& other); // Copy constructor
    SequenceableCollection& operator=(const SequenceableCollection& other); // Copy assignment
    ~SequenceableCollection();                       // Destructor

    int basicSize() const;                           // Returns the capacity of the array
    int size() const;                                // Returns the number of elements
    int logicalToPhysicalIndex(int logicalIndex) const;     // Translating Logical to Physical Index
    SequenceableCollection& insertAt(int i, int x);  // Insert element at position i
    void shiftLeft(int i);
    void shiftRight(int i);
    int find(int x) const;                           // Find element x
    SequenceableCollection& removeAt(int i);         // Remove element at position i
    SequenceableCollection& iterate(int (*fn)(int)); // Apply function to each element
    void printActiveRegion() const; // Public function to print the active region
};

#endif // SEQUENCEABLE_COLLECTION_H
