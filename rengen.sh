#!/usr/local/bin/bash
 
if [ $# != 1 ]
then 
    exit 1;
fi

count=1
while [ $count -le $1 ]
do 
    echo "$RANDOM"
    let "count +=1"
done
