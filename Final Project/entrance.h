#ifndef STORAGE_H_INCLUDED
#define STORAGE_H_INCLUDED

class Entrance
{
    int x;
    int y;
public:
    Entrance();
    ~Entrance(){}
    int GetX() const
    {
        return x;
    }
    int GetY() const
    {
        return y;
    }
    void Set(const int &x1, const int &y1);
};

#endif // STORAGE_H_INCLUDED
