
INCL=${HOME}/hepsoftware/include

all: libSDFlavPlugin.so libFlavInfo.so

SDFlavPlugin.o: SDFlavPlugin.cc
	g++ -std=c++11 -c SDFlavPlugin.cc -I${INCL}

libSDFlavPlugin.so: SDFlavPlugin.o libFlavInfo.so
	g++ -std=c++11 -shared SDFlavPlugin.o -lfastjet -lFlavInfo -lfastjetcontribfragile -lfastjettools -lfastjetplugins -L${HOME}/hepsoftware/lib -L. -o libSDFlavPlugin.so


FlavInfo.o: FlavInfo.cc FlavInfo.hh
	g++ -std=c++11 -c FlavInfo.cc -I${INCL}

libFlavInfo.so: FlavInfo.o
	g++ -std=c++11 -shared FlavInfo.o -I${INCL} -lfastjet -lfastjetcontribfragile -lfastjettools -L${HOME}/hepsoftware/lib -o libFlavInfo.so


example: libSDFlavPlugin.so libFlavInfo.so
	g++ -std=c++11	example.cc -lSDFlavPlugin -lFlavInfo -lfastjet -lfastjetcontribfragile -lfastjetplugins -lfastjettools -I${INCL} -L${HOME}/hepsoftware/lib -L. -o run

clean:
	rm -f SDFlavPlugin.o FlavInfo.o libSDFlavPlugin.so libFlavInfo.so run
