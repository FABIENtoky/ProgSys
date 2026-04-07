import os
import sys

# Programme qui crée 2 fils appelés fils 1 et fils 2
# Le père affiche "Je suis le père", fils1 "Je suis le fils 1", fils2 "Je suis le fils 2"

def main():
    pid1 = os.fork()
    if pid1 == -1:
        print("Erreur dans fork() !", file=sys.stderr)
        sys.exit(1)
    
    if pid1 == 0:
        print("Je suis le fils 1.")
        sys.exit(0)
    
    pid2 = os.fork()
    if pid2 == -1:
        print("Erreur dans fork() !", file=sys.stderr)
        sys.exit(1)
    
    if pid2 == 0:
        print("Je suis le fils 2.")
        sys.exit(0)
    
    # Le père attend ses deux fils
    os.wait()
    os.wait()
    print("Je suis le pere.")

if __name__ == "__main__":
    main()
