#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*Écrire un programme qui crée deux processus. Le processus père
ouvre un ﬁchier texte en lecture. On suppose que le ﬁchier est composé de mots formés de
caractères alphabétiques séparés par des espaces. Le processus ﬁls saisit un mot au clavier. Le
processus père recherche le mot dans le ﬁchier, et transmet au ﬁls la valeur 1 si le mot est dans
le ﬁchier, et 0 sinon. Le ﬁls aﬃche le résultat.*/
int main () {

    int tube[2];
    char motSaisie[64], motFichier[64];

    pipe (tube);
    pid_t pid = fork ();

    if (pid > 0) {
        close (tube[0]);
        printf ("Entrez le mot a rechercher : ");
        scanf ("%s", motSaisie);

        FILE* fp = fopen ("text.txt", "r");
        int isThere = 0;
        while (fscanf (fp, "%s", motFichier) != EOF) {
            if (strcmp (motSaisie, motFichier) == 0) {
                isThere = 1;
                break;
            }
        }

        write (tube[1], &isThere, sizeof (int));
        fclose (fp);
        close (tube[1]);
    } else {
        close (tube[1]);

        int resultat;
        read (tube[0], &resultat, sizeof (int));

        printf ("Mot trouve ? %d\n", resultat);
        close (tube[0]);
    }

    return 0;
}