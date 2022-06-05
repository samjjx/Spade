# Spade: A Real-Time Fraud Detection Framework on Evolving Graphs

Spade is a real-time fraud detection framework.

## Download and compile

Execute the following commands to download and compile the source code

    git clone git@github.com:samjjx/Spade.git && cd Spade 
    mkdir build
    cd build
    cmake ..
    make

## Data format 

./sample/sample.gra is a graph. 

- The first line contains two integers (n is the number of vertices and m is the number of the edges)

    n   m

- Line 2 to Line m+1: each line is an edge.

    u   v   w

u is the source vertex, v is the target vertex, and w is the weight on the edge

./sample/sample.inc is the increment.

- The first line contains an integer (m is the number of edges)

- Line 2 to Line m + 1: each line is an edge.


## Execution

Execute the following command:
    ./Spade file_path batch_size

Test on the sample dataset provided in paper:
    ./Spade ../sample/sample 1


We provide three esusp (dg, dw and fd) in the source codes (line 34-44, spade.cpp).

## Configuration

To turn on the edge grouping or design the peeling algorithms (esusp or vsusp), please follow the instructions in Section 3.