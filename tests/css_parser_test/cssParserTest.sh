#!/bin/bash
cd ../../;
make clean all;
./build/apps/program test-css-parser < ./tests/args_documents/cssParserTestArgs.txt 

