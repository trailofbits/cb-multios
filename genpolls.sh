#!/usr/bin/env bash

DIR=$(cd "$(dirname ${BASH_SOURCE[0]})" && pwd)

for chal in $DIR/challenges/*/; do
    CHAL="$(basename $chal)"
    echo $CHAL

    cd "$DIR/challenges/$CHAL"
    for polldir in poller/*/; do
        if [[ -e "$polldir/machine.py" ]]; then
            OUTDIR="$DIR/polls/$CHAL/$polldir"
            mkdir -p "$OUTDIR"
            /usr/bin/env python -B $DIR/tools/generate-polls/generate-polls --count 100 --store_seed --depth 1048575 "$polldir/machine.py" "$polldir/state-graph.yaml" "$OUTDIR"
        fi
    done
done
