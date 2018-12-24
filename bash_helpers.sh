#!/usr/bin/env bash

check () {
	if [ $? != 0 ]; then
		exit 1;
	fi 
}

exit_trap () {
  local lc="$BASH_COMMAND" rc=$?
  if [ "$rc" != 0 ]; then
  	echo "Command [$lc] exited with code [$rc]"
  fi
}