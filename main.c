#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "encoderrrr.h"
#include "freqTable.h"
#include "buildTree.h"
#include "rowNode.h"
#include "huffmanNode.h"
#include "generateCodes.h"

#define MAX_PATH_LENGTH 255

int encode(int argc, char *argv[]); // Declare the encode function

int main(int argc, char *argv[]) {
    return encode(argc, argv); // Call the encode function from encode.c
}
