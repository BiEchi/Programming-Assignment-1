#!/bin/sh

function makeDirectory() 
{ 
	if [[ ! -d "$1" ]]
	then 
		mkdir $1
		echo "The directory $1 is created."
	else
		echo "The directory $1 already exists." 
	fi
}
function moveFiles()
{
	if [[ ! -f "$1" ]]
	then
		echo "The files $1 does not exist."
	else
		mv $1 $2
		echo "The files $1 are moved."
	fi
}

	export -f makeDirectory
	export -f moveFiles

	makeDirectory include
	makeDirectory src
	makeDirectory out

	moveFiles *.cpp ./src
	moveFiles *.c ./src
	moveFiles *.hpp ./include
	moveFiles *.h ./include