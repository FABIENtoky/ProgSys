import os
import sys
import time
import random

# Programme qui crée 2 fils appelés fils 1 et fils 2
# Chaque fils attend un nombre aléatoire de secondes entre 1 et 10
# Le programme attend que le fils le plus long se termine et affiche la durée totale

def main():
    debut = time.time()
    
    pid1 = os.fork()
    if pid1 == -1:
        print("Erreur dans fork() !", file=sys.stderr)
        sys.exit(1)
    
    if pid1 == 0:
        # Fils 1
        random.seed(int(time.time() ^ os.getpid()))
        dodo1 = random.randint(1, 10)
        print(f"Je suis le fils 1 et je vais dormir {dodo1} secondes ...")
        time.sleep(dodo1)
        sys.exit(0)
    
    pid2 = os.fork()
    if pid2 == -1:
        print("Erreur dans fork() !", file=sys.stderr)
        sys.exit(1)
    
    if pid2 == 0:
        # Fils 2
        random.seed(int(time.time() ^ os.getpid()))
        dodo2 = random.randint(1, 10)
        print(f"Je suis le fils 2 et je vais dormir {dodo2} secondes ...")
        time.sleep(dodo2)
        sys.exit(0)
    
    if pid1 == 0 or pid2 == 0:
        sys.exit(0)
    else:
        # Le père attend ses deux fils
        os.wait()
        os.wait()
        
        fin = time.time()
        print(f"Duree totale d'execution : {int(fin - debut)} secondes.")

if __name__ == "__main__":
    main()
