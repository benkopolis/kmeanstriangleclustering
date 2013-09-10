#ifndef KMEANSTRIANGLE_HPP
#define KMEANSTRIANGLE_HPP

#include <QFile>
#include <QTextStream>

#include "KMeans.hpp"
#include "models.hpp"

//QVector<Coord>& operator += (QVector<Coord>& v1, QVector<Coord>& v2);
//QVector<Coord>& operator -= (QVector<Coord>& v1, QVector<Coord>& v2);

class KMeansTriangle : public KMeans
{
public:
	KMeansTriangle(ClusterId nclusters, unsigned int numIters, AbstractPointsSpace* ps, bool store=false);

	virtual void executeAlgorithm();

	inline unsigned getConditionsUseCount() const {
		return conditions_use_counter__;
	}

protected:

    virtual void storeCurrentIterationState();
	//
	// Zero centroids
	//
	void compute_centroids(QTextStream& log);

	void assignDSVectors();

	void computeLowerAndUpperBounds();

	bool computePointsAssignements(QTextStream& log);

	//
	// Initial partition points among available clusters
	//
	virtual void initial_partition_points();

	void initialLoop(QTextStream* log_stream__);

	void firstLoop(QTextStream& log);

private:

	QVector<QVector<Distance> > centersToCenters__;
	Centroids new_centroids__;
	QVector<Distance> upperBounds__;
	QVector<QVector<Distance> > lowerBounds__;
	QVector<bool> rVector__;
	QVector<Distance> sVector__;
	unsigned conditions_use_counter__;
};

#endif // KMEANSTRIANGLE_HPP
