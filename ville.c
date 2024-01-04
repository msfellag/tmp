#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------- Structure de la Pile ----
typedef struct Ville {
    char nom[20];
    char gouvernorat[20];
    int population;

} ville;

typedef struct Element {
    ville v;
    struct Element *suivant;

} element;

element *Pile;

// --------- Fonctions de base ------

void initialiser(element **sommet) {
    *sommet = NULL;
}

int estVide(element **sommet) {
    return *sommet == NULL;
}

// empiler : recoit en parametre un enregistrement de type 'ville' qu'elle empilera
// au sommet de la pile
void empiler(element** sommet, ville nouvelleVille) {
    element* nouveauSommet;

    nouveauSommet = (element*) malloc(sizeof(element));

    // Le nouvel element recoit l'adresse de l'ancien Sommet de la pile
    // Stocker dans notre variable globale sommet
    nouveauSommet->suivant = *sommet;

    *sommet = nouveauSommet;

    // On copie les valeurs recues vers le nouveau element creer
    nouveauSommet->v = nouvelleVille;
}

// Depiler : retourne un enregistrement de type 'ville' qui contient nom, gouvernorat et population
// qui represente le sommet actuel de la pile
ville depiler(element **sommet) {
    ville valeurDepiler;
    element *temp;

    // on stocke l'adresse du sommet actuel dans une var temporaire
    temp = *sommet;
    // on fait pointer le sommet vers l'element suivant
    *sommet = (*sommet)->suivant;

    valeurDepiler = temp->v;

    free(temp);
    return valeurDepiler;
}

// -------- 2.1 Compter le nombre de villes -------

int compter(element **sommet) {
    int i = 0;
    ville villeTemporaire;
    element *pileTemporaire;

    initialiser(&pileTemporaire);

    // On depile et on compte les nbr d'elements (en stockant une copie dans pileTemporaire)
    while(estVide(sommet) == 0) {
        villeTemporaire = depiler(sommet);
        empiler(&pileTemporaire, villeTemporaire);
        i++;
    }

    // on restore la Pile a son etat initial
    while (estVide(&pileTemporaire) == 0)
    {
        villeTemporaire = depiler(&pileTemporaire);
        empiler(sommet, villeTemporaire);
    }
    
    return i;
}

// -------- 2.2 Afficher toutes les villes ayant plus de 100 000 habitants ---

void afficherPlusDe100k(element **sommet) {
    ville villeTemporaire;
    element *pileTemporaire;

    initialiser(&pileTemporaire);

    while (estVide(sommet) == 0)
    {
        villeTemporaire = depiler(sommet);
        empiler(&pileTemporaire, villeTemporaire);

        if (villeTemporaire.population > 100000) {
            printf("Nom : %s \n", villeTemporaire.nom);
            printf("Gouvernorat : %s \n", villeTemporaire.gouvernorat);
            printf("Population : %d \n\n", villeTemporaire.population);
        }
        
    }

    // on restore la Pile a son etat initial
    while (estVide(&pileTemporaire) == 0)
    {
        villeTemporaire = depiler(&pileTemporaire);
        empiler(sommet, villeTemporaire);
    }
    
}

// ---------  2.3 - Supprimer la 3eme ville ----------

void supprime3eme(element **sommet) {

    ville villeTemporaire;
    element *pileTemporaire;

    // On depile 3 elements
    for (int i = 0; i < 3; i++) {
        villeTemporaire = depiler(sommet);
        empiler(&pileTemporaire, villeTemporaire); 
    }

    // On fait un depiler sans stocker sa valeur pour supprimer la 3eme valeur
    // qui est la 1ere valeure dans la pileTemporaire
    depiler(&pileTemporaire);

    // on restore la Pile a son etat initial
    while (estVide(&pileTemporaire))
    {
        villeTemporaire = depiler(&pileTemporaire);
        empiler(sommet, villeTemporaire);
    }
    
}

// ---------- 2.4 - Supprimer la dernière ville -----

void supprimeDerniereVal(element **sommet) {

    ville villeTemporaire;
    element *pileTemporaire;

    // on depile toute la pile dans pileTemporaire
    while (estVide(sommet) == 0)
    {
        villeTemporaire = depiler(sommet);
        empiler(&pileTemporaire, villeTemporaire);        
    }

    // On fait un depiler sans stocker sa valeur pour supprimer la derniere valeure
    // qui est la premiere valeure dans la pileTemporaire
    depiler(&pileTemporaire);

    // on restore la Pile a son etat initial
    while (estVide(&pileTemporaire))
    {
        villeTemporaire = depiler(&pileTemporaire);
        empiler(sommet, villeTemporaire);
    }

}

// ---------- Supprimer toutes les villes ayant plus de 100 000 habitants ----

void supprimerPlusDe100k(element **sommet) {
    ville villeTemporaire;
    element *pileTemporaire;

    // On depile completement la pile
    while (estVide(sommet) == 0)
    {
        villeTemporaire = depiler(sommet);
        empiler(&pileTemporaire, villeTemporaire);        
    }

    // on restore la Pile en empilant seulement les valeurs avec : population < 100k
    while (estVide(&pileTemporaire))
    {
        villeTemporaire = depiler(&pileTemporaire);
        if (villeTemporaire.population < 100000) {
            empiler(sommet, villeTemporaire);
        }
    }
    
}

// --------- Supprimer toutes les villes qui commencent par la lettre 'S' -------

void supprimerLettreS(element **sommet) {

    ville villeTemporaire;
    element *pileTemporaire;

    // On depile completement la pile
    while (estVide(sommet) == 0)
    {
        villeTemporaire = depiler(sommet);
        empiler(&pileTemporaire, villeTemporaire);        
    }

    // on restore la Pile en empilant seulement les valeurs avec : nom[0] != 'S'
    while (estVide(&pileTemporaire))
    {
        villeTemporaire = depiler(&pileTemporaire);
        if (villeTemporaire.nom[0] != 'S') {
            empiler(sommet, villeTemporaire);
        }
    }
    
}

// ----------- Bonus -------

void affichageRecursive(element **sommet) {
    ville villeTemporaire;

    if(estVide(sommet) == 0) {
        villeTemporaire = depiler(sommet);
        printf("Nom : %s \n", villeTemporaire.nom);
        printf("Gouvernorat : %s \n", villeTemporaire.gouvernorat);
        printf("Population : %d \n", villeTemporaire.population);

        affichageRecursive(sommet);

        empiler(sommet, villeTemporaire);
    }
}

// ------------ main ----------

int main() {

    // On remplie la Pile avec les valeurs du fichier
    ville villeTemp;
    FILE *fptr;
    initialiser(&Pile);
    fptr = fopen("municipalite.txt", "r");
    if (fptr == NULL) {
        printf("Erreur ouverture du fichier\n");
        return EXIT_FAILURE;
    }
    while (!feof(fptr)) {
        fscanf(fptr, "%s %s %d", villeTemp.nom, villeTemp.gouvernorat, &villeTemp.population);
        empiler(&Pile, villeTemp);
    }
    fclose(fptr);

    // On execute les fonctions de l'exercices en ordre
    int nbr = compter(&Pile);
    printf("Nombre des villes = %d \n", nbr);

    printf("\n---- Affichage recursive ----\n");
    affichageRecursive(&Pile);

    printf("\n---- Afficher plus de 100k population ----\n");
    afficherPlusDe100k(&Pile);

    supprime3eme(&Pile);

    supprimeDerniereVal(&Pile);

    supprimerPlusDe100k(&Pile);

    supprimerLettreS(&Pile);




    return 0;
}