#!/bin/bash

echo "Running tfidf to discover stop words."
time -p ./app -stem ../../contents.txt -tfidf ../../MGR/results/contents.tfidf -stop ../../MGR/results/contents.stem.stop -stop_stats ../../MGR/results_stats/contents.stop.stats -min_variation 5 -min_docfreq 40 &> ../../MGR/results_stats/content_stats.txt 
declare -A sources
declare -A tfidfs
declare -A stops
declare -A stopStats

$abs="abstract"
$ctn="content"
$mrg="merged"
$m5="merged5"
$m10="merged10"
$m15="merged15"
$sources=([$abs]="../../abstracts.txt" [$ctn]="../../contents.txt" [$mrg]="../../all_merged.txt") 
$tfidfs=( [$abs]="../../MGR/results/abstracts.tfidf" [$ctn]="../../MGR/results/contents.tfidf" [$mrg]="../../MGR/results/merged.tfidf" )
$stops=( [$abs]="../../MGR/results/abstracts.stem.stop" [$ctn]="../../MGR/results/contents.stem.stop" [$mrg]="../../MGR/results/merged.stem.stop" )
$stopStats=( [$abs]="../../MGR/results_stats/abstracts.stop.stats" [$ctn]="../../MGR/results_stats/contents.stop.stats" [$mrg]="../../MGR/results_stats/merged.stop.stats" )

$logPrefix="../../MGR/results_stats/$(date +%Y%m%d%H%M%S)"

time -p ./app -stem "${sources[$abs]}" -tfidf "${tfidfs[$abs]}" -stop "${stops[$abs]}" -stop_stats "${stopStats[$abs]}" -min_variation 1 -min_docfreq 40 &> "${logPrefix}abstracts_stats.txt" 

time -p ./app -stem "${sources[$ctn]}" -tfidf "${tfidfs[$ctn]}" -stop "${stops[$ctn]}" -stop_stats "${stopStats[$ctn]}" -min_variation 5 -min_docfreq 40 &> "${logPrefix}content_stats.txt" 

time -p ./app -stem "${sources[$mrg]}" -tfidf "${tfidfs[$mrg]}" -stop "${stops[$mrg]}" -stop_stats "${stopStats[$mrg]}" -min_variation 10 -min_docfreq 40 &> "${logPrefix}merged_stats.txt"

time -p ./app -stem "${sources[$mrg]}" -tfidf "${tfidfs[$mrg]}" -stop "${stops[$m5]}" -stop_stats "${stopStats[$m5]}" -min_variation 10 -min_docfreq 40 &> "${logPrefix}merged_stats.txt"

time -p ./app -stem "${sources[$mrg]}" -tfidf "${tfidfs[$mrg]}" -stop "${stops[$m10]}" -stop_stats "${stopStats[$m10]}" -min_variation 10 -min_docfreq 40 &> "${logPrefix}merged_stats.txt"

time -p ./app -stem "${sources[$mrg]}" -tfidf "${tfidfs[$mrg]}" -stop "${stops[$m15]}" -stop_stats "${stopStats[$m15]}" -min_variation 10 -min_docfreq 40 &> "${logPrefix}merged_stats.txt"

echo "Running tfidf with stopwords as input."
time -p ./app -stem ."${sources[$abs]}" -tfidf ../../MGR/results/abstracts_stops.tfidf -istop "${stops[$abs]}" &> ../../MGR/results_stats/abstracts_stopVO_stats.txt 
time -p ./app -stem "${sources[$ctn]}" -tfidf ../../MGR/results/contents_stops.tfidf -istop "${stops[$abs]}" &> ../../MGR/results_stats/content_stopVO_stats.txt 
time -p ./app -stem "${sources[$mrg]}" -tfidf ../../MGR/results/merged_stops.tfidf -istop "${stops[$abs]}" &> ../../MGR/results_stats/merged_stopVO_stats.txt 

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
