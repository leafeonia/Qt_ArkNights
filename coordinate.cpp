#include "coordinate.h"

Coordinate::Coordinate()
{
    w = h = 110;
    for(int i = 0;i < 9;i++){
        v.push_back(std::make_pair(240 + 110*i,140));
    }
    for(int i = 0;i < 9;i++){
        v.push_back(std::make_pair(210 + 115*i,230));
    }
    for(int i = 0;i < 9;i++){
        v.push_back(std::make_pair(190 + 120*i,320));
    }
    for(int i = 0;i < 9;i++){
        v.push_back(std::make_pair(155 + 127*i,430));
    }
}

std::pair<int,std::pair<int,int>> Coordinate::getCoordinate(int x, int y)
{
    for(int i = 0;i < v.size();i++){
        if(v[i].first <= x && x < v[i].first + w && v[i].second <= y && y < v[i].second + h){
            return std::make_pair(i, v[i]);
        }
    }
    return std::make_pair(-1,std::make_pair(-1,-1));
}
