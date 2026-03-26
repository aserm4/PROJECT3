#ifndef FIFO_H
#define FIFO_H

#include <string>
using namespace std;

// Max message size (must be > longest verse ~535 chars)
const int MaxMess = 800;

// MUST be your username followed by "_"
const string SIG = "shabusch_";

class Fifo {
public:
    Fifo();                 // Default constructor
    Fifo(string);           // Construct with pipe name

    void openread();        // Open for reading
    void openwrite();       // Open for writing
    void fifoclose();       // Close pipe

    string recv();          // Receive message
    void send(string);      // Send message

private:
    string pipename;        // Name of pipe
    int fd;                 // File descriptor
};

#endif