#!/bin/bash

echo "RUN - time: $(date) Process id:$$"

sleep $((RANDOM % 21))

echo "END - time:$(date) Process id:$$"