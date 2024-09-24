
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_USERS 100

//======admin pasword/name=============
char admin_username[] = "BRAHIM";    //
char admin_password[] = "BRAhim-123";//
//=====================================

//=====for acccunts====================
int totalaccounts =0;                //
int isAdmin=0;                       //
int reclamation_count = 0;           //
//=====================================

//=======  Informations new client=========
struct client {                          //
    char nomUtilisateur[50];             //
    char motDePasse[50];                 //
    char tele[10];                       //
     bool isAgent;                       //
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

//=======================Fonction pour obtenir la date actuelle   ===================================
                                                                                                   //
void afficher_date_actuelle(char date[]) {                                                         //
    time_t t = time(NULL);                                                                         //
    struct tm dateStruct;                                                                          //
    localtime_s(&dateStruct, &t);                                                                  //
    sprintf(date, "%04d-%02d-%02d", dateStruct.tm_year + 1900, dateStruct.tm_mon + 1, dateStruct.tm_mday);
}                                                                                                  //
//===================================================================================================

//================== Fonction pour vérifier les contraintes du mot de passe==========================================================
bool verifierMotDePasse(char motDePasse[], char nomUtilisateur[]) {                                                                //
     // *Vérifie la longueur minimale du mot de passe**|                                                                           //
    if (strlen(motDePasse) < 7) {
        return false;}                                                                                                              //
      //****
    bool majuscule = false, minuscule = false, chiffre = false, special = false;                                                    //
    for (int i = 0; motDePasse[i] != '\0'; i++) {
        if (motDePasse[i] >= 'A' && motDePasse[i] <= 'Z') {                                                                         //
            majuscule = true;}
             else if (motDePasse[i] >= 'a' && motDePasse[i] <= 'z') {                                                               //
            minuscule = true;}
             else if (motDePasse[i] >= '0' && motDePasse[i] <= '9') {                                                               //
            chiffre = true;}
             else if (strchr("!@#$%^&*)(_-+={[}?/><.,'~`]|\:;", motDePasse[i])) {                                                   //
            special = true;}
        }                                                                                                                           //
//* Vérifie si le mot de passe contient au moins une lettre majuscule, une lettre minuscule, un chiffre et un caractère spécial
     if (!majuscule || !minuscule || !chiffre || !special) {                                                                        //
        return false;}
      // *Vérifie si le mot de passe contient le nom d'utilisateur|                                                                 //
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
    printf("    Entrez vos informations :)   \n");
    printf("Telephone: ");                                                       //
    scanf(" %[^\n]", new_client.tele);
    printf("Entrez votre nom d'utilisateur : ");                                 //
    scanf(" %[^\n]", new_client.nomUtilisateur);
    printf("Entrez votre mot de passe : ");                                      //
    scanf(" %[^\n]", new_client.motDePasse);
        //  verifierMotDePasse Fonction pour vérifier  mot de passe 54           //
    if (verifierMotDePasse(new_client.motDePasse, new_client.nomUtilisateur)) {
        clients_data[totalaccounts] = new_client;                                //
        totalaccounts++;
        printf("   ~Inscription reussie~     \n");                               //
    } else {
        printf("Erreur : Le mot de passe ne respecte pas les contraintes.\n");   //
    }
}                                                                                //
//=================================================================================

//================================================= Fonction Se connecter ============================================================
void Se_connecter() {                                                                                                               //
    char name[100], password[100];                                                                                                  //
    isAdmin = 0;
    int attempts = 0;

    while (attempts < 3) {                                                                                                          //
        printf("Entrez votre nom d'utilisateur : ");                                                                                //
        scanf(" %[^\n]", name);
        printf("Entrez votre mot de passe : ");
        scanf(" %[^\n]", password);                                                                                                 //
                                                                                                                                    //
        if (strcmp(name, admin_username) == 0 && strcmp(password, admin_password) == 0) {
            printf("Connexion reussie en tant qu'administrateur.\n");
            isAdmin = 1;                                                                                                            //
            menu_admin();//Fonction Menu admin 447                                                                                  //
            return;
        }
                                                                                                                                    //
        for (int i = 0; i < totalaccounts; i++) {                                                                                   //
            if (strcmp(clients_data[i].nomUtilisateur, name) == 0 && strcmp(clients_data[i].motDePasse, password) == 0) {
                printf("%s, vous etes connecte\n", clients_data[i].nomUtilisateur);
                if (clients_data[i].isAgent) {                                                                                      //
                    menu_agent();//Fonction Menu Reclamation agent 621                                                              //
                } else {
                    Menu_dutilisateur();//Fonction Menu utilisateur 148
                }                                                                                                                   //
                return;                                                                                                             //
            }
        }
                                                                                                                                    //
        attempts++;                                                                                                                 //
        printf("Erreur : nom d'utilisateur ou mot de passe incorrect. Tentatives restantes : %d\n", 3 - attempts);

        if (attempts == 3) {                                                                                                        //
            printf("Trop de tentatives echouees. Veuillez patienter 1 minute avant de reessayer.\n");                               //
            Sleep(60000);
            printf("Vous pouvez maintenant réessayer.\n");
            attempts = 0;                                                                                                           //
        }                                                                                                                           //
    }
}                                                                                                                                   //
//====================================================================================================================================

//=================Fonction Menu utilisateur =======================================
void Menu_dutilisateur() {                                                       //
    int choice;
    do {                                                                         //
        printf("               Menu d'utilisateur                     \n");
        printf("                    Menu                              \n");      //
        printf("            1. Ajouter une reclamation                \n");
        printf("            2.modifier  de reclamation                \n");      //
        printf("            3.Supprimer la reclamation                \n");
        printf("            4.  Les reclamations                      \n");      //
        printf("                 0. Quitter                           \n");      //
        printf("Veuillez entrer votre choix ici ==> ");
        scanf("%d", &choice);                                                    //

        if (choice == 1) {                                                       //
          add_reclamation();//Fonction Ajouter une reclamation 181
        }
        else if (choice==2){                                                     //
        modifier_de_reclamation();//Fonction modifier my reclamation 217
        }
        else if (choice==3){
        Supprimerlareclamationutilisateur();//Fonction Supprimer la reclamation 275
        }
        else if (choice==4){                                                     //
        my_reclamations();//Fonction my reclamations 302
        }
        else if (choice != 0) {                                                  //
            printf("Choix invalide, reessayez.\n");
        }                                                                        //
    } while (choice != 0);
}                                                                                //
//=================================================================================

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
    printf("nom et prenom : ");
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
    printf(" Nom d'utilisateur: %s               \n", new_reclamation.usernam);
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

//===========================Fonction modifier de reclamation d'utilisateur===========================================================================
                                                                                                                                                    //
void modifier_de_reclamation() {
    int ID;                                                                                                                                         //
    bool found = false;
    printf("Entrez l'ID de la reclamation a modifier : ");
    if (scanf("%d", &ID) != 1) {
        printf("Erreur : Entree invalide.\n");                                                                                                      //
        return;
    }
    for (int i = 0; i < reclamation_count; i++) {
        if (reclamation_data[i].id == ID) {                                                                                                         //
            found = true;

            char current_date[20];
            afficher_date_actuelle(current_date);                                                                                                   //

            struct tm date_submitted = {0};
            if (sscanf(reclamation_data[i].date, "%d-%d-%d", &date_submitted.tm_year, &date_submitted.tm_mon, &date_submitted.tm_mday) != 3) {
                printf("Erreur : Date de soumission invalide.\n");
                return;                                                                                                                             //
            }
            date_submitted.tm_year -= 1900;
            date_submitted.tm_mon -= 1;
                                                                                                                                                    //
            struct tm date_now = {0};
            if (sscanf(current_date, "%d-%d-%d", &date_now.tm_year, &date_now.tm_mon, &date_now.tm_mday) != 3) {
                printf("Erreur : Date actuelle invalide.\n");                                                                                       //
                return;
            }                                                                                                                                       //
            date_now.tm_year -= 1900;
            date_now.tm_mon -= 1;

            double seconds = difftime(mktime(&date_now), mktime(&date_submitted));
            double hours = seconds / 3600;                                                                                                          //

            if (hours < 24) {
                printf("Reclamation trouvee. Entrez les nouvelles informations:\n");                                                                //
                printf("Entrez le nouveau motif de la reclamation : ");
                scanf(" %[^\n]", reclamation_data[i].motif);
                printf("Entrez une nouvelle description detaillee du probleme: ");                                                                  //
                scanf(" %[^\n]", reclamation_data[i].description);
                printf("Entrez la nouvelle categorie de la reclamation: ");
                scanf(" %[^\n]", reclamation_data[i].categorie);
                                                                                                                                                    //
                printf(" ~Reclamation modifiee avec succes~\n");
            } else {
                printf("Erreur : Vous ne pouvez pas modifier cette reclamation car plus de 24 heures se sont ecoulees.\n");
            }                                                                                                                                       //
            break;
        }
    }                                                                                                                                                //
    if (!found) {
        printf("Erreur : ID %d non trouve.\n", ID);
    }                                                                                                                                               //
}
//=====================================================================================================================================================

//===============================Fonction Supprimer la reclamation ============================
void Supprimerlareclamationutilisateur() {                                                   //
    int ID;
    bool found = false;                                                                      //



    printf("Entrez l'ID de la reclamation a supprimer : ");                                  //
    scanf("%d", &ID);

    for (int i = 0; i < reclamation_count; i++) {                                            //
        if (reclamation_data[i].id == ID ) {
            found = true;
            for (int j = i; j < reclamation_count - 1; j++) {                                 //
                reclamation_data[j] = reclamation_data[j + 1];
            }                                                                                //
            reclamation_count--;
            printf("Reclamation avec ID %d supprimee avec succes.\n", ID);
            break;                                                                           //
        }
    }

    if (!found) {                                                                            //
        printf("Erreur : ID %d non trouvee ou vous n'etes pas l'auteur de cette reclamation.\n", ID);
    }
}                                                                                            //
//=============================================================================================

//================Fonction my reclamations  ======================================
void my_reclamations() {                                                        //
     int ID;
     printf("Entrez l'ID  ");                                                   //
     scanf("%d", &ID);
                                                                                //
    printf("Liste de vos reclamations :\n");

    bool hasReclamations = false;

     for (int i = 0; i < reclamation_count; i++) {                              //
        if (reclamation_data[i].id == ID ) {
            hasReclamations = true;
            printf("======================================\n");
            printf("Nom d'utilisateur: %s\n", reclamation_data[i].usernam);     //
            printf("ID de reclamation : %d\n", reclamation_data[i].id);
            printf("Motif : %s\n", reclamation_data[i].motif);
            printf("Description : %s\n", reclamation_data[i].description);
            printf("Categorie : %s\n", reclamation_data[i].categorie);          //
            printf("Statut : %s\n", reclamation_data[i].status);
            printf("Date : %s\n", reclamation_data[i].date);
            printf("======================================\n");                 //
        }
    }                                                                           //

    if (!hasReclamations) {
   printf("Erreur : ID %d non trouvee.\n", ID);      }
}                                                                               //
//================================================================================
//==========================Fonction Rechercher les reclamations =======================================
void Rechercher_reclamations() {
    int choix;
    printf("Choisissez un critere de recherche :\n");
    printf("1. Rechercher par nom d'utilisateur\n");
    printf("2. Rechercher par date\n");
    printf("3. Rechercher par description\n");
    printf("4. Rechercher par statut\n");
    printf("0. Quitter la recherche\n");
    printf("Veuillez entrer votre choix ici ==> ");
    scanf("%d", &choix);

    switch (choix) {
        case 1: {
            char nomUtilisateur[50];
            printf("Entrez le nom et prenom : ");
            scanf(" %[^\n]", nomUtilisateur);
            printf("Résultats de la recherche par nom et prenom '%s' :\n", nomUtilisateur);
            bool found = false;
            for (int i = 0; i < reclamation_count; i++) {
                if (strcmp(reclamation_data[i].usernam, nomUtilisateur) == 0) {
                    found = true;
                    afficher_detail_reclamation(reclamation_data[i]);
                }
            }
            if (!found) {
                printf("Aucune reclamation trouvée pour l'utilisateur %s.\n", nomUtilisateur);
            }
            break;
        }
        case 2: {
            char dateRecherche[20];
            printf("Entrez la date (YYYY-MM-DD) : ");
            scanf(" %[^\n]", dateRecherche);
            printf("Résultats de la recherche par date '%s' :\n", dateRecherche);
            bool found = false;
            for (int i = 0; i < reclamation_count; i++) {
                if (strcmp(reclamation_data[i].date, dateRecherche) == 0) {
                    found = true;
                    afficher_detail_reclamation(reclamation_data[i]);
                }
            }
            if (!found) {
                printf("Aucune réclamation trouvée pour la date %s.\n", dateRecherche);
            }
            break;
        }
        case 3: {
            char descriptionRecherche[200];
            printf("Entrez un mot clé de description : ");
            scanf(" %[^\n]", descriptionRecherche);
            printf("Résultats de la recherche par description '%s' :\n", descriptionRecherche);
            bool found = false;
            for (int i = 0; i < reclamation_count; i++) {
                if (strstr(reclamation_data[i].description, descriptionRecherche) != NULL) {
                    found = true;
                    afficher_detail_reclamation(reclamation_data[i]);
                }
            }
            if (!found) {
                printf("Aucune réclamation trouvée avec la description contenant '%s'.\n", descriptionRecherche);
            }
            break;
        }
        case 4: {
            char statutRecherche[50];
            printf("Entrez le statut (ex: en cours, resolue, rejetee) : ");
            scanf(" %[^\n]", statutRecherche);
            printf("Résultats de la recherche par statut '%s' :\n", statutRecherche);
            bool found = false;
            for (int i = 0; i < reclamation_count; i++) {
                if (strcmp(reclamation_data[i].status, statutRecherche) == 0) {
                    found = true;
                    afficher_detail_reclamation(reclamation_data[i]);
                }
            }
            if (!found) {
                printf("Aucune réclamation trouvée avec le statut '%s'.\n", statutRecherche);
            }
            break;
        }
        case 0:
            printf("Retour au menu principal.\n");
            break;
        default:
            printf("Choix invalide, veuillez réessayer.\n");
            break;
    }
}

// Fonction d'affichage des détails d'une réclamation
void afficher_detail_reclamation(struct reclamation reclam) {
    printf("======================================\n");
    printf("  nom et prenom  : %s\n", reclam.usernam);
    printf("ID de réclamation: %d\n", reclam.id);
    printf("Motif: %s\n", reclam.motif);
    printf("Description: %s\n", reclam.description);
    printf("Catégorie: %s\n", reclam.categorie);
    printf("Statut: %s\n", reclam.status);
    printf("Date: %s\n", reclam.date);
    printf("======================================\n");
}
//=======================================================================================================================












//===============================================Fonction Menu admin =====================================================================
void menu_admin() {
    int adminchoice;                                                                                                                    //
    while (isAdmin) {
        printf("------------------ ~ Admin Menu~  -----------------\n");
        printf("          1. Voir tous les utilisateurs            \n");                                                                //
        printf("             2. Supprimer un compte                \n");
        printf("            3. lister les reclamations             \n");
        printf("       4. modifier le statut de reclamation        \n");                                                                //
        printf("            5. Supprimer la reclamation            \n");
        printf("        6.Changer le role de l'utilisateur         \n");
        printf("7. Afficher les reclamations ordonnees par priorite\n");
        printf("             8.Statistiques et Rapports            \n");
        printf("            9.Rechercher les reclamations          \n");
        printf("                  0. Quitter                       \n");
        printf("Veuillez entrer votre choix ici ==> ");
        scanf("%d", &adminchoice);                                                                                                      //

        switch (adminchoice) {
            case 1:                                                                                                                     //
                printf("Total des comptes : %d\n", totalaccounts);
                for (int i = 0; i < totalaccounts; i++) {
                    printf("Nom d'utilisateur : %s | Telephone : %s\n", clients_data[i].nomUtilisateur, clients_data[i].tele);          //
                }
                break;
                                                                                                                                        //
            case 2:
             totalaccounts = supprimer_comte(clients_data, totalaccounts); //Fonction pour supprimer un compte utilisateur 512
                break;
                                                                                                                                        //
            case 3:
                list_les_reclamations();//Fonction list les réclamations 533                                                            //
                break;
            case 4:                                                                                                                     //
                    reclamationstatus();//Fonction modifier le statut de reclamation 550
                    break;
            case 5:                                                                                                                     //
                   Supprimer_la_reclamation();//Fonction Supprimer la réclamation 576
                    break;
             case 6:
                   Changer_le_role_de_lutilisateur();//Fonction Changer le role de l'utilisateur  600                                     //
                    break;

            case 7:
                   afficherReclamationsTriees();//Fonction Afficher les reclamations ordonnees par priorite 665
                    break;
            case 8:
                Statistiques_Rapports();//Fonction Statistiques_Rapports 710
                    break;
            case 9:
               Rechercher_reclamations();//Fonction Rechercher les reclamations 332
                    break;
            case 0:
                printf("Administrateur deconnecte.\n");
                isAdmin = 0;                                                                                                           //
                break;

            default:                                                                                                                   //
                printf("Choix invalide.  veuillez reessayer.\n");
        }
    }                                                                                                                                 //
}
                                                                                                                                    //
//=====================================================================================================================================

//====================== Fonction pour supprimer un compte utilisateur=============
int supprimer_comte(struct client clients_data[], int totalaccounts) {           //
    char nameuser[100];                                                          //
    printf("Entrez le nom d'utilisateur du compte a supprimer : ");              //
    scanf(" %[^\n]", nameuser);                                                  //
                                                                                 //
    for (int i = 0; i < totalaccounts; i++) {                                    //
        if (strcmp(clients_data[i].nomUtilisateur, nameuser) == 0) {             //
            for (int j = i; j < totalaccounts - 1; j++) {                        //
                clients_data[j] = clients_data[j + 1];                           //
            }                                                                    //
            totalaccounts--;                                                     //
            printf("Compte supprime avec succes !\n");                           //
            return totalaccounts;                                                //
        }                                                                        //
    }                                                                            //
    printf("Compte non trouve !\n");                                             //
    return totalaccounts;                                                        //
}                                                                                //
//=================================================================================

//=================Fonction list les réclamations=========================================
void list_les_reclamations() {                                                          //
    printf("Liste de toutes les reclamations :\n");                                     //
    for (int i = 0; i < reclamation_count; i++) {
        printf("======================================\n");                              //
         printf("  nom et prenom  : %s               \n", reclamation_data[i].usernam);
        printf("ID de reclamation : %d               \n", reclamation_data[i].id);       //
        printf("       Motif      : %s               \n", reclamation_data[i].motif);
        printf("    Description   : %s               \n", reclamation_data[i].description);
        printf("     Categorie    : %s               \n", reclamation_data[i].categorie);
        printf("      Statut      : %s               \n", reclamation_data[i].status);   //
        printf("       Date       : %s\n             \n", reclamation_data[i].date);
        printf("======================================\n");                              //
    }
}                                                                                        //
//=========================================================================================

//====================Fonction modifier le statut de reclamation===========================
void reclamationstatus() {                                                               //
    int ID;
    bool found = false;                                                                  //

    printf("Entrez l'ID de la reclamation a modifier : ");
    scanf("%d", &ID);                                                                    //

    for (int i = 0; i < reclamation_count; i++) {                                        //
        if (reclamation_data[i].id == ID) {
            found = true;                                                                //
            char new_status[50];
            printf("Reclamation trouvee. Statut actuel : %s\n", reclamation_data[i].status);
            printf("Entrez le nouveau statut : ");                                       //
            scanf(" %[^\n]", new_status);
            strcpy(reclamation_data[i].status, new_status);                              //
            printf("Statut modifie avec succes.\n");
            break;                                                                       //
        }
    }                                                                                    //
    if (!found) {
        printf("Erreur : ID %d non trouvee.\n", ID);                                     //
    }
}                                                                                        //
//=========================================================================================

//=======================Fonction Supprimer la réclamation=================================
void Supprimer_la_reclamation() {                                                        //
    int ID;
    bool found = false;                                                                  //
    printf("Entrez l'ID de la reclamation a supprimer : ");
    scanf("%d", &ID);                                                                    //

    for (int i = 0; i < reclamation_count; i++) {                                        //
        if (reclamation_data[i].id == ID) {
            found = true;                                                                //
            for (int j = i; j < reclamation_count - 1; j++) {
                reclamation_data[j] = reclamation_data[j + 1];                           //
            }
            reclamation_count--;                                                         //
            printf("Reclamation avec ID %d supprimee avec succes.\n", ID);
            break;                                                                       //
        }
    }                                                                                    //
    if (!found) {
        printf("Erreur : ID %d non trouvee.\n", ID);                                     //
    }
}                                                                                        //
//=========================================================================================

//=========================Fonction Changer le role de l'utilisateur =====================
void Changer_le_role_de_lutilisateur() {                                                //
    char nomUtilisateur[50];
    printf("Entrez le nom d'utilisateur du compte a changer de role : ");               //
    scanf("%s", nomUtilisateur);

    for (int i = 0; i < totalaccounts; i++) {                                           //
        if (strcmp(clients_data[i].nomUtilisateur, nomUtilisateur) == 0) {
            clients_data[i].isAgent = !clients_data[i].isAgent;                         //
            printf("Role de l'utilisateur %s change avec succes.\n", nomUtilisateur);
            printf("Le role actuel de %s est maintenant : %s\n", nomUtilisateur, clients_data[i].isAgent ? "Agent" : "Client");
menu_admin();                                                                           //
                return;
        }                                                                               //
    }

    printf("Utilisateur non trouve.\n");                                                //
}
                                                                                        //
//========================================================================================

//========================Fonction Menu Reclamation agent =================================
void menu_agent(){                                                                      //
  int agentcoice;
     do {                                                                                //
        printf("------------------ ~ Agent Menu~  -----------------\n");
        printf("            1. lister les reclamations             \n");                 //
        printf("       2. modifier le statut de reclamation        \n");
        printf("            3. Supprimer la reclamation            \n");                 //
        printf("4. Afficher les reclamations ordonnees par priorite\n");
        printf("             5.Statistiques et Rapports            \n");
        printf("            6.Rechercher les reclamations          \n");
        printf("                  0. Quitter                       \n");
        printf("Veuillez entrer votre choix ici ==> ");                                  //
        scanf("%d", &agentcoice);
                                                                                         //
        switch (agentcoice) {
            case 1:                                                                      //
                list_les_reclamations();//Fonction list les réclamations 553
                break;                                                                   //
            case 2:
                reclamationstatus();//Fonction modifier le statut de reclamation 550     //
                break;
            case 3:                                                                      //
               Supprimer_la_reclamation();//Fonction Supprimer la réclamation 576
                break;                                                                   //
            case 4:
                afficherReclamationsTriees();//Fonction Afficher les reclamations ordonnees par priorite 665
                break;
             case 5:
                Statistiques_Rapports();//Fonction Statistiques_Rapports 710
                    break;
            case 6:
               Rechercher_reclamations();//Fonction Rechercher les reclamations 332
                    break;
            case 0:
                printf("agent deconnecte.\n");                                           //
                break;
            default:                                                                     //
                printf("Invalid choice, please try again.\n");
        }                                                                                //
    } while (agentcoice != 0);
}                                                                                        //
//=========================================================================================

//=====================================Fonction Afficher les reclamations ordonnees par priorite==============================
                                                                                                                            //
int prioriteIndex(char description[]) {                                                                                     //
    if (strstr(description, "Urgence")  || strstr(description, "urgence") || strstr(description, "Décisif") || strstr(description, "décisif")
    || strstr(description, "d'urgence") || strstr(description, "Urgent")|| strstr(description, "urgent")|| strstr(description, "d'urgence"))
    return 1;
    if (strstr(description, "moyenne")  ||strstr(description, "Moyenne")||strstr(description, "Relatif")||strstr(description, "relatif")
    ||strstr(description, "Normal")||strstr(description, "Normal")||strstr(description, "Intermédiaire")||strstr(description, "intermédiaire"))
    return 2;
    return 3;                                                                                                               //
}
void trierReclamationsParPriorite() {
    int i, j;                                                                                                               //
    struct reclamation temp;
                                                                                                                            //
    for (i = 0; i < reclamation_count - 1; i++) {
        for (j = 0; j < reclamation_count - i - 1; j++) {
            if (prioriteIndex(reclamation_data[j].description) > prioriteIndex(reclamation_data[j + 1].description)) {      //
                // Swap reclamations based on priority
                temp = reclamation_data[j];
                reclamation_data[j] = reclamation_data[j + 1];
                reclamation_data[j + 1] = temp;                                                                             //
            }
        }                                                                                                                   //
    }
    printf("Reclamations triees par priorite avec succes.\n");
}                                                                                                                           //
void afficherReclamationsTriees() {
    trierReclamationsParPriorite();
                                                                                                                            //
    printf("==================== Liste des Reclamations Triees ====================\n");
    for (int i = 0; i < reclamation_count; i++) {
        printf("ID: %d\n", reclamation_data[i].id);                                                                          //
        printf("Nom d'utilisateur: %s\n", reclamation_data[i]. usernam);
        printf("Motif: %s\n", reclamation_data[i].motif);
        printf("Description: %s\n", reclamation_data[i].description);
        printf("Categorie: %s\n", reclamation_data[i].categorie);                                                            //
        printf("Statut: %s\n", reclamation_data[i].status);
        printf("Date: %s\n", reclamation_data[i].date);                                                                      //
        printf("--------------------------------------------------------------------\n");                                    //
    }
}                                                                                                                            //
//============================================================================================================================

//===========================================Fonction Statistiques_Rapports======================================


void Statistiques_Rapports() {
    int totalReclamations = reclamation_count;
    int totalUsers = totalaccounts;
    int resolvedCount = 0;
    int inProgressCount = 0;
    int rejectedCount = 0;


    for (int i = 0; i < reclamation_count; i++) {
        if (strcmp(reclamation_data[i].status, "resolue") == 0) {
            resolvedCount++;
        } else if (strcmp(reclamation_data[i].status, "en cours") == 0) {
            inProgressCount++;
        } else if (strcmp(reclamation_data[i].status, "rejetee") == 0) {
            rejectedCount++;
        }
    }

    // Print the statistics
    printf("\n===== Statistiques & Rapports ====\n");
    printf("Total des reclamations |     %d    |\n", totalReclamations);
    printf("------------------------------------\n");
    printf("Total des utilisateurs |     %d    |\n", totalUsers);
    printf("------------------------------------\n");
    printf("Reclamations resolues  |     %d    |\n", resolvedCount);
    printf("------------------------------------\n");
    printf("Reclamations en cours  |     %d    |\n", inProgressCount);
    printf("------------------------------------\n");
    printf("Reclamations rejetees  |     %d    |\n", rejectedCount);
    printf("====================================\n");
}
//==================================================================================================================

int main() {
    int choix;
    do {
        printf("======================================================\n");
        printf("Bienvenue dans le systeme de gestion des reclamations.\n");
        printf("                       Menu                           \n");
        printf("                1. Creer un compte                    \n");
        printf("                 2. Se connecter                      \n");
        printf("                  0. Quitter                          \n");
        printf("Veuillez entrer votre choix ici ==> ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                create_account();//==Fonction create account 82
                break;
            case 2:

                Se_connecter();//==Fonction Se connecter 104
                break;
            case 0:
                printf("Merci d'avoir utilise le systeme. Au revoir!\n");
                break;
            default:
                printf("Choix invalide, veuillez reessayer.\n");
                break;
        }
    } while (choix != 0);

    return 0;
}
