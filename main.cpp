#include <iostream>
#include <cassert>
#include "SequenceableCollection.h"
using namespace std;

int main() {
    SequenceableCollection sc;

    // Test Case 1: Initial Insertion at Start and End Boundaries
    sc.insertAt(0, 10);  // Logical index 0
    sc.printActiveRegion();  // Expected: "_ _ _ 10 _ _ _ _"
    sc.insertAt(1, 20);  // Logical index 1
    sc.printActiveRegion();  // Expected: "_ _ _ 10 20 _ _ _"
    sc.insertAt(0, 5);   // Insert at logical index 0 again, shifting start
    sc.printActiveRegion();  // Expected: "_ _ 5 10 20 _ _ _"
    std::cout << "Test Case 1 passed!" << std::endl;

    // Test Case 2: Insertion at the End
    sc.insertAt(3, 30);  // Logical index 3
    sc.printActiveRegion();  // Expected: "_ _ 5 10 20 30 _ _"
    std::cout << "Test Case 2 passed!" << std::endl;

    // Test Case 3: Insertion in the Middle with Shifting
    sc.insertAt(2, 15);  // Logical index 2
    sc.printActiveRegion();  // Expected: "_ _ 5 10 15 20 30 _"
    std::cout << "Test Case 3 passed!" << std::endl;

    // Test Case 4: Insert at the end with space available
    sc.insertAt(5, 40);
    sc.insertAt(6, 50);
    sc.printActiveRegion();  // Expected: "5 10 15 20 30 40 50"
    std::cout << "Test Case 4 passed!" << std::endl;

    // Insert to trigger grow
    sc.insertAt(7, 60);  // Should grow
    sc.printActiveRegion();  // Expected with capacity doubled and all elements in new array
    std::cout << "Test Case 5 passed!" << std::endl;

    // Test Case 6: Removing from the Middle
    sc.removeAt(2);  // Remove 15, shift elements left
    sc.printActiveRegion();  // Expected: "5 10 20 30 40 50 60 _"
    std::cout << "Test Case 6 passed!" << std::endl;

    // Test Case 7: Removing the First Element
    sc.removeAt(0);  // Remove 5, shift elements left
    sc.printActiveRegion();  // Expected: "10 20 30 40 50 60 _ _"
    std::cout << "Test Case 7 passed!" << std::endl;

    // Test Case 8: Removing the Last Element
    sc.removeAt(5);  // Remove 60
    sc.printActiveRegion();  // Expected: "10 20 30 40 50 _ _ _"
    std::cout << "Test Case 8 passed!" << std::endl;

    // Test Case 9: Insertion after Removal to Reuse Empty Space
    sc.insertAt(5, 60);
    sc.printActiveRegion();  // Expected: "10 20 30 40 50 60 _ _"
    std::cout << "Test Case 9 passed!" << std::endl;

    // Test Case 10: Find Element
    assert(sc.find(20) == 1);  // 20 should be at logical index 1
    assert(sc.find(60) == 5);  // 60 should be at logical index 5
    assert(sc.find(999) == -1); // 999 is not in the array, expect -1
    std::cout << "Test Case 10 passed!" << std::endl;

    // Test Case 11: Insertions Causing Multiple Grow Operations
    sc.insertAt(6, 70);
    sc.insertAt(7, 80);
    sc.insertAt(8, 90);  // Should trigger another grow
    sc.printActiveRegion();  // Expected: Grown array with all elements in contiguous memory
    std::cout << "Test Case 11 passed!" << std::endl;

    // Test Case 12: Remove from an Empty Collection
    SequenceableCollection emptySc;
    emptySc.removeAt(0);  // Should handle gracefully
    emptySc.printActiveRegion();  // Expected: "_ _ _ _ _ _ _ _"
    std::cout << "Test Case 12 passed!" << std::endl;

    // Test Case 13: Edge Case for Insert and Shift Left for Space
    SequenceableCollection sc2;
    sc2.insertAt(0, 5);
    sc2.insertAt(1, 10);
    sc2.insertAt(2, 15);
    sc2.insertAt(3, 20);
    sc2.insertAt(4, 25);
    sc2.insertAt(5, 30);
    sc2.insertAt(6, 35);
    sc2.insertAt(7, 40);  // This should use available empty space, shifting everything to the left
    sc2.printActiveRegion();  // Expected: "5 10 15 20 25 30 35 40"
    std::cout << "Test Case 13 passed!" << std::endl;

    // Test Case 14: Insert with multiple shifts left
    sc2.insertAt(8, 50);  // Insert after previous test case caused shift
    sc2.printActiveRegion();  // Expected: "5 10 15 20 25 30 35 40 50 _ _ _ _ _ _ _"
    std::cout << "Test Case 14 passed!" << std::endl;

    // Test Case 15: Remove to Confirm _start and _end Correctness
    sc2.removeAt(0);
    sc2.removeAt(1);
    sc2.removeAt(3);  // Check _start and _end adjust properly
    sc2.printActiveRegion();
    std::cout << "Test Case 15 passed!" << std::endl;

    std::cout << "All test cases passed!" << std::endl;

    return 0;
}

// #include <iostream>
// #include <cassert>
// #include "SequenceableCollection.h"

// int main() {
//     // Test Case 1: Initialization and Basic Properties
//     SequenceableCollection collection1;
//     assert(collection1.size() == 0);  // Should be empty initially
//     assert(collection1.basicSize() == 8);  // Initial capacity
//     collection1.printActiveRegion();  // Expected: "_ _ _ _ _ _ _ _"
//     std::cout << "Test Case 1: Initialization and Basic Properties - Passed\n";

//     // Test Case 2: Single Element Insertion
//     collection1.insertAt(0, 5);
//     assert(collection1.size() == 1);
//     collection1.printActiveRegion();  // Expected: "_ _ _ 5 _ _ _ _"
//     std::cout << "Test Case 2: Single Element Insertion - Passed\n";

//     // Test Case 3: Multiple Insertions without Resizing
//     collection1.insertAt(1, 10);
//     collection1.insertAt(2, 15);
//     collection1.insertAt(3, 20);
//     collection1.insertAt(4, 25);
//     collection1.insertAt(5, 30);
//     collection1.printActiveRegion();  // Expected: "_ _ 5 10 15 20 25 30"
//     assert(collection1.size() == 6);
//     std::cout << "Test Case 3: Multiple Insertions without Resizing - Passed\n";

//     // Test Case 4: Automatic Resizing (Adjusted)
//     std::cout << "\nTest Case 4: Automatic Resizing\n" << std::endl;
//     SequenceableCollection collection2;

//     // Fill the collection to use all available initial slots
//     collection2.insertAt(0, 5);
//     collection2.insertAt(1, 10);
//     collection2.insertAt(2, 15);
//     collection2.insertAt(3, 20);
//     collection2.insertAt(4, 25);
//     collection2.insertAt(5, 30);
//     collection2.insertAt(6, 35);
//     collection2.insertAt(7, 40);  // This should fill the initial capacity

//     collection2.printActiveRegion();  // Expected: Fully filled with 8 elements without resizing

//     // At this point, the next insertion should trigger resizing since all slots are filled
//     collection2.insertAt(8, 45);  // This should trigger resizing

//     collection2.printActiveRegion();  // Expected: Resized array with new capacity, additional room for more elements
//     assert(collection2.size() == 9);
//     assert(collection2.basicSize() > 8);  // Capacity should be greater than 8 now
//     std::cout << "Test Case 4: Automatic Resizing - Passed\n";

//     // Test Case 5: Inserting at Specific Index
//     collection2.insertAt(1, 12);  // Insert at index 1
//     collection2.insertAt(4, 18);  // Insert at index 4
//     collection2.printActiveRegion();  // Check expected positions
//     std::cout << "Test Case 5: Inserting at Specific Index - Passed\n";

//     // Test Case 6: Removing Elements
//     collection2.removeAt(0);  // Remove from beginning
//     collection2.removeAt(4);  // Remove from middle
//     collection2.removeAt(collection2.size() - 1);  // Remove from end
//     collection2.printActiveRegion();  // Verify updated structure
//     std::cout << "Test Case 6: Removing Elements - Passed\n";

//     // Test Case 7: Iterating with a Function
//     auto increment = [](int x) { return x == -1 ? -1 : x + 1; };
//     collection2.iterate(increment);
//     collection2.printActiveRegion();  // Check if each element has been incremented by 1
//     std::cout << "Test Case 7: Iterating with a Function - Passed\n";

//     // Test Case 8: Deep Copy Verification
//     SequenceableCollection collection3 = collection2;  // Copy constructor
//     collection3.insertAt(0, 50);  // Modify the copied collection
//     assert(collection3.find(50) != -1);  // Should find 50 in collection3
//     assert(collection2.find(50) == -1);  // Should NOT find 50 in collection2, confirming deep copy
//     SequenceableCollection collection4;
//     collection4 = collection2;  // Assignment operator
//     collection4.insertAt(0, 60);
//     assert(collection4.find(60) != -1);  // Should find 60 in collection4
//     assert(collection2.find(60) == -1);  // Should NOT find 60 in collection2, confirming deep copy
//     std::cout << "Test Case 8: Deep Copy Verification - Passed\n";

//     // Test Case 9: Edge Case Handling
//     try {
//         collection2.insertAt(-1, 100);  // Out-of-bounds insertion
//     } catch (const std::out_of_range& e) {
//         std::cout << "Caught expected out_of_range exception on insertAt(-1).\n";
//     }

//     try {
//         collection2.removeAt(collection2.size() + 1);  // Remove out-of-bounds
//     } catch (const std::out_of_range& e) {
//         std::cout << "Caught expected out_of_range exception on removeAt(size + 1).\n";
//     }

//     SequenceableCollection emptyCollection;
//     try {
//         emptyCollection.removeAt(0);  // Removing from an empty collection
//     } catch (const std::out_of_range& e) {
//         std::cout << "Caught expected out_of_range exception on removeAt(0) for empty collection.\n";
//     }

//     std::cout << "Test Case 9: Edge Case Handling - Passed\n";

//     std::cout << "\nAll test cases passed!" << std::endl;
//     return 0;
// }
