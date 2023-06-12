/**
 * @file TROADEC_Ryan_PUISSANCE4.c
 * @author TROADEC Ryan
 * @brief Puissance 4 pour 2 joueurs humains, dans le terminal en C
 * @version 1.0
 * @date 2022-11-26
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @def PION_A
 * 
 * @brief Constante du Pion du joueur A
 */
const char PION_A = 'X';
/**
 * @def PION_B
 * 
 * @brief Constante du Pion du joueur B
 */
const char PION_B = 'O';
/**
 * @def VIDE
 * 
 * @brief Constante du Vide d'une case
 */
const char VIDE = ' ';
/**
 * @def INCONNU
 * 
 * @brief Constante en cas de match nul
 */
const char INCONNU = ' ';
/**
* @def NBLIG
*
* @brief definition du nombre de lignes du tableau
*/
#define NBLIG 6
/**
* @def NBCOL
*
* @brief definition du nombre de colonnes du tableau
*/
#define NBCOL 7
/**
 * @def COLONNE_DEBUT 
 * 
 * @brief colonne du milieu
 */
const int COLONNE_DEBUT = NBCOL/2;
/**
* @typedef tab
*
* @brief type tableau a deux dimensions NBLIG x NBCOL
*/
typedef char tabEntiers[NBLIG][NBCOL];

void initGrille(tabEntiers grille);
void afficher(tabEntiers grille, char joueur, int colonne);
bool grillePleine(tabEntiers grille);
void jouer(tabEntiers grille, char joueur, int *ligne, int *colonne);
int choisirColonne(tabEntiers grille, char joueur, int colonne);
int boutGrille(int colonne);
int trouverLigne(tabEntiers grille, int colonne);
bool colonnePleine(tabEntiers grille, int colonne);
bool estVainqueur(tabEntiers grille, int ligne, int colonne);
void finDePartie(char caractere);
int recup_touche();
int compterColonne(tabEntiers grille, int colonne, char joueur);
int compterLigne(tabEntiers grille, int ligne, char joueur);
int compterDiagonales(tabEntiers grille, int ligne, int colonne, char joueur);

//Les changements liés à la maquette sont décrits dans les fonctions concernées

/**
 * @brief Fonction principale
 * 
 * @return int 
 */
int main() {
    char vainqueur;
    int ligne, colonne;
    tabEntiers grille;
    initGrille(grille);
    vainqueur = INCONNU;
    afficher(grille, PION_A, COLONNE_DEBUT);
    while (vainqueur == INCONNU && !grillePleine(grille)) {
        jouer(grille, PION_A, &ligne, &colonne);
        afficher(grille, PION_B, COLONNE_DEBUT);
        if (estVainqueur(grille, ligne, colonne)) {
            vainqueur = PION_A;
        }
        else if (!grillePleine(grille)) {
            jouer(grille, PION_B, &ligne, &colonne);
            afficher(grille, PION_A, COLONNE_DEBUT);
            if (estVainqueur(grille, ligne, colonne)) {
                vainqueur = PION_B;
            }
        }
    }
    finDePartie(vainqueur);
    return EXIT_SUCCESS;
}


/**
 * @brief Initialise la grille du jeu en affectant la constante VIDE à chacun de ses éléments.
 * 
 * @param grille La grille de jeu
 */
void initGrille(tabEntiers grille){
    //Initialise la grille en affectant la constante VIDE à chacun de ses éléments.
    for (int i = 0; i < NBLIG; i++)
    {
        for (int j = 0; j < NBCOL; j++)
        {
            grille[i][j] = VIDE;
        } 
    }
}


/**
 * @brief Réalise l’affichage à l’écran du contenu de la grille avec les pions déjà joués. Cette procédure affiche aussi, au-dessus de la grille, le prochain pion à tomber : il sera affiché au-dessus de la colonne dont le numéro est donné en paramètre. Cette procédure commencera par effacer l’écran.
 * 
 * @param grille La grille de jeu
 * @param joueur Le joueur qui doit jouer
 * @param colonne La colonne où le joueur doit jouer
 */
void afficher(tabEntiers grille, char joueur, int colonne){
    /*Réalise l’affichage à l’écran du contenu de la grille avec les pions déjà joués. 
    Cette procédure affiche aussi, au-dessus de la grille, le prochain pion à tomber : 
    il sera affiché au-dessus de la colonne dont le numéro est donné en paramètre. 
    Cette procédure commencera par effacer l’écran.*/

    /*Changements maquette: remplacement des caractères 
    ainsi que l'ajout de couleurs pour rendre le jeu plus lisible,
    affiche aussi les touches de jeu*/
    system("clear");

    //affichage du pion en couleur au dessus du tableau
    for (int curseur = 0; curseur < colonne; curseur++)
    {
        printf("     ");
    }
    if (joueur==PION_A)
    {   
        printf(" \033[31;1m %c \033[m \n", joueur);
    }
    else
    {
        
        printf(" \033[33;1m %c \033[m \n", joueur);
    }

    for (int i = 0; i < NBLIG; i++)
    {
        for (int j = 0; j < NBCOL; j++)
        {
            //affichage des caractères avec leurs couleurs dans le tableau
            if (grille[i][j] == ' '){
                printf("| %c |", grille[i][j]);
            }
            else if (grille[i][j] == PION_A){
                printf("|\033[31;1m %c \033[m|", grille[i][j]);
            }
            else if (grille[i][j] == PION_B){
                printf("|\033[33;1m %c \033[m|", grille[i][j]);
            }
        }
        printf("\n");
    }
    for (int k = 0; k < 35; k++)
    {
        printf("-");
    }
    //affichage des commandes
    printf("\n");
    printf("Déplacements: q - d\nValider: touche espace\n");
}

/**
 * @brief Parcours tout le tableau pour vérifier s'il est plein
 * 
 * @param grille La grille de jeu
 * 
 * @return true Si la grille est pleine
 * @return false Si la grille n'est pas pleine
 */
bool grillePleine(tabEntiers grille){
    //fonction qui parcours tout le tableau pour vérifier s'il est plein
    for (int i = 0; i < NBLIG; i++)
    {
        for (int j = 0; j < NBCOL; j++)
        {
            if (grille[i][j] == VIDE)
            {
                return false;
            } 
        } 
    }
    return true;
}

/**
 * @brief Déroule le tour d'un joueur en permettant au joueur de déplacer son pion. Si la colonne choisie est valide, le pion du joueur est placé dans l'espace vide le plus bas de la colonne. Retourne ensuite les coordonées du pion dans la grille.
 * 
 * @param grille La grille de jeu
 * @param joueur Le joueur qui doit jouer
 * @param[out] ligne La ligne où le joueur a joué
 * @param[out] colonne La colonne où le joueur a joué
 */
void jouer(tabEntiers grille, char joueur, int *ligne, int *colonne){
    //fonction qui appelle d'autres fonctions pour pouvoir dérouler le tour d'un joueur
    bool valide=false;
    while (valide==false)
    {
    *colonne=choisirColonne(grille, joueur, COLONNE_DEBUT);
    *ligne=trouverLigne(grille, *colonne);
    if (*ligne!=-1)
    {
        grille[*ligne][*colonne]=joueur;
        valide=true;
    }
    }
}

/**
 * @brief Permet au joueur de se déplacer de colonne en colonne grâce à **q** ou **d**, puis de valider son choix avec **espace**. Appelle une fonction pour retourner à la colonne opposée une fois le bord atteint, appelle une autre fonction pour passer les colonnes pleines.
 * 
 * @param grille La grille de jeu
 * @param joueur Le joueur qui doit jouer
 * @param colonne La colonne où le joueur va jouer
 * 
 * @return int La colonne où le joueur veut jouer
 */
int choisirColonne(tabEntiers grille, char joueur, int colonne){
    /*fonction qui permet au joueur de séléctionner la colonne où il veut jouer, 
    appelle une fonction pour retourner à la colonne opposée 
    quand on continue de se déplacer alors qu'on a atteint la limite du tableau,
    appelle une autre fonction pour passer les colonnes pleines*/
    int action;
    action=0;
    while (action!=32)
    //en fonction de l'ASCII de q d et espace
    {
        action=recup_touche();
        if (action==113)
        //test q
        {   
            while (colonnePleine(grille, colonne-1)==true)
            {
                colonne=boutGrille(colonne-1);
            }
            
            colonne=boutGrille(colonne-1);
            
            afficher(grille, joueur, colonne);
        }
            
        else if (action==100)
        {
            //test d
            while (colonnePleine(grille, colonne+1)==true)
            {
                colonne=boutGrille(colonne+1);
            }
        
            colonne=boutGrille(colonne+1);
            
            afficher(grille, joueur, colonne);
        }
        else if (action==32)
        {
            //test espace
            return colonne;
        }
        else
        {
            //test autres touches
            afficher(grille, joueur, colonne);
        }
    }
}

/**
 * @brief Retourne à la colonne opposée quand on continue de se déplacer alors qu'on a atteint la limite du tableau
 * 
 * @param colonne La colonne où le joueur se trouve théoriquement
 * 
 * @return int La colonne où le joueur se trouve après vérification
 */
int boutGrille(int colonne){
    //fonction qui permet le retour à la colonne opposée dans la fonction choisirColonne
    if (colonne == -1)
    {
        colonne= 6;
        return colonne;
    }
    if (colonne > 6)
    {
        colonne= 0;
        return colonne;
    }
    return colonne;
    
    
    
}

/**
 * @brief Vérifie si la colonne est pleine
 * 
 * @param grille La grille de jeu
 * @param colonne La colonne où le joueur veut se déplacer
 * 
 * @return true Si la colonne est pleine
 * @return false Si la colonne n'est pas pleine
 */
bool colonnePleine(tabEntiers grille, int colonne){
    //fonction qui permet de savoir si une colonne est pleine, pour pouvoir la passer dans la fonction choisirColonne
    if (colonne < 0)
    {
        colonne= 6;
    }
    else if (colonne > 6)
    {
        colonne= 0;
    }

    if (grille[0][colonne]!=VIDE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Lit directement une touche du clavier en brut, \net l'envoie dans le programme sans avoir à appuyer sur entrée afin de fluidifier l'experience de jeu. \nbémol: ne fonctionnera que sur Linux et MacOS, et empêche de pouvoir faire CTRL X ou CTRL C
 *
 * @return int L'ASCII de la touche appuyée
 */
int recup_touche(){
    /*fonction qui lit directement une touche du clavier en brut, et l'envoie dans le programme 
    sans avoir à appuyer sur entrée afin de fluidifier l'experience de jeu
    bémol: ne fonctionnera que sur Linux et MacOS, et empêche de pouvoir faire CTRL X ou CTRL C*/
    int touche;
    system ("/bin/stty raw");
    touche=getchar();
    system ("/bin/stty cooked");
    return touche;
}

/**
 * @brief Trouve la ligne où le pion doit être placé
 * 
 * @param grille La grille de jeu
 * @param colonne La colonne où le joueur veut jouer
 * 
 * @return int La ligne où le pion doit être placé ou -1 si la colonne est pleine
 */
int trouverLigne(tabEntiers grille, int colonne){
    //fonction qui trouve la ligne où va se poser le pion, si la colonne pleine, renvoie -1
    for (int i = 0; i < NBLIG; i++)
    {
        if ((i==0) && (grille[i][colonne]!= VIDE))
        {
            return -1;
        }
        else if ((i!=0) && (grille[i][colonne]!= VIDE))
        {
            return i-1;
        }   
    }
    if (grille[5][colonne]== VIDE)
    {
        return 5;
    }
}

/**
 * @brief regarde si le pion placé aux coordonnées créé une victoire
 * 
 * @param grille La grille de jeu
 * @param colonne coordonnée de la colonne du pion
 * @param ligne coordonnée de la ligne du pion
 * 
 * @return true Si le joueur a gagné
 * @return false Si le joueur n'a pas gagné
 */
bool estVainqueur(tabEntiers grille, int ligne, int colonne){
    //fonction qui retourne si le dernier pion placé créé une victoire
    //dans la maquette: La victoire devait highlight le joueur gagnant, cependant je n'ai pas réussi à le faire
    char joueur=grille[ligne][colonne];
    if (compterColonne(grille, colonne, joueur)==4 || (compterLigne(grille, ligne, joueur)==4) || (compterDiagonales(grille, ligne, colonne, joueur)==4))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Affiche le résultat de la partie (victoire d'un des joueurs, match nul )
 * 
 * @param joueur le joueur qui a gagné, ou le caractère INCONNU si match nul, sinon erreur
 */
void finDePartie(char joueur){
    //Fonction qui affiche le vainqueur ou le match nul
    if (joueur==PION_A)
    {
        printf("Le gagnant est: %c!\n", PION_A);
    }
    else if (joueur==PION_B)
    {
        printf("Le gagnant est: %c!\n", PION_B);
    }
    else if (joueur==VIDE)
    {
        printf("Match nul!\n");
    }
    else
    {
        printf("Argument incorrect, impossible de donner le résultat");
    }
    
    
}

/**
 * @brief Compte le nombre de pions alignés dans une colonne réinitialise le compteur à 0 si le pion n'est pas le même
 * 
 * @param grille La grille de jeu
 * @param colonne La colonne où le joueur vient de jouer
 * @param joueur Le joueur qui vient de jouer
 * 
 * @return int compteur final 
 */
int compterColonne(tabEntiers grille, int colonne, char joueur){
    //fonction qui analyse la colonne pour savoir si 4 pions sont alignés.
    int compteur, i;
    compteur=0;
    i=0;
    while ((compteur!=4) && (i<NBLIG))
    {
        if (grille[i][colonne]==joueur)
        {
            compteur= compteur+1;

        }
        else
        {
            compteur=0;
        }
        i=i+1;
    }
    return compteur;
}

/**
 * @brief Compte le nombre de pions alignés dans une ligne réinitialise le compteur à 0 si le pion n'est pas le même
 * 
 * @param grille La grille de jeu
 * @param colonne La colonne où le joueur vient de jouer
 * @param joueur Le joueur qui vient de jouer
 * 
 * @return int compteur final 
 */
int compterLigne(tabEntiers grille, int ligne, char joueur){
    //fonction qui analyse la ligne pour savoir si 4 pions sont alignés.
    int compteur, i;
    compteur=0;
    i=0;

    while ((compteur!=4) && (i<NBCOL))
    {
        if (grille[ligne][i]==joueur)
        {
            compteur= compteur+1;

        }
        else
        {
            compteur=0;
        }
        i=i+1;
    }
    return compteur;
}

/**
 * @brief Compte le nombre de pions alignés dans les diagonales réinitialise le compteur à 0 si le pion n'est pas le même
 * 
 * @param grille La grille de jeu
 * @param colonne La colonne où le joueur vient de jouer
 * @param joueur Le joueur qui vient de jouer
 * 
 * @return int compteur final 
 */
int compterDiagonales(tabEntiers grille, int ligne, int colonne, char joueur){
    //fonction qui analyse les diagonales pour savoir si 4 pions sont alignés.
    int compteur, i1, i2, j1, j2;
    compteur=0;
    i1=ligne;
    j1=colonne;
    i2=ligne;
    j2=colonne;
    //test diagonales ascendantes
    while ((i1!=0) && (j1!=0))
    {
        i1= i1-1;
        j1= j1-1;
    }
    while ((compteur!=4) && (i1<NBLIG) && (j1<NBCOL))
    {
        if (grille[i1][j1]==joueur)
        {
            compteur= compteur+1;

        }
        else
        {
            compteur=0;
        }
        i1=i1+1;
        j1=j1+1;
    }
    if (compteur==4)
    {
        return compteur;
    }
    else
    {
        //test diagonales descendantes
        compteur=0;
        while ((i2!=NBLIG) && (j2!=0))
        {
        i2= i2+1;
        j2= j2-1; 
        }
        
        while ((compteur!=4) && (i2>=0) && (j2>=0))
        {
            if (grille[i2][j2]==joueur)
            {
                compteur= compteur+1;

            }
            else
            {
                compteur=0;
            }
            i2=i2-1;
            j2=j2+1;
        }
        return compteur;
    }
}