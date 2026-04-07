#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


/*Ecrire un programme avec un processus pere qui engendre 5 fils dans une bouble for.
Les fils sont nommes fils 1 a fils 5.
Le fils 1 doit afficher "je suis le fils 1" et le fils 2
doit afficher je suis le fils 2, et ainsi de suite.
Indication. on pourra utiliser une variable globale.*/

int numFils = 0;

int main () {

    int i;
    pid_t pid;

    for (i = 1; i <= 5; i++) {
        numFils = i;
        pid = fork ();
        if (pid == -1) {
            fprintf (stderr, "Erreur dans fork () !\n");
            exit (errno);
        }
        if (pid == 0) {
            fprintf (stdout, "Je suis le fils %d.\n", numFils);
            exit (0);
        }
    }

    if (pid == 0) {
        exit (0);
    } else {
        for (i = 1; i <= 5; i++) {
            wait (NULL);
        }
        fprintf (stdout, "Je suis le pere.\n");
    }

    return 0;
}