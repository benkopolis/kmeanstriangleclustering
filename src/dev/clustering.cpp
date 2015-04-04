//============================================================================
// Name        : clustering.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <QTimer>
#include <cmath>
#include "models.hpp"
#include "KMeans.hpp"


int mainTest(void) {


	ClusterId num_clusters = 2;
	PointId num_points = 30;
	Dimensions num_dimensions = 2;

	PointsSpace ps(num_points, num_dimensions);
	//std::cout << "PointSpace" << ps;

	KMeans clusters(num_clusters, 5, ps);
	clusters.setDistanceFunction(&cosinDist);

	clusters.executeAlgorithm();

	//std::cout << elapsed1.system + elapsed1.user << '\n';
	std::cout.flush();

	return EXIT_SUCCESS;
}
