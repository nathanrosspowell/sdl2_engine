#!/usr/bin/env bash 
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# make.bash Authored by Nathan Ross Powell.
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Measure time.
starttime=$(date +%s)
# Make the folder if it's missing.
if [[ ! -d build ]]
then
    mkdir build 
    # If it was missing, run cmake.bash.
    bash cmake.bash
fi

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Push into cmake dir.
pushd build
# Run the actual make command.
make
popd
# Print out the time.
endtime=$(date +%s)
elapse=$(($endtime - $starttime))
echo Time Taken "$(($elapse / 60)):$(($elapse % 60))"
