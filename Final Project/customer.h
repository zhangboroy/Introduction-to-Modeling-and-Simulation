#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

#include <set>
#include <cstdlib>
#include <random>
using namespace std;

class Map;

struct Position
{
    int x;
    int y;
    Position(const int &x1, const int &y1);
    bool operator==(const Position &position) const;
    bool operator<(const Position &position) const;
    bool operator>(const Position &position) const;
};

struct PositionRecord
{
    int x;
    int y;
    int visitTimes;
    PositionRecord(const int &x1, const int &y1);
    bool operator==(const PositionRecord &record) const;
    bool operator<(const PositionRecord &record) const;
    bool operator>(const PositionRecord &record) const;
};

class Customer
{
    static default_random_engine generator;
    int maxShoppingTime;
    int shoppingTime;
    int x;
    int y;
    int directionX;
    int directionY;
    set<Position> route;
public:
    Customer(const int &x1, const int &y1, poisson_distribution<int> &Poisson);
    ~Customer(){}
    int GetMaxShoppingTime() const
    {
        return maxShoppingTime;
    }
    int GetShoppingTime() const
    {
        return shoppingTime;
    }
    int GetX() const
    {
        return x;
    }
    int GetY() const
    {
        return y;
    }
    int GetDirectionX() const
    {
        return directionX;
    }
    int GetDirectionY() const
    {
        return directionY;
    }
    set<Position> GetRoute() const
    {
        return route;
    }
    //move 1 step
    void Move(set<PositionRecord> &routeRecord);
    //check if there is an object in front
    bool CheckObject(const Map* supermarket);
    //decide new direction
    void DecideDirection(const Map* supermarket);
};

#endif // ROBOT_H_INCLUDED
