#!/usr/bin/python3
# Ref: https://github.com/rust-lang-ja/ac-library-rs/blob/master/expand.py

import getopt
import os
import re
import subprocess
import sys
import tempfile

usage = """USAGE: $ expander.py [options] <PATH>
    e.g.) lib/go/expander.py -f src_go/memo/memo.go
    e.g.) lib/go/expander.py -f src_go/memo/memo.go > src_go/memo/memo-bundled.go
Options:
    -f  --format    format with "go fmt"
    -h  --help      print this help and exit
"""
opt_list = {"format": "f", "help": "h"}
lib_folder = "lib/go/"
par_folder_list = ["atcoder/", "data_structures/", "graphs/", "others/", "trees/"]
removal_pattern = r"((\t|\s)*//.*|.*Stderr.*)"
package_pattern = "package"
import_pattern = "import"
import_start_pattern = "import ("
import_end_pattern = ")"
import_removal_pattern = r'(.*\s|\t|")'
import_iib_removal_pattern = r".*go/"
get_file_name_pattern = r".*/"


def kill(s, status):
    if s != "":
        print("[\033[31m!\033[m]", s, file=sys.stderr)
    print(usage, end="", file=sys.stderr)
    sys.exit(status)


try:
    opts, args = getopt.getopt(sys.argv[1:],
        "".join(opt_list.values()), list(opt_list.keys()))
except getopt.GetoptError as e:
    kill(e, 2)

formats = False
for o, v in opts:
    for (opt_long, opt_short) in opt_list.items():
        if opt_long in o:
            o = "-" + opt_short
            break
    print(f"[\033[34m#\033[m] o: {o}, v: {v}", file=sys.stderr)
    if o == "-f":
        formats = True
    elif o == "-h":
        kill("", 0)

if len(args) != 1:
    kill(f"len(args) : {len(args)}", 2)
if not os.path.isdir(lib_folder):
    kill(f"The directory {lib_folder} was not found.", 1)


def get_file_name(out_name: str):
    file_name = re.sub(get_file_name_pattern, "", out_name)
    return file_name

parsed_out_names = set()
output_imports: "set[str]" = set()
os_used_except_for_stderr = False
def parse(first_out_name):
    global lib_folder
    global output_imports
    global parsed_out_names
    global os_used_except_for_stderr
    res = []
    out_names = set()
    out_names.add(first_out_name)

    for out_name in out_names:
        if out_name not in parsed_out_names:
            print(f"[\033[34m#\033[m] Parse {out_name}.", file=sys.stderr)
            parsed_out_names.add(out_name)
            file_path = lib_folder + out_name + "/" + get_file_name(out_name) + ".go"
            if not os.path.isfile(file_path):
                kill(f"The file {file_path} was not found.", 1)
            with open(file_path, "r") as f:
                is_block_comment = False
                is_inc_block = False
                prev_line = ""
                lib_akas = []
                for line in f:
                    line = line.rstrip()
                    if is_inc_block:
                        if line == import_end_pattern:
                            is_inc_block = False
                            continue
                        next_out_name = re.sub(import_removal_pattern, "", line)
                        if lib_folder in next_out_name:
                            next_out_name = re.sub(import_removal_pattern, "", next_out_name)
                            lib_akas.append(get_file_name(next_out_name))
                            res[0:0] = parse(next_out_name)
                        else:
                            output_imports.add(next_out_name)
                    elif not is_block_comment:
                        if line.startswith(package_pattern):
                            continue
                        if line.startswith(import_pattern):
                            if line == import_start_pattern:
                                is_inc_block = True
                                continue
                            next_out_name = re.sub(import_removal_pattern, "", line)
                            if lib_folder in next_out_name:
                                next_out_name = re.sub(import_removal_pattern, "", next_out_name)
                                res[0:0] = parse(next_out_name)
                            else:
                                output_imports.add(next_out_name)
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
                        for aka in lib_akas:
                            line = re.sub(aka + ".", "", line)
                        if "os." in line:
                            os_used_except_for_stderr = True
                        # If there is nothing left due to this removal,
                        # do not display it (to prevent extra line breaks).
                        if line:
                            output_data.append(line)
                            prev_line = line
                    else:
                        if line.endswith("*/"):
                            is_block_comment = False
    return res


output_data: "list[str]" = []
src_path = args[0]
file_names_to_be_parsed = []
with open(src_path) as f:
    lines = f.readlines()
    is_block_comment = False
    is_inc_block = False
    prev_line = ""
    lib_akas = []
    for line in lines:
        line = line.rstrip()
        if is_inc_block:
            if line == import_end_pattern:
                is_inc_block = False
                continue
            out_name = re.sub(import_removal_pattern, "", line)
            if lib_folder in out_name:
                out_name = re.sub(import_iib_removal_pattern, "", out_name)
                lib_akas.append(get_file_name(out_name))
                file_names_to_be_parsed.append(out_name)
            else:
                output_imports.add(out_name)
            continue
        elif not is_block_comment:
            if line.startswith(import_pattern):
                if line == import_start_pattern:
                    is_inc_block = True
                    continue
                out_name = re.sub(import_removal_pattern, "", line)
                if lib_folder in out_name:
                    out_name = re.sub(import_iib_removal_pattern, "", out_name)
                    file_names_to_be_parsed.append(out_name)
                else:
                    output_imports.add(out_name)
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
            for aka in lib_akas:
                line = re.sub(aka + ".", "", line)
            if "os." in line:
                os_used_except_for_stderr = True
            # If there is nothing left due to this removal,
            # do not display it (to prevent extra line breaks).
            if line:
                output_data.append(line)
                prev_line = line
        else:
            if line.endswith("*/"):
                is_block_comment = False


for out_name in file_names_to_be_parsed:
    output_data.extend(parse(out_name))
# Remove the trailing blank lines if any.
while not output_data[-1]:
    output_data.pop()
if not os_used_except_for_stderr:
    output_imports.discard("os")

# Format with rustfmt and output.
with tempfile.TemporaryDirectory() as temp_dir:
    temp_file_path = temp_dir + "/output.go"
    with open(temp_file_path, "w") as f:
        for line in output_data:
            print(line, file=f)
            if line.startswith(package_pattern):
                print("", file=f)
                if len(output_imports) == 1:
                    print(f'import "{output_imports.pop()}"', file=f)
                else:
                    print(import_start_pattern, file=f)
                    for impt in sorted(list(output_imports)):
                        print(f'\t"{impt}"', file=f)
                    print(import_end_pattern, file=f)
    if formats:
        print('[\033[34m#\033[m] Format with "go fmt".', file=sys.stderr)
        subprocess.run(["go", "fmt", temp_file_path], check=True)
    with open(temp_file_path, "r") as f:
        for line in f:
            print(line, end="")
