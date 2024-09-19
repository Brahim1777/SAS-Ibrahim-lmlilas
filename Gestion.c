#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

// Fonction pour vérifier les contraintes du mot de passe
bool verifierMotDePasse(const char motDePasse[], const char nomUtilisateur[]) {
    if (strlen(motDePasse) < 8) {
        return false; 
    }
    bool majuscule = false, minuscule = false, chiffre = false, special = false;

    for (int i = 0; motDePasse[i] != '\0'; i++) {    
        if (motDePasse[i] >= 'A' && motDePasse[i] <= 'Z') {
            majuscule = true; 
        } else if (motDePasse[i] >= 'a' && motDePasse[i] <= 'z') {
            minuscule = true;
        } else if (motDePasse[i] >= '0' && motDePasse[i] <= '9') {
            chiffre = true;
        } else if (strchr("!@#$%^&*", motDePasse[i])) {
            special = true; 
        }
    }
    if (!majuscule || !minuscule || !chiffre || !special) {
        return false; 
    }
    if (strstr(motDePasse, nomUtilisateur) != NULL) {
        return false; 
    }
    return true;
}

int main() {
    int choix;
    do {
        printf("\n    ~~Menu~~  \n");
        printf("1 -->  Gestion des réclamations\n");
        printf("0 --> Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        if (choix == 1) {
            int choix2;
            char nomUtilisateur[50]; 
            char motDePasse[50];
            int tentatives = 0;
            bool utilisateurConnecte = false;

            printf("\n1 --> Créer un nouveau compte\n");
            printf("2 --> Se connecter\n");
            printf("Votre choix : ");
            scanf("%d", &choix2);

            switch (choix2) {
                case 1:  // Inscription
                    printf("Entrez votre nom d'utilisateur : ");
                    scanf("%s", nomUtilisateur);

                    printf("Entrez votre mot de passe : ");
                    scanf("%s", motDePasse);

                    if (verifierMotDePasse(motDePasse, nomUtilisateur)) {
                        printf("Inscription réussie.\n"); 
                    } else {
                        printf("Erreur : Le mot de passe ne respecte pas les contraintes.\n"); 
                    }
                    break;

                case 2:  // Connexion
                    while (tentatives < 3 && !utilisateurConnecte) {
                        printf("Entrez votre nom d'utilisateur : ");
                        scanf("%s", nomUtilisateur);

                        printf("Entrez votre mot de passe : ");
                        scanf("%s", motDePasse);

                        // Vérifiez ici si les informations d'identification sont correctes
                        // Pour l'exemple, nous supposerons un utilisateur avec ces informations
                        if (strcmp(nomUtilisateur, "client1") == 0 && strcmp(motDePasse, "Password123!") == 0) {
                            printf("Connexion réussie. Bienvenue, %s!\n", nomUtilisateur);
                            utilisateurConnecte = true;
                        } else {
                            tentatives++;
                            printf("Nom d'utilisateur ou mot de passe incorrect. Tentatives restantes : %d\n", 3 - tentatives);
                        }
                    }

                    if (tentatives == 3) {
                        printf("Compte verrouillé après 3 tentatives échouées. Veuillez réessayer plus tard.\n");
                    }
                    break;

                default: 
                    printf("Choix invalide. Veuillez réessayer.\n"); 
                    break;
            }
        }
    } while (choix != 0);

    return 0;
}
