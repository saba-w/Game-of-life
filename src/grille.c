/**
 * @file grille.c
 * @brief Fichier .c pour les grilles
 * @author Saba WOLDEAREGAY
 * @version 5.2
 * @date 05 avril 2020
 */

#include "grille.h"

void alloue_grille (int l, int c, grille* g) {
	int i;
	g->nbl=l;
	g->nbc=c;
	g->cellules=(int**) calloc(l,sizeof(int*));
	if (g->cellules==NULL) exit(-1);
	for(i=0; i<l; i++) {
		g->cellules[i] = (int*) calloc(c,sizeof(int));
		if (g->cellules[i]==NULL) exit(-1);
	}
}

void libere_grille (grille* g) {
	int i;
	for(i=0; i<g->nbl; i++) {
		free(g->cellules[i]);
	}
	free(g->cellules);
	g->nbl=0;
	g->nbc=0;
}

void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0, non_viables=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}
	
	fscanf(pfile, "%d", & non_viables);
	for (n=0; n< non_viables; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_non_viable(i,j,*g);
	}
	fclose (pfile);
	return;
}


void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}

int compare_grilles(grille *g, grille *gc) {
	for(int i=0; i<g->nbl; i++) {
		for(int j=0; j<g->nbc; j++) {
			if(g->cellules[i][j]!=gc->cellules[i][j]) 
				return 0;
		}
	}
	if(grille_vide(g)==1) return 0;
	return 1;
}

int grille_vide(grille *g) {
	for(int i=0; i<g->nbl; i++) {
		for(int j=0; j<g->nbc; j++) {
			if(g->cellules[i][j]>0)
				return 0;
		}
	}
	return 1;
}
