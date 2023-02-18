/**
 * @file jeu.h
 * @brief Fonction pour les regles du jeu, header pour 'jeu.c'
 *@author Saba WOLDEAREGAY
 * @version 5.2
 * @date 05 avril 2020
 */

#ifndef __JEU_H__
#define __JEU_H__

#include "grille.h"

/**
 * @fn static inline int modulo(int i, int m);
 * @brief Fonctions modulo modifié pour traiter correctement les 
 * bords i=0 et j=0 dans le calcul des voisins avec bords cycliques
 * @param[in] i: premiere operande
 * @param[in] m: seconde operande
 * @return valeur du modulo modifier
 */
static inline int modulo(int i, int m) {return (i+m)%m;}

/**
 * @fn int (*compte_voisins_vivants)(int,int,grille);
 * @brief Pointeur pour les fonctions compte_voisins_vivants_cyclique
 * et compte_voisins_vivants_non_cyclique
 */
int (*compte_voisins_vivants)(int,int,grille);

/**
 * @fn int compte_voisins_vivants_cyclique (int i, int j, grille g);
 * @brief Fonction qui compte le nombre de voisins vivants 
 * de la cellule (i,j) dont les bords sont cycliques 
 * @param[in] i: ligne de la cellule
 * @param[in] j: colonne de la cellule
 * @param[in] g: grille surlequel on travail
 * @return nombre de voisins vivants
 */
int compte_voisins_vivants_cyclique (int i, int j, grille g);

/**
 * @fn int compte_voisins_vivants_non_cyclique (int i, int j, grille g);
 * @brief Fonction qui compte le nombre de voisins vivants 
 * de la cellule (i,j) dont les bords sont non cyclique
 * @param[in] i: ligne de la cellule
 * @param[in] j: colonne de la cellule
 * @param[in] g: grille surlequel on travail
 * @return nombre de voisins vivants
 */
int compte_voisins_vivants_non_cyclique (int i, int j, grille g);

/**
 * @fn void evolue (grille *g, grille *gc, int(*compte_voisins_vivants)(int,int,grille), int test);
 * @brief Fonction qui fait évoluer la grille g d'un pas de temps
 * @param[in] g: pointeur sur la grille a faire evoluer
 * @param[in] gc: pointeur sur la grille evoluee
 */
void evolue (grille *g, grille *gc, int(*compte_voisins_vivants)(int,int,grille), int test);

#endif
