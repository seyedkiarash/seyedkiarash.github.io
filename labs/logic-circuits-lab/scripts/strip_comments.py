#!/usr/bin/env python3
import pathlib, re, sys

def strip(text):
    out, i, n, in_str = [], 0, len(text), False
    while i < n:
        ch = text[i]
        if in_str:
            out.append(ch)
            if ch == "\\" and i + 1 < n:
                out.append(text[i + 1]); i += 2; continue
            if ch == '"': in_str = False
            i += 1; continue
        if ch == '"':
            in_str = True; out.append(ch); i += 1; continue
        if text.startswith("//", i):
            j = text.find("\n", i); i = n if j < 0 else j; continue
        if text.startswith("/*", i):
            j = text.find("*/", i + 2); i = n if j < 0 else j + 2; continue
        out.append(ch); i += 1
    lines = [l.rstrip() for l in "".join(out).splitlines()]
    res = []
    for l in lines:
        if l == "" and (not res or res[-1] == ""):
            continue
        res.append(l)
    while res and res[-1] == "":
        res.pop()
    return "\n".join(res) + "\n"

root = pathlib.Path(sys.argv[1] if len(sys.argv) > 1 else ".")
files = [p for p in root.rglob("*.v")] + [p for p in root.rglob("*.vh")]
for p in files:
    p.write_text(strip(p.read_text()))
print(f"stripped {len(files)} files")
