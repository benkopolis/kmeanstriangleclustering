#ifndef ABSTRACTPOINT_H
#define ABSTRACTPOINT_H

#include "exceptions/badindex.h"
#include "exceptions/notdensepoint.h"
#include "exceptions/notsparsepoint.h"
#include "exceptions/dimensionsnotset.h"

#include <iterator>
#include <list>
#include <string>

class AbstractPoint
{
protected:
    AbstractPoint(unsigned pid);

    unsigned pointId;

    std::string _fileId;

public:

    virtual ~AbstractPoint();

    inline unsigned getPointId() { return this->pointId; }
    inline std::string getFileId() const throw() { this->_fileId; }
    inline void setFileId(std::string fileId) throw() { this->_fileId = fileId; }

    virtual double& operator [] (const unsigned& index) throw(BadIndex) = 0;
    virtual double operator [] (const unsigned& index) const throw(BadIndex) = 0;

    virtual unsigned diff(const AbstractPoint* another, bool exact) const throw(NotSparsePoint, NotDensePoint) = 0;
    virtual void insert(unsigned key, double value) throw(BadIndex) = 0;
    virtual unsigned size() const throw() = 0;
    virtual bool contains(unsigned dimIndex) const throw() = 0;
    virtual double get(const unsigned& index) const throw(BadIndex) = 0;

    /**
     * @brief getKeys method returns list of unsigned values representing indexes of point coordinates.
     * @param fileName is the name of the text file with point space in a proper format.
     * @param container - the points' space object.
     * @return Sorted list of point's coordinates' indexes.
     *
     * The list is always sorted! From smaller to bigger.
     */
    virtual const std::list<unsigned>& getKeys() const throw(DimensionsNotSet) = 0;
};

typedef AbstractPoint const * const CPtrCAbstractPoint;

typedef AbstractPoint const * PtrCAbstractPoint;

#endif // ABSTRACTPOINT_H



//    class const_iterator : public std::iterator<std::input_iterator_tag, double>
//    {
//    public:

//        const_iterator() {}
//        const_iterator(const const_iterator& another) {}
//        virtual ~const_iterator() {}

//        const_iterator& operator=(const const_iterator& another) {}
//        bool operator==(const const_iterator& another) const;
//        bool operator!=(const const_iterator& another) const;
//        const_iterator& operator++() {}

//        const double & operator*() const;
//        const double * operator->() const;
//    };

//    class iterator : public std::iterator<std::output_iterator_tag, double>
//    {
//    public:

//        iterator() {}
//        iterator(const iterator& another) {}
//        virtual ~iterator() {}

//        iterator& operator=(const iterator& another) {}
//        bool operator==(const iterator& another) const;
//        bool operator!=(const iterator& another) const;
//        iterator& operator++() {}

//        double & operator*() const;
//        double * operator->() const;
//    };

//    virtual AbstractPoint::const_iterator begin() const = 0;

//    virtual AbstractPoint::iterator begin() = 0;

//    virtual AbstractPoint::const_iterator end() const = 0;

//    virtual AbstractPoint::iterator end() = 0;
