#!/bin/bash

echo "Running tfidf to discover stop words."
time -p ./app -stem ../../contents.txt -tfidf ../../MGR/results/contents.tfidf -stop ../../MGR/results/contents.stem.stop -stop_stats ../../MGR/results_stats/contents.stop.stats -min_variation 5 -min_docfreq 40 &> ../../MGR/results_stats/content_stats.txt 
time -p ./app -stem ../../abstracts.txt -tfidf ../../MGR/results/abstracts.tfidf -stop ../../MGR/results/abstracts.stem.stop -stop_stats ../../MGR/results_stats/abstracts.stop.stats -min_variation 1 -min_docfreq 40 &> ../../MGR/results_stats/abstracts_stats.txt 
time -p ./app -stem ../../all_merged.txt -tfidf ../../MGR/results/merged.tfidf -stop ../../MGR/results/merged.stem.stop -stop_stats ../../MGR/results_stats/merged.stop.stats -min_variation 10 -min_docfreq 40 &> ../../MGR/results_stats/merged_stats.txt 

echo "Running tfidf with stopwords as input."
time -p ./app -stem ../../contents.txt -tfidf ../../MGR/results/contents_stops.tfidf -istop ../../MGR/results/contents.stem.stop &> ../../MGR/results_stats/content_stopVO_stats.txt 
time -p ./app -stem ../../abstracts.txt -tfidf ../../MGR/results/abstracts_stops.tfidf -istop ../../MGR/results/abstracts.stem.stop &> ../../MGR/results_stats/abstracts_stopVO_stats.txt 
time -p ./app -stem ../../all_merged.txt -tfidf ../../MGR/results/merged_stops.tfidf -istop ../../MGR/results/merged.stem.stop &> ../../MGR/results_stats/merged_stopVO_stats.txt 

echo "Done with tfidf..."
echo "Starting clustering ... (10x25, random pickers, euclidean)"
time -p ./app -input ../../MGR/results/contents_stops.tfidf -clusters 10 -iter 25 -rand -deuc -out ../../MGR/results/contents_stopVO_10x25_rand_deuc.clustered &> ../../MGR/results_stats/content_stopVO_cluster_stats_10x25_rand_deuc.txt 
time -p ./app -input ../../MGR/results/abstracts_stops.tfidf -clusters 10 -iter 25 -rand -deuc -out ../../MGR/results/abstracts_stopVO_10x25_rand_deuc.clustered &> ../../MGR/results_stats/abstracts_stopVO_cluster_stats_10x25_rand_deuc.txt 
time -p ./app -input ../../MGR/results/merged_stops.tfidf -clusters 10 -iter 25 -rand -deuc -out ../../MGR/results/merged_stopVO_10x25_rand_deuc.clustered &> ../../MGR/results_stats/merged_cluster_stopVO_stats_10x25_rand_deuc.txt

echo "Starting clustering ... (10x25, squential pickers, euclidean)"
time -p ./app -input ../../MGR/results/contents_stops.tfidf -clusters 10 -iter 25 -seq -deuc -out ../../MGR/results/contents_stopVO_10x25_seq_deuc.clustered &> ../../MGR/results_stats/content_stopVO_cluster_stats_10x25_seq_deuc.txt 
time -p ./app -input ../../MGR/results/abstracts_stops.tfidf -clusters 10 -iter 25 -seq -deuc -out ../../MGR/results/abstracts_stopVO_10x25_seq_deuc.clustered &> ../../MGR/results_stats/abstracts_stopVO_cluster_stats_10x25_seq_deuc.txt 
time -p ./app -input ../../MGR/results/merged_stops.tfidf -clusters 10 -iter 25 -seq -deuc -out ../../MGR/results/merged_stopVO_10x25_seq_deuc.clustered &> ../../MGR/results_stats/merged_cluster_stopVO_stats_10x25_seq_deuc.txt

echo "Starting clustering ... (10x25, dimension-based pickers, euclidean)"
time -p ./app -input ../../MGR/results/contents_stops.tfidf -clusters 10 -iter 25 -dim -deuc -out ../../MGR/results/contents_stopVO_10x25_dim_deuc.clustered &> ../../MGR/results_stats/content_stopVO_cluster_stats_10x25_dim_deuc.txt 
time -p ./app -input ../../MGR/results/abstracts_stops.tfidf -clusters 10 -iter 25 -dim -deuc -out ../../MGR/results/abstracts_stopVO_10x25_dim_deuc.clustered &> ../../MGR/results_stats/abstracts_stopVO_cluster_stats_10x25_dim_deuc.txt 
time -p ./app -input ../../MGR/results/merged_stops.tfidf -clusters 10 -iter 25 -dim -deuc -out ../../MGR/results/merged_stopVO_10x25_dim_deuc.clustered &> ../../MGR/results_stats/merged_cluster_stopVO_stats_10x25_dim_deuc.txt

echo "Starting clustering ... (10x25, random pickers, hamilton)"
time -p ./app -input ../../MGR/results/contents_stops.tfidf -clusters 10 -iter 25 -rand -dham -out ../../MGR/results/contents_stopVO_10x25_rand_dham.clustered &> ../../MGR/results_stats/content_stopVO_cluster_stats_10x25_rand_dham.txt 
time -p ./app -input ../../MGR/results/abstracts_stops.tfidf -clusters 10 -iter 25 -rand -dham -out ../../MGR/results/abstracts_stopVO_10x25_rand_dham.clustered &> ../../MGR/results_stats/abstracts_stopVO_cluster_stats_10x25_rand_dham.txt 
time -p ./app -input ../../MGR/results/merged_stops.tfidf -clusters 10 -iter 25 -rand -dham -out ../../MGR/results/merged_stopVO_10x25_rand_dham.clustered &> ../../MGR/results_stats/merged_cluster_stopVO_stats_10x25_rand_dham.txt

echo "Starting clustering ... (10x25, squential pickers, hamilton)"
time -p ./app -input ../../MGR/results/contents_stops.tfidf -clusters 10 -iter 25 -seq -dham -out ../../MGR/results/contents_stopVO_10x25_seq_dham.clustered &> ../../MGR/results_stats/content_stopVO_cluster_stats_10x25_seq_dham.txt 
time -p ./app -input ../../MGR/results/abstracts_stops.tfidf -clusters 10 -iter 25 -seq -dham -out ../../MGR/results/abstracts_stopVO_10x25_seq_dham.clustered &> ../../MGR/results_stats/abstracts_stopVO_cluster_stats_10x25_seq_dham.txt 
time -p ./app -input ../../MGR/results/merged_stops.tfidf -clusters 10 -iter 25 -seq -dham -out ../../MGR/results/merged_stopVO_10x25_seq_dham.clustered &> ../../MGR/results_stats/merged_cluster_stopVO_stats_10x25_seq_dham.txt

echo "Starting clustering ... (10x25, dimension-based pickers, hamilton)"
time -p ./app -input ../../MGR/results/contents_stops.tfidf -clusters 10 -iter 25 -dim -dham -out ../../MGR/results/contents_stopVO_10x25_dim_dham.clustered &> ../../MGR/results_stats/content_stopVO_cluster_stats_10x25_dim_dham.txt 
time -p ./app -input ../../MGR/results/abstracts_stops.tfidf -clusters 10 -iter 25 -dim -deuc -out ../../MGR/results/abstracts_stopVO_10x25_dim_dham.clustered &> ../../MGR/results_stats/abstracts_stopVO_cluster_stats_10x25_dim_dham.txt 
time -p ./app -input ../../MGR/results/merged_stops.tfidf -clusters 10 -iter 25 -dim -deuc -out ../../MGR/results/merged_stopVO_10x25_dim_dham.clustered &> ../../MGR/results_stats/merged_cluster_stopVO_stats_10x25_dim_dham.txt

echo "Done?"
