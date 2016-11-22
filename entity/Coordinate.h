#pragma once

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/serialization.hpp>

/// Struct that represents a map coordinate
struct Coordinate {
    int row;
    int column;

    Coordinate() : row(0), column(0){}
    Coordinate(int row, int column) : row(row), column(column) {}

    bool operator==(const Coordinate& rhs)
    {
        return this->row == rhs.row
            && this->column == rhs.column;
    }


    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & row;
            ar & column;
        }

};



