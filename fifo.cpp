#include "fifo.h"
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>

using namespace std;

// Default constructor
Fifo::Fifo() {
    pipename = "";
    fd = -1;
}

// Constructor with pipe name
Fifo::Fifo(string name) {
    pipename = "/home/class/csc3004/tmp/" + SIG + name;

    // Create the FIFO if it doesn't exist
    mkfifo(pipename.c_str(), 0666);
}

// Open pipe for reading
void Fifo::openread() {
    fd = open(pipename.c_str(), O_RDONLY);
    if (fd < 0) {
        perror("openread");
        exit(1);
    }
}

// Open pipe for writing
void Fifo::openwrite() {
    fd = open(pipename.c_str(), O_WRONLY);
    if (fd < 0) {
        perror("openwrite");
        exit(1);
    }
}

// Close pipe
void Fifo::fifoclose() {
    close(fd);
}

// Receive a message
string Fifo::recv() {
    char buf[MaxMess];
    int i = 0;
    char ch;

    while (i < MaxMess - 1) {
        int n = read(fd, &ch, 1);

        if (n <= 0) break;

        if (ch == '\n') break;

        buf[i++] = ch;
    }

    buf[i] = '\0';
    return string(buf);
}

// Send a message
void Fifo::send(string message) {
    string msg = message + "\n";
    write(fd, msg.c_str(), msg.length());
}