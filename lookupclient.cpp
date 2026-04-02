// lookupclient.cpp

#include <iostream>
#include <string>

#include "fifo.h"

/* Required libraries for AJAX */
#include "/home/class/csc3004/cgicc/Cgicc.h"

using namespace std;
using namespace cgicc;

int main()
{
    cout << "Content-Type: text/html\n\n";

    Cgicc cgi;

    form_iterator book = cgi.getElement("book");
    form_iterator chapter = cgi.getElement("chapter");
    form_iterator verse = cgi.getElement("verse");
    form_iterator nv = cgi.getElement("num_verse");

    bool validInput = true;

    if (book == cgi.getElements().end() ||
        chapter == cgi.getElements().end() ||
        verse == cgi.getElements().end())
    {
        cout << "<p>Error: Missing input.</p>";
        validInput = false;
    }

    int bookNum = 0, chapterNum = 0, verseNum = 0, numVerses = 1;

    if (validInput)
    {
        bookNum = book->getIntegerValue();
        chapterNum = chapter->getIntegerValue();
        verseNum = verse->getIntegerValue();

        if (nv != cgi.getElements().end())
        {
            numVerses = nv->getIntegerValue();
            if (numVerses <= 0) numVerses = 1;
        }

        // Build request string for server
        string ref = to_string(bookNum) + ":" +
                     to_string(chapterNum) + ":" +
                     to_string(verseNum) + ":" +
                     to_string(numVerses);

        // Pipes: use only the names, Fifo class adds PATH + SIG
        Fifo requestPipe("request");
        Fifo replyPipe("reply");

        // Send request
        requestPipe.openwrite();
        requestPipe.send(ref);
        requestPipe.fifoclose();

        // Receive response
        replyPipe.openread();
        string output = replyPipe.recv();
        replyPipe.fifoclose();

        // Parse response: first char = status (0 = OK)
        int status = output.empty() ? 1 : output[0] - '0';
        string text = output.length() > 2 ? output.substr(2) : "No response.";

        if (status != 0)
            cout << "<p>Error: " << text << "</p>";
        else
            cout << "<p>" << text << "</p>";
    }

    return 0;
}