import os
import sys

# Programme avec un processus père qui engendre 5 fils
# Les fils sont nommés fils 1 à fils 5
# Utilisation d'une variable globale (simulée par une variable d'instance)

num_fils = 0

def main():
    global num_fils
    pid = None
    
    for i in range(1, 6):
        num_fils = i
        pid = os.fork()
        if pid == -1:
            print("Erreur dans fork() !", file=sys.stderr)
            sys.exit(1)
        if pid == 0:
            print(f"Je suis le fils {num_fils}.")
            sys.exit(0)
    
    if pid == 0:
        sys.exit(0)
    else:
        # Le père attend ses 5 fils
        for _ in range(5):
            os.wait()
        print("Je suis le pere.")

if __name__ == "__main__":
    main()
