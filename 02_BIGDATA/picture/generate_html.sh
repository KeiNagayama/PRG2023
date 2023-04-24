#!/bin/sh

# constants
img=$1
base=$(basename ${1%.*})
rgb=rgb/"$base".rgb
html=html/"$base".html

# extract colors
if [ ! -f "$rgb" ]; then
    echo "Extracting colors..."
    cat $img | convert - -depth 8 txt:- | awk '{if(NR>1)print $3}' | awk '{cnt[$1]++}END{for(i in cnt)print i,cnt[i]}' | sort -k2gr > $rgb
fi

hex=$(head -n24 $rgb | awk '{if(NR>1) printf ","; printf $1}')

# generate html
cat html/template.html | sed -e "s|IMG-PATH|../$img|" -e "s/HEX-CODES/$hex/" > $html

# open html in default browser
explorer.exe $(wslpath -w $html)