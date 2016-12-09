#include "headers.h"

// select(S, k)
projectNode find_median(vector<projectNode> varr, int k) {
  vector<projectNode> left;
  vector<projectNode> right;
  projectNode median;
  int size =  varr.size();
  if (size == 1) return varr.at(0);
  int random = (rand() % (size));

  for (int i = 0; i < size; i++) {
    if (varr.at(i).length < varr.at(random).length) {
      left.push_back(varr.at(i));
    }
    if (varr.at(i).length > varr.at(random).length){
      right.push_back(varr.at(i));
    }
  }

  if (left.size() == k-1) {
    median = varr.at(random);
  } else if (left.size() >= k) {
    median = find_median(left, k);
  } else {
    median = find_median(right, k-1-left.size());
  }
  return median;
}

// find the closest pair in a certain projectVector by finding out the median
candidate find_closest_bymedian(vector<projectNode> varr) {
    int size = varr.size();
    candidate subCandidate;
    if (size == 1) {
        subCandidate.length = INT_MAX;
        return subCandidate;
    }
    if (size == 2) {
        subCandidate.pointPair = make_pair(varr.at(0).imageNum, varr.at(1).imageNum);
        subCandidate.length = fabs(varr.at(0).length-varr.at(1).length);
        return subCandidate;
    }
    projectNode median = find_median(varr, varr.size()/2+1);
    vector<projectNode> left, right;
    candidate left_dis, right_dis, left_min;
    for (int i = 0; i < varr.size(); i++) {
        if (varr.at(i).length < median.length) {
            left.push_back(varr.at(i));
            if (left.size() == 1) {
                left_min.length = median.length-varr.at(i).length;
                left_min.pointPair = make_pair(varr.at(i).imageNum, median.imageNum);
            }
            if (left_min.length > median.length- varr.at(i).length) {
                left_min.length = median.length-varr.at(i).length;
                left_min.pointPair = make_pair(varr.at(i).imageNum, median.imageNum);
            }
        } else {
            right.push_back(varr.at(i));
        }
    }
    left_dis = find_closest_bymedian(left);
    right_dis = find_closest_bymedian(right);

    if (left_dis.length < right_dis.length) {
        if (left_dis.length > left_min.length) return left_min;
        else return left_dis;
    } else {
        if (right_dis.length > left_min.length) return left_min;
        else return right_dis;
    }
}

// find the closest pair in a certain projectVector by finding a random pivot
candidate find_closest_byrandom(vector<projectNode> varr) {
    int size = varr.size();
    candidate subCandidate;
    if (size == 1 || size == 0) {
        subCandidate.length = INT_MAX;
        return subCandidate;
    }
    if (size == 2) {
        subCandidate.pointPair = make_pair(varr.at(0).imageNum, varr.at(1).imageNum);
        subCandidate.length = fabs(varr.at(0).length-varr.at(1).length);
        return subCandidate;
    }
    vector<projectNode> left, right;
    candidate left_dis, right_dis, left_min;
    while (left.size() == 0 || right.size() == 0) {
      int random = (rand() % (size));
      projectNode pivot = varr.at(random);
      left.clear();
      right.clear();
        for (int i = 0; i < varr.size(); i++) {
            if (varr.at(i).length < pivot.length) {
                left.push_back(varr.at(i));
                if (left.size() == 1) {
                    left_min.length = pivot.length-varr.at(i).length;
                    left_min.pointPair = make_pair(varr.at(i).imageNum, pivot.imageNum);
                }
                if (left_min.length > pivot.length- varr.at(i).length) {
                    left_min.length = pivot.length-varr.at(i).length;
                    left_min.pointPair = make_pair(varr.at(i).imageNum, pivot.imageNum);
                }
            } else {
                right.push_back(varr.at(i));
            }
        }
    }
    left_dis = find_closest_byrandom(left);
    right_dis = find_closest_byrandom(right);

    if (left_dis.length < right_dis.length) {
        if (left_dis.length > left_min.length) return left_min;
        else return left_dis;
    } else {
        if (right_dis.length > left_min.length) return left_min;
        else return right_dis;
    }
}

candidate closest_pair(projectNode (*projectVector)[60000], int (*images)[784], int chose) {
    double min = INT_MAX;
    candidate counter[100];
    Pair tempClosest;
    for (int i = 0; i < 100; i++) {
        vector<projectNode> varr(projectVector[i], projectVector[i] + 60000);
        if (chose == 0)
            counter[i] = find_closest_bymedian(varr);
        if (chose == 1)
            counter[i] = find_closest_byrandom(varr);
        // compute the Euclidean distance for i candidate
        int first = counter[i].pointPair.first;
        int second = counter[i].pointPair.second;
        double length = 0;
        for (int i = 0; i < 784; i++) {
            length += pow(images[first][i]-images[second][i], 2);
        }
        length = sqrt(length);
        // update the closest pair
        if (length < min) {
            min = length;
            tempClosest = counter[i].pointPair;
        }
    }
    candidate result;
    result.pointPair = tempClosest;
    result.length = min;
    return result;
}
