#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*Écrire un programme qui crée un tube, crée un processus ﬁls,
puis, dans le ﬁls, lance par execv un autre programme, appelé programme ﬁls. Le programme
père transmets les descripteurs de tubes au programmes ﬁls en argument, et transmet un
message au ﬁls par le tube. Le programme ﬁls aﬃche le message.*/
int main () {

    int tube[2];

    pipe (tube);

    if (fork () == 0) {
        char arg[16];
        sprintf (arg, "%d", tube[0]);
        char* args[] = {"./fils", arg, NULL};
        close (tube[1]);
        execv (args[0], args);
    } else {
        close (tube[0]);
        write (tube[1], "Hello exec.\n", 11);
        close (tube[1]);
    }
    return 0;
}

//fils.c
int main (int argc, char* argv[]) {
    int fd_lecture = atoi (argv[1]);
    char buffer[24];
    read (fd_lecture, buffer, sizeof (buffer));
    printf ("Message recu par execv : %s\n", buffer);

    return 0;
}