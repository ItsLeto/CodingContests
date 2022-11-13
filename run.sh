#!/bin/bash

RED="\e[91m"
GREEN="\e[32m"
YELLOW="\e[33m"
ENDCOLOR="\e[0m"

SHORT=e,s,l:
LONG=example,suppress,level:
OPTS=$(getopt -a -n weather --options $SHORT --longoptions $LONG -- "$@")

eval set -- "$OPTS"

example=""
suppress=""

while :
do
  case "$1" in
    -e | --example ) example="true";  shift   ;;
    -s | --suppress) suppress="true"; shift   ;;
    -l | --level)    level="$2";      shift 2 ;;
    --) shift; break; ;;
    *) echo "Unexpected option: $1" ;;
  esac
done

echo $level, $suppress, $example

mkdir -p "output/${level}"

if [[ ${example} == "true" ]]; then
  echo -e "${YELLOW}$level example${ENDCOLOR}"
  if test -f "input/${level}/${level}_example.in"; then
    echo -e "${GREEN}>>>>>> Running ${level}_example.in${ENDCOLOR}"
    if [[ ${suppress} == "true" ]]; then
      ./${level} < "input/${level}/${level}_example.in" > /dev/null 2>&1
    else
      ./${level} < "input/${level}/${level}_example.in"
    fi
    if [[ ${?} == "0" ]]; then
      echo -e "${GREEN}>>>>>> Execution of ${level}_example.in successful!${ENDCOLOR}"
      mv "output/output" "output/${level}/${level}_example.out"
      diff --strip-trailing-cr "input/${level}/${level}_example.out" "output/${level}/${level}_example.out"
      if [[ ${?} == "0" ]]; then
        echo -e "${GREEN}>>>>>> Example passed!!${ENDCOLOR}"
      else
        echo -e "${RED}>>>>>> Example failed!!${ENDCOLOR}"
      fi
    else
      echo -e "${RED}>>>>>> Execution of ${level}_example.in failed!${ENDCOLOR}"
    fi
  fi
else
  echo -e "${YELLOW}Test${ENDCOLOR}"
  for i in {1..7}
  do
    if test -f "input/${level}/${level}_${i}.in"; then
      echo -e "${GREEN}>>>>>> Running ${level}_${i}.in${ENDCOLOR}"
      if [[ ${suppress} == "true" ]]; then
        ./${level} < "input/${level}/${level}_${i}.in" > /dev/null 2>&1
      else
        echo -e "${YELLOW}>>>>>> Running ${level}_${i}.in${ENDCOLOR}"
        ./${level} < "input/${level}/${level}_${i}.in"
      fi
      if [[ ${?} == "0" ]]; then
        echo -e "${GREEN}>>>>>> Execution of ${level}_${i}.in successful!${ENDCOLOR}"
        mv "output/output" "output/${level}/${level}_${i}.out"
      else
        echo -e "${RED}>>>>>> Execution of ${level}_${i}.in failed!${ENDCOLOR}"
      fi
    fi
  done
fi
