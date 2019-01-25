#ifndef SHELF_H_INCLUDED
#define SHELF_H_INCLUDED

class Shelf
{
    int x;
    int y;
public:
    Shelf();
    ~Shelf(){}
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

#endif // SHELF_H_INCLUDED
