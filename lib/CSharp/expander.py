#!/usr/bin/python3
# Ref: https://github.com/rust-lang-ja/ac-library-rs/blob/master/expand.py
import getopt
import os
import re
import sys

usage = """USAGE: $ expander.py [options] <PATH>
    e.g.) lib/CSharp/expander.py src/Program.cs
    e.g.) lib/CSharp/expander.py src/Program.cs > src/ProgramBundled.cs
Options:
    -h  --help      print this help and exit
"""
opt_list = {"help": "h"}
lib_folder = "lib/CSharp/"
par_folder_list = ["Algebra/", "AtCoder/", "Collections/", "DataStructures/", "Graphs/", "Misc/", "Strings/", "Trees/"]
src_removal_pattern = r"\s*(//|Console\.Error\.WriteLine|Dbg\.Dump).*"
inc_pattern = ("using Lib.", "using static Lib.")
special_parse_pattern = {"ModInt": "ModInt.cs"}
inc_removal_pattern = r".*using.*Lib\.|;|\..*"
using_pattern = "using"


def kill(s, status):
    if s != "":
        print("[\033[31m!\033[m]", s, file=sys.stderr)
    print(usage, end="", file=sys.stderr)
    sys.exit(status)


try:
    opts, args = getopt.getopt(sys.argv[1:],
        "".join(opt_list.values()), list(opt_list.keys()))
except getopt.GetoptError as e:
    kill(e, 1)

for o, v in opts:
    for (opt_long, opt_short) in opt_list.items():
        if opt_long in o:
            o = "-" + opt_short
            break
    if o == "-h":
        kill("", 0)

if len(args) != 1:
    kill(f"len(args) : {len(args)}", 1)
if not os.path.isdir(lib_folder):
    kill(f"The directory {lib_folder} was not found.", 2)


parsed_out_names = set()
output_usings: "set[str]" = set()
def parse(first_out_name):
    global lib_folder
    global parsed_out_names
    global output_usings
    res = []
    out_names = set()
    out_names.add(first_out_name)

    for out_name in out_names:
        if out_name not in parsed_out_names:
            parsed_out_names.add(out_name)
            file_path = ""
            # Find out which is the correct parent folder name.
            for par_folder in par_folder_list:
                file_path = lib_folder + par_folder + out_name
                if os.path.isfile(file_path):
                    break
            else:
                kill(f"The file {first_out_name} was not found.", 2)
            with open(file_path, "r") as f:
                is_block_comment = False
                prev_line = ""
                for line in f:
                    line = line.rstrip()
                    if not is_block_comment:
                        if line.startswith(using_pattern):
                            output_usings.add(line)
                            next_out_name = ""
                            for (special_pattern, special_out_name) in special_parse_pattern.items():
                                if special_pattern in line:
                                    next_out_name = special_out_name
                                    break
                            if line.startswith(inc_pattern):
                                next_out_name = re.sub(inc_removal_pattern, "", line) + ".cs"
                            if next_out_name:
                                res[0:0] = parse(next_out_name)
                                res.append("")
                            continue
                        if line.startswith("/*"):
                            is_block_comment = True
                            continue

                        # Just a line break
                        if not line and prev_line:
                            output_data.append(line)
                            prev_line = line
                            continue
                        line = re.sub(src_removal_pattern, "", line)
                        # If there is nothing left due to this removal,
                        # do not display it (to prevent extra line breaks).
                        if line:
                            output_data.append(line)
                            prev_line = line
                    else:
                        if line.endswith("*/"):
                            is_block_comment = False
    return res


output_data = []
src_path = args[0]
file_names_to_be_parsed = []
with open(src_path) as f:
    lines = f.readlines()
    is_block_comment = False
    prev_line = ""
    for line in lines:
        line = line.rstrip()
        if not is_block_comment:
            if line.startswith(using_pattern):
                output_usings.add(line)
                out_name = ""
                for (special_pattern, special_out_name) in special_parse_pattern.items():
                    if special_pattern in line:
                        out_name = special_out_name
                        break
                if line.startswith(inc_pattern):
                    out_name = re.sub(inc_removal_pattern, "", line) + ".cs"
                if out_name:
                    file_names_to_be_parsed.append(out_name)
                continue
            if line.startswith("/*"):
                is_block_comment = True
                continue
            # Just a line break
            if not line and prev_line:
                output_data.append(line)
                prev_line = line
                continue

            line = re.sub(src_removal_pattern, "", line)
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


# Output
normal_output_usings = list()
static_output_usings = list()
equal_output_usings = list()

for line in sorted(list(output_usings)):
    if "=" in line:
        equal_output_usings.append(line)
    elif line.startswith("using static"):
        static_output_usings.append(line)
    else:
        normal_output_usings.append(line)

for line in normal_output_usings:
    print(line)
for line in static_output_usings:
    print(line)
for line in equal_output_usings:
    print(line)

print()

for line in output_data:
    print(line)
