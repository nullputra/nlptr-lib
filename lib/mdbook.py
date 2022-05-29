#!/usr/bin/python3
from collections import defaultdict
import getopt
import glob
import os
import re
import shutil
import subprocess
import toml
import sys

usage = """USAGE: $ mdbook.py [options] <PATH>
    e.g.) $ rm -rf book && lib/mdbook.py -l cpp -s hpp -S cpp
    e.g.) $ rm -rf book && lib/mdbook.py -l CSharp -s cs -S cs
    e.g.) $ rm -rf book && lib/mdbook.py -l rust -s rs -S rs
Options:
    -h  --help      print this help and exit
    -l  --lang      lang (e.g. cpp)
    -s  --suffix    suffix (e.g. hpp)
    -S  --syntax-highlight
                    syntax highlighting (e.g. cpp)
"""
opt_list = {"help": "h", "lang=": "l:", "suffix=": "s:", "syntax-highlight=": "S:"}

lang = "cpp"  # -l
suffix = "hpp"  # -s
syntax_highlight = "cpp"  # -S

src_folder = "book_src/"
github = "https://github.com/nullputra/nlptr-lib/tree/master/"
title = "nlptr-lib"


def kill(s, status):
    if s != "":
        print("[\033[31m!\033[m]", s, file=sys.stderr)
    print(usage, end="", file=sys.stderr)
    sys.exit(status)

try:
    opts, args = getopt.getopt(sys.argv[1:], "".join(opt_list.values()), list(opt_list.keys()))
except getopt.GetoptError as e:
    kill(e, 2)

if args:
    kill(f"Do not set args: {args}", 2)

for opt, v in opts:
    for (opt_long, opt_short) in opt_list.items():
        # Shorten
        if opt_long in opt:
            opt = "-" + opt_short
            break
    print(f"(dbg) opt : {opt}, v : {v}", file=sys.stderr)
    if opt == "-h":
        kill("", 0)
    elif opt == "-l":
        lang = v
    elif opt == "-s":
        suffix = v
    elif opt == "-S":
        syntax_highlight = v

lib_folder = f"lib/{lang}/"
docs_folder = f"docs/{lang}/"
dest_folder = f"book/{lang}/"
block_fence = [f"## Impl\n```{syntax_highlight}", "```"]
is_local = os.path.isfile("input.txt")


def setup_toml(str_title: str):
    if is_local:
        return
    di = toml.load(open("book.toml"))
    di["book"]["title"] = str_title
    toml.dump(di, open("book.toml", mode="w"))

# 1-1. 既存ファイルの削除
for rm_folder in glob.glob(f"{src_folder}*/", recursive=True):
    if not os.path.isdir(rm_folder):
        kill(f"The folder {rm_folder} does not exist", 1)
    shutil.rmtree(rm_folder)

for rm_file in glob.glob(f"{src_folder}/*.md", recursive=True):
    if rm_file.endswith("404.md"):
        continue
    os.remove(rm_file)

# 1-2. Copy files
shutil.copyfile("docs/404.md", f"{src_folder}/404.md")
shutil.copyfile("docs/set-up-wsl.md", f"{src_folder}/set-up-wsl.md")
shutil.copyfile("README.md", f"{src_folder}/README.md")

# 1-3. Genarate `/index.html`
if not os.path.isfile("book/index.html"):
    with open(f"{src_folder}/SUMMARY.md", "w") as f:
        print("# Summary\n", file=f)
        print("[README](README.md)", file=f)
        print("[set-up-wsl](set-up-wsl.md)", file=f)
    setup_toml(title)
    os.environ["MDBOOK_OUTPUT__HTML__SITE_URL"] = f"/{title}/"
    dest_idx_folder = "book"
    subprocess.run(["mdbook", "build", "-d", dest_idx_folder], check=True)

# 1-4. Copy setup.md
if os.path.isfile(f"{docs_folder}setup.md"):
    shutil.copyfile(f"{docs_folder}setup.md", f"{src_folder}/setup.md")


# 2-1. lib/cpp/data-structures/union-find.hpp -> src/data-structures/union-find.md
lib_files = glob.glob(f"{lib_folder}*/*.{suffix}")

lib_md = defaultdict(list)
for lib_file_abs in lib_files:
    # absolute -> relative
    # lib/cpp/data-structures/union-find.hpp -> data-structures/union-find.hpp
    lib_file_rel = lib_file_abs[len(lib_folder):]
    # data-structures/union-find.md
    md_to_file = lib_file_rel.replace(f".{suffix}", ".md")
    # docs/cpp/data-structures/union-find.md
    md_from_file = docs_folder + md_to_file
    # data-structures
    lib_folder_name = re.sub(r"/.*", "", lib_file_rel)
    # union-find.hpp
    lib_file = re.sub(r".*/", "", lib_file_rel)
    md_to_file_abs = src_folder + md_to_file
    os.makedirs(src_folder + lib_folder_name, exist_ok=True)
    with open(md_to_file_abs, "w") as f_to:
        if not os.path.isfile(md_from_file):
            print(f"(dbg) {md_from_file} does not exist", file=sys.stderr)
            print(f"# {lib_file}", file=f_to)
        else:
            with open(md_from_file, "r") as f_from:
                lines = f_from.readlines()
                lines_nxt = ""
                scanned_yaml_front_matter = True
                cnt = 0
                for line in lines:
                    line = line.rstrip("\n")
                    if line == "---":
                        scanned_yaml_front_matter = not scanned_yaml_front_matter
                        continue
                    if scanned_yaml_front_matter:
                        if line.startswith("## Brief"):
                            continue
                        line = re.sub(r"\\:", r"\\\\:", line)
                        prv_c = ""
                        for c in line:
                            if c == "$" and prv_c != "\\":
                                cnt += 1
                                lines_nxt += r"\\(" if cnt & 1 else r"\\)"
                            else:
                                lines_nxt += c
                            prv_c = c
                        lines_nxt += "\n"
                        continue
                    if line.startswith("title: "):
                        lib_file = line.rstrip("\n").replace("title: ", "")
                        lines_nxt += f"# {lib_file}\n\n"
                    elif line.startswith("documentation_of: "):
                        if lib_file_abs not in line:
                            kill(f"{lib_file_abs} not in {line}", 1)
                    else:
                        kill(f"Invalid YAML front matter: {line}", 1)
                print(lines_nxt, file=f_to)
        print(block_fence[0], file=f_to)
        with open(lib_file_abs, "r") as f_from:
            print(f_from.read().rstrip("\n"), file=f_to)
        print(block_fence[1], file=f_to)
    # (lib_file, md_to_file)
    lib_md[lib_folder_name].append((lib_file, md_to_file))

# 2-2. 記録された md の名前 -> src/SUMMARY.md
# # Summary
# [README.md](README.md)
# # data-structures
# - [swag.hpp](data-structures/swag.md)
# - [union-find.hpp](data-structures/union-find.md)
with open(src_folder + "SUMMARY.md", "w") as f:
    print("# Summary\n", file=f)
    print("[README](README.md)\n", file=f)
    if os.path.isfile(f"{src_folder}/setup.md"):
        print("[setup](setup.md)\n", file=f)

    print(f"# {lib_folder}\n", file=f)
    lib_md_keys = sorted(lib_md.keys())
    for lib_folder_name in lib_md_keys:
        md_section_path = lib_folder_name + ".md"
        with open(src_folder + md_section_path, "w") as f_section:
            # https://github.com/nullputra/nlptr-lib/tree/master/lib/cpp/data-structures
            print(f"GitHub: [{lib_folder + lib_folder_name}]({github}{lib_folder + lib_folder_name})", file=f_section)
        print(f"- [{lib_folder_name}]({md_section_path})", file=f)
        lib_md[lib_folder_name].sort()
        for lib_file, md_to_file in lib_md[lib_folder_name]:
            print(f"  - [{lib_file}]({md_to_file})", file=f)
        if lib_folder_name != lib_md_keys[-1]:
            print(file=f)

# 2-3. mdbook build -o -d book/cpp とする.
# MDBOOK_OUTPUT__HTML__SITE_URL: https://github.com/rust-lang/mdBook/issues/1302
setup_toml(f"{title} ({lib_folder})")
os.environ["MDBOOK_OUTPUT__HTML__SITE_URL"] = f"/{title}/{lang}/"
subprocess.run(["mdbook", "build", "-d", dest_folder], check=True)
os.environ.pop("MDBOOK_OUTPUT__HTML__SITE_URL")
