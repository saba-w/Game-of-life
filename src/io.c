/**
 * @file io.c
 * @brief Fichier .c pour l'interface utilisateur
 * @author Saba WOLDEAREGAY
 * @version 5.2
 * @date 05 avril 2020
 */
 

#include "io.h"

int etape=0;

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) {
		if (ligne[i] == 0 ) printf ("|   ");
		else if (ligne[i]==-1) printf("| X "); 
		else {
			if (est_vivante==est_vivante_v) 
				printf("| %d ", ligne[i]);
			else printf ("| O ");
		}
	}
	printf("|\n");
	return;
}

void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("Temps : \e[1;34m%d\e[0m ",etape);
	printf("| Cyclique : %s ", (compte_voisins_vivants==compte_voisins_vivants_cyclique)? "\e[1;34mOui\e[0m" : "\e[0;34mNon\e[0m");
	printf("| Vieillissement : %s ", (est_vivante==est_vivante_v)? "\e[1;34mOui\e[0m" : "\e[0;34mNon\e[0m");
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
}

int oscillation (grille *g) {
	grille g1,gc;
	int i=1;
	alloue_grille(g->nbl,g->nbc,&gc);
	alloue_grille(g->nbl,g->nbc,&g1);
	copie_grille(*g,g1);
	evolue(&g1,&gc,compte_voisins_vivants_cyclique,0);
	while(compare_grilles(g,&g1)!=1 && i<100) {
		evolue(&g1,&gc,compte_voisins_vivants_cyclique,0);
		i++;
	}
	return i;
}

void oscillation_delai (grille *g) {
	int delai=1; int pas=1;
	grille g1,gc;
	alloue_grille(g->nbl,g->nbc,&gc);
	alloue_grille(g->nbl,g->nbc,&g1);
	copie_grille(*g,g1);
	evolue(&g1,&gc,compte_voisins_vivants_cyclique,0);
	while (delai<100 && oscillation(&g1)==100) {
		evolue(&g1,&gc,compte_voisins_vivants_cyclique,0);
		delai++;
	}
	pas=oscillation(&g1);
	if(pas==100 && delai==100) {
		printf("La grille ne semble pas etre oscillante\n");
	}
	else if(delai<100 && delai>1) {
		printf("La grille oscille sur une periode de %d pas apres un delai de %d pas \n",pas,delai);
	}
	else {
		printf("La grille oscille sur une periode de %d pas \n",pas);
	}
}

void debut_jeu(grille *g, grille *gc){
	compte_voisins_vivants=compte_voisins_vivants_cyclique;
	est_vivante=est_vivante_nr;
	char c = getchar(); 
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				etape++;
				evolue(g,gc,compte_voisins_vivants,est_vivante==est_vivante_v);
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}
			case 'n' :
			{// touche 'n' pour entrer le nom d'une nouvelle grille
				char nom[20];
				etape=0;
				printf("Entrer le nom de votre grille.\n");
				scanf("%s",nom);
				libere_grille(g);
				libere_grille(gc);
				init_grille_from_file(nom,g);
				alloue_grille(g->nbl, g->nbc, gc);
				affiche_grille(*g);
				printf("\n");
				getchar();
				break;
			}
			case 'c' :
			{// touche 'c' pour activer/desactiver le voisinage cyclique
				if(compte_voisins_vivants==compte_voisins_vivants_cyclique)
				{
					compte_voisins_vivants=compte_voisins_vivants_non_cyclique;
				}
				else 
				{
					compte_voisins_vivants=compte_voisins_vivants_cyclique;
				}
				getchar();
				break;
			}
			case 'v' :
			{// touche 'v' pour activer le vieillissement des cellules
				if (est_vivante==est_vivante_v){
					est_vivante=est_vivante_nr;
				}
				else {
					est_vivante=est_vivante_v;
				}
				break;
			}
			case 'o' :
			{//touche 'o' pour activer le teste d'oscillation
				oscillation_delai(g);
				break;
			}
			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar(); 
	}
	return;	
}
