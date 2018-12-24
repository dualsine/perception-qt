#!/usr/bin/env bash

from="$(pwd)"
cd "$(dirname "$0")"

source  configs/variables
source bash_helpers.sh

trap exit_trap EXIT
set -e

cd "$from"; check
echo "$from"

git format-patch -n HEAD^
count="$(find . -name '0001-*' -type f -printf '.' | wc -c)"
if [ "$count" == "1" ]; then
  rm -rf /tmp/tmp_patches_perception
  mkdir -p /tmp/tmp_patches_perception
  mv 0001-* /tmp/tmp_patches_perception/.
  cd /tmp/tmp_patches_perception

  path="/tmp/tmp_patches_perception/$(ls | sort -n | head -1)"
  filename=$(basename "$path")
  
  # remove 0001-
  target=$(echo $filename|sed -e 's/0001-//g'|sed -e 's/.patch/.template/g')
  mv "$filename" "$target"

  # replace all PERCEPTION_SRC paths with template variable
  path_escaped=$(echo $PERCEPTION_SRC_PATH | sed 's_/_\\/_g');check
  sed -i s/$path_escaped/PERCEPTION_SRC_PATH/g "$target"

  mv "$target" "$from/$target" ; check
else
  echo "please move file manual"
fi
#mv 0001-*
