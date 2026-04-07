#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


/*Ecrire un programme qui cree un fils.
Le pere doit afficher "Je suis le pere"
et le fils "Je suis le fils"*/
int main () {

    pid_t pid_fils;

    pid_fils = fork ();

    if (pid_fils == -1) {
        fprintf (stderr, "Erreur dans fork () !\n");
        exit (errno);
    } else if (pid_fils == 0) {
        fprintf (stdout, "Je suis le fils.\n");
    } else {
        fprintf (stdout, "Je suis le pere.\n");
    }

    return 0;
}