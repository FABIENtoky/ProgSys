#!/usr/bin/env python3
import sys
import os

# Programme qui ouvre un fichier dans l'éditeur emacs

def main():
    if len(sys.argv) != 2:
        print("Veuillez le nom d'un fichier en argument.", file=sys.stderr)
        sys.exit(0)
    
    fichier = sys.argv[1]
    print(f"Ouverture de {fichier} dans emacs ...")
    
    # Correction: execv prend deux arguments: chemin et liste d'arguments
    os.execv("/usr/bin/emacs", ["/usr/bin/emacs", fichier])

if __name__ == "__main__":
    main()