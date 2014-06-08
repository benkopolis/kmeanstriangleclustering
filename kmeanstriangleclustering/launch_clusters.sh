#!/bin/bash

./rel_clustering -res data/20ng-train-tfidf-out.txt 10 10 > logs/10g10i_20ng.console.log
./rel_clustering -res data/r52-train-tfidf-out.txt 10 10 > logs/10g10i_r52.console.log
./rel_clustering -res data/r8-train-tfidf-out.txt 10 10 > logs/10g10i_r8.console.log
echo "Done 10g10i"

./rel_clustering -res data/20ng-train-tfidf-out.txt 8 10 > logs/10g8i_20ng.console.log
./rel_clustering -res data/r52-train-tfidf-out.txt 8 10 > logs/10g8i_r52.console.log
./rel_clustering -res data/r8-train-tfidf-out.txt 8 10 > logs/10g8i_r8.console.log
echo "Done 10g8i"

./rel_clustering -res data/20ng-train-tfidf-out.txt 5 10 > logs/10g5i_20ng.console.log
./rel_clustering -res data/r52-train-tfidf-out.txt 5 10 > logs/10g5i_r52.console.log
./rel_clustering -res data/r8-train-tfidf-out.txt 5 10 > logs/10g5i_r8.console.log
echo "Done 10g5i"

./rel_clustering -res data/20ng-train-tfidf-out.txt 3 10 > logs/10g3i_20ng.console.log
./rel_clustering -res data/r52-train-tfidf-out.txt 3 10 > logs/10g3i_r52.console.log
./rel_clustering -res data/r8-train-tfidf-out.txt 3 10 > logs/10g3i_r8.console.log
echo "Done 10g3i"
