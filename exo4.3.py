import os
import sys

# Programme père : crée un tube, crée un fils, transmet le descripteur via argument
# Programme fils (exécuté par execv) : lit le message et l'affiche

# Ceci est le programme principal (père)
def main():
    r, w = os.pipe()
    pid = os.fork()

    if pid == 0:  # Processus fils
        os.close(w)
        # Exécuter le programme fils avec le descripteur de lecture en argument
        # Note : Ce script doit être exécuté avec un programme fils séparé
        # Pour une démonstration autonome, nous allons utiliser une fonction
        os.execl(sys.executable, sys.executable, __file__, "fils", str(r))
    else:  # Processus père
        os.close(r)
        os.write(w, b"Hello exec.\n")
        os.close(w)
        os.wait()

# Programme fils (exécuté quand le script est appelé avec "fils" comme argument)
def fils_programme(fd_lecture):
    buffer = os.read(fd_lecture, 24)
    print(f"Message recu par execv : {buffer.decode()}")
    os.close(fd_lecture)

if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] == "fils":
        # Exécution en tant que programme fils
        fd_lecture = int(sys.argv[2])
        fils_programme(fd_lecture)
    else:
        main()
