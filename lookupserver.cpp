/* CSC-3004 Project 3
 * STUDENT NAME: Shane Busch
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "Bible.h"
#include "Ref.h"
#include "Verse.h"

using namespace std;

int main()
{
    string requestPipe = "/home/class/csc3004/tmp/shabusch_request";
    string replyPipe   = "/home/class/csc3004/tmp/shabusch_reply";

    //Open pipes
    ifstream requestStream(requestPipe);
    ofstream replyStream(replyPipe);

    if (!requestStream)
    {
        cerr << "Error opening request pipe." << endl;
        return 1;
    }

    if (!replyStream)
    {
        cerr << "Error opening reply pipe." << endl;
        return 1;
    }

    //Create log file (append mode)
    ofstream logFile("shabusch_log.log", ios::app);

    if (!logFile)
    {
        cerr << "Error opening log file." << endl;
        return 1;
    }else{
        cout << "log is open." << endl;
    }

    //Load Bible
    Bible bible("/home/class/csc3004/Bibles/web-complete");

    cout << "Lookup Server running..." << endl;
    logFile << "Lookup Server started..." << endl;
    logFile.flush();

    string message;

    //Main server loop
    while (true)
    {
        //Read request
        if (!getline(requestStream, message))
            continue;

        //Print + log received message
        cout << "Received: " << message << endl;
        logFile << "Received: " << message << endl;

        // Process request
        Ref ref(message);
        LookupResult status;
        Verse verse = bible.lookup(ref, status);

        string reply;

        if (status == SUCCESS)
        {
            reply = "0|" + verse.getVerse();
        }
        else
        {
            reply = "1|Error: verse not found";
        }

        //Print + log sent message
        cout << "Sent: " << reply << endl;
        logFile << "Sent: " << reply << endl;

        // Send reply
        replyStream << reply << endl;
        replyStream.flush();

        //Flush log file so it updates immediately
        logFile.flush();
    }

    return 0;
}