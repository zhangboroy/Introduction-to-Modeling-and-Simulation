#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <list>
#include <iostream>
#include "wall.h"
#include "shelf.h"
#include "entrance.h"
#include "customer.h"

class Map
{
    int wallNumber;
    int shelfNumber;
    int entranceNumber;
    Wall* wall;
    Shelf* shelf;
    Entrance* entrance;
    list<Customer*> customerList;
    set<Position> intersections;
    set<PositionRecord> routeRecord;
public:
    Map();
    ~Map()
    {
        delete []wall;
        wall=0;
        delete []shelf;
        shelf=0;
        delete []entrance;
        entrance=0;
    }
    int GetWallNumber() const
    {
        return wallNumber;
    }
    int GetShelfNumber() const
    {
        return shelfNumber;
    }
    int GetEntranceNumber() const
    {
        return entranceNumber;
    }
    Wall GetWall(const int &n) const
    {
        return wall[n];
    }
    Shelf GetShelf(const int &n) const
    {
        return shelf[n];
    }
    Entrance GetEntrance(const int &n) const
    {
        return entrance[n];
    }
    list<Customer*> GetCustomerList() const
    {
        return customerList;
    }
    set<Position> GetIntersections() const
    {
        return intersections;
    }
    set<PositionRecord> GetRouteRecord() const
    {
        return routeRecord;
    }
    //start simulation
    void StartSimulation();
};

#endif // MAP_H_INCLUDED
