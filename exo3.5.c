#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


/*Ecrire un programme qui saisit des nom de fichiers texte au clavier et
ouvre tous ces fichiers dans l'editeur emacs. Le programme doit se poursuivre jusqu'a ce que
l'utilisateur demande de quitter.*/
int main () {

    char* fichier = malloc (256);

    while (1) {
        fprintf (stdout, "Entrez un fichier texte : ");
        scanf ("%s", fichier);

        if (strcmp (fichier, "quit") == 0) {
            break;
        }

        pid_t pid = fork ();
        if (pid == -1) {
            fprintf (stderr, "Erreur dans fork ()\n");
            exit (errno);
        } else if (pid == 0) {
            char* arg[] = {"emacs", fichier, NULL};

            fprintf (stdout, "Ouverture de %s dans emacs ... \n", fichier);
            execv ("/usr/bin/emacs", arg);
        } else {
            wait (NULL);
            fprintf (stdout, "Terminee.\n");
        }
    }

    free (fichier);
    return 0;
}