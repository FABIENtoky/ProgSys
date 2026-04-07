#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


/*Ecrire un programme qui cree 5 fils en utilisant une boucle for.
On remarquera que pour que le fils ne cree pas lui-meme plusieurs fils,
il faut interompre la boucle par
un break dans le fils.*/
int main () {

    int i;
    pid_t pid;

    for (i = 1; i <= 5; i++) {
        pid = fork ();
        if (pid == -1) {
            fprintf (stderr, "Erreur dans fork () !\n");
            exit (errno);
        }
        if (pid == 0) {
            fprintf (stdout, "Je suis le fils %d.\n", i);
            break;
        }
    }

    if (pid == 0) {
        exit (0);
    } else {
        for (int j = 1; j <= 5; j++) {
            wait (NULL);
        }
        fprintf (stdout, "Je suis le pere.\n");
    }

    return 0;
}