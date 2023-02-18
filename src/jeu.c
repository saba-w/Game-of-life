/**
 * @file jeu.c
 * @brief Fichier .c pour les fonctions du jeu
 * @author Saba WOLDEAREGAY
 * @version 5.2
 * @date 05 avril 2020
 */


#include "jeu.h"

int compte_voisins_vivants_cyclique (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}

int compte_voisins_vivants_non_cyclique (int i, int j, grille g) {
	int v=0, l=g.nbl, c=g.nbc;
	v += (i>0 && j>0)? est_vivante(i-1,j-1,g): 0;
	v += (i>0)? est_vivante(i-1,j,g): 0;
	v += (i>0 && j<c-1)? est_vivante(i-1,j+1,g): 0;
	v += (j>0)? est_vivante(i,j-1,g): 0;
	v += (j<c-1)? est_vivante(i,j+1,g): 0;
	v += (i<l-1 && j>0)? est_vivante(i+1,j-1,g): 0;
	v += (i<l-1)? est_vivante(i+1,j,g): 0;
	v += (i<l-1 && j<c-1)? est_vivante(i+1,j+1,g): 0;
	
	return v;
}

void evolue (grille *g, grille *gc, int(*compte_voisins_vivants)(int,int,grille), int test){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			v = compte_voisins_vivants(i, j, *gc);
			int val=g->cellules[i][j];
			if (est_vivante(i,j,*g)) 
			{ // evolution d'une cellule vivante
				if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
				else {
					if (test==1) {
						g->cellules[i][j]++;
						if (val>=8) set_morte(i,j,*g);
					}
				}	
			}
			else 
			{ // evolution d'une cellule morte
				if ( v==3 && g->cellules[i][j]!=-1) set_vivante(i,j,*g);
			} 
		}
	}
	return;
}
