#!/bin/bash

echo "Running tfidf to discover stop words - merge only, v10,20,40."
time -p ./app -stem ../../all_merged.txt -tfidf ../../MGR/results/merged.tfidf -stop ../../MGR/results/mergedV10.stem.stop -stop_stats ../../MGR/results_stats/mergedV10.stop.stats -min_variation 10 -min_docfreq 40 &> ../../MGR/results_stats/mergedV10_stats.txt 
time -p ./app -stem ../../all_merged.txt -tfidf ../../MGR/results/merged.tfidf -stop ../../MGR/results/mergedV20.stem.stop -stop_stats ../../MGR/results_stats/mergedV20.stop.stats -min_variation 20 -min_docfreq 40 &> ../../MGR/results_stats/mergedV20_stats.txt 
time -p ./app -stem ../../all_merged.txt -tfidf ../../MGR/results/merged.tfidf -stop ../../MGR/results/mergedV40.stem.stop -stop_stats ../../MGR/results_stats/mergedV40.stop.stats -min_variation 40 -min_docfreq 40 &> ../../MGR/results_stats/mergedV40_stats.txt 

echo "Running tfidf with stopwords as input."
time -p ./app -stem ../../all_merged.txt -tfidf ../../MGR/results/merged_stopsV10.tfidf -istop ../../MGR/results/mergedV10.stem.stop &> ../../MGR/results_stats/merged_stopV1O_stats.txt 
time -p ./app -stem ../../all_merged.txt -tfidf ../../MGR/results/merged_stopsV20.tfidf -istop ../../MGR/results/mergedV20.stem.stop &> ../../MGR/results_stats/merged_stopV2O_stats.txt 
time -p ./app -stem ../../all_merged.txt -tfidf ../../MGR/results/merged_stopsV40.tfidf -istop ../../MGR/results/mergedV40.stem.stop &> ../../MGR/results_stats/merged_stopV4O_stats.txt 

echo "Done with tfidf..."
echo "Starting clustering ... (10x25, random pickers, euclidean)"
time -p ./app -input ../../MGR/results/merged_stopsV10.tfidf -clusters 10 -iter 25 -rand -deuc -out ../../MGR/results/merged_stopV1O_10x25_rand_deuc.clustered &> ../../MGR/results_stats/merged_cluster_stopV1O_stats_10x25_rand_deuc.txt
time -p ./app -input ../../MGR/results/merged_stopsV20.tfidf -clusters 10 -iter 25 -rand -deuc -out ../../MGR/results/merged_stopV2O_10x25_rand_deuc.clustered &> ../../MGR/results_stats/merged_cluster_stopV2O_stats_10x25_rand_deuc.txt
time -p ./app -input ../../MGR/results/merged_stopsV40.tfidf -clusters 10 -iter 25 -rand -deuc -out ../../MGR/results/merged_stopV4O_10x25_rand_deuc.clustered &> ../../MGR/results_stats/merged_cluster_stopV4O_stats_10x25_rand_deuc.txt

echo "Starting clustering ... (10x25, squential pickers, euclidean)"
time -p ./app -input ../../MGR/results/merged_stopsV10.tfidf -clusters 10 -iter 25 -seq -deuc -out ../../MGR/results/merged_stopV1O_10x25_seq_deuc.clustered &> ../../MGR/results_stats/merged_cluster_stopV1O_stats_10x25_seq_deuc.txt
time -p ./app -input ../../MGR/results/merged_stopsV20.tfidf -clusters 10 -iter 25 -seq -deuc -out ../../MGR/results/merged_stopV2O_10x25_seq_deuc.clustered &> ../../MGR/results_stats/merged_cluster_stopV2O_stats_10x25_seq_deuc.txt
time -p ./app -input ../../MGR/results/merged_stopsV40.tfidf -clusters 10 -iter 25 -seq -deuc -out ../../MGR/results/merged_stopV4O_10x25_seq_deuc.clustered &> ../../MGR/results_stats/merged_cluster_stopV4O_stats_10x25_seq_deuc.txt

echo "Starting clustering ... (10x25, dimension-based pickers, euclidean)"
time -p ./app -input ../../MGR/results/merged_stopsV10.tfidf -clusters 10 -iter 25 -dim -deuc -out ../../MGR/results/merged_stopV1O_10x25_dim_deuc.clustered &> ../../MGR/results_stats/merged_cluster_stopV1O_stats_10x25_dim_deuc.txt
time -p ./app -input ../../MGR/results/merged_stopsV20.tfidf -clusters 10 -iter 25 -dim -deuc -out ../../MGR/results/merged_stopV2O_10x25_dim_deuc.clustered &> ../../MGR/results_stats/merged_cluster_stopV2O_stats_10x25_dim_deuc.txt
time -p ./app -input ../../MGR/results/merged_stopsV40.tfidf -clusters 10 -iter 25 -dim -deuc -out ../../MGR/results/merged_stopV4O_10x25_dim_deuc.clustered &> ../../MGR/results_stats/merged_cluster_stopV4O_stats_10x25_dim_deuc.txt

echo "Starting clustering ... (10x25, random pickers, hamilton)"
time -p ./app -input ../../MGR/results/merged_stopsV10.tfidf -clusters 10 -iter 25 -rand -dham -out ../../MGR/results/merged_stopV1O_10x25_rand_dham.clustered &> ../../MGR/results_stats/merged_cluster_stopV1O_stats_10x25_rand_dham.txt
time -p ./app -input ../../MGR/results/merged_stopsV20.tfidf -clusters 10 -iter 25 -rand -dham -out ../../MGR/results/merged_stopV2O_10x25_rand_dham.clustered &> ../../MGR/results_stats/merged_cluster_stopV2O_stats_10x25_rand_dham.txt
time -p ./app -input ../../MGR/results/merged_stopsV40.tfidf -clusters 10 -iter 25 -rand -dham -out ../../MGR/results/merged_stopV4O_10x25_rand_dham.clustered &> ../../MGR/results_stats/merged_cluster_stopV4O_stats_10x25_rand_dham.txt

echo "Starting clustering ... (10x25, squential pickers, hamilton)"
time -p ./app -input ../../MGR/results/merged_stopsV10.tfidf -clusters 10 -iter 25 -seq -dham -out ../../MGR/results/merged_stopV1O_10x25_seq_dham.clustered &> ../../MGR/results_stats/merged_cluster_stopV1O_stats_10x25_seq_dham.txt
time -p ./app -input ../../MGR/results/merged_stopsV20.tfidf -clusters 10 -iter 25 -seq -dham -out ../../MGR/results/merged_stopV2O_10x25_seq_dham.clustered &> ../../MGR/results_stats/merged_cluster_stopV2O_stats_10x25_seq_dham.txt
time -p ./app -input ../../MGR/results/merged_stopsV40.tfidf -clusters 10 -iter 25 -seq -dham -out ../../MGR/results/merged_stopV4O_10x25_seq_dham.clustered &> ../../MGR/results_stats/merged_cluster_stopV4O_stats_10x25_seq_dham.txt

echo "Starting clustering ... (10x25, dimension-based pickers, hamilton)"
time -p ./app -input ../../MGR/results/merged_stopsV10.tfidf -clusters 10 -iter 25 -dim -deuc -out ../../MGR/results/merged_stopV1O_10x25_dim_dham.clustered &> ../../MGR/results_stats/merged_cluster_stopV1O_stats_10x25_dim_dham.txt
time -p ./app -input ../../MGR/results/merged_stopsV20.tfidf -clusters 10 -iter 25 -dim -deuc -out ../../MGR/results/merged_stopV2O_10x25_dim_dham.clustered &> ../../MGR/results_stats/merged_cluster_stopV2O_stats_10x25_dim_dham.txt
time -p ./app -input ../../MGR/results/merged_stopsV40.tfidf -clusters 10 -iter 25 -dim -deuc -out ../../MGR/results/merged_stopV4O_10x25_dim_dham.clustered &> ../../MGR/results_stats/merged_cluster_stopV4O_stats_10x25_dim_dham.txt

echo "Done?"
