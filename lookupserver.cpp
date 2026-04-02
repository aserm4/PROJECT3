// lookupserver.cpp

#include <iostream>
#include <string>
#include <sstream>
#include "Ref.h"
#include "Verse.h"
#include "Bible.h"
#include "fifo.h"

using namespace std;

int main()
{
    Bible bible;

    // Pipes: use only the names
    Fifo requestPipe("request");
    Fifo replyPipe("reply");

    // Create the pipes if they don't exist
    // (Fifo constructor does this)

    cout << "Server started, waiting for requests..." << endl;

    while (true)
    {
        // Wait for request
        requestPipe.openread();
        string req = requestPipe.recv();
        requestPipe.fifoclose();

        int statusInt = 1;  // default error
        string responseText = "Unknown error.";

        if (!req.empty())
        {
            stringstream ss(req);
            int b, c, v, num;
            char colon;

            ss >> b >> colon >> c >> colon >> v >> colon >> num;

            LookupResult status;

            responseText = "";
            for (int i = 0; i < num; i++)
            {
                Ref r(b, c, v + i);
                Verse verse = bible.lookup(r, status);

                if (status != SUCCESS)
                {
                    responseText += bible.error(status);
                    statusInt = 1;
                    break;
                }
                else
                {
                    responseText += verse.getVerse();
                    if (i < num - 1)
                        responseText += " ";  // separate verses by space
                }
            }

            if (status == SUCCESS)
                statusInt = 0;
        }

        // Send response
        string out = to_string(statusInt) + ":" + responseText;
        replyPipe.openwrite();
        replyPipe.send(out);
        replyPipe.fifoclose();
    }

    return 0;
}