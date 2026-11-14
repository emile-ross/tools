#!/usr/bin/env bash

HOME_PATH="/home/$SUDO_USER"
GIT_DIRECTORY="$HOME_PATH/n"

GIT_SOURCE="git@github.com"
GIT_USERNAME="emile-ross"

goto_repo()
{
	if [ $# -lt 1 ];
	then
		echo "Missing arguments to goto_repo() function"
	fi


	cd $GIT_DIRECTORY/

	if [ ! -d "$GIT_DIRECTORY/$1" ];
	then
		if "$DOWNLOADING_ENABLED"; then
			git clone "$GIT_SOURCE:$GIT_USERNAME/$1.git"
		else
			echo "skipping unknown \"$1\" repo"
		fi

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



DOWNLOADING_ENABLED=false

if question "Do you want to allow downloading" ;
then
	DOWNLOADING_ENABLED=true
fi


goto_repo "wordle"

