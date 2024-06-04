#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//structure pour les livres
typedef struct livre {
    int id;
    char titre[100];
    char auteur[50];
    int stock;
    struct livre* suivant;
} livre;

//structure pour les membres
typedef struct membre{
    int id;
    char nom[50];
    char telephone[15];
    struct membre* suivant;
} membre;

//structure pour les Emprunts
typedef struct emprunt{
    int idEmprunt;
    int idLivre;
    int idMembre;
    int quantite;
    struct emprunt* suivant;
} emprunt;

//Liste des livres
typedef struct {
    livre* tete;
    int nombre;
} listeLivres;

//Pile des membres
typedef struct {
    membre* sommet;
    int nombre;
} pileMembres;

//File des emprunts
typedef struct{
    emprunt* avant;
    emprunt* arriere;
    int nombre;
} fileEmprunts;

//Initialisation

listeLivres ListeLivres = {NULL, 0};
pileMembres PileMembres = {NULL, 0};
fileEmprunts FileEmprunts = {NULL, NULL, 0};

//Gestion des Livres

//Ajouter un livre
void ajouterLivre() {
    livre* nouveauLivre = (livre*)malloc(sizeof(livre));
    nouveauLivre->id = ListeLivres.nombre + 1;
    printf("Entrer le titre du livre: \t");
    scanf("%s", nouveauLivre->titre);
    printf("Entrer l'auteur du livre: \t");
    scanf("%s", nouveauLivre->auteur);
    printf("Entrer le stock du livre: \t");
    scanf("%d", &nouveauLivre->stock);
    nouveauLivre->suivant = ListeLivres.tete;
    ListeLivres.tete = nouveauLivre;
    ListeLivres.nombre++;
    printf("Livre ajoute avec succes!\n");
};

//Afficher tous les livres
void afficherLivres() {
    livre* actuel = ListeLivres.tete;
    //Parcourir la liste
    while (actuel != NULL){
        printf(" ID:\t %d \n Titre:\t %s\n auteur:\t %s\n Stock:\t %d\n =======================\n", actuel->id,actuel->titre, actuel->auteur, actuel->stock);
        actuel = actuel->suivant;
    };

};

//Chercher un livre
void chercherLivre() {
    char titre[50];
    printf("Entrer le titre du livre a chercher: \t");
    scanf("%s", titre);
    livre* actuel = ListeLivres.tete;
    while (actuel != NULL) {
        if (strcasecmp(actuel->titre, titre) == 0) {
            printf("Livre trouve!\nID:\t %d\nTitre:\t %s\nAuteur:\t %s\nStock:\t %d\n=======================\n", actuel->id, actuel->titre, actuel->auteur, actuel->stock);
            return;
        }
        actuel = actuel->suivant;
    }
    printf("Livre non trouve!\n");
}

//sauvegarder les livres  dans un ficher
void sauvegarderLivres() {
    FILE* fichier = fopen("livres.txt", "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier pour sauvegarder les livres!\n");
        return;
    }
    livre* actuel = ListeLivres.tete;
    while (actuel != NULL) {
        fprintf(fichier, "%d %s %s %d\n", actuel->id, actuel->titre, actuel->auteur, actuel->stock);
        actuel = actuel->suivant;
    }
    fclose(fichier);
    printf("Livres sauvegardes avec succes!\n");
}
//charger les livres depuis un fichier

void chargerLivres() {
    FILE* fichier = fopen("livres.txt", "r");
    if (fichier == NULL) {
        printf("Aucun fichier de sauvegarde trouvé!\n");
        return;
    }
    while (!feof(fichier)) {
        livre* nouveauLivre = (livre*)malloc(sizeof(livre));
        fscanf(fichier, "%d %s %s %d\n", &nouveauLivre->id, nouveauLivre->titre, nouveauLivre->auteur, &nouveauLivre->stock);
        nouveauLivre->suivant = ListeLivres.tete;
        ListeLivres.tete = nouveauLivre;
        ListeLivres.nombre++;
    }
    fclose(fichier);
    printf("Livres charges avec succes!\n");
}

//Gestion des Membres
//Ajouter un membre
void ajouterMembre() {
    membre* nouveauMembre = (membre*)malloc(sizeof(membre));
    nouveauMembre->id = PileMembres.nombre + 1;
    printf("Entrer le nom du membre: \t");
    scanf("%s", nouveauMembre->nom);
    printf("Entrer le numero de telephone du membre: \t");
    scanf("%s", nouveauMembre->telephone);
    nouveauMembre->suivant = PileMembres.sommet;
    PileMembres.sommet = nouveauMembre;
    PileMembres.nombre++;
    printf("Membre ajoute avec succes!\n");

};

//afficher les membres
void afficherMembres() {
    membre* actuel = PileMembres.sommet;
    while (actuel != NULL){
        printf("ID:\t %d \n Nom:\t %s\n Telephone:\t %s\n =======================\n", actuel->id,actuel->nom, actuel->telephone);
        actuel = actuel->suivant;
    };
};

//chercher un membre par nom
void chercherMembre() {
    char nom[50];
    printf("Entrer le nom du membre a chercher: \t");
    scanf("%s", nom);
    membre* actuel = PileMembres.sommet;
    while (actuel != NULL) {
        if (strcasecmp(actuel->nom, nom) == 0) {
            printf("Membre trouve!\nID: %d\nNom: %s\nTelephone: %s\n=======================\n", actuel->id, actuel->nom, actuel->telephone);
            return;
        }
        actuel = actuel->suivant;
    }
    printf("Membre non trouve!\n");
}

//sauvegarder les membres dans un ficher
void sauvegarderMembres() {
    FILE* fichier = fopen("membres.txt", "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier pour sauvegarder les membres!\n");
        return;
    }
    membre* actuel = PileMembres.sommet;
    while (actuel != NULL) {
        fprintf(fichier, "%d %s %s\n", actuel->id, actuel->nom, actuel->telephone);
        actuel = actuel->suivant;
    }
    fclose(fichier);
    printf("Membres sauvegardes avec succes!\n");
}
//charger les membres depuis un fichier
void chargerMembres() {
    FILE* fichier = fopen("membres.txt", "r");
    if (fichier == NULL) {
        printf("Aucun fichier de sauvegarde trouvé!\n");
        return;
    }
    while (!feof(fichier)) {
        membre* nouveauMembre = (membre*)malloc(sizeof(membre));
        fscanf(fichier, "%d %s %s\n", &nouveauMembre->id, nouveauMembre->nom, nouveauMembre->telephone);
        nouveauMembre->suivant = PileMembres.sommet;
        PileMembres.sommet = nouveauMembre;
        PileMembres.nombre++;
    }
    fclose(fichier);
    printf("Membres charges avec succes!\n");
}
//Gestion des emprunts

void enregistrerEmprunt(){
    emprunt* nouveauEmprunt = (emprunt*)malloc(sizeof(emprunt));
    nouveauEmprunt->idEmprunt = FileEmprunts.nombre + 1;
    printf("Entrez l'ID du livre: ");
    scanf("%d", &nouveauEmprunt->idLivre);
    printf("Entrez l'ID du membre: ");
    scanf("%d", &nouveauEmprunt->idMembre);
    printf("Entrez la quantite: ");
    scanf("%d", &nouveauEmprunt->quantite);

    livre* Livre = ListeLivres.tete;
    while (Livre != NULL && Livre->id != nouveauEmprunt->idLivre) {
        Livre = Livre->suivant;
    };

    membre* Membre = PileMembres.sommet;
    while (Membre != NULL && Membre->id != nouveauEmprunt->idMembre){
        Membre = Membre->suivant;
    };

    //Verifier Si le livre ou membre est valide
    if (Livre == NULL || Membre == NULL){
        printf("ID du livre ou de membre est invalide!\n");
        free(nouveauEmprunt);
        return;
    };
    //verifier le stock
    if (Livre->stock < nouveauEmprunt->quantite){
        printf("Stock insuffisant!\n");
        free(nouveauEmprunt);
        return;
    };
    //misajour du stock
    Livre->stock -= nouveauEmprunt->quantite;

    nouveauEmprunt->suivant = NULL;
    if (FileEmprunts.arriere == NULL){
        FileEmprunts.avant = nouveauEmprunt;
    }else{
       FileEmprunts.arriere->suivant = nouveauEmprunt;
    };
    FileEmprunts.arriere = nouveauEmprunt;
    FileEmprunts.nombre++;
    printf("Emprunt enregistree avec succes!\n");
};

//Afficher les Emprunts
void afficherEmprunts() {
    emprunt* actuel = FileEmprunts.avant;
    while (actuel != NULL) {
        printf("ID Emprunt:\t %d\n ID Livre:\t %d\n ID Membre:\t %d\n Quantite:\t %d\n =======================\n", actuel->idEmprunt, actuel->idLivre, actuel->idMembre, actuel->quantite);
        actuel = actuel->suivant;
    }
}

//Retourner un livre
void supprimerEmprunt() {
    int idEmprunt;
    printf("Entrez l'ID de l'emprunt à supprimer: ");
    scanf("%d", &idEmprunt);

    emprunt *actuel = FileEmprunts.avant;
    emprunt *precedent = NULL;

    while (actuel != NULL && actuel->idEmprunt != idEmprunt) {
        precedent = actuel;
        actuel = actuel->suivant;
    }

    if (actuel == NULL) {
        printf("Emprunt non trouve.\n");
        return;
    }

    // Trouver le livre correspondant et mettre à jour le stock
    livre *Livre = ListeLivres.tete;
    while (Livre != NULL && Livre->id != actuel->idLivre) {
        Livre = Livre->suivant;
    }

    if (Livre != NULL) {
        Livre->stock += actuel->quantite;
    }

    if (precedent == NULL) { // Supprimer le premier emprunt
        FileEmprunts.avant = actuel->suivant;
    } else {
        precedent->suivant = actuel->suivant;
    }

    if (actuel == FileEmprunts.arriere) {
        FileEmprunts.arriere = precedent;
    }

    free(actuel);
    FileEmprunts.nombre--;
    printf("Emprunt supprime avec succes!\n");
}
//Sauvegard des emprunts dans un fichier
void sauvegarderEmprunts(){
    FILE* fichier = fopen("emprunts.txt", "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier pour sauvegarder les emprunts!\n");
        return;
    }
    emprunt* actuel = FileEmprunts.avant;
    while (actuel != NULL) {
        fprintf(fichier, "%d %d %d %d\n", actuel->idEmprunt, actuel->idLivre, actuel->idMembre, actuel->quantite);
        actuel = actuel->suivant;
    }

    fclose(fichier);
    printf("Emprunts sauvegardés avec succès!\n");
}

//Charger les emprunts depuis un fichier
void chargerEmprunts() {
    FILE* fichier = fopen("emprunts.txt", "r");
    if (fichier == NULL) {
        printf("Aucun fichier de sauvegarde trouvé.\n");
        return;
    }

    emprunt temp;
    while (fscanf(fichier, "%d %d %d %d", &temp.idEmprunt, &temp.idLivre, &temp.idMembre, &temp.quantite) != EOF) {
        emprunt* nouveauEmprunt = (emprunt*)malloc(sizeof(emprunt));
        if (nouveauEmprunt == NULL) {
            printf("Erreur lors de l'allocation de mémoire pour l'emprunt.\n");
            return;
        }
        *nouveauEmprunt = temp;
        nouveauEmprunt->suivant = NULL;

        if (FileEmprunts.avant == NULL) {
            FileEmprunts.avant = nouveauEmprunt;
        } else {
            FileEmprunts.arriere->suivant = nouveauEmprunt;
        }
        FileEmprunts.arriere = nouveauEmprunt;
        FileEmprunts.nombre++;
    }

    fclose(fichier);
    printf("Emprunts charges avec succes!\n");
}
//Menu Principal
void afficherMenu(){
    printf("====Bibliotheque Essaada====\n");
    printf("1. Ajouter un Livre\n");
    printf("2. Afficher les Livres\n");
    printf("3. Chercher un livre\n");
    printf("4. Ajouter un Membre\n");
    printf("5. Afficher les Membres\n");
    printf("6. Chercher un Membre\n");
    printf("7. Enregistrer un emprunt\n");
    printf("8. Afficher les emprunts\n");
    printf("9. Retourner un livre\n");
    printf("10. Sauvegarder et Quitter\n");
};

int main() {
    int choix;

    //Charger les donnees
    chargerLivres();
    chargerMembres();
    chargerEmprunts();
    do{
       
       afficherMenu();
       printf("Entrer votre choix:\t");
       scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            system("cls");
            printf("====Ajouter un Livre====\n");
            ajouterLivre();
            break;
        case 2:
            system("cls");
            printf("====Afficher les Livres====\n");
            afficherLivres();
            break;
        case 3:
            system("cls");
            printf("====Chercher un Livre====\n");
            chercherLivre();
            break;
        case 4:
            system("cls");
            printf("====Ajouter un Membre====\n");
            ajouterMembre();
            break;
        case 5:
            system("cls");
            printf("====Afficher les Membres====\n");
            afficherMembres();
            break;
        case 6:
            system("cls");
            printf("====Chercher un membre====\n");
            chercherMembre();
            break;
        case 7:
            system("cls");
            printf("====Enregistrer un Emprunt====\n");
            enregistrerEmprunt();
            break;
        case 8:
            system("cls");
            printf("====Afficher les Emprunts====\n");
            afficherEmprunts();
            break;
        case 9:
            system("cls");
            printf("====Retourner un livre====\n");
            supprimerEmprunt();
            break;
        case 10:
            system("cls");
            sauvegarderLivres();
            sauvegarderMembres();
            sauvegarderEmprunts();
            printf("sauvegarde complet!");
            printf("Au revoir!\n");
            break;
        default:
            printf("Choix invalide ! Veuillez réessayer.\n");
        }
    } while (choix != 10);
    return 0;

}