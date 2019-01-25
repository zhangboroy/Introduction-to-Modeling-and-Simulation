#include <fstream>
#include <string>
#include <ctime>
#include "map.h"

using namespace std;

Map::Map()
{
    srand(time(0));

    wallNumber=0;
    shelfNumber=0;
    entranceNumber=0;
    wall=0;
    shelf=0;
    entrance=0;

    //ask user to input the map file name
    string line;
    cout<<"Please Enter the Map File Name: "<<flush;
    getline(cin,line);
    //ask user to input the number of customers
    cout<<"Please Enter the number of customers: "<<flush;
    int customerNumber=0;
    cin>>customerNumber;
    //ask user to input the average shopping time of customers
    cout<<"Please Enter the average shopping time of customers: "<<flush;
    int averageShoppingTime=0;
    cin>>averageShoppingTime;

    poisson_distribution<int> Poisson(averageShoppingTime);

    //read the parameters of the map
    ifstream inData;
    inData.open(line.c_str());

    while (getline(inData,line))
    {
        for (unsigned int i=0;i<line.size();++i)
        {
            if (line[i]=='S')
            {
                ++shelfNumber;
            }
            else if (line[i]=='W')
            {
                ++wallNumber;
            }
            else if (line[i]=='E')
            {
                ++entranceNumber;
            }
        }
        cout<<line<<endl;
    }

    //generate the objects in the map
    shelf=new Shelf[shelfNumber];
    wall=new Wall[wallNumber];
    entrance=new Entrance[entranceNumber];

    //read the position of the objects
    inData.clear();
    inData.seekg(0);
    //index of the shelves
    int s=0;
    //index of the walls
    int w=0;
    //index of the entrances
    int e=0;

    //set the coordinates of the objects
    for (int i=0;getline(inData,line);++i)
    {
        for (unsigned int j=0;j<line.size();++j)
        {
            if (line[j]=='S')
            {
                shelf[s].Set(j,i);
                ++s;
            }
            else if (line[j]=='W')
            {
                wall[w].Set(j,i);
                ++w;
            }
            else if (line[j]=='E')
            {
                entrance[e].Set(j,i);
                ++e;
            }
            else if (line[j]=='I')
            {
                intersections.insert(Position(j,i));
            }
        }
    }
    inData.close();

    srand(time(0));
    int entranceIndex=0;
    for (int i=0;i<customerNumber;++i)
    {
        entranceIndex=rand()%entranceNumber;
        Customer* newCustomer=new Customer(entrance[entranceIndex].GetX(), entrance[entranceIndex].GetY(), Poisson);
        (*newCustomer).DecideDirection(this);
        customerList.insert(customerList.end(), newCustomer);
    }

    //output the parameters of the map
    cerr<<"\nNumber of Shelves: "<<shelfNumber<<endl;
    cerr<<"Number of Walls: "<<wallNumber<<endl;
    cerr<<"Number of Entrances: "<<entranceNumber<<endl;
}

void Map::StartSimulation()
{
    while (customerList.size()>0)
    {
        for (list<Customer*>::iterator iter=customerList.begin(); iter!=customerList.end();)
        {

            //cerr<<"Time: "<<(**iter).GetShoppingTime()<<endl;
            //cerr<<"P: "<<(**iter).GetX()<<'\t'<<(**iter).GetY()<<endl;
            //cerr<<"D: "<<(**iter).GetDirectionX()<<'\t'<<(**iter).GetDirectionY()<<endl;

            //move 1 step
            (**iter).Move(routeRecord);
            //if shopping time end, leave
            if ((**iter).GetShoppingTime()==(**iter).GetMaxShoppingTime())
            {
                delete (*iter);
                (*iter)=0;
                customerList.erase(iter++);
            }
            else
            {
                //if arrive an intersection, decide direction
                if (intersections.find(Position((**iter).GetX(), (**iter).GetY()))!=intersections.end())
                {
                    (**iter).DecideDirection(this);
                }
                ++iter;
            }
        }
    }

    //output the result
    ofstream outData;
    outData.open("result.txt");
    for (static set<PositionRecord>::iterator iter=routeRecord.begin(); iter!=routeRecord.end(); iter++)
    {
        outData<<"("<<(*iter).x<<", "<<(*iter).y<<"): "<<(*iter).visitTimes<<endl;
    }
    outData.close();
}
