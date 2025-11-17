# ! usr/bin/bash

# extract the content (-xzf extract, ...
tar -xzf solver_output.tar.gz

# rename output file
filename=$(tar -tf solver_output.tar.gz | head -n 1) #tar -tf could show table of contents if existing, we only want filename
mv "$filename" solver_output.txt

# redirect cleaned data pipe into csv file, put /g to replace all characters in line (-v for inverse)
grep -v "^it\|^---" solver_output.txt | sed 's/ | /,/g' | sed 's/ //g' > solver_data.csv

# create compressed archive (-czf stands fo create, gzip, file) 
tar -czf processed_outputs.tar.gz solver_output.txt solver_data.csv 


# which iterations are unstable?
echo 'unstable iterations:'
awk 'BEGIN {FS=","} $4 >= 1.0 {print $0}' solver_data.csv

# lines with positive exponent, warning Message with back-reference (-E for Extended Regex without special character)
grep 'e+' solver_data.csv | sed -E 's/^([0-9]+),.*/Warning: High residual change at iteration \1./' > instability_report.txt

# Matlab script
awk 'BEGIN {FS=","; print "solver_data = ["} {print "    " $1 " " $2 " " $3 " " $4 ";"} END {print "];"}' solver_data.csv > load_data.m
 
