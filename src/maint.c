/**
 * @file maint.c
 * @brief Programme de tests sur 'Jeu de la vie' en mode texte
 * @author Saba WOLDEAREGAY
 * @version 5.2
 * @date 05 avril 2020
 *
 * 
 * Programme de test pour afficher et faire evoluer une grille 
 * parmi les 8 grilles presente celon les regles du 'Jeu de la vie'
 * 
 */
  
#include <stdio.h>

#include "grille.h"
#include "jeu.h"
#include "io.h"


int main (int argc, char ** argv) {
	
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}

	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	affiche_grille(g);
	
	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
