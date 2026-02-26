/* 
 * Bible class function definitions
 * Computer Science, MVNU
 * CSC-3004 Introduction to Software Development
 *
 * NOTE: You may add code to this file, but do not
 * delete any code or delete any comments.
 *
 * STUDENT NAME: Shane Busch
 */

#include "Ref.h"
#include "Verse.h"
#include "Bible.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// Default constructor
Bible::Bible() {
    infile = "/home/class/csc3004/Bibles/web-complete";
    buildIndex();
}

// Constructor – pass bible filename
Bible::Bible(const string s) {
    infile = s;
    buildIndex();
}

// REQUIRED: lookup finds a given verse in this Bible
Verse Bible::lookup(Ref ref, LookupResult& status)
{ 
   // Always start at the beginning of the file for each lookup
   if (instream.is_open())
      instream.close();

   auto it = index.find(ref);// auto is a map iterator

   if (it == index.end())
   {
      status = NO_VERSE;
      return Verse();
   }

   instream.open(infile.c_str(), ios::in);

   if (!instream)
   {
      status = OTHER;
      return Verse();
   }

   instream.seekg(it->second);

   string line;
   getline(instream, line);

   instream.close();

   status = SUCCESS;
   return Verse(line);
}

// REQUIRED: Return the next verse from the Bible file stream
// If the file is not open, open the file and return the first verse
Verse Bible::nextVerse(LookupResult& status) {
    if (!instream.is_open()) {
        instream.open(infile.c_str(), ios::in);
        if (!instream) {
            cerr << "Error - can't open input file: " << infile << endl;
            exit(2);
        }
        instream.unsetf(ios::skipws);
    }

    string line;
    if (getline(instream, line)) {
        status = SUCCESS;
        return Verse(line);
    } else {
        status = OTHER;
        return Verse();
    }
}

// REQUIRED: Return an error message string to describe status
string Bible::error(LookupResult status) {
    if (status == NO_BOOK) {
        return "If you can find that book in a real Bible, I'd be impressed.";
    }
    if (status == NO_CHAPTER) {
        return "If you can find that chapter in a real Bible, I'd be impressed.";
    }
    if (status == NO_VERSE) {
        return "If you can find that verse in a real Bible, I'd be impressed.";
    }
    return "I don't know what you did, but you did it.";
}

// Display the current Bible file being used
void Bible::display() {
    cout << "Bible file: " << infile << endl;
}

// OPTIONAL access functions

// Return the reference after the given ref
Ref Bible::next(const Ref ref, LookupResult& status) { //unused for now.

    auto it = index.upper_bound(ref); //upper_bound returns an iterator to the first element whose key is greater than the given key.
    if (it == index.end())
    {
        status = OTHER;
        return Ref();
    }

    status = SUCCESS;
    return it->first;
}

// Return the reference before the given ref
Ref Bible::prev(const Ref ref, LookupResult& status) { //unused for now.

    auto it = index.lower_bound(ref);

    if (it == index.begin())
    {
        status = OTHER;
        return Ref();
    }

    it--;

    status = SUCCESS;
    return it->first;
}

void Bible::buildIndex(){

    if (instream.is_open())
        instream.close();

    instream.open(infile.c_str(), ios::in);

    if (!instream) {
        cerr << "Error - can't open input file: " << infile << endl;
        exit(2);
    }

    instream.unsetf(ios::skipws);

    string line;
    int count = 0;
    int lastOffset = 0;

    while (true){

        int offset = instream.tellg();

        if (!getline(instream, line))
        {
            break;
        }

        Ref hold(line);

        index[hold] = offset;

        lastOffset = offset;
        count++;
    }

    cout << "Index built successfully." << endl;
    cout << "Total references indexed: " << count << endl;
    cout << "Last reference offset: " << lastOffset << endl;

    instream.close();
}

int Bible::lookupOffset(const Ref ref){

    auto it = index.find(ref);

    if (it != index.end())
    {
        return it->second;
    }

    return -1;
}