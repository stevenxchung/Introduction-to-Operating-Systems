// Priority readers and writers
// Pseudo code

// Include packages
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Constants
#define READERS 5
#define READS 5
#define WRITERS 5
#define WRITES 5

// Globals
int shared_resource = 0;

// Main
int main() {}

// Reader helper function to print value read and number of readers
void reader_helper() {}

// Writer helper function to print value written and number of readers during write
void writer_helper() {}
