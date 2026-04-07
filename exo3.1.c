#include <stdio.h>
#include <stdlib.h>


/*Ecrire un programme qui prend deux arguments en ligne de commande en
supposant que ce sont des nombres entiers, et qui affiche l'addition de ces deux nombres.*/
int main (int argc, char** argv) {

    if (argc != 3) {
        fprintf (stderr, "Veuillez entrez 2 nombres en arguments.\n");
        exit (0);
    }

    char* a,* b;
    a = argv[1];
    b = argv[2];

    int nb1, nb2;
    nb1 = atoi (a);
    nb2 = atoi (b);

    fprintf (stdout, "La somme des 2 nombres entres en arguments est : %d.\n", nb1 + nb2);

    return 0;
}