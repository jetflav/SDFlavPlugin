
CXX:=g++
CXXFLAGS:=$(shell fastjet-config --cxxflags)
LIBS:=$(shell fastjet-config --libs --plugins)

TARGET:=run
DATA_PATH:=data/pythia8_Zq_vshort.dat
REFERENCE_OUTPUT:= example.ref
ACTUAL_OUTPUT:= example.dat

.PHONY: all clean

all: libSDFlavPlugin.a libFlavInfo.a

SDFlavPlugin.o: SDFlavPlugin.cc SDFlavPlugin.hh
	${CXX} -std=c++11 -c SDFlavPlugin.cc ${CXXFLAGS}

libSDFlavPlugin.a: SDFlavPlugin.o libFlavInfo.a
	ar rvs libSDFlavPlugin.a SDFlavPlugin.o

FlavInfo.o: FlavInfo.cc FlavInfo.hh
	${CXX} -std=c++11 -c FlavInfo.cc ${CXXFLAGS}

libFlavInfo.a: FlavInfo.o
	ar rvs libFlavInfo.a FlavInfo.o


example: libSDFlavPlugin.a libFlavInfo.a
	${CXX}    -std=c++11	example.cc -lSDFlavPlugin -lFlavInfo -lfastjetcontribfragile ${CXXFLAGS} ${LIBS} -L. -o run

check: ${TARGET}
	@echo "Running ${TARGET} and comparing output"
	./${TARGET} 10 7 < ${DATA_PATH} > ${ACTUAL_OUTPUT}
	tail -n +14 ${ACTUAL_OUTPUT} > .trimmed.dat
	tail -n +14 ${REFERENCE_OUTPUT} > .trimmed.ref
	@if diff -q .trimmed.dat .trimmed.ref; then \
		echo "\e[32mCheck passed: output matches reference.\e[0m"; \
	else \
		echo "\e[31mCheck failed: output differs from reference. \e[0m"; \
		diff .trimmed.dat .trimmed.ref; \
	fi
	rm -f .trimmed.ref .trimmed.dat

clean:
	rm -f SDFlavPlugin.o FlavInfo.o libSDFlavPlugin.a libFlavInfo.a run example.dat .trimmed.dat .trimmed.ref
