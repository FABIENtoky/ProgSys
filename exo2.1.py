import os
import sys

# Programme qui crée un fils
# Le père affiche "Je suis le père" et le fils "Je suis le fils"

def main():
    pid_fils = os.fork()
    
    if pid_fils == -1:
        print("Erreur dans fork() !", file=sys.stderr)
        sys.exit(1)
    elif pid_fils == 0:
        print("Je suis le fils.")
    else:
        print("Je suis le pere.")

if __name__ == "__main__":
    main()