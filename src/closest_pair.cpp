#include "headers.h"

// select(S, k)
projectNode find_median(vector<projectNode> varr) {
  vector<projectNode> left;
  vector<projectNode> right;
  projectNode median;
  int size =  varr.size();
  int k = size/2;
  int random = (size-1)*rand()/RAND_MAX;

  for (int i = 0; i < size; i++) {
    if (varr.at(i).length < varr.at(random).length) {
      left.push_back(varr.at(i));
    } else {
      right.push_back(varr.at(i));
    }
  }

  if (left.size() == k-1) {
    median = varr.at(random);
  } else if (left.size() >= k) {
    median = find_median(left);
  } else {
    median = find_median(right);
  }
  return median;
}

// find the closest pair in a certain projectVector
candidate find_closest(vector<projectNode> varr) {
    int size = varr.size();
    candidate subCandidate;
    projectNode median = find_median(varr);
    vector<projectNode> left, right;
    candidate left_dis, right_dis, left_min;
    if (size == 1) {
        subCandidate.length = 100000;
        return subCandidate;
    }
    if (size == 2) {
        subCandidate.pointPair = make_pair(varr.at(0).imageNum, varr.at(1).imageNum);
        subCandidate.length = fabs(varr.at(0).length-varr.at(1).length);
        return subCandidate;
    }
    for (int i = 0; i < varr.size(); i++) {
        if (varr.at(i).length < median.length) {
            left.push_back(varr.at(i));
            if (left.size()== 1) {
                left_min.length = varr.at(i).length-median.length;
                left_min.pointPair = make_pair(varr.at(i).imageNum, median.imageNum);
            }
            if (left_min.length > varr.at(i).length-median.length) {
                left_min.length = varr.at(i).length-median.length;
                left_min.pointPair = make_pair(varr.at(i).imageNum, median.imageNum);
            }
        } else {
            right.push_back(varr.at(i));
        }
    }

    left_dis = find_closest(left);
    right_dis = find_closest(right);

    if (left_dis.length < right_dis.length) {
        if (left_dis.length > left_min.length) return left_min;
        else return left_dis;
    } else {
        if (right_dis.length > left_min.length) return left_min;
        else return right_dis;
    }
}

candidate closest_pair(projectNode (*projectVector)[60000] , int (*images)[784]) {
    double min = 99999;
    candidate counter[100];
    Pair tempCloest;
    for (int i = 0; i < 100; i ++) {
        vector<projectNode> varr(projectVector[i], projectVector[i]+60000);
        counter[i] = find_closest(varr);
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
    candidate result;
    result.pointPair = tempCloest;
    result.length = min;
    return result;
}
