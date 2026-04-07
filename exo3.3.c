#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/*Ecrire un programme qui saisit un nom de fichier texte au clavier et ouvre ce
fichier dans l'editeur emacs, dont le fichier executable se trouve a l'emplacement /usr/bin/emacs.*/
int main (int argc, char** argv) {

    if (argc != 2) {
        fprintf (stderr, "Veuillez le nom d'un fichier en argument.\n");
        exit (0);
    }

    char* fichier = argv[1];
    fprintf (stdout, "Ouverture de %s dans emacs ... \n", fichier);

    execv ("/usr/bin/emacs", "emacs", fichier, NULL);

    return 0;
}