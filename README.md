# ProcBinder
Un simple client-serveur avec connexion gérée via Socket. 
Le client est écrit en C et le serveur en Python.

J'ai commencé ce projet pour approfondir mes (très faibles) bases en C, soyez indulgents ! :)

Le code est à portée éducative uniquement.




Le client a été développé sous Visual Studio et nécessite l'ajout de la librairie Winsock :

Dans Visual Studio, clic droit sur le projet -> Propriétés -> Propriétés de configuration -> Editeur de liens -> entrée -> Dépendances supplémentaires
Ajouter cette ligne :
ws2_32.lib




Basé sur les travaux d'OpenClassroom sur les sockets :

http://sdz.tdct.org/sdz/les-sockets.html#Partie1L039applicationserveur
