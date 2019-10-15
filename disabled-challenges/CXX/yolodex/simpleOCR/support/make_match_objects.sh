#/usr/bin/env bash

make_array () {
  res=""
  for x in "$@"; do
    length=${#x}
    for i in $(seq 0 $((length - 1))); do
      res=$res$(printf "'${x:i:1}',")
    done
    res="$res\n"
  done
  echo $res
}

i = 0
for x in a b c d e f g h i j k l m n o p q r s t u v w x y z; do
  dims=$(pbmtext -builtin fixed -plain -nomargins $x | sed -n '2p')
  width=$(cut -f 1 -d ' ' <<< $dims)
  height=$(cut -f 2 -d ' ' <<< $dims)
  data=$(pbmtext -builtin fixed -plain -nomargins $x | tail -n+3)
  array=$(make_array $data)
  printf "{\n\t.character = '%c'\n\t.width = %d,\n\t.height = %d,\n\t.map = {\n%s\n\t}\n},\n" \
    $x $width $height "$array"
  i=$((i+1))
done
