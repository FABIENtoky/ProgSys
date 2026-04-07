import os
import sys

# Programme qui crée 5 fils en utilisant une boucle for
# Le fils ne doit pas créer lui-même plusieurs fils

def main():
    pid = None
    
    for i in range(1, 6):
        pid = os.fork()
        if pid == -1:
            print("Erreur dans fork() !", file=sys.stderr)
            sys.exit(1)
        if pid == 0:
            print(f"Je suis le fils {i}.")
            break  # Sortie de la boucle pour éviter que le fils ne crée d'autres fils
    
    if pid == 0:
        sys.exit(0)
    else:
        # Le père attend ses 5 fils
        for _ in range(5):
            os.wait()
        print("Je suis le pere.")

if __name__ == "__main__":
    main()
