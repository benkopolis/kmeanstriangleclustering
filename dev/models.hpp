/*
 * models.hpp
 *
 *  Created on: 12-12-2012
 *      Author: zby
 */

#ifndef MODELS_HPP_
#define MODELS_HPP_

#include <limits>
#include <iostream>

#define LOG_ALL 1

#ifdef LOG_ALL
#define logall(x) log_all(x)
#define logoneline(s) log_one_line(s)
#else
#define logall(x) log_all("")
#define logoneline(s) log_one_line("")
#endif

extern std::ostream* m_globalLogger;

typedef double Coord;

typedef double Distance;

typedef unsigned int Dimensions; // how many dimensions

typedef unsigned int PointId; // the id of this point

typedef unsigned int ClusterId; // the id of this cluster

struct DistancesCountData {

    DistancesCountData()
    {
        reset();
    }

    bool notCounted;
    Distance distance;

    void reset()
    {
        distance = std::numeric_limits<Distance>::max();
        notCounted = true;
    }
};

//





#endif /* MODELS_HPP_ */
