#!/bin/sh

echo "My Student Account is $USER" | cat - > HW2.txt
echo "Today's Date is 09/22/2020" | cat - >> HW2.txt
echo "" | cat - >> HW2.txt

grep '[[:blank:]][[:blank:]][[:blank:]]^*[A-Z0-9]' Part_01.txt | cat - >> HW2.txt
echo "" | cat - >> HW2.txt

count1=$(grep -c '[\.,;]$' Part_01.txt)
echo 'There are' $count1 'lines that end with ".", ",", or ";".' | cat - >> HW2.txt
echo "" | cat - >> HW2.txt

count2=$(grep -c -w 'owner' Part_01.txt)
echo 'There are' $count2 'lines that contain the word "owner".' | cat - >> HW2.txt
echo "" | cat - >> HW2.txt

count3=$(grep -c 'owner' Part_01.txt)
count4=$(expr $count3 - $count2)
echo 'There are' $count4 'lines that contain the string "owner" as part of a longer word.' | cat - >> HW2.txt
echo "" | cat - >> HW2.txt

count5=$(grep -E -w -o '[A-Za-z]{8}' Part_01.txt | wc -l)
echo 'There are' $count5 'words that are 8 characters long.' | cat - >> HW2.txt
echo "" | cat - >> HW2.txt

count6=$(grep -E -w -o '[A-Za-z]{12}' Part_01.txt | wc -l)
echo 'There are' $count6 'words that are 12 characters long.' | cat - >> HW2.txt
echo "" | cat - >> HW2.txt

average1=$(awk -F, 'NR > 1 {sum += $4} END {print sum/(NR-1)}' Part_02.csv)
echo 'The average number of reactions is' $average1'.' | cat - >> HW2.txt
echo "" | cat - >> HW2.txt

average2=$(awk -F, 'NR > 1 {sum += $5} END {print sum/(NR-1)}' Part_02.csv)
echo 'The average number of comments is' $average2'.' | cat - >> HW2.txt
echo "" | cat - >> HW2.txt

average3=$(awk -F, 'NR > 1 {sum += $6} END {print sum/(NR-1)}' Part_02.csv)
echo 'The average number of shares is' $average3'.' | cat - >> HW2.txt
echo "" | cat - >> HW2.txt

average4=$(awk -F, 'NR > 1 {sum += $7} END {print sum/(NR-1)}' Part_02.csv)
echo 'The average number of likes is' $average4'.' | cat - >> HW2.txt
echo "" | cat - >> HW2.txt

awk -F, 'NR > 1 {a[$2]++} END {for(k in a) print "There are " a[k] " instances of the " k " status type.\n"}' Part_02.csv | cat - >> HW2.txt
