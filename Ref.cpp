#include "Ref.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
using namespace std;

// GetNextToken
string GetNextToken(string& str, const string& delimiters)
{
    string::size_type startPos = str.find_first_not_of(delimiters, 0);
    string::size_type endPos = str.find_first_of(delimiters, startPos);

    string next = str.substr(startPos, endPos - startPos);

    string rest = (endPos == string::npos) ? "" : str.substr(endPos + 1);
    str = rest;
    return next;
}

// Constructors
Ref::Ref() : book(0), chapter(0), verse(0) {}

Ref::Ref(const string s)
{
    string rtext = s;
    book = atoi(GetNextToken(rtext, ":").c_str());
    chapter = atoi(GetNextToken(rtext, ":").c_str());
    verse = atoi(GetNextToken(rtext, " ").c_str());
}

Ref::Ref(const int b, const int c, const int v) : book(b), chapter(c), verse(v) {}

// Accessors
int Ref::getBook() const { return book; }
int Ref::getChapter() const { return chapter; }
int Ref::getVerse() const { return verse; }

// Comparison operators
bool Ref::operator==(const Ref & ref) const
{
    return book == ref.book && chapter == ref.chapter && verse == ref.verse;
}

bool Ref::operator<(const Ref & ref) const
{
    if (book != ref.book) 
    {
       return book < ref.book;
    }
    if (chapter != ref.chapter) 
    {
       return chapter < ref.chapter;
    }

    return verse < ref.verse;
}

bool Ref::operator>(const Ref & ref) const
{
    if (book != ref.book) 
    {
       return book > ref.book;
    }
    if (chapter != ref.chapter) 
    {
       return chapter > ref.chapter;
    }

    return verse > ref.verse;
}

// Display
void Ref::display() const
{
    if (book >= 1 && book <= 66)
        cout << bookNumberToName(book);
    else
        cout << book;
    cout << " " << chapter << ":" << verse;
}

// Book name ? number
int Ref::bookNameToNumber(const string& name)
{
    static const string books[] = {
        "", "Genesis","Exodus","Leviticus","Numbers","Deuteronomy","Joshua","Judges","Ruth",
        "1Samuel","2Samuel","1Kings","2Kings","1Chronicles","2Chronicles","Ezra","Nehemiah",
        "Esther","Job","Psalms","Proverbs","Ecclesiastes","Song","Isaiah","Jeremiah","Lamentations",
        "Ezekiel","Daniel","Hosea","Joel","Amos","Obadiah","Jonah","Micah","Nahum","Habakkuk",
        "Zephaniah","Haggai","Zechariah","Malachi","Matthew","Mark","Luke","John","Acts","Romans",
        "1Corinthians","2Corinthians","Galatians","Ephesians","Philippians","Colossians",
        "1Thessalonians","2Thessalonians","1Timothy","2Timothy","Titus","Philemon","Hebrews",
        "James","1Peter","2Peter","1John","2John","3John","Jude","Revelation"
    };

    string lowerName = name;
    for (char &c : lowerName) if (isupper(c)) c = tolower(c);

    for (int i = 1; i <= 66; ++i)
    {
        string lowerBook = books[i];
        for (char &c : lowerBook) if (isupper(c)) c = tolower(c);
        if (lowerBook == lowerName) return i;
    }
    return 0;
}

string Ref::bookNumberToName(int num)
{
    static const string books[] = {
        "", "Genesis","Exodus","Leviticus","Numbers","Deuteronomy","Joshua","Judges","Ruth",
        "1Samuel","2Samuel","1Kings","2Kings","1Chronicles","2Chronicles","Ezra","Nehemiah",
        "Esther","Job","Psalms","Proverbs","Ecclesiastes","Song","Isaiah","Jeremiah","Lamentations",
        "Ezekiel","Daniel","Hosea","Joel","Amos","Obadiah","Jonah","Micah","Nahum","Habakkuk",
        "Zephaniah","Haggai","Zechariah","Malachi","Matthew","Mark","Luke","John","Acts","Romans",
        "1Corinthians","2Corinthians","Galatians","Ephesians","Philippians","Colossians",
        "1Thessalonians","2Thessalonians","1Timothy","2Timothy","Titus","Philemon","Hebrews",
        "James","1Peter","2Peter","1John","2John","3John","Jude","Revelation"
    };

    if (num < 1 || num > 66) return "Unknown";
    return books[num];
}