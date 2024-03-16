
CXXFLAGS:=$(shell fastjet-config --cxxflags)
LIBS:=$(shell fastjet-config --libs --plugins)

all: libTransformedFlavPlugin.a libFlavInfo.a

TransformedFlavPlugin.o: TransformedFlavPlugin.cc TransformedFlavPlugin.hh
	g++ -std=c++11 -c TransformedFlavPlugin.cc ${CXXFLAGS}

libTransformedFlavPlugin.a: TransformedFlavPlugin.o libFlavInfo.a
	ar rvs libTransformedFlavPlugin.a TransformedFlavPlugin.o

FlavInfo.o: FlavInfo.cc FlavInfo.hh
	g++ -std=c++11 -c FlavInfo.cc ${CXXFLAGS}

libFlavInfo.a: FlavInfo.o
	ar rvs libFlavInfo.a FlavInfo.o


example: libTransformedFlavPlugin.a libFlavInfo.a
	g++ -std=c++11	example.cc -lTransformedFlavPlugin -lFlavInfo -lfastjetcontribfragile ${CXXFLAGS} ${LIBS} -L. -o run

clean:
	rm -f TransformedFlavPlugin.o FlavInfo.o libTransformedFlavPlugin.a libFlavInfo.a run
