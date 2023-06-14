
INCL=${HOME}/hepsoftware/include
LIBS=${HOME}/hepsoftware/lib

all: libSDFlavPlugin.a libFlavInfo.a

SDFlavPlugin.o: SDFlavPlugin.cc
	g++ -std=c++11 -c SDFlavPlugin.cc -I${INCL}

libSDFlavPlugin.a: SDFlavPlugin.o libFlavInfo.a
	ar rvs libSDFlavPlugin.a SDFlavPlugin.o

FlavInfo.o: FlavInfo.cc FlavInfo.hh
	g++ -std=c++11 -c FlavInfo.cc -I${INCL}

libFlavInfo.a: FlavInfo.o
	ar rvs libFlavInfo.a FlavInfo.o


example: libSDFlavPlugin.a libFlavInfo.a
	g++ -std=c++11	example.cc -lSDFlavPlugin -lFlavInfo -lfastjet -lfastjetcontribfragile -lfastjetplugins -lfastjettools -I${INCL} -L${LIBS} -L. -o run

clean:
	rm -f SDFlavPlugin.o FlavInfo.o libSDFlavPlugin.a libFlavInfo.a run
