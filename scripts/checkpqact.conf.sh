#!/bin/bash

g() {
grep -E "$1" watchlog_20141102
}

while read line
do
#    echo -n "$line"' '
    matches=$(g "$line" | wc -l)


    if [[ "$matches" == "0" ]]
    then
        echo  "$line"
    fi

done <<< "$(grep -F '^' pqact.testy | grep -v -e '^#' | uniq | sed 's/.*[\^]\(.*\)/\1/')"






