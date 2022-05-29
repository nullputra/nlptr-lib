#!/usr/bin/python3
import getopt
import os
import sys
import json

usage = """USAGE: $ python3 save_codes.py https://atcoder.jp/contests/abc244/tasks/abc244_a bin/out/v220314.py
Options:
    -h  --help      print this help and exit
"""
opt_list = {"help": "h"}
json_path = "./bin/codes.json"


def kill(s, status):
    if s != "":
        print("[\033[31m!\033[m]", s, file=sys.stderr)
    print(usage, end="", file=sys.stderr)
    sys.exit(status)

try:
    opts, args = getopt.getopt(sys.argv[1:], "".join(opt_list.values()), list(opt_list.keys()))
except getopt.GetoptError as e:
    kill(e, 2)

for o, v in opts:
    for opt_long, opt_short in opt_list.items():
        # Shorten
        if opt_long in o:
            o = "-" + opt_short
            break
    print(f"[\033[34m#\033[m] o: {o}, v: {v}", file=sys.stderr)
    if o == "-h":
        kill("", 0)

if len(args) != 2:
    kill(f"len(args): {len(args)}", 2)

url, src_path = args
if not url:
    kill("url is empty", 2)
if not src_path:
    kill("src_path is empty", 2)
print("[\033[34m#\033[m] url:", url, file=sys.stderr)
src_suffix = src_path.split(".")[-1]

f = open(src_path, "r")
lines = f.read().splitlines()
while lines[-1] == "":
    lines.pop()

if not os.path.isfile(json_path):
    # Create json file
    with open(json_path, "w") as f:
        json.dump({}, f)

# Input
with open(json_path, "r") as f:
    codes_json = json.load(f)

# {
#   "https://atcoder.jp/contests/abc244/tasks/abc244_a": {
#     "bin/out/v220314.py": [
#       "n = int(input())",
#       "s = input()",
#       "print(s[-1])",
#     ]
#   }
# }
# Add
di = codes_json.get(url, {})
di[src_path] = lines
codes_json[url] = di

# Output
# Options: ensure_ascii=False, indent=2, sort_keys=True
with open(json_path, "w") as f:
    json.dump(codes_json, f, ensure_ascii=False, indent=2)

print(f"[\033[32m+\033[m] {src_path} -> {json_path}", file=sys.stderr)
