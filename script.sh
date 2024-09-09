#!/bin/bash

./ghc data/a.in &> a.log 
./ghc data/b.in data/b.in.out.202569 &> b.log 
./ghc data/c.in data/c.in.out.1430 &> c.log 
./ghc data/d.in data/d.in.out.414810 &> d.log 
./ghc data/e.in data/e.in.out.408421 &> e.log 

cat a.log b.log c.log d.log e.log | grep 'eval' | sed -r -e 's/.* ([0-9]*)(\(.*)/\1;\2/g' | awk -F';' '{sum+=0+$1;} END{print sum;}' | sed ':a;s/\B[0-9]\{3\}\>/,&/;ta'

batcat a.log b.log c.log d.log e.log
