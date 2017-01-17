#!/bin/bash

echo "Running tfidf to discover stop words."
./app -stem /home/zby/MAGISTERKA/contents.txt -tfidf /home/zby/MAGISTERKA/MGR/results/contents.tfidf -stop /home/zby/MAGISTERKA/MGR/results/contents.stem.stop -min_variation 1 -min_docfreq 40 &> content_stats.txt 
./app -stem /home/zby/MAGISTERKA/abstracts.txt -tfidf /home/zby/MAGISTERKA/MGR/results/abstracts.tfidf -stop /home/zby/MAGISTERKA/MGR/results/abstracts.stem.stop -min_variation 1 -min_docfreq 40 &> abstracts_stats.txt 
./app -stem /home/zby/MAGISTERKA/all_merged.txt -tfidf /home/zby/MAGISTERKA/MGR/results/merged.tfidf -stop /home/zby/MAGISTERKA/MGR/results/merged.stem.stop -min_variation 1 -min_docfreq 40 &> merged_stats.txt 

echo "Running tfidf with stopwords as input."
./app -stem /home/zby/MAGISTERKA/contents.txt -tfidf /home/zby/MAGISTERKA/MGR/results/contents_stops.tfidf -istop /home/zby/MAGISTERKA/MGR/results/contents.stem.stop &> content_stop_stats.txt 
./app -stem /home/zby/MAGISTERKA/abstracts.txt -tfidf /home/zby/MAGISTERKA/MGR/results/abstracts_stops.tfidf -istop /home/zby/MAGISTERKA/MGR/results/abstracts.stem.stop &> abstracts_stop_stats.txt 
./app -stem /home/zby/MAGISTERKA/all_merged.txt -tfidf /home/zby/MAGISTERKA/MGR/results/merged_stops.tfidf -istop /home/zby/MAGISTERKA/MGR/results/merged.stem.stop &> merged_stop_stats.txt 

echo "Done with tfidf..."
echo "Starting clustering ... (10x25, random pickers, euclidean)"
./app -input /home/zby/MAGISTERKA/MGR/results/contents_stops.tfidf -clusters 10 -iter 25 -rand -deuc -out /home/zby/MAGISTERKA/MGR/results/contents_stop_10x25_rand_deuc.clustered &> content_stop_cluster_stats.txt 
./app -input /home/zby/MAGISTERKA/MGR/results/abstracts_stops.tfidf -clusters 10 -iter 25 -rand -deuc -out /home/zby/MAGISTERKA/MGR/results/abstracts_stop_10x25_rand_deuc.clustered &> abstracts_stop_cluster_stats.txt 
./app -input /home/zby/MAGISTERKA/MGR/results/merged_stops.tfidf -clusters 10 -iter 25 -rand -deuc -out /home/zby/MAGISTERKA/MGR/results/merged_stop_10x25_rand_deuc.clustered &> merged_cluster_stop_stats.txt

echo "Starting clustering ... (10x25, squential pickers, euclidean)"
./app -input /home/zby/MAGISTERKA/MGR/results/contents_stops.tfidf -clusters 10 -iter 25 -seq -deuc -out /home/zby/MAGISTERKA/MGR/results/contents_stop_10x25_seq_deuc.clustered &> content_stop_cluster_stats.txt 
./app -input /home/zby/MAGISTERKA/MGR/results/abstracts_stops.tfidf -clusters 10 -iter 25 -seq -deuc -out /home/zby/MAGISTERKA/MGR/results/abstracts_stop_10x25_seq_deuc.clustered &> abstracts_stop_cluster_stats.txt 
./app -input /home/zby/MAGISTERKA/MGR/results/merged_stops.tfidf -clusters 10 -iter 25 -seq -deuc -out /home/zby/MAGISTERKA/MGR/results/merged_stop_10x25_seq_deuc.clustered &> merged_cluster_stop_stats.txt

echo "Starting clustering ... (10x25, dimension-based pickers, euclidean)"
./app -input /home/zby/MAGISTERKA/MGR/results/contents_stops.tfidf -clusters 10 -iter 25 -dim -deuc -out /home/zby/MAGISTERKA/MGR/results/contents_stop_10x25_dim_deuc.clustered &> content_stop_cluster_stats.txt 
./app -input /home/zby/MAGISTERKA/MGR/results/abstracts_stops.tfidf -clusters 10 -iter 25 -dim -deuc -out /home/zby/MAGISTERKA/MGR/results/abstracts_stop_10x25_dim_deuc.clustered &> abstracts_stop_cluster_stats.txt 
./app -input /home/zby/MAGISTERKA/MGR/results/merged_stops.tfidf -clusters 10 -iter 25 -dim -deuc -out /home/zby/MAGISTERKA/MGR/results/merged_stop_10x25_dim_deuc.clustered &> merged_cluster_stop_stats.txt

echo "Starting clustering ... (10x25, random pickers, hamilton)"
./app -input /home/zby/MAGISTERKA/MGR/results/contents_stops.tfidf -clusters 10 -iter 25 -rand -dham -out /home/zby/MAGISTERKA/MGR/results/contents_stop_10x25_rand_dham.clustered &> content_stop_cluster_stats.txt 
./app -input /home/zby/MAGISTERKA/MGR/results/abstracts_stops.tfidf -clusters 10 -iter 25 -rand -dham -out /home/zby/MAGISTERKA/MGR/results/abstracts_stop_10x25_rand_dham.clustered &> abstracts_stop_cluster_stats.txt 
./app -input /home/zby/MAGISTERKA/MGR/results/merged_stops.tfidf -clusters 10 -iter 25 -rand -dham -out /home/zby/MAGISTERKA/MGR/results/merged_stop_10x25_rand_dham.clustered &> merged_cluster_stop_stats.txt

echo "Starting clustering ... (10x25, squential pickers, hamilton)"
./app -input /home/zby/MAGISTERKA/MGR/results/contents_stops.tfidf -clusters 10 -iter 25 -seq -dham -out /home/zby/MAGISTERKA/MGR/results/contents_stop_10x25_seq_dham.clustered &> content_stop_cluster_stats.txt 
./app -input /home/zby/MAGISTERKA/MGR/results/abstracts_stops.tfidf -clusters 10 -iter 25 -seq -dham -out /home/zby/MAGISTERKA/MGR/results/abstracts_stop_10x25_seq_dham.clustered &> abstracts_stop_cluster_stats.txt 
./app -input /home/zby/MAGISTERKA/MGR/results/merged_stops.tfidf -clusters 10 -iter 25 -seq -dham -out /home/zby/MAGISTERKA/MGR/results/merged_stop_10x25_seq_dham.clustered &> merged_cluster_stop_stats.txt

echo "Starting clustering ... (10x25, dimension-based pickers, hamilton)"
./app -input /home/zby/MAGISTERKA/MGR/results/contents_stops.tfidf -clusters 10 -iter 25 -dim -dham -out /home/zby/MAGISTERKA/MGR/results/contents_stop_10x25_dim_dham.clustered &> content_stop_cluster_stats.txt 
./app -input /home/zby/MAGISTERKA/MGR/results/abstracts_stops.tfidf -clusters 10 -iter 25 -dim -deuc -out /home/zby/MAGISTERKA/MGR/results/abstracts_stop_10x25_dim_dham.clustered &> abstracts_stop_cluster_stats.txt 
./app -input /home/zby/MAGISTERKA/MGR/results/merged_stops.tfidf -clusters 10 -iter 25 -dim -deuc -out /home/zby/MAGISTERKA/MGR/results/merged_stop_10x25_dim_dham.clustered &> merged_cluster_stop_stats.txt

echo "Done?"
