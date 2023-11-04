#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "encode.h"
#include "freqTable.h"
#include "buildTree.h"
#include "rowNode.h"
#include "huffmanNode.h"
#include "generateCodes.h"
#include "decode.h"

#define MAX_PATH_LENGTH 255



int main(int argc, char *argv[]) {
    //encodeToFile(argc, argv);
    decodeFromFile(argc, argv);
    return 0;// Call the encode function from encode.c
}