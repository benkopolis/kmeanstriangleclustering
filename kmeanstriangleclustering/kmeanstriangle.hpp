#ifndef KMEANSTRIANGLE_HPP
#define KMEANSTRIANGLE_HPP

#include <QFile>
#include <QTextStream>

#include "KMeans.hpp"
#include "models.hpp"

class KMeansTriangle : public KMeans
{
public:
	KMeansTriangle(ClusterId nclusters, unsigned int numIters, AbstractPointsSpace* ps) :
		KMeans(nclusters, numIters, ps), conditions_use_counter__(0)
//	    ,pointsToCenters__(nclusters, QVector<Distance>(ps.getNumPoints(), 1.0))
	{

	}

	virtual void executeAlgorithm();

	inline unsigned getConditionsUseCount() const {
		return conditions_use_counter__;
	}

protected:

	//
	// Zero centroids
	//
	void compute_centroids(bool first, QTextStream& log);

	//
	// Initial partition points among available clusters
	//
	virtual void initial_partition_points();

	void initialLoop(QTextStream* log_stream__);

private:

	Distances pointsToCenters__;
	Distances centersToCenters__;
	QVector<Distance> upperBounds__;
	Distances lowerBounds__;
	QVector<bool> rVector__;
	QVector<Distance> sVector__;
	unsigned conditions_use_counter__;
};

#endif // KMEANSTRIANGLE_HPP
