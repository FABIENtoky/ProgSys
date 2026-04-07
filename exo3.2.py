#!/usr/bin/env python3
import sys
import os
import subprocess

# Programme qui exécute cp -r . <répertoire>

def main():
    if len(sys.argv) != 2:
        print("Veuillez entrer un seul argument.", file=sys.stderr)
        sys.exit(0)
    
    rep = sys.argv[1]
    
    # Utilisation de subprocess.run pour remplacer execv
    # Cela équivaut à exécuter: cp -r . rep
    result = subprocess.run(["/usr/bin/cp", "-r", ".", rep])
    
    # Le processus Python continue après l'exécution (contrairement à execv)
    # Pour imiter exactement execv, on pourrait utiliser os.execv mais cela
    # remplacerait le processus Python

if __name__ == "__main__":
    main()

