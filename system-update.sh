#!/usr/bin/env bash

HOME_PATH="/home/$SUDO_USER"
GIT_DIRECTORY="$HOME_PATH/nd"

GIT_SOURCE="git@github.com:"

goto_repo()
{
	if [ $# -lt 1 ];
	then
		echo "Missing arguments to goto_repo() function"
	fi


	if [ ! -d $GIT_DIRECTORY ];
	then
		question "Do you want to clone $1 from github"
	fi


}

function question
{
	while true; do

		read -p "$1 [Y/n] " answer
		case $answer in
			[Yy]*) return 0 ;;
			[Nn]*) 
				echo "Denied" ;
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
	echo "The target git directory wasn't found \"$GIT_DIRECTORY\""
fi

question "Do you want to allow downloading"

DOWNLOADING_ENABLED=[ $EUID -eq 0 ]

if [ "$EUID" -eq 0 ];
then

fi


