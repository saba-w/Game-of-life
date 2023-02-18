/**
 * @file io.h
 * @brief Fonction d'affichage et manipulations des grilles
 * @author Saba WOLDEAREGAY
 * @version 5.2
 * @date 05 avril 2020
 */

#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

/**
 * @fn void affiche_trait (int c);
 * @brief Fonction d'affichage d'un trait horizontal
 * @param[in] c: nombre de cellules du trait
 */
void affiche_trait (int c);

/**
 * @fn void affiche_ligne (int c, int* ligne);
 * @brief Fonction d'affichage d'une ligne de la grille
 * @param[in] c: nombre de colonne
 * @param[in] ligne: tableau indiquant si une cellule est morte ou vivante
 */
void affiche_ligne (int c, int* ligne);

/**
 * @fn void affiche_grille (grille g);
 * @brief Fonction d'affichage d'une grille
 * @param[in] g: grille qu'on va afficher
 */
void affiche_grille (grille g);

/**
 * @fn void efface_grille (grille g);
 * @brief Fonction qui efface une grille
 * @param[in] g: grille a effacer
 */
void efface_grille (grille g);

/**
 * @fn int oscillation(grille *g);
 * @brief Fonction qui teste si la grille oscille apres 100 pas de temps sans delai
 * @param[in] g: pointeur de grille
 * @return int
 */
int oscillation (grille *g);

/**
 * @fn void oscillation_delai(grille *g);
 * @brief Fonction qui teste si la grille oscille apres 100 pas en prenant en compte un delai
 * @param[in] g: pointeur de grille
 */
void oscillation_delai (grille *g);

/**
 * @fn void debut_jeu (grille *g, grille *gc);
 * @brief Fonction qui debute le jeu
 * @param[in] g: pointeur de grille 
 * @param[in] gc: pointeur de grille  
 */
void debut_jeu(grille *g, grille *gc);

#endif
