#ifndef _CLOSEST_PAIR_H_
#define _CLOSEST_PAIR_H_

// typedef pair<int, int> Pair;
//
// struct candidate {Pair pointPair; double length;};
candidate find_colsest_bymedian(vector<projectNode> varr);
candidate find_colsest_byrandom(vector<projectNode> varr);
projectNode find_median(vector<projectNode> varr);
candidate closest_pair(projectNode (*projectVector)[60000] , int (*images)[784], int chose);

#endif
