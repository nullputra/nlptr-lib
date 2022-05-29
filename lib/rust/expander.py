#!/usr/bin/python3
# Ref: https://github.com/rust-lang-ja/ac-library-rs/blob/master/expand.py

import getopt
import os
import re
import subprocess
import sys
import tempfile

usage = """USAGE: $ expander.py [options] <PATH>
    e.g.) lib/rust/expander.py -fp src/sample.rs
    e.g.) lib/rust/expander.py -fp src/sample.rs > src/sample-bundled.rs
Options:
    -f  --format    format with rustfmt
    -h  --help      print this help and exit
    -p  --proconio  parse proconio macro
"""
opt_list = {"format": "f", "help": "h", "proconio": "p"}
lib_folder = "lib/rust/"
par_folder_list = ["algebra/", "data_structures/", "graphs/", "others/", "trees/"]
removal_pattern = r"(\s*(//|dbg!|eprintln!).*|.*clippy.*)"
inc_pattern = "include!"
inc_removal_pattern = r'.*\("|.*/|"\);'
proconio_removal_pattern = r".*proconio.*"
proconio_parse_pattern = r".*fn main.*"
cfg_pattern = "#[cfg(test)]"


def kill(s, status):
    if s != "":
        print("[\033[31m!\033[m]", s, file=sys.stderr)
    print(usage, end="", file=sys.stderr)
    sys.exit(status)


try:
    opts, args = getopt.getopt(sys.argv[1:], "".join(opt_list.values()), list(opt_list.keys()))
except getopt.GetoptError as e:
    kill(e, 2)

formats = False
parses_proconio = False
for o, v in opts:
    for (opt_long, opt_short) in opt_list.items():
        # Shorten
        if opt_long in o:
            o = "-" + opt_short
            break
    print(f"[\033[34m#\033[m] o: {o}, v: {v}", file=sys.stderr)
    if o == "-f":
        formats = True
    elif o == "-h":
        kill("", 0)
    elif o == "-p":
        parses_proconio = True

if len(args) != 1:
    kill(f"len(args): {len(args)}", 2)
if not os.path.isdir(lib_folder):
    kill(f"The directory {lib_folder} was not found.", 1)


parsed_out_names = set()


def parse(first_out_name):
    global lib_folder
    global parsed_out_names
    res = []
    out_names = set()
    out_names.add(first_out_name)

    for out_name in out_names:
        if out_name not in parsed_out_names:
            parsed_out_names.add(out_name)
            file_path = ""
            # Find out which is the correct parent folder name
            for par_folder in par_folder_list:
                file_path = lib_folder + par_folder + out_name
                if os.path.isfile(file_path):
                    break
            else:
                kill(f"The file {first_out_name} was not found.", 1)
            with open(file_path, "r") as f:
                is_block_comment = False
                for line in f:
                    line = line.rstrip()
                    if not is_block_comment:
                        if line.startswith(inc_pattern):
                            next_out_name = re.sub(inc_removal_pattern, "", line)
                            res.extend(parse(next_out_name))
                            continue
                        if line.startswith(cfg_pattern):
                            break
                        if line.startswith("/*"):
                            is_block_comment = True
                            continue
                        line = re.sub(removal_pattern, "", line)
                        if line:
                            res.append(line)
                    else:
                        if line.endswith("*/"):
                            is_block_comment = False
    return res


output_data = []
src_path = args[0]
use_proconio = False
with open(src_path) as f:
    lines = f.readlines()
    is_block_comment = False
    prev_line = ""
    for line in lines:
        line = line.rstrip()
        if not is_block_comment:
            if re.match(proconio_removal_pattern, line) and parses_proconio:
                use_proconio = True
                continue
            if re.match(proconio_parse_pattern, line):
                if use_proconio:
                    output_data.extend(parse("proconio.rs"))
            if line.startswith(inc_pattern):
                out_name = re.sub(inc_removal_pattern, "", line)
                output_data.extend(parse(out_name))
                continue
            if line.startswith("/*"):
                is_block_comment = True
                continue
            # Just a line break
            if not line and prev_line:
                output_data.append(line)
                prev_line = line
                continue
            line = re.sub(removal_pattern, "", line)
            # If there is nothing left due to this removal,
            # do not display it (to prevent extra line breaks)
            if line:
                output_data.append(line)
                prev_line = line
        else:
            if line.endswith("*/"):
                is_block_comment = False


# Format with rustfmt and output
with tempfile.TemporaryDirectory() as temp_dir:
    temp_file_path = temp_dir + "/output.rs"
    with open(temp_file_path, "w") as f:
        for line in output_data:
            print(line, file=f)
    if formats:
        print("[\033[34m#\033[m] Format with rustfmt.", file=sys.stderr)
        print("[\033[34m#\033[m] temp_file_path :", temp_file_path, file=sys.stderr)
        subprocess.run(["rustfmt", temp_file_path], check=True)
    with open(temp_file_path, "r") as f:
        for line in f:
            print(line, end="")
