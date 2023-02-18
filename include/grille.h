/**
 * @file grille.h
 * @brief Fonctions qui concerne tous les operations pour gerer les grilles
 * @author Saba WOLDEAREGAY
 * @version 5.2
 * @date 05 avril 2020
 */

#ifndef __GRILLE_H__
#define __GRILLE_H__

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * @struct grille:
 * nbl: nombre de lignes
 * nbc: nombre de colonnes
 * cellules: tableau de tableau de cellules
 * @brief Declaration de la structure de grille du jeu
 */
typedef struct {int nbl; int nbc; int** cellules;} grille;
 
/**
 * @fn void alloue_grille (int l, int c, grille* g);
 * @brief Fonction qui alloue un espace memoire de taille l*c
 * a une grille.
 * 
 * @param[in] l: nombre de ligne pour la grille a allouer
 * @param[in] c: nombre de colonne pour la grille a allouer
 */
void alloue_grille (int l, int c, grille* g);

/**
 * @fn void libere_grille (grille* g);
 * @brief Fonctions qui libere l'espace memoire allouee a une grille
 * 
 * @param[in] g: pointeur vers la grille qu'on doit liberer
 */
void libere_grille (grille* g);

/**
 * @fn void init_grille_from_file (char * filename, grille* g);
 * @brief Fonction qui alloue et initialise la grille g a partir 
 * d'un fichier
 * @param[in] filename: le nom de notre ficher surlequel on veut travailler
 */
void init_grille_from_file (char * filename, grille* g);

/**
 * @brief Rend vivante la cellule (i,j) de la grille g
 * @param[in] i: ligne de la cellule
 * @param[in] j: colonne de la cellule
 * @param[in] g: grille
 */
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}

/**
 * @brief Rend morte la cellule (i,j) de la grille g
 * @param[in] i: ligne de la cellule
 * @param[in] j: colonne de la cellule
 * @param[in] g: grille
 */
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}

/**
 * @brief Rend non viable la cellule (i,j) dans la grille g cad les cellules ne peuvent pas etre vivantes a cet endroit
 * @param[in] i: ligne de la cellule
 * @param[in] j: colonne de la cellule
 * @param[in] g: grille
 */
static inline void set_non_viable(int i, int j, grille g){g.cellules[i][j] = -1;}

/**
 * @brief Pointeur de fonctions qui pointe sur est_vivante_nr et est_vivante_v en fonction de la touche 'v' pour
 * activer le vieillissement.
 */
int (*est_vivante)(int,int,grille);

/**
 * @brief Teste si la cellule (i,j) de la grille g est vivante quand le vieillissement est desactiver
 * @param[in] i: abscisse de la cellule dans la grille
 * @param[in] j: ordonnee de la cellule dans la grille
 * @param[in] g: grille
 * @return booleen (0 ou 1) indiquant si la cellule est vivante 
 * ou non
 */
static inline int est_vivante_nr (int i, int j, grille g) {return g.cellules[i][j] > 0;}

/**
 * @brief Teste si la cellule (i,j) de la grille g est vivante quand le vieillissement est activer
 * @param[in] i: abscisse de la cellule dans la grille
 * @param[in] j: ordonnee de la cellule dans la grille
 * @param[in] g: grille
 * @return booleen (0 ou 1) indiquant si la cellule est vivante 
 * ou non
 */
static inline int est_vivante_v (int i, int j, grille g) {return g.cellules[i][j] >= 1;}

/**
 * @fn void copie_grille (grille gs, grille gd);
 * @brief Fonction qui copie une grille dans une autre
 * @param[in] gs: grille a copier
 * @param[in] gd: destination de la grille a copier
 */
void copie_grille (grille gs, grille gd);

/**
 * @fn int compare_grilles(grille *g, grille *gc);
 * @brief Fonction qui teste si 2 grilles sont egales
 * @param[in] g: pointeur de grille
 * @param[in] gc: pointeur de grille
 * @return int
 */
int compare_grilles(grille *g, grille *gc);

/**
 * @fn int grille_vide(grille *g);
 * @brief Fonction qui teste si une grille est vide ou pas
 * @param[in] g: pointeur de grille
 * @return 1 si grille vide 0 sinon
 */
int grille_vide(grille *g);
#endif
