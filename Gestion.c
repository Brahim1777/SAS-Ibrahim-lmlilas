#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

#define MAX_ACCOUNTS 100
#define MAX_RECLAMATIONS 100

// Structure pour gérer les informations utilisateur
struct conixion {
    struct singUp {
        char username[100];
        char password[100];
        char email[100];
    } SIGN_UP[MAX_ACCOUNTS];

    struct signIn {
        char username1[100];
        char password1[100];
    } SIGN_IN;
};

// Structure pour gérer les réclamations
struct reclamation {
    int reclamationID;
    char username[100];
    char motif[100];
    char description[200];
    char category[100];
    char status[20];
    char date[20];
};

// Identifiants de l'administrateur
char adminusername[] = "BRAHIM";
char adminpassword[] = "BRAhim_123";

// Tableau des réclamations
struct reclamation reclamations[MAX_RECLAMATIONS];
int totalReclamations = 0;

// Fonction pour générer un identifiant de réclamation aléatoire
int generateReclamationID() {
    return rand() % 10000; // Génère un nombre aléatoire entre 0 et 9999
}

// Fonction pour obtenir la date actuelle
void getCurrentDate

// Fonction pour ajouter une réclamation
void addReclamation(char username[]) {
    if (totalReclamations < MAX_RECLAMATIONS) {
        struct reclamation newReclamation;
        newReclamation.reclamationID = generateReclamationID();
        strcpy(newReclamation.username, username);

        printf("Entrez le motif de la réclamation (par exemple, produit défectueux, facturation) : ");
        fgets(newReclamation.motif, sizeof(newReclamation.motif), stdin);
        newReclamation.motif[strcspn(newReclamation.motif, "\n")] = '\0';

        printf("Entrez une description détaillée du problème : ");
        fgets(newReclamation.description, sizeof(newReclamation.description), stdin);
        newReclamation.description[strcspn(newReclamation.description, "\n")] = '\0';

        printf("Entrez la catégorie de la réclamation (par exemple, produit, service) : ");
        fgets(newReclamation.category, sizeof(newReclamation.category), stdin);
        newReclamation.category[strcspn(newReclamation.category, "\n")] = '\0';

        strcpy(newReclamation.status, "En cours"); // Statut par défaut est "en cours"

        getCurrentDate(newReclamation.date); // Obtenir la date actuelle

        // Stocker la nouvelle réclamation dans le tableau des réclamations
        reclamations[totalReclamations++] = newReclamation;

        printf("\nRéclamation ajoutée avec succès !\n");
        printf("Identifiant de réclamation : %d\n", newReclamation.reclamationID);
        printf("Motif : %s\n", newReclamation.motif);
        printf("Description : %s\n", newReclamation.description);
        printf("Catégorie : %s\n", newReclamation.category);
        printf("Statut : %s\n", newReclamation.status);
        printf("Date : %s\n\n", newReclamation.date);
    } else {
        printf("Limite de réclamations atteinte !\n");
    }
}

// Fonction pour gérer les réclamations (implémentation fictive pour l'instant)
void manageReclamations() {
    printf("Liste de toutes les réclamations :\n");
    for (int i = 0; i < totalReclamations; i++) {
        printf("Identifiant de réclamation : %d\n", reclamations[i].reclamationID);
        printf("De : %s\n", reclamations[i].username);
        printf("Motif : %s\n", reclamations[i].motif);
        printf("Description : %s\n", reclamations[i].description);
        printf("Catégorie : %s\n", reclamations[i].category);
        printf("Statut : %s\n", reclamations[i].status);
        printf("Date : %s\n", reclamations[i].date);
        printf("----------------------------------------\n");
    }
}

// Fonction pour supprimer un compte utilisateur
void deleteAccount(struct conixion *conixion1, int *totalaccounts) {
    char username[100];
    printf("Entrez le nom d'utilisateur du compte à supprimer : ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Retirer le saut de ligne

    for (int i = 0; i < *totalaccounts; i++) {
        if (strcmp(conixion1->SIGN_UP[i].username, username) == 0) {
            for (int j = i; j < *totalaccounts - 1; j++) {
                conixion1->SIGN_UP[j] = conixion1->SIGN_UP[j + 1];
            }
            (*totalaccounts)--;
            printf("Compte supprimé avec succès !\n");
            return;
        }
    }
    printf("Compte non trouvé !\n");
}

// Fonction pour vérifier si le mot de passe respecte la politique de base
int isPasswordValid(char *password) {
    int numberfound = 0, upercasefound = 0, specialcharfound = 0;

    for (int i = 0; i < strlen(password); i++) {
        if (isdigit(password[i])) numberfound = 1;
        if (isupper(password[i])) upercasefound = 1;
        if (strchr("!@#$%^&*()-_=+[]{}|;:'\",.<>?/`~", password[i])) specialcharfound = 1;
    }

    // Vérification simple de la politique de mot de passe
    if (!upercasefound || !specialcharfound || !numberfound || strlen(password) < 8) {
        return 0;
    }
    return 1;
}

int main() {
    struct conixion conixion1;
    int choice, attempoflogin = 0, isadminlogedin = 0, totalaccounts = 0;

    srand(time(NULL)); // Graine pour la génération d'identifiants de réclamation aléatoires

    do {
       
        printf("|                   1. INSCRIPTION                     |\n");
        printf("|                   2. CONNEXION                       |\n");
        printf("|                   3. QUITTER LE PROGRAMME            |\n");
        printf("|          Veuillez entrer votre choix ici :           |\n");
       
        getchar(); // Effacer le tampon d'entrée

        switch (choice) {
            case 1: { // Enregistrer un nouvel utilisateur
                printf("Veuillez entrer votre nom d'utilisateur : \n");
                fgets(conixion1.SIGN_UP[totalaccounts].username, sizeof(conixion1.SIGN_UP[totalaccounts].username), stdin);
                conixion1.SIGN_UP[totalaccounts].username[strcspn(conixion1.SIGN_UP[totalaccounts].username, "\n")] = '\0';

                printf("Veuillez entrer votre email : \n");
                fgets(conixion1.SIGN_UP[totalaccounts].email, sizeof(conixion1.SIGN_UP[totalaccounts].email), stdin);
                conixion1.SIGN_UP[totalaccounts].email[strcspn(conixion1.SIGN_UP[totalaccounts].email, "\n")] = '\0';

                printf("Veuillez entrer votre mot de passe : \n");
                fgets(conixion1.SIGN_UP[totalaccounts].password, sizeof(conixion1.SIGN_UP[totalaccounts].password), stdin);
                conixion1.SIGN_UP[totalaccounts].password[strcspn(conixion1.SIGN_UP[totalaccounts].password, "\n")] = '\0';

                // Valider le mot de passe selon une politique de base
                if (!isPasswordValid(conixion1.SIGN_UP[totalaccounts].password)) {
                    printf("Le mot de passe doit comporter au moins 8 caractères et contenir une lettre majuscule, un caractère spécial et un chiffre !\n");
                } else {
                    printf("Vous avez été inscrit avec succès !\n");
                    totalaccounts++;
                }
                break;
            }

            case 2: { // Interface de connexion
                printf("Veuillez entrer votre nom d'utilisateur : ");
                fgets(conixion1.SIGN_IN.username1, sizeof(conixion1.SIGN_IN.username1), stdin);
                conixion1.SIGN_IN.username1[strcspn(conixion1.SIGN_IN.username1, "\n")] = '\0';

                printf("Veuillez entrer votre mot de passe : ");
                fgets(conixion1.SIGN_IN.password1, sizeof(conixion1.SIGN_IN.password1), stdin);
                conixion1.SIGN_IN.password1[strcspn(conixion1.SIGN_IN.password1, "\n")] = '\0';

                if (strcmp(conixion1.SIGN_IN.username1, adminusername) == 0 && strcmp(conixion1.SIGN_IN.password1, adminpassword) == 0) {
                    printf("Administrateur connecté avec succès !\n");
                    isadminlogedin = 1;
                } else {
                    int loggedIn = 0;
                    for (int i = 0; i < totalaccounts; i++) {
                        if (strcmp(conixion1.SIGN_IN.username1, conixion1.SIGN_UP[i].username) == 0 &&
                            strcmp(conixion1.SIGN_IN.password1, conixion1.SIGN_UP[i].password) == 0) {
                            printf("Connexion réussie !\n");
                            loggedIn = 1;

                            // Afficher le menu utilisateur après une connexion réussie
                            int userChoice;
                            do {
                                printf("-----------------MENU UTILISATEUR--------------------\n");
                                printf("|                1. AJOUTER UNE RÉCLAMATION         |\n");
                                printf("|                   2. SE DÉCONNECTER                |\n");
                                
                                scanf("%d", &userChoice);
                                getchar(); // Effacer le tampon d'entrée

                                switch (userChoice) {
                                    case 1:
                                        addReclamation(conixion1.SIGN_IN.username1);
                                        break;

                                    case 2:
                                        printf("Utilisateur déconnecté.\n");
                                        break;

                                    default:
                                        printf("Choix invalide. Réessayez.\n");
                                }
                            } while (userChoice != 2);

                            break;
                        }
                    }
                    if (!loggedIn) {
                        printf("Nom d'utilisateur ou mot de passe invalide.\n");
                    }
                }

                break;
            }

            case 3:
                printf("Sortie du programme.\n");
                break;

            default:
                printf("Choix invalide !\n");
                break;
        }

        // Actions administratives
        while (isadminlogedin) {
            int adminchoice;

           
            printf("|                1. VOIR TOUS LES UTILISATEURS        |\n");
            printf("|               2. SUPPRIMER UN COMPTE               |\n");
            printf("|             3. GÉRER LES RÉCLAMATIONS                |\n");
            printf("|                  4. SE DÉCONNECTER                 |\n");

            scanf("%d", &adminchoice);
            getchar(); // Effacer le tampon d'entrée

            switch (adminchoice) {
                case 1:
                    printf("Total des comptes : %d\n", totalaccounts);
                    for (int i = 0; i < totalaccounts; i++) {
                        printf("Nom d'utilisateur : %s, Email : %s\n", conixion1.SIGN_UP[i].username, conixion1.SIGN_UP[i].email);
                    }
                    break;

                case 2:
                    deleteAccount(&conixion1, &totalaccounts);
                    break;

                case 3:
                    manageReclamations();
                    break;

                case 4:

                    break;

                default:
                    printf("Choix invalide. Réessayez.\n");
            }
        }

    } while (choice != 3);

    return 0;
}

