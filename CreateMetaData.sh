function AddMeta 
{
	IFS=- 
	read -ra ADDR <<< "$1"

	declare -i tLen=${#ADDR[@]}
	declare -i tEnd=0

    if [ "$tLen" -gt "3" ]
	then
		echo "Improperly formatted filename: $1"
	 	return
	fi


	if [ "$tLen" -eq "1" ]
	then
		echo "Warning - No Meta Data for: $1"
	 	return
	fi

	tEnd=$(($tLen - 1))

	newFilename=""
	description="" 

	# use for loop read all nameservers
	for (( i=0; i<${tLen}; i++ ));
	do
	  if [ "$i" -eq "0" ]
	  then
	  	newFilename=${ADDR[$i]}
	  	continue
	  fi

	  if [ "$i" -eq "$tEnd" ]
	  then
	  	newFilename="$newFilename-${ADDR[$i]}"
	  	continue
	  fi
	  description="${ADDR[$i]}"
	done

	newFilename=$(basename $newFilename)
	# echo $newFilename
    
	# remove spaces for | for storage
	storagename=${newFilename//[[:space:]]/}
	echo Storage Name: $storagename

    # check if name exist in map
	if [ ${filenamemap[$storagename]+_} ]; 
	  then
        echo Exist in map. Increment usage: [ $storagename , ${filenamemap[$storagename]} ]
        filenamemap[$storagename]=$(( ${filenamemap[$storagename]} + 1 ))
      else
        echo "Doesn't exist. Start Usage at 1"
        filenamemap[$storagename]=1
	fi


	superNewFilename=$newFilename"_${filenamemap[$storagename]}"
	echo "NewFilename $superNewFilename"
	echo "Description $description"
}

declare -a filenamemap

IFS=
bmwedit=/Users/bijan/joshScripts/Project/GNU/CLI/bwfmetaedit
#find . -name "*.[wW][aA][vV]" -type f -exec AddMetaData {} \;
files=`find . -name "*.[wW][aA][vV]" -type f`

echo Enter: [ Song , ${filenamemap[Song]} ]
for i in $files
do
	echo Pre: [ Song , ${filenamemap[Song]} ]
    AddMeta $(basename $i)
    echo Post: [ Song , ${filenamemap[Song]} ]

done
echo Exit: [ Song , ${filenamemap[Song]} ]


AddMeta "Song- What in the ;work isthe m ;m, riavmo 'm rea9m 43]kvr - p.wav"
AddMeta "stuff- What in the ;work isthe m ;m, riavmo 'm rea9m 43]kvr - p.wav"
unset filenamemap





