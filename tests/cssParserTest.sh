#!/bin/bash
cd ../;
make clean all;
./build/apps/program < ./tests/args_documents/cssParserTestArgs.txt 

