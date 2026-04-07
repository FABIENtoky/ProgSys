#!/usr/bin/env python3
import os
import sys

# Programme qui ouvre des fichiers texte dans emacs
# Jusqu'à ce que l'utilisateur demande de quitter

def main():
    while True:
        fichier = input("Entrez un fichier texte : ")
        
        if fichier == "quit":
            break
        
        pid = os.fork()
        if pid == -1:
            print("Erreur dans fork()", file=sys.stderr)
            sys.exit(1)
        elif pid == 0:
            # Processus fils
            print(f"Ouverture de {fichier} dans emacs ...")
            os.execv("/usr/bin/emacs", ["/usr/bin/emacs", fichier])
        else:
            # Processus père
            os.wait()
            print("Terminee.")

if __name__ == "__main__":
    main()
