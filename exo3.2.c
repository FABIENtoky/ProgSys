#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main (int argc, char** argv) {

    if (argc != 2) {
        fprintf (stderr, "Veuillez entrez un seul argument.\n");
        exit (0);
    }

    char* cp = "/usr/bin/cp";
    char* rep = argv[1];
    char* arg[] = {cp, "-r", ".", rep, NULL};

    execv (cp, arg);

    return 0;
}
