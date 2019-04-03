#!/bin/bash
make -C src;echo === Testing build ===;cp build/prog prog;./prog 2>/dev/null;rm -rf prog;