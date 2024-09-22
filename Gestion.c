#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_USERS 100

//=====for acccunts====================
int totalaccounts =0;                //
int isAdmin=0;                       //
int reclamation_count = 0;           //
//=====================================

//======admin pasword/name=============
char admin_username[] = "BRAHIM";    //
char admin_password[] = "BRAhim-123";//
//=====================================

//=======  Informations new client=========
struct client {                          //
    char nomUtilisateur[50];             //
    char motDePasse[50];                 //
    char tele[10];                       //
};                                       //
struct client clients_data[MAX_USERS];   //
//=========================================

//===== Informations add reclamation==
struct reclamation {                //
    int id;                         //
    char usernam[20];               //
    char motif[50];                 //
    char description[200];          //
    char categorie[20];             //
    char status[50];                //
     char date[20];                 //
};                                  //
struct reclamation reclamation_data[MAX_USERS];
//====================================

//================== Fonction pour vérifier les contraintes du mot de passe==========================================================
bool verifierMotDePasse(char motDePasse[], char nomUtilisateur[]) {                                                                //
     // *******Vérifie la longueur minimale du mot de passe****************|                                                       //
    if (strlen(motDePasse) < 7) {
        return false;}                                                                                                              //
      //**************************
    bool majuscule = false, minuscule = false, chiffre = false, special = false;                                                    //
    for (int i = 0; motDePasse[i] != '\0'; i++) {
        if (motDePasse[i] >= 'A' && motDePasse[i] <= 'Z') {                                                                         //
            majuscule = true;}
             else if (motDePasse[i] >= 'a' && motDePasse[i] <= 'z') {                                                               //
            minuscule = true;}
             else if (motDePasse[i] >= '0' && motDePasse[i] <= '9') {                                                               //
            chiffre = true;}
             else if (strchr("!@#$%^&*", motDePasse[i])) {                                                                          //
            special = true;}
        }                                                                                                                           //
//*** Vérifie si le mot de passe contient au moins une lettre majuscule, une lettre minuscule, un chiffre et un caractère spécial
     if (!majuscule || !minuscule || !chiffre || !special) {                                                                        //
        return false;}
      // *****Vérifie si le mot de passe contient le nom d'utilisateur**|                                                           //
    if (strstr(motDePasse, nomUtilisateur) != NULL) {
        return false;}
                                                                                                                                    //
    return true;
}                                                                                                                                   //
//====================================================================================================================================

//=========================== Fonction create account ============================
void create_account() {                                                          //
    struct client new_client;
                                                                                 //
    printf("Entrez vos informations:\n");
    printf("Telephone: ");                                                       //
    scanf(" %[^\n]", new_client.tele);
    printf("Entrez votre nom d'utilisateur : ");                                 //
    scanf(" %[^\n]", new_client.nomUtilisateur);
    printf("Entrez votre mot de passe : ");                                      //
    scanf(" %[^\n]", new_client.motDePasse);
        //  verifierMotDePasse Fonction pour vérifier  mot de passe              //
    if (verifierMotDePasse(new_client.motDePasse, new_client.nomUtilisateur)) {
        clients_data[totalaccounts] = new_client;                                //
        totalaccounts++;
        printf("Inscription reussie.\n");                                        //
    } else {
        printf("Erreur : Le mot de passe ne respecte pas les contraintes.\n");   //
    }
}                                                                                //
//=================================================================================

//================================================= Fonction Se connecter ================================================
void Se_connecter() {
    char name[100], password[100];                                                                                      //
    isAdmin = 0;
                                                                                                                        //
    printf("Entrez votre nom d'utilisateur : ");
    scanf(" %[^\n]", name);                                                                                             //
    printf("Entrez votre mot de passe : ");
    scanf(" %[^\n]", password);
                                                                                                                        //
    if (strcmp(name, admin_username) == 0 && strcmp(password, admin_password) == 0) {
        printf("Connexion reussie en tant qu'administrateur.\n");
        isAdmin = 1;                                                                                                    //
        menu_admin();//Fonction Menu admin
        return;
    }
                                                                                                                        //
    for (int i = 0; i < totalaccounts; i++) {
        if (strcmp(clients_data[i].nomUtilisateur, name) == 0 && strcmp(clients_data[i].motDePasse, password) == 0) {   //
            printf("%s, vous êtes connecté\n", clients_data[i].nomUtilisateur);
            Menu_dutilisateur();// Fonction Menu utilisateur                                                                                       //
            return;
        }
    }                                                                                                                   //
    printf("Erreur : nom d'utilisateur ou mot de passe incorrect.\n");
}                                                                                                                       //
//========================================================================================================================

//=================Fonction Menu utilisateur =======================================
void Menu_dutilisateur() {                                                       //
    int choice;
    do {                                                                         //
        printf("               Menu d'utilisateur                     \n");
        printf("                  ~~Menu~~                            \n");      //
        printf("            1. Ajouter une reclamation                \n");
        printf("                 0. Quitter                           \n");      //
        printf("Veuillez entrer votre choix ici ==> ");
        scanf("%d", &choice);                                                    //

        if (choice == 1) {                                                       //
          add_reclamation();//Fonction Ajouter une reclamation
        } else if (choice != 0) {                                                //
            printf("Choix invalide, reessayez.\n");
        }                                                                        //
    } while (choice != 0);
}                                                                                //
//=================================================================================

//=======================Fonction pour obtenir la date actuelle   ===================================
                                                                                                   //
void afficher_date_actuelle(char date[]) {                                                         //
    time_t t = time(NULL);                                                                         //
    struct tm dateStruct;                                                                          //
    localtime_s(&dateStruct, &t);                                                                  //
    sprintf(date, "%04d-%02d-%02d", dateStruct.tm_year + 1900, dateStruct.tm_mon + 1, dateStruct.tm_mday);
}                                                                                                  //
//===================================================================================================


//=================Fonction Ajouter une reclamation ===============================
void add_reclamation() {
    if (reclamation_count >= MAX_USERS) {                                        //
        printf("Erreur : Limite maximale de réclamations atteinte.\n");
        return;                                                                  //
    }
                                                                                 //
    struct reclamation new_reclamation;
    new_reclamation.id = rand() % 1000;                                          //
    strcpy(new_reclamation.status, "en cours");
afficher_date_actuelle(new_reclamation.date);// Fonction pour obtenir la date actuelle
    printf("Nom d'utilisateur: ");
    scanf(" %[^\n]", new_reclamation.usernam);                                   //
    printf("Entrez le motif de la reclamation : ");
    scanf(" %[^\n]", new_reclamation.motif);
    printf("Entrez une description detaillee du probleme: ");                    //
    scanf(" %[^\n]", new_reclamation.description);
    printf("Entrez la categorie de la reclamation: ");                           //
    scanf(" %[^\n]", new_reclamation.categorie);
                                                                                 //
    reclamation_data[reclamation_count++] = new_reclamation;

    printf("======================================\n");                          //
    printf("\nReclamation ajoutee avec succes    \n");
    printf("ID de reclamation : %d               \n", new_reclamation.id);
    printf("       Motif      : %s               \n", new_reclamation.motif);   //
    printf("    Description   : %s               \n", new_reclamation.description);
    printf("     Categorie    : %s               \n", new_reclamation.categorie);
    printf("      Statut      : %s               \n", new_reclamation.status);  //
    printf("       Date       : %s\n             \n", new_reclamation.date);
    printf("======================================\n");
                                                                                 //
}
//=================================================================================

//=========================== Fonction pour supprimer un compte utilisateur========
void supprimer_comte(struct client clients_data[], int totalaccounts) {
    char nameuser[100];
    printf("Entrez le nom d'utilisateur du compte à supprimer : ");
    scanf(" %[^\n]", nameuser);

    for (int i = 0; i < totalaccounts; i++) {
        if (strcmp(clients_data[i].nomUtilisateur, nameuser) == 0) {
            for (int j = i; j < totalaccounts - 1; j++) {
                clients_data[j] = clients_data[j + 1];
            }
            totalaccounts--;
            printf("Compte supprimé avec succès !\n");
            return totalaccounts;
        }
    }
    printf("Compte non trouve !\n");
     return totalaccounts;
}



//=================Fonction Menu admin ==============================================
void menu_admin() {
    int adminchoice;
    while (isAdmin) {
        printf("             1. Voir tous les utilisateurs            \n");
        printf("             2. Supprimer un compte                \n");
        printf("             3. Gérer les réclamations              \n");
        printf("             0. Quitter                            \n");
        printf("Veuillez entrer votre choix ici ==> ");
        scanf("%d", &adminchoice);

        switch (adminchoice) {
            case 1:
                printf("Total des comptes : %d\n", totalaccounts);
                for (int i = 0; i < totalaccounts; i++) {
                    printf("Nom d'utilisateur : %s, Telephone : %s\n", clients_data[i].nomUtilisateur, clients_data[i].tele);
                }
                break;

            case 2:
              supprimer_comte(clients_data, totalaccounts);
                break;

            case 3:
                printf("Gestion des réclamations non implementee.\n");
                break;

            case 0:
                printf("Administrateur déconnecté.\n");
                isAdmin = 0;
                break;

            default:
                printf("Choix invalide. Réessayez.\n");
        }
    }
}

















int main() {
    int choix;
    do {
        printf("Bienvenue dans le systeme de gestion des reclamations.\n");
        printf("                    ~~Menu~~                          \n");
        printf("                1. Creer un compte                    \n");
        printf("                 2. Se connecter                      \n");
        printf("                  0. Quitter                          \n");
        printf("Veuillez entrer votre choix ici ==> ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                create_account();//Fonction create account
                break;
            case 2:

                Se_connecter();// Fonction Se connecter
                break;
            case 0:
                printf("Merci d'avoir utilisé le système. Au revoir!\n");
                break;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
                break;
        }
    } while (choix != 0);

    return 0;
}
