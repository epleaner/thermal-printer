#!/bin/sh
# ptest - test some escposf commands for a 58mm ESC/POS thermal printer
#
# note: modes are persistent between settings, not power-cycling
#
FILE=/tmp/out.txt

# initialize printer
escposf --i >/tmp/out.txt
# set 'normal' text
escposf --t 0 >/tmp/out.txt
echo "Normal text." >>/tmp/out.txt
echo "ABCDEFGHIJKLMNOPQRSTUVWXYZ" >>/tmp/out.txt
echo "abcdefghijklmnopqrstuvwxyz" >>/tmp/out.txt
echo "0123456789" >>/tmp/out.txt
echo "?&'-@';]{]}/,.$:%^\!&*)(_~" >>/tmp/out.txt

escposf --a 0 >>/tmp/out.txt
echo "Left aligned." >>/tmp/out.txt

escposf --a 1 >>/tmp/out.txt
echo "Centered." >>/tmp/out.txt

escposf --a 2 >>/tmp/out.txt
echo "Right aligned." >>/tmp/out.txt

escposf --a 0 >>/tmp/out.txt
escposf --r 1 >>/tmp/out.txt
echo "REVERSED TEXT" >>/tmp/out.txt

escposf --r 0 >>/tmp/out.txt
escposf --t 1 >>/tmp/out.txt
echo "2X high." >>/tmp/out.txt

escposf --r 1 >>/tmp/out.txt
escposf --t 1 >>/tmp/out.txt
echo "Reversed 2X high." >>/tmp/out.txt

escposf --r 0 >>/tmp/out.txt
escposf --t 2 >>/tmp/out.txt
echo "2X wide" >>/tmp/out.txt

escposf --r 1 >>/tmp/out.txt
escposf --t 2 >>/tmp/out.txt
echo "Reversed 2X" >>/tmp/out.txt

escposf --r 0 >>/tmp/out.txt
escposf --t 3 >>/tmp/out.txt
echo "Large text." >>/tmp/out.txt

escposf --r 1 >>/tmp/out.txt
escposf --t 3 >>/tmp/out.txt
echo "Reversed large" >>/tmp/out.txt

escposf --r 0 >>/tmp/out.txt
escposf --t 0 >>/tmp/out.txt
escposf --u 2 >>/tmp/out.txt
echo "Normal underlined." >>/tmp/out.txt

escposf --u 0 >>/tmp/out.txt
escposf --f 1 >>/tmp/out.txt
echo "Font B." >>/tmp/out.txt
echo "ABCDEFGHIJKLMNOPQRSTUVWXYZ" >>/tmp/out.txt
echo "abcdefghijklmnopqrstuvwxyz" >>/tmp/out.txt
echo "0123456789" >>/tmp/out.txt
echo "?&'-@';]{]}/,.$:%^\!&*)(_~" >>/tmp/out.txt

escposf --t 0 >>/tmp/out.txt
echo "End of test.\n\n\n" >>/tmp/out.txt

/usr/bin/lpr -Pthermie -o raw /tmp/out.txt
/bin/rm -fr /tmp/out.txt
