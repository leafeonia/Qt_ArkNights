#ifndef COORDINATE_H
#define COORDINATE_H

#include <vector>

class Coordinate{
public:
    Coordinate();
    std::pair<int,std::pair<int,int>> getCoordinate(int x, int y);

private:
    std::vector<std::pair<int,int>> v;
    int w, h;
};

#endif // COORDINATE_H
