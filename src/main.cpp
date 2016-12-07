#include "headers.h"

int main(int argc, char *argv[]) {
    candidate closest;
    Pair closest_pair;
    closest = preProcessing();
    closest_pair = closest.pointPair;

    cout << "The cloest Pair in this dateset is: ";
    if (closest_pair.first > closest_pair.second) {
      cout << closest_pair.second << " and " << closest_pair.first << endl;
    } else {
      cout << closest_pair.first << " and " << closest_pair.second << endl;
    }
    cout << "The distance between these two points is " << closest.length << endl;
	return 0;
}
