#!/bin/bash

cleanup() {
    echo "Cleaning stuff up..."
    for pid in "${pids[@]}"
	do
   		echo "Killing worker with PID $pid..."
		kill $pid
	done
    exit
}

trap cleanup INT

if [ "$#" -lt 1 ]; then
    echo "Please specify file names!"
    echo "Usage:"
    echo "$0 <space separated file names>"
    exit 1
fi

pids=()

for fname in "$@"
do
    ./MT $fname &
    pids+=("$!")
done

wait

