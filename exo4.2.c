#include <stdio.h>
#include <unistd.h>

/*(R) eprendre les programmes de l’exercice ??. Nous allons faire un programme
qui fait la même chose, mais transmet les données diﬀérement. Dans le programme père, on
liera les ﬂots stdout et stdin à un tube.*/
int main () {

    int tube[2];

    pipe (tube);

    if (fork () > 0) {
        close (tube[0]);
        dup2 (tube[1], STDOUT_FILENO);

        printf ("Message_via_printf : ");
        close (tube[1]);
    } else {
        close (tube[1]);

        dup2 (tube[0], STDIN_FILENO);

        char buffer[256];
        scanf ("%s", buffer);
        printf ("Le fils a recu : %s\n", buffer);
        close (tube[0]);
    }

    return 0;
}