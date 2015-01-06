#!/bin/bash



add_regex_matches() {
    regex="$1"
    file="$2"
    date="$3"
    grep "$file" -e "$date" |\
     grep -E "$regex" |\
     sed 's/.*INFO:[ ]*\([0-9]*\) .*/\1/' |\
     paste -sd+ |\
     bc

}


pqact_totals() {

    pqact="$1"
    log="$2"
    date="$3"

    while read line
    do
        echo -n "$line"' '

        add_regex_matches "$line" "$log" "$date"



    done <<< "$(grep -F '^' "$pqact" | grep -v -e '^#' | uniq | sed 's/.*[\^]\(.*\)/\1/')"

}

add_pqact_totals() {

    pqact="$1"
    log="$2"
    date="$3"

    while read line
    do
 
       add_regex_matches "$line" "$log" "$date"



    done <<< "$(grep -F '^' "$pqact" | grep -v -e '^#' | uniq | sed 's/.*[\^]\(.*\)/\1/')" |\
        paste -sd+ |\
        bc

}


get_total() {
    file="$1"
    date="$2"
    grep "$file" -e "$date" |\
     grep -e "FNMOC\|CONDUIT\|NGRID\|HDS" |\
     sed 's/.*INFO:[ ]*\([0-9]*\) .*/\1/' |\
     paste -sd+ |\
     bc

}


