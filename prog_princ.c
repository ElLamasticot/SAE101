#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ligne 6
#define colonne 7
typedef char tabEntiers[ligne][colonne];

void crea_tableau(tabEntiers jeu);
void affiche_tableau(tabEntiers jeu);
void jouer();
void verif_victoire();
int recup_touche();



/*
int main() {
    tabEntiers grille;
    bool verif;
    int joueur;
    verif= false;
    crea_tableau(grille);
    while (verif == false)
    {
        joueur=1;
        affiche_tableau(grille);
        jouer(grille, joueur);
        verif_victoire(grille, joueur);
    }
    
    return EXIT_SUCCESS;
}
*/

int main() {
    tabEntiers grille;
    crea_tableau(grille);
    affiche_tableau(grille);
    printf("%d", recup_touche());
    return EXIT_SUCCESS;
}


void crea_tableau(tabEntiers jeu){
    for (int i = 0; i < ligne; i++)
    {
        for (int j = 0; j < colonne; j++)
        {
            jeu[i][j] = 'J';
        } 
    }
}

void affiche_tableau(tabEntiers jeu){
    for (int i = 0; i < ligne; i++)
    {
        for (int j = 0; j < colonne; j++)
        {
            if (jeu[i][j] == ' '){
                printf("| %c |", jeu[i][j]);
            }
            else if (jeu[i][j] == 'R'){
                printf("|\033[31;1m %c \033[m|", jeu[i][j]);
            }
            else if (jeu[i][j] == 'J'){
                printf("|\033[33;1m %c \033[m|", jeu[i][j]);
            }
        }
        printf("\n");
    }
    for (int k = 0; k < 35; k++)
    {
        printf("-");
    }
    printf("\n");
}

void jouer(){
    int touche;
    touche=recup_touche();
    if (touche == 113)
    {
        printf("touche 1");
    }
    else if (touche == 113)
    {
        printf("touche 1");
    }
    else
    {
        printf("touche non valide");
    }
    
}

void verif_victoire(){
    printf("verif victoire");
}

int recup_touche(){
    //fonction qui lit directement une touche du clavier 
    //sans avoir à appuyer sur entrée afin de fluidifier l'experience de jeu
    int touche;
    system ("/bin/stty raw");
    touche=getchar();
    system ("/bin/stty cooked");
    return touche;
}
