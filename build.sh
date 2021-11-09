#!/bin/bash

g++ control_GPIO.cpp -o control_GPIO

# set pinmodes
config-pin -a p9.12 out
config-pin -a p8.16 in+
