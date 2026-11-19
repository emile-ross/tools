#!/usr/bin/env bash

HOME_PATH="/home/$SUDO_USER"
GIT_DIRECTORY="$HOME_PATH/temp"
USED_GIT_DIRECTORY="$HOME_PATH/n"

GIT_SOURCE="https://github.com"
GIT_USERNAME="emile-ross"

function download
{
	echo "Downloading remote $1"

	if [ $# -lt 1 ] ;
	then
		echo "Missing arguments to download function"
	fi

	git clone --depth=1 "$GIT_SOURCE/$GIT_USERNAME/$1.git"

	return 0
}

function goto_repo
{
	if [ $# -lt 1 ];
	then
		echo "Missing arguments to goto_repo() function"
	fi

	DOWNLOADED_REPO=false

	if [ ! -d $GIT_DIRECTORY ];
	then
		echo "The target git directory wasn't found \"$GIT_DIRECTORY\""
		mkdir $GIT_DIRECTORY
	fi

	cd $GIT_DIRECTORY/

	if [ ! -d "$USED_GIT_DIRECTORY/$1" ];
	then
		if "$DOWNLOADING_ENABLED"; then
			mkdir -p $GIT_SOURCE

			echo "$GIT_SOURCE/$GIT_USERNAME/$1.git"
			download "$1"
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


	if "$DOWNLOADED_REPO" ;
	then
		cd $1/
		echo "repo has been downloaded!"
	else
		cd $USED_GIT_DIRECTORY/$1
		if "$DOWNLOADING_ENABLED";
		then
			# update the repository
			git pull --all
			# TODO: if git pull fails, attempt (due to missing permission) 
			# attempt to download the repo normally just like we did above
			if [ "$EUID" -ne 0 ];
				then
					download
			fi
		fi
	fi
	# continue with build/install instructions
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

if [ "$EUID" -ne 0 ] ;
then
	echo "Missing root privileges"
	exit 1
fi


DOWNLOADING_ENABLED=false

if question "Do you want to allow downloading" ;
then
	DOWNLOADING_ENABLED=true
fi

goto_repo "dwm-config"
cd dwl/
make clean
make
make install
cd -
goto_repo "dotfiles"
# install each configuration selected below
ls
./script.sh -c btop
./script.sh -c bpytop
./script.sh -c waybar
./script.sh -c fastfetch
cd -

goto_repo "wordle-solver"
make install


# now sys-update
if question "System update?" ;
then
	pacman -Syu --noconfirm
fi

pacman -Qdtq
echo "These orphaned packages can be removed with 'pacman -Rns \$(pacman -Qdtq)'"
