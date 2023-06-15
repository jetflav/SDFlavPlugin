
CXXFLAGS:=$(shell fastjet-config --cxxflags)
LIBS:=$(shell fastjet-config --libs --plugins)

all: libSDFlavPlugin.a libFlavInfo.a

SDFlavPlugin.o: SDFlavPlugin.cc
	g++ -std=c++11 -c SDFlavPlugin.cc ${CXXFLAGS}

libSDFlavPlugin.a: SDFlavPlugin.o libFlavInfo.a
	ar rvs libSDFlavPlugin.a SDFlavPlugin.o

FlavInfo.o: FlavInfo.cc FlavInfo.hh
	g++ -std=c++11 -c FlavInfo.cc ${CXXFLAGS}

libFlavInfo.a: FlavInfo.o
	ar rvs libFlavInfo.a FlavInfo.o


example: libSDFlavPlugin.a libFlavInfo.a
	g++ -std=c++11	example.cc -lSDFlavPlugin -lFlavInfo -lfastjetcontribfragile ${CXXFLAGS} ${LIBS} -L. -o run

clean:
	rm -f SDFlavPlugin.o FlavInfo.o libSDFlavPlugin.a libFlavInfo.a run
