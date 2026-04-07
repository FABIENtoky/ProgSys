#!/usr/bin/env python3
import os
import sys
import subprocess

# Programme qui copie le répertoire courant dans des répertoires saisis
# Jusqu'à ce que l'utilisateur demande de quitter

def main():
    while True:
        destination = input("Entrez un repertoire : ")
        
        if destination == "quit":
            break
        
        pid = os.fork()
        if pid == -1:
            print("Erreur dans fork()", file=sys.stderr)
            sys.exit(1)
        elif pid == 0:
            # Processus fils
            print(f"Copie en cours vers {destination} ...")
            os.execv("/usr/bin/cp", ["/usr/bin/cp", "-r", ".", destination])
        else:
            # Processus père
            os.wait()
            print("Copie terminee.")

if __name__ == "__main__":
    main()
