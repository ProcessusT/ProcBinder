# coding: utf-8
import socket
import sys

# on créer un objet socket
serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# informations du serveur
host = "127.0.0.1"
port = 666

# on démarre notre connexion socket et on écoute les requêtes
serversocket.bind((host, port))
serversocket.listen(5)
print ('server started and listening on port '+str(port))

# tant que la connexion socket est active
while 1:
    # réception d'une requête cliente
    (clientsocket, address) = serversocket.accept()
    print ("new connection from : "+str(address))
    print("Send commands : ")
    # tant que le client est connecté on peut envoyer des commandes
    while 1:
        # envoi de la commande
        r=str( sys.stdin.readline() )
        clientsocket.send(r.encode())
        # réception du résultat
        r = clientsocket.recv(9999)
        # on réencode en utf-8 avec le flag "errors=ignore" car certains caractères ne sont pas supportés
        client_answer = str( r.decode("utf-8", errors="ignore"))
        print(str(client_answer)+"\n")