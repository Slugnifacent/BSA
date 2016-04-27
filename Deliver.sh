IFS=""
Folder="/Users/bijan/Dropbox/Hard Data Audio DropBox Folder"
findCommand="$(find $Folder  -type f \(  ! -iname ".DS_Store" \)  )"
filename="/Users/bijan/joshScripts/Email.txt"
printf "%s\n" "Hey guys," " " "I've uploaded a few sounds to dropbox:" " "> "$filename"
printf "%s\n" $findCommand " " >> "$filename"
printf "%s\n" "The spreadsheet has been updated to reflect these changes as well." " "  >> "$filename"
printf "%s\n" "Cheers." >> "$filename"
sublime $filename