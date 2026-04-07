#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main () {
    int fd[2];
    char str_fd[16];

    if (pipe (fd) == -1) {
        perror ("erreur pipe.\n");
        exit (1);
    }

    pid_t pid = fork ();
    if (pid == -1) {
        perror ("erreur fork ()\n");
        exit (1);
    }

    if (pid > 0) {
        close (fd[0]);
        char message[] = "Message via variable d'environnement.\n";
        write (fd[1], message, strlen (message) + 1);

        close (fd[1]);
        wait (NULL);
    } else {
        close (fd[1]);

        sprintf (str_fd, "%d", fd[0]);
        if (setenv ("PIPE_READ_FD", str_fd, 1) != 0) {
            perror ("setenv");
            exit (1);
        }

        char* args[] = {"./fils_env", NULL};
        execv (args[0], args);
    }

    return 0;
}

//fils

int main () {
    

    char* env_val = getenv ("PIPE_READ_FD");

    if (env_val == NULL) {
        fprintf (stderr, "Fils : Variable d'environnement non trouvee.\n");
        exit (1);
    } 

    int fd_lecture = atoi (env_val);
    char buffer[256];

    ssize_t n = read (fd_lecture, buffer, sizeof (buffer));
    if (n > 0) {
        printf ("Fils : via env a recu : %s\n", buffer);
    }

    close (fd_lecture);
    return 0;
}