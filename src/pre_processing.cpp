#include "headers.h"

bool isLow;
double rand_temp[100];

void checkEndian() {
    short int test = 0x1234;
    if (*((char *)&test) == 0x12)
        isLow = 0;  // high endian
    else
        isLow = 1;  // low endian
}

// turn high-endian data to low-endian data
#define high2Low(data) ((((uint32_t)(data) & 0xff000000) >> 24) | \
                        (((uint32_t)(data) & 0x00ff0000) >> 8 ) | \
                        (((uint32_t)(data) & 0x0000ff00) << 8 ) | \
                        (((uint32_t)(data) & 0x000000ff) << 24))

int (*images)[784];

bool readFromDataset() {
    checkEndian();
    FILE *file;
    printf("Reading from dataset...\n");
    file = fopen("../data/Mnist.ds", "rb");
    if (file == NULL)
        return 0;  // dataset is not open correctly

    int *temp;
    temp = (int*)malloc(4);
    // magic number, number of images, number of rows, number of columns
    for (int i = 0; i < 4; i++) {
        fread(temp, 4, 1, file);
        if (isLow) *temp = high2Low(*temp);
        switch (i) {
            case 0: printf("[Magic number: "); break;
            case 1: printf("[Number of images: "); break;
            case 2: printf("[Number of rows: "); break;
            case 3: printf("[Number of columns "); break;
            default: break;
        }
        printf("%d]\n", *temp);
    }

    printf("Reading images from dataset...\n");
    // 60,000 images, each has 784 bytes
    images = (int((*)[784]))malloc(60000 * 784 * sizeof(int));
    for (int i = 0; i < 60000; i++) {
        for (int j = 0; j < 196; j++) {
            fread(temp, 4, 1, file);
            if (isLow) *temp = high2Low(*temp);
            images[i][j * 4 + 3] = (*temp) & 0x000000ff;
            images[i][j * 4 + 2] = ((*temp) & 0x0000ff00) >> 8;
            images[i][j * 4 + 1] = ((*temp) & 0x00ff0000) >> 16;
            images[i][j * 4] = ((*temp) & 0xff000000) >> 24;
        }
    }
    free(temp);

    fclose (file);
    return 1;
}

// standard normal distribution N(0, 1)
void boxMuller(double* data, int count, int number) {
    static const double epsilon = numeric_limits<double>::min();
    static const double twopi = double(2.0 * 3.14159265358979323846);
    double u1;
    double u2;

    srand(rand_temp[number]);

    for (int i = 0; i < count; i += 2) {
        do {
            u1 = rand() * (1.0 / RAND_MAX);
            u2 = rand() * (1.0 / RAND_MAX);
        }
        while (u1 <= epsilon);
        double radius = sqrt(-2 * log(u1));
        double theta = twopi * u2;
        data[i] = radius * cos(theta);
        data[i + 1] = radius * sin(theta);
    }
}

void normalize(double* data, int count) {
    double total = 0;
    for (int i = 0; i < count; i++)
    {
       total += data[i]*data[i];
    }
    total = sqrt(total);
    for (int i= 0 ; i< count ; i++) {
        data[i] = data[i] / total;
    }
}

// generate random projection vectors 100*784
double projectData[100][784];

void geneRandProjVects() {
    double data[784];
    int count = 784;
    srand((int)time(0));
    for (int i = 0; i < 100; i++)
        rand_temp[i] = rand() % RAND_MAX;

    printf("Generating random projection vectors...\n");
    for (int i = 0; i < 100; i++) {
        boxMuller(data, count, i);
        normalize(data, count);
        for (int j = 0; j < count; j++) {
            projectData[i][j] = data[j];
        }
    }
}

// project 60000 images to 100 vectors
projectNode (*projectVector)[60000];

void projection() {
    printf("Projecting images to vectors...\n");
    projectVector = (projectNode((*)[60000]))malloc(100 * 60000 * sizeof(projectNode));

    for (int i = 0; i < 60000; i++)
        for (int j = 0; j < 100; j++) {
            projectVector[j][i].imageNum = i;
            projectVector[j][i].length = 0;
            for (int k = 0; k < 784; k++)
                projectVector[j][i].length += (double)images[i][k] * projectData[j][k];
        }
    // free(images);
}

candidate preProcessing() {
    clock_t start = clock();
    printf("==================== Pre-processing ====================\n");
    if (readFromDataset() == 0) {
        printf("Dataset is not open correctly\n");
        exit(1);
    }
    geneRandProjVects();
    projection();

    double end = (double)(clock() - start) / (double)CLOCKS_PER_SEC;
    printf("\n[Pre-processing tie: %lf seconds]\n\n", end);

    start = clock();
    printf("================= Finding Closest-pair =================\n");
    candidate closest;
    closest = closest_pair(projectVector, images);
    return closest;
}
