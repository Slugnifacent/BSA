Directory="/Users/bijan/Desktop/SD2Files"
mkdir $Directory
results=$(find . -name "*.[sS][dD]2" -type f -exec cp {} $Directory \; -exec printf "%s\n" {} \; > /Users/bijan/Desktop/SD2Files/locations.txt )

