#!/bin/bash

# ─────────────────────────────────────────────
# Benchmark script for multi-threaded and
# single-threaded prime counting programs
# Usage: bash run_benchmarks.sh <LastName>
# ─────────────────────────────────────────────

if [ -z "$1" ]; then
    echo "Usage: bash run_benchmarks.sh <LastName>"
    exit 1
fi

LAST=$1
MT_SRC="primes_mT_${LAST}.c"
ST_SRC="primes_sT_${LAST}.c"
MT_BIN="./primes_mT"
ST_BIN="./primes_sT"
RUNS=3
NS=(1000 2000 4000 8000)
RESULTS_FILE="results.csv"

# ── Compile ──────────────────────────────────
echo "Compiling $MT_SRC ..."
gcc -o primes_mT "$MT_SRC" -lpthread -lm
if [ $? -ne 0 ]; then echo "ERROR: Failed to compile $MT_SRC"; exit 1; fi

echo "Compiling $ST_SRC ..."
gcc -o primes_sT "$ST_SRC" -lm
if [ $? -ne 0 ]; then echo "ERROR: Failed to compile $ST_SRC"; exit 1; fi

echo ""
echo "Both programs compiled successfully."
echo ""

# ── Write CSV header ─────────────────────────
echo "Program,N,Run1(s),Run2(s),Run3(s),Average(s)" > "$RESULTS_FILE"

# ── Benchmark function ────────────────────────
# Args: $1=label  $2=binary
benchmark() {
    local label=$1
    local bin=$2

    for n in "${NS[@]}"; do
        times=()
        printf "%-20s n=%-6s" "$label" "$n"

        for run in $(seq 1 $RUNS); do
            # Run the program and grab the elapsed time from its output
            output=$("$bin" "$n" 2>&1)
            t=$(echo "$output" | grep -oP '[0-9]+\.[0-9]+(?= seconds)')

            # Fallback: if program doesn't print time, measure externally
            if [ -z "$t" ]; then
                start=$(date +%s%N)
                "$bin" "$n" > /dev/null 2>&1
                end=$(date +%s%N)
                t=$(echo "scale=6; ($end - $start) / 1000000000" | bc)
            fi

            times+=("$t")
            printf "  run%d: %ss" "$run" "$t"
        done

        # Compute average in Python (handles float arithmetic cleanly)
        avg=$(python3 -c "vals=[${times[0]},${times[1]},${times[2]}]; print(f'{sum(vals)/len(vals):.6f}')")
        printf "  avg: %ss\n" "$avg"

        echo "$label,$n,${times[0]},${times[1]},${times[2]},$avg" >> "$RESULTS_FILE"
    done
}

# ── Run benchmarks ────────────────────────────
echo "=== Multi-Threaded ==="
benchmark "Multi-Threaded" "$MT_BIN"

echo ""
echo "=== Single-Threaded ==="
benchmark "Single-Threaded" "$ST_BIN"

echo ""
echo "Results saved to $RESULTS_FILE"

# ── Generate Excel file ───────────────────────
echo "Generating Excel spreadsheet..."
python3 generate_excel.py "$RESULTS_FILE" "$LAST"
