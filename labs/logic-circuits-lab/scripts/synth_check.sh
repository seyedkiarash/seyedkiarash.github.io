#!/usr/bin/env bash
# Independent synthesis check with Yosys (synth_xilinx, 7-series primitives).
# Confirms that every part elaborates and maps without errors, and reports
# LUT / flip-flop counts and any inferred latches.
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
printf "%-56s %-24s %5s %5s  %s\n" PART TOP LUTs FFs CHECK
for top in "$ROOT"/lab*/*/TOP; do
  part=$(dirname "$top"); mod=$(cat "$top")
  log=$(mktemp); stat=$(mktemp)
  yosys -q -l "$log" -p "read_verilog -sv $ROOT/common/*.v $part/src/*.v; synth_xilinx -top $mod -flatten; tee -q -o $stat stat" >/dev/null 2>&1
  st=$?
  luts=$(awk '$1 ~ /^LUT[1-6]$/ {s+=$2} END{print s+0}' "$stat")
  ffs=$(awk  '$1 ~ /^FD(RE|SE|CE|PE)$/ {s+=$2} END{print s+0}' "$stat")
  latches=$(grep -c "Latch inferred" "$log")
  check="ok"; [ $st -ne 0 ] && check="ERROR"; [ "$latches" -gt 0 ] && check="$check, $latches latch(es)"
  printf "%-56s %-24s %5s %5s  %s\n" "${part#$ROOT/}" "$mod" "$luts" "$ffs" "$check"
  rm -f "$log" "$stat"
done
