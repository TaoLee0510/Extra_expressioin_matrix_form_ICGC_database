//
//  mapiter.hpp
//  extra_expression_matrix_ICGC_map
//
//  Created by Tao Lee on 11/3/19.
//  Copyright © 2019 Tao Lee. All rights reserved.
//

#ifndef mapiter_hpp
#define mapiter_hpp

#include <stdio.h>
#include <map>
using namespace std;

string mapiter(map<string,string> &map_mat,string ID)
{
string temp_expression="0";
map<string, string>::iterator tempiter;
tempiter=map_mat.find(ID);
if (tempiter!=map_mat.end())
{
    temp_expression=tempiter->second;
    return temp_expression;
}
else
{
    return temp_expression;
}
}

#endif /* mapiter_hpp */
