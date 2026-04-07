import os
import sys

# Programme qui transmet un descripteur de tube via une variable d'environnement

def main():
    r, w = os.pipe()
    pid = os.fork()

    if pid > 0:  # Processus père
        os.close(r)
        message = "Message via variable d'environnement.\n"
        os.write(w, message.encode())
        os.close(w)
        os.wait()
    else:  # Processus fils
        os.close(w)
        # Définir la variable d'environnement
        os.environ['PIPE_READ_FD'] = str(r)
        # Exécuter le programme fils
        os.execl(sys.executable, sys.executable, __file__, "fils")

# Programme fils
def fils_programme():
    env_val = os.environ.get('PIPE_READ_FD')
    
    if env_val is None:
        print("Fils : Variable d'environnement non trouvee.", file=sys.stderr)
        sys.exit(1)
    
    fd_lecture = int(env_val)
    buffer = os.read(fd_lecture, 256)
    
    if buffer:
        print(f"Fils : via env a recu : {buffer.decode()}")
    
    os.close(fd_lecture)

if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] == "fils":
        # Exécution en tant que programme fils
        fils_programme()
    else:
        main()
