#!/usr/bin/env python3
import os
import sys
import tempfile

# Programme pour calculer C(n,k) sans utiliser de boucles
# Utilise des fichiers temporaires et la récursion via fork()

def main():
    if len(sys.argv) != 3:
        sys.exit(0)
    
    n = int(sys.argv[1])
    k = int(sys.argv[2])
    
    if n < k:
        return 1
    
    if k == 0 or k == n:
        print("1")
        return 0
    
    # Création de fichiers temporaires
    with tempfile.NamedTemporaryFile(mode='w+', delete=False) as f1:
        file1 = f1.name
    
    with tempfile.NamedTemporaryFile(mode='w+', delete=False) as f2:
        file2 = f2.name
    
    pid1 = os.fork()
    if pid1 == 0:
        # Premier fils: calcule C(n-1, k)
        # Rediriger stdout vers file1
        with open(file1, 'w') as f:
            sys.stdout = f
            os.execl(sys.argv[0], sys.argv[0], str(n-1), str(k))
        sys.exit(0)
    
    pid2 = os.fork()
    if pid2 == 0:
        # Deuxième fils: calcule C(n-1, k-1)
        with open(file2, 'w') as f:
            sys.stdout = f
            os.execl(sys.argv[0], sys.argv[0], str(n-1), str(k-1))
        sys.exit(0)
    
    # Père attend ses deux fils
    os.wait()
    os.wait()
    
    if pid1 != 0 and pid2 != 0:
        # Lecture des résultats
        with open(file1, 'r') as f1:
            res1 = int(f1.read().strip())
        
        with open(file2, 'r') as f2:
            res2 = int(f2.read().strip())
        
        print(f"Resultat : {res1 + res2}")
        
        # Nettoyage des fichiers temporaires
        os.unlink(file1)
        os.unlink(file2)
    
    return 0

if __name__ == "__main__":
    main()