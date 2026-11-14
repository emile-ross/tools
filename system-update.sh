#!/usr/bin/env bash

GIT_DIRECTORY=~/n

goto_repo()
{
	if [ $# -lt 1 ];
	then
		echo "Missing arguments to goto_repo() function"
	fi
}

if [ "$EUID" -ne 0 ]; then
	echo "Missing root privileges"
	exit 1
fi

if [ ! -d $GIT_DIRECTORY ];
then
	echo "git directory wasn't found \'$GIT_DIRECTORY\'"
fi

goto_repo $GIT_DIRECTORY

