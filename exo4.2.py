import os
import sys

# Programme qui lie stdout et stdin du père à un tube

def main():
    r, w = os.pipe()
    pid = os.fork()

    if pid > 0:  # Processus père
        os.close(r)
        # Sauvegarder le stdout original
        original_stdout = os.dup(1)
        # Rediriger stdout vers le tube
        os.dup2(w, 1)
        
        print("Message_via_printf :")
        
        # Restaurer stdout
        os.dup2(original_stdout, 1)
        os.close(w)
        os.close(original_stdout)
    else:  # Processus fils
        os.close(w)
        # Rediriger stdin depuis le tube
        original_stdin = os.dup(0)
        os.dup2(r, 0)
        
        buffer = input()
        print(f"Le fils a recu : {buffer}")
        
        # Restaurer stdin
        os.dup2(original_stdin, 0)
        os.close(r)
        os.close(original_stdin)

if __name__ == "__main__":
    main()
