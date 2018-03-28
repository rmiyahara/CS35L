#!/bin/sh
#Ryan Miyahara
#UCID: 804858999
temp=`ls $1 -a`
total=`ls $1 -a | wc -l`
#The line above gives us the number of files we are working with
count=0
for i in $temp
do
    count=$((count+1))
    tempnum=`expr $total - $count`
    ggez=`ls $1 -a | tail -n $tempnum`
    #Make a new vairable containing all files beyond i
    if [ $tempnum -gt 0 ]
    then
	for j in $ggez
	do
	    if cmp -s $1/$i $1/$j
	    then #If they are the same
		rm $1/$j
		ln $1/$i $1/$j
	    fi
	done
    fi
done
