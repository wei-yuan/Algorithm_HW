#!/usr/bin/bash
gcc hw4.c -o hw4
gcc hw4_tstcasgen.c -o hw4_testcase
hw4_testcase > hw4_testdata
hw4 < hw4_testdata
