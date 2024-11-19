#include "SequenceableCollection.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

// Default constructor
SequenceableCollection::SequenceableCollection()
    : _data(new int[8]), _start(3), _end(2), _capacity(8) { 
        std::fill(_data, _data + _capacity, -1); // Initialize all elements to -1
}

// Constructor with an initial element
SequenceableCollection::SequenceableCollection(int initialElem)
    : SequenceableCollection() {
    _data[_start] = initialElem;
    _end = _start;
}

// Copy constructor
SequenceableCollection::SequenceableCollection(const SequenceableCollection& other)
    : _data(new int[other._capacity]), _start(other._start), _end(other._end), _capacity(other._capacity) {
    for (int i = _start; i <= _end; ++i) {
        _data[i] = other._data[i];
    }
}

// Copy assignment operator
SequenceableCollection& SequenceableCollection::operator=(const SequenceableCollection& other) {
    if (this == &other) return *this; // Handle self-assignment

    delete[] _data; // Free existing resources

    // Copy data from `other`
    _data = new int[other._capacity];
    _capacity = other._capacity;
    _start = other._start;
    _end = other._end;

    for (int i = _start; i <= _end; ++i) {
        _data[i] = other._data[i];
    }

    return *this;
}

// Destructor
SequenceableCollection::~SequenceableCollection() {
    delete[] _data;
}

// Return the total allocated size of the array
int SequenceableCollection::basicSize() const {
    return _capacity;
}

// Return the number of elements in the collection
int SequenceableCollection::size() const {
    return (_end >= _start) ? (_end - _start + 1) : 0;
}

// Translating Logical to Physical Index
int SequenceableCollection::logicalToPhysicalIndex(int logicalIndex) const {
    return _start + logicalIndex;
}

SequenceableCollection& SequenceableCollection::insertAt(int logicalIndex, int x) {
    int i = _start + logicalIndex;  // Map logical index to physical index

    // If logical index exceeds the current capacity, attempt to shift left if possible
    if (i >= _capacity && _start > 0) {
        int shiftAmount = _start;
        for (int j = _start; j <= _end; ++j) {
            _data[j - shiftAmount] = _data[j];
        }
        std::fill(_data + _end - shiftAmount + 1, _data + _capacity, -1); // Mark the freed spaces as empty
        _end -= shiftAmount;
        _start = 0;
        i = _end + 1;  // Adjust `i` to the new position after the shift
        std::cout << "Shifted left to make space. New start: " << _start << ", end: " << _end << "\n";
    }

    // Trigger `grow` only if we can't shift left and there's no room in the current capacity
    if (i >= _capacity) {
        grow();
        std::cout << "Array grew to accommodate new insertion.\n";
    }

    std::cout << "Before insertion: start = " << _start << ", end = " << _end << ", capacity = " << _capacity << "\n";

    // Initial insertion if the collection is empty
    if (_start > _end) {
        _start = 3;
        _end = 3;
        i = _start + logicalIndex;
        std::cout << "Inserting " << x << " at logical index " << logicalIndex << ", physical index " << i << "\n";
        _data[i] = x;
    } else if (logicalIndex == 0 && _start > 0) {
        // Insert at the beginning of the active region by shifting `_start` left
        _start--;
        i = _start + logicalIndex;
        std::cout << "Inserting " << x << " at logical index " << logicalIndex << ", physical index " << i << "\n";
        _data[_start] = x;
    } else if (logicalIndex == (_end - _start + 1)) {
        // Insert at the end of the active region by shifting `_end` right
        _end++;
        i = _start + logicalIndex;
        std::cout << "Inserting " << x << " at logical index " << logicalIndex << ", physical index " << i << "\n";
        _data[_end] = x;
    } else if (i >= _start && i <= _end) {
        // Calculate midpoint based on the number of elements in the active region
        int numElements = _end - _start + 1;
        double midpoint = numElements / 2.0;

        // Determine whether to shift left or right based on the midpoint
        if (logicalIndex < midpoint) {
            // Closer to `_start`: Shift left to create space at `i`
            for (int j = _start - 1; j < i; ++j) {
                _data[j] = _data[j + 1];
            }
            _start--;
            i = _start + logicalIndex;
            std::cout << "Inserting " << x << " at logical index " << logicalIndex << ", physical index " << i << "\n";
            _data[i] = x;
        } else {
            // Closer to `_end`: Shift right to create space at `i`
            _end++;  // Move `_end` one position right
            for (int j = _end; j > i; --j) {
                _data[j] = _data[j - 1];
            }
            i = _start + logicalIndex;
            std::cout << "Inserting " << x << " at logical index " << logicalIndex << ", physical index " << i << "\n";
            _data[i] = x;
        }
    } else {
        throw std::out_of_range("Logical index out of bounds");
    }

    std::cout << "After insertion: start = " << _start << ", end = " << _end << "\n";
    std::cout << "Data array from start to end: ";
    for (int k = 0; k < _capacity; ++k) {
        if (k >= _start && k <= _end) {
            std::cout << _data[k] << " ";
        } else {
            std::cout << "_ "; // Represent uninitialized space as _
        }
    }
    std::cout << "\n\n";

    return *this;
}


// Find element x and return its index, or -1 if not found
int SequenceableCollection::find(int x) const {
    for (int i = _start; i <= _end; ++i) {
        if (_data[i] == x) {
            // return i;
            return i - _start;  // Return logical index
        }
    }
    return -1;  // Return -1 if not found
}

// Remove element from position i
SequenceableCollection& SequenceableCollection::removeAt(int logicalIndex) {
    int i = logicalToPhysicalIndex(logicalIndex);  // Convert logical index to physical index

    std::cout << "Before removal: start = " << _start << ", end = " << _end << ", capacity = " << _capacity << "\n";

    // Check if `i` is within bounds
    if (i < _start || i > _end) {
        return *this;  // No action if index out of bounds
    }

    // Determine whether to shift left or right based on proximity to `_start` or `_end`
    if (i - _start < _end - i) {
        // Closer to `_start`: shift all elements from `_start` to `i-1` one position right
        for (int j = i; j > _start; --j) {
            _data[j] = _data[j - 1];
        }
        _data[_start] = -1;  // Mark the previous `_start` as empty (optional)
        _start++;  // Move `_start` right
    } else {
        // Closer to `_end`: shift all elements from `i+1` to `_end` one position left
        for (int j = i; j < _end; ++j) {
            _data[j] = _data[j + 1];
        }
        _data[_end] = -1;  // Mark the previous `_end` as empty (optional)
        _end--;  // Move `_end` left
    }

    std::cout << "After removal: start = " << _start << ", end = " << _end << "\n";
    std::cout << "Data array from start to end: ";
    for (int k = 0; k < _capacity; ++k) {
        if (k >= _start && k <= _end) {
            std::cout << _data[k] << " ";
        } else {
            std::cout << "_ "; // Represent uninitialized space as _
        }
    }
    std::cout << "\n\n";

    return *this;
}

// Apply function fn to each element in the collection
SequenceableCollection& SequenceableCollection::iterate(int (*fn)(int)) {
    for (int i = _start; i <= _end; ++i) {
        _data[i] = fn(_data[i]);
    }
    return *this;
}

// Grow the array by doubling its capacity
void SequenceableCollection::grow() {
    int newCapacity = _capacity * 2;
    int* newData = new int[newCapacity];

    // Initialize newArray with a default value (e.g., -1)
    for (int i = 0; i < newCapacity; i++) {
        newData[i] = -1;
    }

    // Copy elements to the new array, keeping them in the same relative positions
    for (int i = _start; i <= _end; ++i) {
        newData[i] = _data[i];
    }

    std::cout<<"Array grows! New Array: ";
    std::for_each(newData, newData + newCapacity, [](int val) { std::cout << val << " "; });
    std::cout<<endl;

    delete[] _data; // Free old memory
    _data = newData;
    _capacity = newCapacity;
}

void SequenceableCollection::printActiveRegion() const {
    std::cout << "Array: ";
    for (int i = 0; i < _capacity; ++i) {
        std::cout << _data[i] << " ";
    }
    std::cout << std::endl << std::endl;
}
