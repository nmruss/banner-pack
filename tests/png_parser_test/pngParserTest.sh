#!/bin/bash
cd ../../;
make clean all;
./build/apps/program test-png-parser < ./tests/args_documents/pngParserTestArgs.txt
