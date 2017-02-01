#!/bin/bash

echo "Getting tfidf for keywords"
time -p ./app -stem ../../keywords.txt -tfidf ../../MGR/results/keywords.tfidf &> ../../MGR/results_stats/kw_stats.txt 

echo "Running only for keywords..."
echo "Starting clustering ... (10x25, random pickers, euclidean)"
time -p ./app -input ../../MGR/results/keywords.tfidf -clusters 10 -iter 25 -rand -deuc -out ../../MGR/results/keywords_stopVO_10x25_rand_deuc.clustered &> ../../MGR/results_stats/kw_stopVO_cluster_stats_10x25_rand_deuc.txt 


echo "Starting clustering ... (10x25, squential pickers, euclidean)"
time -p ./app -input ../../MGR/results/keywords.tfidf -clusters 10 -iter 25 -seq -deuc -out ../../MGR/results/keywords_stopVO_10x25_seq_deuc.clustered &> ../../MGR/results_stats/kw_stopVO_cluster_stats_10x25_seq_deuc.txt 

echo "Starting clustering ... (10x25, dimension-based pickers, euclidean)"
time -p ./app -input ../../MGR/results/keywords.tfidf -clusters 10 -iter 25 -dim -deuc -out ../../MGR/results/keywords_stopVO_10x25_dim_deuc.clustered &> ../../MGR/results_stats/kw_stopVO_cluster_stats_10x25_dim_deuc.txt 

echo "Starting clustering ... (10x25, random pickers, hamilton)"
time -p ./app -input ../../MGR/results/keywords.tfidf -clusters 10 -iter 25 -rand -dham -out ../../MGR/results/keywords_stopVO_10x25_rand_dham.clustered &> ../../MGR/results_stats/kw_stopVO_cluster_stats_10x25_rand_dham.txt 

echo "Starting clustering ... (10x25, squential pickers, hamilton)"
time -p ./app -input ../../MGR/results/keywords.tfidf -clusters 10 -iter 25 -seq -dham -out ../../MGR/results/keywords_stopVO_10x25_seq_dham.clustered &> ../../MGR/results_stats/kw_stopVO_cluster_stats_10x25_seq_dham.txt 

echo "Starting clustering ... (10x25, dimension-based pickers, hamilton)"
time -p ./app -input ../../MGR/results/keywords.tfidf -clusters 10 -iter 25 -dim -dham -out ../../MGR/results/keywords_stopVO_10x25_dim_dham.clustered &> ../../MGR/results_stats/kw_stopVO_cluster_stats_10x25_dim_dham.txt 


echo "Done?"
