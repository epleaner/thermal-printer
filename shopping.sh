#!/bin/sh
# psl - print shopping list on thermal printer

# graphic pathname
GRAPHIC=./images/pic.png

# text list pathname
LIST=./test.txt

# print custom header
./png2escpos/png2escpos $GRAPHIC | /usr/bin/lpr -PUSB_Thermal_Printer_LOCAL -o raw

# set reverse character printing
./escposf/escposf -r 1 >/tmp/out.txt

# set 2Xw font
./escposf/escposf -t 3 >>/tmp/out.txt

echo "*SHOPPING LIST*" >>/tmp/out.txt

# turn off reverse
./escposf/escposf -r 0 >>/tmp/out.txt

# select normal font
./escposf/escposf -t 0 >>/tmp/out.txt

# save each line to /tmp file (avoids multiple print jobs)
while read line; do
    echo "$line" >>/tmp/out.txt
done < $LIST

# reset to normal font
./escposf/escposf -t 0 >>/tmp/out.txt

# print the list
/usr/bin/lpr -PUSB_Thermal_Printer_LOCAL -o raw /tmp/out.txt

# clean up
/bin/rm -fr /tmp/out.txt
