#!/usr/bin/env bash
set -u
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
labs=("$@"); [ ${#labs[@]} -eq 0 ] && labs=("$ROOT"/lab*/)
pass=0; fail=0
for lab in "${labs[@]}"; do
  for part in "$lab"/*/; do
    [ -d "$part/sim" ] || continue
    for tb in "$part"/sim/tb_*.v; do
      [ -e "$tb" ] || continue
      name=$(basename "$tb" .v)
      ( cd "$part/sim" &&
        iverilog -g2012 -I "$ROOT/sim/common" -o "$name.vvp" "$tb" "$part"/src/*.v "$ROOT"/common/*.v 2> "$name.compile.log" &&
        vvp -n "$name.vvp" > "$name.log" 2>&1 )
      res=$(grep -h "RESULT" "$part/sim/$name.log" 2>/dev/null | tail -1)
      if echo "$res" | grep -q "PASS"; then pass=$((pass+1)); st=PASS; else fail=$((fail+1)); st=FAIL; fi
      printf "%-4s %s\n" "$st" "${part#$ROOT/}sim/$name.v"
    done
  done
done
echo "----"; echo "passed: $pass   failed: $fail"
