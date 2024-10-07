#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define vmax 30
#define vmin 5

struct T_Case {
  int ligne;
  int colonne;
};
typedef struct T_Case Case;

struct T_Tab_Case {
  struct T_Case voisins[4];
  int nbvoisins;
};
typedef struct T_Tab_Case T_Case;

struct T_Grille {
  int nbligne;
  int nbcolonne;
  struct T_Case pion;
} plateau;
typedef struct T_Grille Grille;

void Afficher() { // Fonction permettant d'afficher le plateau
  for (int i = 0; i < plateau.nbligne; i++) {
    printf("|");
    for (int j = 0; j < plateau.nbcolonne; j++) {
      if (plateau.pion.ligne == i && plateau.pion.colonne == j)
        printf("0|");
      else
        printf("-|");
    }
    printf("\n");
  }
}

T_Case Voisins() { // Fonction permettant de déterminer les coups jouables
  T_Case vois;
  vois.nbvoisins = 1;
  T_Case fin;
  fin.nbvoisins = 5;
  if (plateau.pion.ligne + 1 < plateau.nbligne) {
    vois.voisins[vois.nbvoisins - 1].colonne = plateau.pion.colonne;
    vois.voisins[vois.nbvoisins - 1].ligne = plateau.pion.ligne + 1;
    vois.nbvoisins = vois.nbvoisins + 1;
  }
  if (plateau.pion.ligne + 2 < plateau.nbligne) {
    vois.voisins[vois.nbvoisins - 1].colonne = plateau.pion.colonne;
    vois.voisins[vois.nbvoisins - 1].ligne = plateau.pion.ligne + 2;
    vois.nbvoisins = vois.nbvoisins + 1;
  }
  if (plateau.pion.colonne + 1 < plateau.nbcolonne) {
    vois.voisins[vois.nbvoisins - 1].colonne = plateau.pion.colonne + 1;
    vois.voisins[vois.nbvoisins - 1].ligne = plateau.pion.ligne;
    vois.nbvoisins = vois.nbvoisins + 1;
  }
  if (plateau.pion.colonne + 2 < plateau.nbcolonne) {
    vois.voisins[vois.nbvoisins - 1].colonne = plateau.pion.colonne + 2;
    vois.voisins[vois.nbvoisins - 1].ligne = plateau.pion.ligne;
    vois.nbvoisins = vois.nbvoisins + 1;
  }
  vois.nbvoisins = vois.nbvoisins - 1;
  if (vois.nbvoisins == 0)
    return fin;
  return vois;
}
void AfficherVoisins(
    T_Case vois) { // Fonction qui affiche au joueur les coups jouables
  if (vois.nbvoisins != 5) {
    printf("Choisissez un coup à jouer parmi les %d disponibles :\n",
           vois.nbvoisins);
    for (int i = 0; i < vois.nbvoisins; i++) {
      printf("\n%d : %d;%d  ", i + 1, vois.voisins[i].ligne,
             vois.voisins[i].colonne);
    }
    printf("\n");
  }
}

void Mouvement(
    T_Case vois) { // Fonction qui permet au joueur de jouer son mouvement
  if (vois.nbvoisins != 5) {
    int coup;
    int valide = 0;
    printf("Coup à jouer : ");
    while (valide == 0) {
      scanf("%d", &coup);
      if (coup <= vois.nbvoisins && coup >= 1) {
        plateau.pion.ligne = vois.voisins[coup - 1].ligne;
        plateau.pion.colonne = vois.voisins[coup - 1].colonne;
        valide = 1;
      } else
        printf("Saisissez une valeur correcte : ");
    }
  }
}

T_Case Jeu(T_Case voisins) {
  Afficher();
  voisins = Voisins();
  AfficherVoisins(voisins);
  Mouvement(voisins);
  return voisins;
};

int Difficulte() {
  int diff;
  int verif = 0;
  printf("Saisissez la difficulté de l'ordinateur :\n");
  printf("1 : L'ordinateur joue au hasard\n");
  printf("2 : L'ordinateur joue 1/3 de coups parfaits\n");
  printf("3 : L'ordinateur joue 2/3 de coups parfaits\n");
  printf("4 : L'ordinateur joue uniquement des coups parfaits\n");
  printf("Difficultée choisie : ");
  while (verif == 0) {
    scanf("%d", &diff);
    if (diff >= 1 && diff <= 4) {
      verif = 1;
    } else
      printf("Veuillez saisir une valeur correcte : ");
  }
  return diff;
}

void MouvementBot(T_Case voisins, int diff) {}

void CoupAleatoire(T_Case voisins) {
  int coup = ((rand() % voisins.nbvoisins));
  plateau.pion.ligne = voisins.voisins[coup].ligne;
  plateau.pion.colonne = voisins.voisins[coup].colonne;
  printf("L'ordinateur s'est déplacé en %d;%d\n", plateau.pion.ligne,
         plateau.pion.colonne);
}

void CoupParfait(T_Case voisins) {
  int coup_l, coup_c, nimber;
  coup_l = -1;
  coup_c = -1;
  for (int i = 0; i < voisins.nbvoisins; i++) {
    nimber = Nimber(voisins.voisins[i].ligne, voisins.voisins[i].colonne);
    if (nimber == 0) {
      coup_l = voisins.voisins[i].ligne;
      coup_c = voisins.voisins[i].colonne;
    }
  }
  if (coup_l == -1 && coup_c == -1) {
    CoupAleatoire(voisins);
  } else {
    plateau.pion.ligne = coup_l;
    plateau.pion.colonne = coup_c;
  }
  printf("L'ordinateur s'est déplacé en %d;%d\n", plateau.pion.ligne,
         plateau.pion.colonne);
}

void CoupOrdi(T_Case voisins, int diff) {
  int proba = ((rand() % 3));
  switch (diff) {
  case 1: {
    CoupAleatoire(voisins);
    break;
  }
  case 2: {
    if (proba == 0) {
      CoupParfait(voisins);
      break;
    } else {
      CoupAleatoire(voisins);
      break;
    }
  }
  case 3: {
    if (proba == 0) {
      CoupAleatoire(voisins);
      break;
    } else {
      CoupParfait(voisins);
      break;
    }
  }
  case 4: {
    CoupParfait(voisins);
    break;
  }
  }
}

int Nimber(int ligne, int colonne) {
  int nimber, di, dj;
  di = 0;
  dj = 0;
  if (plateau.nbligne % 3 - plateau.nbcolonne % 3 < 0)
    di = plateau.nbcolonne % 3 - plateau.nbligne % 3;
  else if (plateau.nbligne % 3 - plateau.nbcolonne % 3 > 0)
    dj = plateau.nbligne % 3 - plateau.nbcolonne % 3;
  if ((ligne + di) % 3 == (colonne + dj) % 3) {
    nimber = 0;
  } else {
    nimber = 1;
  }
  return nimber;
}

void InitPlateau() {
  int boole = 0;
  printf("Nombre de lignes(min 5-max 30) : ");
  while (boole == 0) {
    scanf("%d", &plateau.nbligne);
    if (plateau.nbligne >= vmin && plateau.nbligne <= vmax)
      boole = 1;
    else
      printf("Saisissez une valeur correcte(max 30) : ");
  }
  boole = 0;
  printf("Nombre de colonnes(max 30) : ");
  while (boole == 0) {
    scanf("%d", &plateau.nbcolonne);
    if (plateau.nbcolonne >= vmin && plateau.nbcolonne <= vmax)
      boole = 1;
    else
      printf("Saisissez une valeur correcte : ");
  }
}

int main(void) {
  srand((unsigned int)time(NULL));
  InitPlateau();
  int diff = Difficulte();
  plateau.pion.ligne = 0;
  plateau.pion.colonne = 0;
  T_Case voisins;
  voisins.nbvoisins = 0;
  int gagnant;
  while (voisins.nbvoisins != 5) {
    if (voisins.nbvoisins != 5)
      Afficher(); // Mouvements du joueur
    printf("\033[0m");
    voisins = Voisins();
    AfficherVoisins(voisins);
    Mouvement(voisins);
    if (voisins.nbvoisins != 5)
      Afficher();
    if (voisins.nbvoisins == 5) {
      gagnant = 1;
      break;
    }
    voisins = Voisins(); // Mouvements du bot
    if (voisins.nbvoisins != 5) {
      printf("\033[1;31m");
      CoupOrdi(voisins, diff);
      if (voisins.nbvoisins == 5) {
        gagnant = 2;
        break;
      }
    }
  }
  if (gagnant == 2)
    printf("Vous avez gagné");
  else
    printf("L'ordinateur a gagné");
}
