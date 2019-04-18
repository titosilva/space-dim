#!/bin/bash

g++ -c SpacesObj/SpacesObjBasics.c -o ./SpacesObjBasics.o
g++ -c SpacesObj/SpacesObjTransform/SpacesObjTransform2D.c -o ./SpacesObjTransform2D.o
g++ -c SpacesObj/SpacesObjTransform/SpacesObjTransform3D.c -o ./SpacesObjTransform3D.o
g++ -c SpacesObj/SpacesObjTransform/SpacesObjTransformMultiD.c -o ./SpacesObjTransformMultiD.o
g++ -c SpacesObj/SpacesObjPerspective/SpacesObjProjection.c -o ./SpacesObjProjection.o
g++ -c SpacesObj/SpacesObjForSFML/2DSpacesObjForSFML.cpp -o ./2DSpacesObjForSFML.o

ar rcs SpacesObjForSFML.a SpacesObjBasics.o 2DSpacesObjForSFML.o SpacesObjProjection.o \
                        SpacesObjTransform2D.o SpacesObjTransform3D.o SpacesObjTransformMultiD.o

gcc -c SpacesObj/SpacesObjBasics.c -o ./SpacesObjBasics.o
gcc -c SpacesObj/SpacesObjTransform/SpacesObjTransform2D.c -o ./SpacesObjTransform2D.o
gcc -c SpacesObj/SpacesObjTransform/SpacesObjTransform3D.c -o ./SpacesObjTransform3D.o
gcc -c SpacesObj/SpacesObjTransform/SpacesObjTransformMultiD.c -o ./SpacesObjTransformMultiD.o
gcc -c SpacesObj/SpacesObjPerspective/SpacesObjProjection.c -o ./SpacesObjProjection.o

ar rcs SpacesObj.a SpacesObjBasics.o SpacesObjProjection.o \
                SpacesObjTransform2D.o SpacesObjTransform3D.o SpacesObjTransformMultiD.o


rm  SpacesObjBasics.o 2DSpacesObjForSFML.o SpacesObjProjection.o \
    SpacesObjTransform2D.o SpacesObjTransform3D.o SpacesObjTransformMultiD.o