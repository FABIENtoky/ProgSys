#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


/*Ecrire un programme pour calculerCnk qui n'utilise aucune boucle (ni while ni for), et qui n'ait
comme seule fonction que la fonction main. La fonction main ne doit contenir aucun appel a
elle-meme.On pourra utiliser des fichiers textes temporaires dans le repertoire /tmp.*/
int main (int argc, char** argv) {

    if (argc != 3) {
        exit (0);
    }

    int n = atoi (argv[1]);
    int k = atoi (argv[2]);

    if (n < k) {
        return 1;
    }

    if (k == 0 || k == n) {
        printf ("1\n");
        return 0;
    }

    char file1[64], file2[64];

    sprintf (file1, "/home/fabien/S3/tmp_res_%d_%d_a.txt", n, k);
    sprintf (file2, "/home/fabien/S3/tmp_res_%d_%d_b.txt", n, k);

    pid_t pid1 = fork ();
    if (pid1 == 0) {
        char sn[16], sk[16];
        
        snprintf (sn, sizeof (sn), "%d", n - 1);
        snprintf (sk, sizeof (sk), "%d", k);

        freopen (file1, "w", stdout);
        execl (argv[0], argv[0], sn, sk, NULL);

        exit (0);
    }

    pid_t pid2 = fork ();
    if (pid2 == 0) {
        char sn[16], sk[16];

        snprintf (sn, sizeof (sn), "%d", n - 1);
        snprintf (sk, sizeof (sk), "%d", k - 1);

        freopen (file2, "w", stdout);
        execl (argv[0], argv[0], sn, sk, NULL);

        exit (0);
    }

    wait (NULL);
    wait (NULL);

    if (pid1 != 0 && pid2 != 0) {
        int res1, res2;
    
        FILE* f1 = fopen (file1, "r");
        FILE* f2 = fopen (file2, "r");

        fscanf (f1, "%d", &res1);
        fscanf (f2, "%d", &res2);

        fclose (f1); fclose (f2);

        printf ("Resultat : %d\n", res1 + res2);

        unlink (file1);
        unlink (file2);
    }
    return 0;
}