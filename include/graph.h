/**
 * @file graph.h
 * @brief Fichiers header pour l'affichage graphique des grilles
 * @author Saba WOLDEAREGAY
 * @version 5.2
 * @date 05 avril 2020
 */

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "grille.h"
#include "jeu.h"

#define SIZEX 1000
#define SIZEY 1000

/**
 * @fn void paint(cairo_surface_t *surface, grille *g);
 * @brief Fonction qui dessine la grille sur Cairo en mode graphique
 * @param[in] surface : pointeur sur la surface cairo
 * @param[in] g : pointeur de grille
 */
void paint(cairo_surface_t *surface, grille *g);

/**
 * @fn int chargement(cairo_surface_t *surface, Display *dpy, grille *g, grille *gc);
 * @brief Fonction pour charger une nouvelle grille
 * @param[in] surface: pointeur sur la surface cairo
 * @param[in] dpy: pointeur pour le display
 * @param[in] g: pointeur de grille
 * @param[in] gc: pointeur de grille
 * @return int
 */
int chargement(cairo_surface_t *surface, Display *dpy, grille *g, grille *gc);

/**
 * @fn int oscillation_graph (grille *g);
 * @brief Fonction qui teste si la grille oscille apres 100 pas
 * @param[in] g: pointeur de grille
 * @return int
 */
int oscillation_graph(grille *g);

/**
 * @fn void oscillation_delai_graph (cairo_surface_t *surface, Display *dpy, grille *g);
 * @brief Fonction qui teste si la grille oscille apres 100 pas
 * @param[in] surface: pointeur sur la surface graphique
 * @param[in] dpy: pointeur sur la fenetre graphique
 * @param[in] g: pointeur de grille
 */
void oscillation_delai_graph(cairo_surface_t *surface, Display *dpy, grille *g);

/**
 * @fn debut_jeu(grille *g, grille *gc);
 * @brief Fonction qui debute le jeu sur l'outil graphique Cairo
 * @param[in] g : pointeur de grille
 * @param[in] gc : pointeur de grille
 */
void debut_jeu(grille *g, grille *gc);


#endif
