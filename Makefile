CXX = g++

CXXFLAGS = -W -Wall -std=c++11 -lm -O2 -g -Wno-sign-compare -Wno-narrowing

IMAGES=$(wildcard images/*.jpg)
IMAGES_PGM=$(IMAGES:%.jpg=%.pgm)
IMAGES_PPM=$(IMAGES:%.jpg=%.ppm)

PROGS=pbm-affiche pbm-tout-en-un pgm-tout-en-un sobel-tout-en-un seuillage-tout-en-un renormalise TIN
TESTS=pbm-affiche pbm-tout-en-un pgm-tout-en-un ppm-test pgm-test sobel-test seuillage-test gris-couleurs-test superpixel-test
TEST_DIR=gris-couleurs pbm pgm seuillage seuillage_double sobel superpixel

all: $(TESTS) $(PROGS)

images: $(IMAGES_PGM) $(IMAGES_PPM)

ppm-test: ppm-test.o ppm.o
	$(CXX) $^ -o $@ $(CXXFLAGS)

pgm-test: pgm-test.o pgm.o
	$(CXX) $^ -o $@ $(CXXFLAGS)

sobel-test: sobel-test.o sobel.o pgm.o
	$(CXX) $^ -o $@ $(CXXFLAGS)

seuillage-test: seuillage-test.o seuillage.o sobel.o pgm.o
	$(CXX) $^ -o $@ $(CXXFLAGS)

gris-couleurs-test: gris-couleurs-test.o ppm.o pgm.o gris-couleurs.o
	$(CXX) $^ -o $@ $(CXXFLAGS)

superpixel-test: superpixel-test.o superpixel.o ppm.o pgm.o gris-couleurs.o
	$(CXX) $^ -o $@ $(CXXFLAGS)

renormalise: renormalise.o pgm.o sobel.o seuillage.o
	$(CXX) $^ -o $@ $(CXXFLAGS)

TIN: TIN.o pgm.o ppm.o sobel.o seuillage.o gris-couleurs.o superpixel.o
	$(CXX) $^ -o $@ $(CXXFLAGS)

%.o : %.cpp
	$(CXX) -c $< $(CXXFLAGS)

%.ppm: %.jpg
	convert -compress None -strip $< $@

%.pgm: %.jpg
	convert -compress None -strip $< $@

clean :
	rm -rf *.o $(TESTS) $(PROGS) $(TEST_DIR:%=%/*.*) *.log *.aux 


tests:  $(TESTS) images
	pbm-affiche
	pbm-tout-en-un
	pgm-tout-en-un
	pgm-test
	sobel-test
	seuillage-test
	ppm-test
	gris-couleurs-test
	superpixel-test
	superpixel-test

ppm.o: ppm.h
pgm.o: pgm.h
gris-couleurs.o: gris-couleurs.h
sobel.o: sobel.h
seuillage.o: seuillage.h
superpixel.o: superpixel.h
