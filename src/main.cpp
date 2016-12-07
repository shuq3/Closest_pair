#include "headers.h"

int main(int argc, char *argv[]) {
    Pair cloest = new Pair();
    cloest = preProcessing();
    cout << "The cloest Pair in this dateset is: ";
    if (cloest.first > cloest.second) cout << cloest.second << " and " << cloest.first << endl;
    else cout << cloest.first << " " << cloest.second << endl;
	return 0;
}
