#! /bin/bash

for i in src/test/*; do
	echo "$i"
	(cd $i; echo `pwd`)   
	(cd $i; qmake -project "QT += testlib"; qmake;)
	echo `pwd`
done

for i in src/test/*/*.pro; do
	echo $i
	printf '\n\n#rest of the config\n%s\n%s\n%s\n' 'CONFIG += c++11' 'QMAKE_CXXFLAGS += -std=c++11' 'INCLUDEPATH += ../../dev/' >> $i
done

