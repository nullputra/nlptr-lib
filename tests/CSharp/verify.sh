#!/bin/bash

C_RESET="\033[m"
C_RED="\033[0;31;49m"
C_GREEN="\033[0;32;49m"
C_BLUE="\033[0;34;49m"
C_YELLOW="\033[0;33;49m"

indicator() {
  case $1 in
  $) echo -en "[${C_YELLOW}$1${C_RESET}] " ;;  # WARNING
  \#) echo -en "[${C_BLUE}$1${C_RESET}] " ;;   # INFO
  ! | -) echo -en "[${C_RED}$1${C_RESET}] " ;; # FAILURE
  +) echo -en "[${C_GREEN}$1${C_RESET}] " ;;   # SUCCESS
  # @)  echo -en "[${C_MAGENTA}$1${C_RESET}] ";;  # NETWORK
  *) echo -en "[$1] " ;; # otherwise
  esac
  [ -n "$2" ] && echo -e "${@:2}"
}

indicator "#" dotnet version: "$(dotnet --version)"
echo

cnt=1
for f in ./tests/CSharp/*.cs; do
  indicator "#" "<${cnt}> Test $f."
  f_name="${f##*/}"
  f_name="${f_name/\.cs/}"
  # dotnet build -p:StartupObject=FenwickTreeTest
  indicator "$" dotnet build -p:StartupObject="$f_name"
  if ! dotnet build -p:StartupObject="$f_name"; then
    indicator "-" "<${cnt}> An error occurred during compilation of $f."
    exit 1
  fi
  indicator "+" "<${cnt}> Successfully compiled $f."
  echo
  ((cnt++))
done

indicator "+" "All tests were successful."
