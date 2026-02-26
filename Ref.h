#ifndef REF_H
#define REF_H

#include <string>
#include <stdlib.h>
using namespace std;

string GetNextToken(string& str, const string& delimiters = " ");

class Ref
{
private:
    short book, chapter, verse;

public:
    // Constructors
    Ref();
    Ref(const string s);          // "43:3:16"
    Ref(const int, const int, const int);

    // Accessors
    int getBook() const;
    int getChapter() const;
    int getVerse() const;

    // Comparison operators
    bool operator==(const Ref &) const;
    bool operator<(const Ref &) const;
    bool operator>(const Ref &) const;

    // Display reference
    void display() const;

    // Book conversions
    static int bookNameToNumber(const string& name);
    static string bookNumberToName(int num);
};

#endif // REF_H