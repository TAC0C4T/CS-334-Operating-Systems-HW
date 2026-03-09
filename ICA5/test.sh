#!/bin/bash
NS=(1000 2000 4000 8000)

gcc -o primes_mT "primes_mT_Rhoades.c"
gcc -o primes_sT "primes_sT_Rhoades.c"

for n in "${NS[@]}"; do
    for run in 1 2 3; do
        echo "=== MT n=$n run=$run ==="
        ./primes_mT $n
    done
done

for n in "${NS[@]}"; do
    for run in 1 2 3; do
        echo "=== ST n=$n run=$run ==="
        ./primes_sT $n
    done
done