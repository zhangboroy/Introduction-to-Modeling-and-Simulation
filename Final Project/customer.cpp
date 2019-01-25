#include "customer.h"
#include "map.h"

default_random_engine Customer::generator;

Position::Position(const int &x1, const int &y1)
{
    x=x1;
    y=y1;
}

bool Position::operator==(const Position &position) const
{
    return (x==position.x && y==position.y);
}

bool Position::operator<(const Position &position) const
{
    if (x<position.x)
    {
        return true;
    }
    else if (x==position.x)
    {
        return (y<position.y);
    }
    else
    {
        return false;
    }
}

bool Position::operator>(const Position &position) const
{
    if (x>position.x)
    {
        return true;
    }
    else if (x==position.x)
    {
        return (y>position.y);
    }
    else
    {
        return false;
    }
}

PositionRecord::PositionRecord(const int &x1, const int &y1)
{
    x=x1;
    y=y1;
    visitTimes=1;
}

bool PositionRecord::operator==(const PositionRecord &record) const
{
    return (x==record.x && y==record.y);
}

bool PositionRecord::operator<(const PositionRecord &record) const
{
    if (x<record.x)
    {
        return true;
    }
    else if (x==record.x)
    {
        return (y<record.y);
    }
    else
    {
        return false;
    }
}

bool PositionRecord::operator>(const PositionRecord &record) const
{
    if (x>record.x)
    {
        return true;
    }
    else if (x==record.x)
    {
        return (y>record.y);
    }
    else
    {
        return false;
    }
}

Customer::Customer(const int &x1, const int &y1, poisson_distribution<int> &Poisson)
{
    maxShoppingTime=Poisson(generator);
    shoppingTime=0;
    x=x1;
    y=y1;
    directionX=0;
    directionY=0;
}

//move 1 step
void Customer::Move(set<PositionRecord> &routeRecord)
{
    //move 1 step forward
    ++shoppingTime;
    x += directionX;
    y += directionY;

    //add the new position into route history set
    route.insert(Position(x,y));
    //generate the visit record for the new position
    PositionRecord newPositionRecord(x,y);
    set<PositionRecord>::iterator iter=(routeRecord).find(newPositionRecord);
    //if this position is not in the visit record set
    if (iter==routeRecord.end())
    {
        //add it to the set
        routeRecord.insert(newPositionRecord);
    }
    //if this position is in the visit record set
    else
    {
        //update the record
        newPositionRecord.visitTimes+=(*iter).visitTimes;
        routeRecord.erase(iter);
        routeRecord.insert(newPositionRecord);
    }
    /*
    cerr<<"route size: "<<route.size()<<endl;
    cerr<<"route record size: "<<routeRecord.size()<<endl;
    */
}

//check if there is an object in front
bool Customer::CheckObject(const Map* supermarket)
{
    //check for walls
    for (int j=0;j<(*supermarket).GetWallNumber();++j)
    {
        if ((x+directionX==(*supermarket).GetWall(j).GetX()) && (y+directionY==(*supermarket).GetWall(j).GetY()))
        {
            return true;
        }
    }
    //check for shelves
    for (int j=0;j<(*supermarket).GetShelfNumber();++j)
    {
        if ((x+directionX==(*supermarket).GetShelf(j).GetX()) && (y+directionY==(*supermarket).GetShelf(j).GetY()))
        {
            return true;
        }
    }
    //check for entrances
    for (int j=0;j<(*supermarket).GetEntranceNumber();++j)
    {
        if ((x+directionX==(*supermarket).GetEntrance(j).GetX()) && (y+directionY==(*supermarket).GetEntrance(j).GetY()))
        {
            return true;
        }
    }
    return false;
}

//decide new direction
void Customer::DecideDirection(const Map* supermarket)
{
    //initiate 2 direction candidate list, new means non-visited
    int directionListSize=0;
    int newDirectionListSize=0;
    int* directionXList;
    int* directionYList;
    int* newDirectionXList;
    int* newDirectionYList;
    directionXList=new int[4];
    directionYList=new int[4];
    newDirectionXList=new int[4];
    newDirectionYList=new int[4];

    for (int i=0;i<4;++i)
    {
        directionXList[i]=0;
        directionYList[i]=0;
        newDirectionXList[i]=0;
        newDirectionYList[i]=0;
    }

    //check 4 directions 1 by 1
    for (int i=0;i<4;++i)
    {
        //set direction value
        if (i==0)
        {
            directionX=0;
            directionY=-1;
        }
        else if (i==1)
        {
            directionX=1;
            directionY=0;
        }
        else if (i==2)
        {
            directionX=0;
            directionY=1;
        }
        else
        {
            directionX=-1;
            directionY=0;
        }

        //check if there is an object in front of this direction
        if (!CheckObject(supermarket))
        {
            //add the direction into direction candidate list
            directionXList[directionListSize]=directionX;
            directionYList[directionListSize]=directionY;
            ++directionListSize;

            //check if this direction visited
            if (route.find(Position(x+directionX, y+directionY))==route.end())
            {
                //add the direction into new direction candidate list
                newDirectionXList[newDirectionListSize]=directionX;
                newDirectionYList[newDirectionListSize]=directionY;
                ++newDirectionListSize;
            }
        }
    }

    //random choose direction from new direction list
    if (newDirectionListSize>0)
    {
        int index=rand()%newDirectionListSize;
        directionX=newDirectionXList[index];
        directionY=newDirectionYList[index];
    }
    //if all possible direction are all visited, choose direction from all available direction
    else
    {
        int index=rand()%directionListSize;
        directionX=directionXList[index];
        directionY=directionYList[index];
    }

    delete directionXList;
    directionXList=0;
    delete directionYList;
    directionYList=0;
    delete newDirectionXList;
    newDirectionXList=0;
    delete newDirectionYList;
    newDirectionYList=0;
}
