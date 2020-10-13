#!/bin/bash

echo "My Student Account is $USER" | cat - > HW1.txt
echo "Today's Date is 09/15/2020" | cat - >> HW1.txt
echo "" | cat - >> HW1.txt

pwd | cat - >> HW1.txt
echo "" | cat - >> HW1.txt

head words | cat - >> HW1.txt
echo "" | cat - >> HW1.txt

tail words | cat - >> HW1.txt
echo "" | cat - >> HW1.txt

grep -iw pumpkin words | cat - >> HW1.txt
echo "" | cat - >> HW1.txt

wc -l < words | cat - >> HW1.txt
echo "" | cat - >> HW1.txt

head words | cat - > toSort.txt
tail words | cat - >> toSort.txt
grep pumpkin words | cat - >> toSort.txt
sort toSort.txt | cat - >> HW1.txt
