/**
 * @file graph.c
 * @brief Fichier .c pour l'affichage graphique
 * @author Saba WOLDEAREGAY
 * @version 5.2
 * @date 05 avril 2020
 */

#include "graph.h"

int temps=0;
char affichage[255];
char vieux[10];

void paint(cairo_surface_t *surface, grille *g)
{
	int l=g->nbl;
	int c=g->nbc;
	// create cairo mask
	cairo_t *cr;
	cr=cairo_create(surface);

	// background
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_paint(cr);
	
	sprintf(affichage, "Temps: %d Mode cyclique : %s Vieillissement : %s", temps, ((compte_voisins_vivants==compte_voisins_vivants_cyclique)? "Oui" : "Non"),((est_vivante==est_vivante_v)? "Oui" : "Non"));
	cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
	cairo_select_font_face(cr, "Courier", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr, 13);
	cairo_move_to(cr, 5.0, 20.0);
	cairo_show_text(cr, affichage);
	
	// filled rectangle
	for(int i=0;i<c;i++) {
		for(int j=0;j<l;j++) {
			if(g->cellules[j][i]>0 && g->cellules[j][i]<9) {
				cairo_rectangle(cr,10 + 70*i,50+70*j,70,70);
				cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
				cairo_fill(cr);
				if(est_vivante==est_vivante_v) {
					cairo_set_font_size(cr,50);
					cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
					cairo_move_to(cr,10 + 70*i + 20,50+70*j+50);
					sprintf(vieux, "%d", g->cellules[j][i]);
					cairo_show_text(cr, vieux);
				}
			}
			else if(g->cellules[j][i]==-1) {
				cairo_rectangle(cr,10 + 70*i,50+70*j,70,70);
				cairo_set_source_rgb (cr, 0.5, 0.0, 0.0);
				cairo_fill(cr);
			}
			else {
				cairo_rectangle(cr,10 + 70*i,50+70*j,70,70);
				cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
				cairo_stroke(cr);
			}
		}
	}
	cairo_destroy(cr); // destroy cairo mask
}

int chargement(cairo_surface_t *surface, Display *dpy, grille *g, grille *gc){
	
	XEvent e;
	KeySym touche;
	
	char path[52]={};
	char buffer[10];
	char aff[100]={};	

	while(e.type!=ButtonPress && buffer[0]!='\r'){
		cairo_t *cr;
		cr=cairo_create(surface);
		
		cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
		cairo_paint(cr);
		cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
		cairo_select_font_face(cr, "Courier", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
		cairo_set_font_size(cr, 13);
		cairo_move_to(cr, 5.0, 20.0);
		sprintf(aff, "Grille à charger : %s_", path);
		cairo_show_text(cr,aff);

		
		XNextEvent(dpy, &e);
		

		XLookupString(&e.xkey,buffer,10, &touche, 0);
		if(buffer[0]!='\r' && buffer[0]!='\b'){	
				
			strcat(path, buffer);
			printf("%s \n",path);
		}
		if(buffer[0]=='\b'){
			path[strlen(path)-1]='\0';
		}
		if(e.type==ButtonPress || buffer[0]=='\e')return 0;
		
	}
	//printf("%s \n",path);
	init_grille_from_file(path, g);
	alloue_grille(g->nbl, g->nbc, gc);
	return 1;
}

int oscillation_graph(grille *g) {
	int i=1;
	grille g1,gc;
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

void oscillation_delai_graph(cairo_surface_t *surface, Display *dpy, grille *g) {
	char affichedelai[100]={};
	char affiche[100]={};
	// create cairo mask
	cairo_t *cr;
	cr=cairo_create(surface);

	// background
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_paint(cr);
	
	cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
	cairo_select_font_face(cr, "Courier", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr, 13);
	cairo_move_to(cr, 40, 50.0);
	
	grille g1,gc;
	alloue_grille(g->nbl,g->nbc,&gc);
	alloue_grille(g->nbl,g->nbc,&g1);
	int delai=1;
	int pas=1;
	copie_grille(*g,g1);
	evolue(&g1,&gc,compte_voisins_vivants_cyclique,0);
	while(delai<100 && oscillation_graph(&g1)==100) {
		evolue(&g1,&gc,compte_voisins_vivants_cyclique,0);
		delai++;
	}
	pas=oscillation_graph(&g1);
	if (pas==100 && delai==100) {
		sprintf(affiche, "La grille ne semble pas etre oscillante");
		cairo_show_text(cr, affiche);
	}
	else if (delai<100 && delai>1) {
		sprintf(affiche, "La grille semble osciller sur une periode de %d pas",pas);
		cairo_show_text(cr, affiche);
		cairo_move_to(cr,60,70);
		sprintf(affichedelai, "apres un delai de %d pas",delai);
		cairo_show_text(cr, affichedelai);
	}
	else {
		sprintf(affiche, "La grille oscille sur une periode de %d pas",pas);
		cairo_show_text(cr, affiche);
	}
		
}

void debut_jeu (grille *g, grille *gc) {
	compte_voisins_vivants=compte_voisins_vivants_cyclique;
	est_vivante=est_vivante_nr;
	
	// X11 display
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;
	KeySym touch;
	char buffer[10];
	int l=g->nbl;
	int c=g->nbc;
	
	
	// init the display
	if(!(dpy=XOpenDisplay(NULL))) {
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, c*70+20, l*70+60, 0, 
			BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, "jeu de la vie");
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyPressMask);
	XMapWindow(dpy, win);
	
	// create cairo surface
	cairo_surface_t *cs; 
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

	// run the event loop
	while(1 && e.xbutton.button !=Button3) {
		XNextEvent(dpy, &e);
		if(e.type==Expose && e.xexpose.count<1) {
			paint(cs,g);
		} 
		else if(e.type==ButtonPress) {
			if(e.xbutton.button==Button1) {
				temps+=1;
				evolue(g,gc,compte_voisins_vivants,est_vivante==est_vivante_v);
				paint(cs,g);
			}
		}
		else if(e.type==KeyPress) {
			if(e.xkey.keycode==XKeysymToKeycode(dpy, XStringToKeysym("c"))) {
				if(compte_voisins_vivants==compte_voisins_vivants_cyclique) {
					compte_voisins_vivants=compte_voisins_vivants_non_cyclique;
				}
				else {
					compte_voisins_vivants=compte_voisins_vivants_cyclique;
				}
			}
			if(e.xkey.keycode==XKeysymToKeycode(dpy, XStringToKeysym("v"))) {
				if(est_vivante==est_vivante_v) {
					est_vivante=est_vivante_nr;
				}
				else {
					est_vivante=est_vivante_v;
				}
			}
			if(e.xkey.keycode==XKeysymToKeycode(dpy, XStringToKeysym("n"))) {
				int change=chargement(cs,dpy,g,gc);
				if(change) {
					temps=0;
					compte_voisins_vivants=compte_voisins_vivants_cyclique;
					est_vivante=est_vivante_nr;
				}
				paint(cs,g);
			}
			if(e.xkey.keycode==XKeysymToKeycode(dpy, XStringToKeysym("o"))) {
				oscillation_delai_graph(cs,dpy,g);
			}
			XLookupString(&e.xkey,buffer,10,&touch,0);
			if(buffer[0]=='\e') {
				paint(cs,g);
			}
			if(buffer[0]=='\r') {
				temps+=1;
				evolue(g,gc,compte_voisins_vivants,est_vivante==est_vivante_v);
				paint(cs,g);
			}
		}
		
	}

	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display
	
}
