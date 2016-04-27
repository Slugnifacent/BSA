if [ "$#" -ne 2 ]; then
   		    open -a "Sublime Text 2.app"
   else
	   for arg in "$@"
		do
			open -a "Sublime Text 2.app" "$arg"
		done
fi