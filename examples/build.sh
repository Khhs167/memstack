#!/bin/bash

gcc "${1}.c" -lmemstack -o example && ./example && rm example -f