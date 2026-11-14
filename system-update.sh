#!/usr/bin/env bash

GIT_DIRECTORY=~/n

goto_repo()
{
	if [ $# -lt 1 ];
	then
		echo "Missing arguments to goto_repo() function"
	fi
}

function question
{

	while true; do

		read answer
		case $answer in
			[Yy]*) return 0 ;;
			[Nn]*) 
				echo "Denied" ;
				return 1 ;;
			*)
				return 1 ;;
		esac

	done
}

if [ "$EUID" -ne 0 ]; then
	echo "Missing root privileges"
	exit 1
fi

if [ ! -d $GIT_DIRECTORY ];
then
	echo "git directory wasn't found \'$GIT_DIRECTORY\'"
	read -p "Do you want to clone it from github"
fi

goto_repo $GIT_DIRECTORY

