echo "Starting clustering ... (10x25, random pickers, euclidean)"
time -p ./app -input ../../MGR/results/contents.tfidf -clusters 10 -iter 25 -rand -deuc -out ../../MGR/results/contents_10x25_rand_deuc.clustered &> ../../MGR/results_stats/content_cluster_stats_10x25_rand_deuc.txt 
time -p ./app -input ../../MGR/results/abstracts.tfidf -clusters 10 -iter 25 -rand -deuc -out ../../MGR/results/abstracts_10x25_rand_deuc.clustered &> ../../MGR/results_stats/abstracts_cluster_stats_10x25_rand_deuc.txt 
time -p ./app -input ../../MGR/results/merged.tfidf -clusters 10 -iter 25 -rand -deuc -out ../../MGR/results/merged_10x25_rand_deuc.clustered &> ../../MGR/results_stats/merged_cluster_stats_10x25_rand_deuc.txt

echo "Starting clustering ... (10x25, squential pickers, euclidean)"
time -p ./app -input ../../MGR/results/contents.tfidf -clusters 10 -iter 25 -seq -deuc -out ../../MGR/results/contents_10x25_seq_deuc.clustered &> ../../MGR/results_stats/content_cluster_stats_10x25_seq_deuc.txt 
time -p ./app -input ../../MGR/results/abstracts.tfidf -clusters 10 -iter 25 -seq -deuc -out ../../MGR/results/abstracts_10x25_seq_deuc.clustered &> ../../MGR/results_stats/abstracts_cluster_stats_10x25_seq_deuc.txt 
time -p ./app -input ../../MGR/results/merged.tfidf -clusters 10 -iter 25 -seq -deuc -out ../../MGR/results/merged_10x25_seq_deuc.clustered &> ../../MGR/results_stats/merged_cluster_stats_10x25_seq_deuc.txt

echo "Starting clustering ... (10x25, dimension-based pickers, euclidean)"
time -p ./app -input ../../MGR/results/contents.tfidf -clusters 10 -iter 25 -dim -deuc -out ../../MGR/results/contents_10x25_dim_deuc.clustered &> ../../MGR/results_stats/content_cluster_stats_10x25_dim_deuc.txt 
time -p ./app -input ../../MGR/results/abstracts.tfidf -clusters 10 -iter 25 -dim -deuc -out ../../MGR/results/abstracts_10x25_dim_deuc.clustered &> ../../MGR/results_stats/abstracts_cluster_stats_10x25_dim_deuc.txt 
time -p ./app -input ../../MGR/results/merged.tfidf -clusters 10 -iter 25 -dim -deuc -out ../../MGR/results/merged_10x25_dim_deuc.clustered &> ../../MGR/results_stats/merged_cluster_stats_10x25_dim_deuc.txt

echo "Starting clustering ... (10x25, random pickers, hamilton)"
time -p ./app -input ../../MGR/results/contents.tfidf -clusters 10 -iter 25 -rand -dham -out ../../MGR/results/contents_10x25_rand_dham.clustered &> ../../MGR/results_stats/content_cluster_stats_10x25_rand_dham.txt 
time -p ./app -input ../../MGR/results/abstracts.tfidf -clusters 10 -iter 25 -rand -dham -out ../../MGR/results/abstracts_10x25_rand_dham.clustered &> ../../MGR/results_stats/abstracts_cluster_stats_10x25_rand_dham.txt 
time -p ./app -input ../../MGR/results/merged.tfidf -clusters 10 -iter 25 -rand -dham -out ../../MGR/results/merged_10x25_rand_dham.clustered &> ../../MGR/results_stats/merged_cluster_stats_10x25_rand_dham.txt

echo "Starting clustering ... (10x25, squential pickers, hamilton)"
time -p ./app -input ../../MGR/results/contents.tfidf -clusters 10 -iter 25 -seq -dham -out ../../MGR/results/contents_10x25_seq_dham.clustered &> ../../MGR/results_stats/content_cluster_stats_10x25_seq_dham.txt 
time -p ./app -input ../../MGR/results/abstracts.tfidf -clusters 10 -iter 25 -seq -dham -out ../../MGR/results/abstracts_10x25_seq_dham.clustered &> ../../MGR/results_stats/abstracts_cluster_stats_10x25_seq_dham.txt 
time -p ./app -input ../../MGR/results/merged.tfidf -clusters 10 -iter 25 -seq -dham -out ../../MGR/results/merged_10x25_seq_dham.clustered &> ../../MGR/results_stats/merged_cluster_stats_10x25_seq_dham.txt

echo "Starting clustering ... (10x25, dimension-based pickers, hamilton)"
time -p ./app -input ../../MGR/results/contents.tfidf -clusters 10 -iter 25 -dim -dham -out ../../MGR/results/contents_10x25_dim_dham.clustered &> ../../MGR/results_stats/content_cluster_stats_10x25_dim_dham.txt 
time -p ./app -input ../../MGR/results/abstracts.tfidf -clusters 10 -iter 25 -dim -deuc -out ../../MGR/results/abstracts_10x25_dim_dham.clustered &> ../../MGR/results_stats/abstracts_cluster_stats_10x25_dim_dham.txt 
time -p ./app -input ../../MGR/results/merged.tfidf -clusters 10 -iter 25 -dim -deuc -out ../../MGR/results/merged_10x25_dim_dham.clustered &> ../../MGR/results_stats/merged_cluster_stats_10x25_dim_dham.txt

echo "Done?"
