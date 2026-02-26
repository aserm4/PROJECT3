#include "Bible.h"
#include <iostream>

using namespace std;

int main()
{
    // Create Bible object (this automatically builds the index)
    Bible bible("/home/class/csc3004/Bibles/web-complete");

    cout << endl;
    cout << "Testing index lookup offsets:" << endl;

    // Test references near beginning, middle, and end
    Ref ref1(1, 1, 1);       // Genesis 1:1
    Ref ref2(43, 3, 16);     // John 3:16
    Ref ref3(66, 5, 12);     // Revelation 5:12

    cout << "Genesis 1:1 offset: "
         << bible.lookupOffset(ref1) << endl;

    cout << "John 3:16 offset: "
         << bible.lookupOffset(ref2) << endl;

    cout << "Revelation 5:12 offset: "
         << bible.lookupOffset(ref3) << endl;

    cout << endl;
    cout << "Index test complete." << endl;

    return 0;
}