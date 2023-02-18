#Makefile de GoL
CC = gcc -g
CFLAGS = -Wall
CPPFLAGS += -Iinclude -I/usr/include/cairo
IFLAGS = -Iinclude
LDFLAGS += -lcairo -lm -lX11 -Llib

#Variables
EXEC = main
MODE = graph
INC = graph.o
MA = maing.o

#Les repertoires
vpath %.h include
vpath %.c src
OBJPATH = obj/
BINPATH = bin/

#Options de compilation
ifeq ($(MODE), graph)
	CPPFLAGS += -DGRAPH
	MA = maing.o
else
	INC = io.o
	MA = maint.o
endif

#L'executable
$(EXEC): $(MA) $(INC) grille.o jeu.o
		mkdir -p bin/
		$(CC) -o $@ $(OBJPATH)$(MA) $(OBJPATH)$(INC) $(OBJPATH)grille.o $(OBJPATH)jeu.o -lm $(LDFLAGS)
		mv $@ $(BINPATH)
		
maint.o: maint.c io.h grille.h jeu.h
maing.o: maing.c graph.h grille.h jeu.h
io.o: io.c io.h jeu.h
grille.o: grille.c grille.h
jeu.o: jeu.c jeu.h
graph.o : graph.c graph.h

%.o:
		gcc -c $(CFLAGS) $< $(CPPFLAGS)
		mkdir -p obj/
		mv $@ $(OBJPATH)

#Creation de ma lib
lib: 
	ar -crv libjeu.a $(OBJPATH)grille.o $(OBJPATH)jeu.o
	ranlib libjeu.a
	mkdir -p lib/
	mv libjeu.a lib/

#creation de la documentation
doc:
		doxygen Doxyfile
		mv html/ doc/

#Nettoyage complet:
clean:
		rm -rf  obj/ bin/ doc/ lib/
		@echo Clean!!

#Creation de mon archive
dist:
		tar -czf WoldearegaySaba-GoL-5.2.tar.xz \
		src/ include/ grilles/ Makefile Doxyfile README.md
