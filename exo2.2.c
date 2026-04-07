#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


/*Ecrire un programme qui cree 2 fils appeles fils 1 et fils 2.
Le pere doit afficher "Je suis le pere",
Le fils 1 "Je suis le fils 1"
et le fils 2 "Je suis le fils 2".*/
int main () {

    pid_t pid1, pid2;

    pid1 = fork ();
    if (pid1 == -1) {
        fprintf (stderr, "Erreur dans fork () !\n");
        exit (errno);
    }
    if (pid1 == 0) {
        fprintf (stdout, "Je suis le fils 1.\n");
        exit (0);
    }

    pid2 = fork ();
    if (pid2 == -1) {
        fprintf (stderr, "Erreur dans fork () !\n");
        exit (errno);
    }
    if (pid2 == 0) {
        fprintf (stdout, "Je suis le fils 2.\n");
        exit (0);
    }

    wait (NULL);
    wait (NULL);
    fprintf (stdout, "Je suis le pere.\n");

    return 0;
}