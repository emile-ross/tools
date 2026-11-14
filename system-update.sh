#!/usr/bin/env bash

HOME_PATH="/home/$SUDO_USER"
GIT_DIRECTORY="$HOME_PATH/temp"

GIT_SOURCE="https://github.com"
GIT_USERNAME="emile-ross"

function goto_repo
{
	if [ $# -lt 1 ];
	then
		echo "Missing arguments to goto_repo() function"
	fi

	DOWNLOADED_REPO=false

	cd $GIT_DIRECTORY/

	if [ ! -d "$GIT_DIRECTORY/$1" ];
	then
		if "$DOWNLOADING_ENABLED"; then
			echo "$GIT_SOURCE:$GIT_USERNAME/$1.git"
			git clone "$GIT_SOURCE:$GIT_USERNAME/$1.git"
			if [ "$EUID" -eq 0 ] ;
			then
				DOWNLOADED_REPO=true
			else
				echo "encountered an error during the $1 downloading phase"
				return 1
			fi
		else
			echo "skipping download for \"$1\" repo"
			return -1
		fi

	fi

	if [ ! -d "$GIT_DIRECTORY/$1" ];
	then
		echo "git repo download failed"
		return 1
	fi
	cd $1/

	if "$DOWNLOADED_REPO" ;
	then
		echo "repo has been downloaded"
	else
		echo "not downloaded"
	fi
	if "$DOWNLOADING_ENABLED";
	then
		git pull --all
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
	mkdir $GIT_DIRECTORY
fi



DOWNLOADING_ENABLED=false

if question "Do you want to allow downloading" ;
then
	DOWNLOADING_ENABLED=true
fi


goto_repo "wordle"

