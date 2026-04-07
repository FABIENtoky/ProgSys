#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>


/*Ecrire un programme qui cree 2 fils appeles fils 1 et fils 2.
Chaque fils doit attendre un nombre de seconde aleatoire entre 1 et 10,
en utilisant la fonction sleep. Le programme attend que le fils le plus long se termine et affiche la duree totale.
On pourra utiliser la fonction time () de la bibliotheque time.h.*/
int main () {

    pid_t pid1, pid2;
    time_t debut, fin;

    debut = time (NULL);

    pid1 = fork ();
    if (pid1 == -1) {
        fprintf (stderr, "Erreur dans fork () !\n");
        exit (errno);
    }
    if (pid1 == 0) {
        srand (time (NULL) ^ getpid ());
        int dodo1 = (rand () % 10) + 1;
        fprintf (stdout, "Je suis le fils 1 et je vais dormir %d secondes ... \n", dodo1);
        sleep (dodo1);
        exit (0);
    }

    pid2 = fork ();
    if (pid1 == -1) {
        fprintf (stderr, "Erreur dans fork () !\n");
        exit (errno);
    }
    if (pid2 == 0) {
        srand (time (NULL) ^ getpid ());
        int dodo2 = (rand () % 10) + 1;
        fprintf (stdout, "Je suis le fils 2 et je vais dormir %d secondes ... \n", dodo2);
        sleep (dodo2);
        exit (0);
    }

    if ((pid1 == 0) || (pid2 == 0)) {
        exit (0);
    } else {
        wait (NULL);
        wait (NULL);

        fin = time (NULL);

        fprintf (stdout, "Duree totale d'execution : %d secondes.\n", (int)(fin - debut));
    }

    return 0;
}