#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


/*Ecrire un programme qui saisit des noms de repertoires au clavier et copie
le repertoire courant dans tous ces repertoires. Le programme doit se poursuivre jusqu'a ce que
l'utilisateur demande de quitter le programme.*/
int main () {

    char* destination = malloc (256);

    while (1) {
        fprintf (stdout, "Entrez un repertoire : ");
        scanf ("%s", destination);

        if (strcmp (destination, "quit") == 0) {
            break;
        }

        pid_t pid = fork ();
        if (pid == -1) {
            fprintf (stderr, "Erreur dans fork ()\n");
            exit (errno);
        } else if (pid == 0) {
            char* arg[] = {"cp", "-r", ".", destination, NULL};

            fprintf (stdout, "Copie en cours vers %s ... \n", destination);
            execv ("/usr/bin/cp", arg);
        } else {
            wait (NULL);
            fprintf (stdout, "Copie terminee.\n");
        }
    }

    free (destination);
    return 0;
}