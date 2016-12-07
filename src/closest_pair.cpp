#include "headers.h"

// select(S, k)
pair<int, double> find_median(vector<double> varr) {
  vector<double> left;
  vector<double> right;
  int k = varr.size()/2;

}

candidate find_colsest(vector<double> varr) {
    int size = varr.size()
    if (size == 1)
        return null;
    candidate subCandidate;
    if (size == 2) {
        subCandidate.pointPair = make_pair(varr.at(0), varr.at(1));
        subCandidate.length = abs(varr.at(0)-varr.at(1));
        return subCandidate;
    }
    pair<int, double> median = find_median(varr);
    vector<double> left, right;
    candidate left_dis, right_dis, left_min;
    for (int i = 0; i < varr.size(); i++) {
        if (varr.at(i) < median) {
            left.push(varr.at(i));
            if (left.size()== 1) {
                left_min.length = varr.at(i)-median.second;
                left_min.pointPair = make_pair(varr.at(i), median.first);
            }
            if (left_min > varr.at(i)-median) {
                left_min.length = varr.at(i)-median.second;
                left_min.pointPair = make_pair(varr.at(i), median.first);
            }
        } else {
            right.push(varr.at(i));
        }
    }

    left_dis = find_colsest(left);
    right_dis = find_colsest(right);

    if (left_dis.length < right_dis.length) {
        if (left_dis.length > left_min.length) return left_min;
        else return left_dis;
    } else {
        if (right_dis.length > left_min.length) return left_min;
        else return right_dis;
    }
}

pair<int, int> closest_pair(double (&projectVector)[100][60000] , int (*images)[784]) {
    double min = 99999;
    candidate counter[100];
    Pair tempCloest = new Pair();
    for (int i = 0; i < 100; i ++) {
        vector<double> varr(projectVector[i], projectVector[i]+60000);
        counter[i] = find_colsest(varr, 60000);
        // compute the Euclidean distance for i candidate
        int first = counter[i].pointPair.first;
        int second = counter[i].pointPair.second;
        double length = 0;
        for (int i = 0; i < 784; i++) {
            length += pow(images[first][i]-images[second][i], 2);
        }
        length = sqrt(length);
        // update the closest pair
        if (length <  min) {
            min = length;
            tempCloest = counter[i].pointPair;
        }
    }
    return tempCloest;
}
