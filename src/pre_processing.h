#ifndef _PRE_PROCESSING_H_
#define _PRE_PROCESSING_H_

typedef pair<int, int> Pair;

struct candidate { Pair pointPair; double length; };
struct projectNode { int imageNum; double length; };

void checkEndian();
bool readFromDataset();
void boxMuller(double* data, int count);
void normalize(double* data, int count);
void geneRandProjVects();
void projection();

candidate preProcessing();

#endif
