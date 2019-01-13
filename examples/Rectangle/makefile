finaltarget=RectangleExe
mainfile=Rectangle.cpp
spacedimpath=../../

CC=g++
CFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
objects=Main.o SpacesObj.o SpacesObjForSFML.o SpacesObjTransform.o

$(finaltarget): $(objects)
	$(CC) -o $(finaltarget) $(objects) $(CFLAGS)

Main.o: $(mainfile)
	$(CC) -o Main.o -c $(mainfile)

SpacesObj.o:
	$(CC) -o SpacesObj.o -c $(spacedimpath)SpacesObj/SpacesObj.c

SpacesObjForSFML.o:
	$(CC) -o SpacesObjForSFML.o -c $(spacedimpath)SpacesObj/SpacesObjForSFML.cpp

SpacesObjTransform.o:
	$(CC) -o SpacesObjTransform.o -c $(spacedimpath)SpacesObj/SpacesObjTransform.c

.PHONY:clean
clean:
	-rm $(objects)