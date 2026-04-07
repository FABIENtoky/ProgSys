#!/usr/bin/env python3
import sys

# Programme qui prend deux arguments en ligne de commande
# et affiche l'addition de ces deux nombres

def main():
    if len(sys.argv) != 3:
        print("Veuillez entrer 2 nombres en arguments.", file=sys.stderr)
        sys.exit(0)
    
    nb1 = int(sys.argv[1])
    nb2 = int(sys.argv[2])
    
    print(f"La somme des 2 nombres entres en arguments est : {nb1 + nb2}.")

if __name__ == "__main__":
    main()
