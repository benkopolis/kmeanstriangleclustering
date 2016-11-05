#ifndef TESTPOINT_H
#define TESTPOINT_H

#include "commons/abstractpoint.h"

class TestPoint : public AbstractPoint
{
public:
    TestPoint(unsigned pid, double x, double y);

    virtual ~TestPoint();

    virtual double& operator [] (const unsigned& index) throw(BadIndex);
    virtual double operator [] (const unsigned& index) const throw(BadIndex);

    virtual unsigned diff(const AbstractPoint* another, bool exact) const throw(NotSparsePoint, NotDensePoint) { return 0; }
    virtual void insert(unsigned key, double value) throw(BadIndex);
    virtual unsigned size() const throw() { return 2; }
    virtual bool contains(unsigned dimIndex) const throw();
    virtual double get(const unsigned& index) const throw(BadIndex);

    /**
     * @brief getKeys method returns list of unsigned values representing indexes of point coordinates.
     * @param fileName is the name of the text file with point space in a proper format.
     * @param container - the points' space object.
     * @return Sorted list of point's coordinates' indexes.
     *
     * The list is always sorted! From smaller to bigger.
     */
    virtual const std::list<unsigned>& getKeys() const throw(DimensionsNotSet);

private:

    double _x;
    double _y;

    std::list<unsigned> _keys;
};

#endif // TESTPOINT_H
