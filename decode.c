#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "freqTable.h"
#include "buildTree.h"
#include "rowNode.h"
#include "encodER.h"
#include "decodER.h"
#include "huffmanNode.h"

#define MAX_PATH_LENGTH 255

// Define a function to decode the input file and write the output to the output file
int decodeFromFile(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file> [output_file]\n", argv[0]);
        return 1;
    }

    const char *input_filename = argv[1];
    const char *output_filename;

    if (argc >= 3) {
        output_filename = argv[2];
    } else {
        output_filename = "decoded_output"; // Change the default output file name
    }

    int infile = open(input_filename, O_RDONLY);
    if (infile == -1) {
        fprintf(stderr, "Error: Unable to open input file '%s'\n", input_filename);
        return 1;
    }

    int outfile = open(output_filename, O_WRONLY | O_CREAT);
    if (outfile == -1) {
        fprintf(stderr, "Error: Unable to open or create output file '%s'\n", output_filename);
        close(infile);
        return 1;
    }

    //actually decode
    decodeParser(infile, outfile);

    // Teardown and cleanup

    close(infile);
    close(outfile);
    return 0;
}

