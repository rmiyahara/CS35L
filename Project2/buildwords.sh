#!/bin/sh #Ryan Miyahara UCID: 804858999
#"<tr> <td>Eword</td> <td>Hword</td>"
#Extract the Hword

cat $1 | #Take in entire page
    grep -E "<tr>|<td>" | #Filter for all words
    sed "s/^ *//g" | #Delete all whitespace
    sed "/<tr>/,/<\/td>/g" | #Delete everything starting with <tr> and ending
    #with </td>
    sed "s/<td>//g" | #Delete starting <td>
    sed "s/<\/td>//g" | #Delete ending </td>

    tr '[:upper:]' '[:lower:]' | #Treat upper case as if it was lower case
    sed "s/<\/u>//g" |
    sed "s/<u>//g" | #Treat "<u>a</u>" as if it were "a"
    tr "\`" "\'" | #Treat ` as if it were '
    tr ' ' '\n' | #Treat words with ", " as seperate words
    tr -d ',' | #Delete the comma after ", " words
    grep "^[pkmnwlhaeiou']*$" | #Display only words with Hawaiian letters

    tr -d "^$" | #Delete empty lines
    sort -u >hwords #Sort the resulting list of words, removing any
    #duplicates
cat hwords
