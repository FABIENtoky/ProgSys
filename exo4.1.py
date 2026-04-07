import os
import sys

# Programme qui crée deux processus.
# Le père ouvre un fichier texte, le fils saisit un mot au clavier.
# Le père recherche le mot dans le fichier et transmet le résultat au fils.

def main():
    r, w = os.pipe()
    pid = os.fork()

    if pid > 0:  # Processus père
        os.close(r)
        mot_saisie = input("Entrez le mot a rechercher : ")

        is_there = 0
        try:
            with open("text.txt", "r") as fp:
                for ligne in fp:
                    for mot_fichier in ligne.split():
                        if mot_saisie == mot_fichier:
                            is_there = 1
                            break
                    if is_there:
                        break
        except FileNotFoundError:
            print("Fichier text.txt non trouvé.")

        os.write(w, is_there.to_bytes(4, 'little'))
        os.close(w)
        os.wait()  # Attendre la fin du fils
    else:  # Processus fils
        os.close(w)
        resultat_bytes = os.read(r, 4)
        resultat = int.from_bytes(resultat_bytes, 'little')
        print(f"Mot trouve ? {resultat}")
        os.close(r)

if __name__ == "__main__":
    main()
