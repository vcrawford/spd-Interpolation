#! /bin/bash
# Interpolate 9 matrix1.txt matrix2.txt 

image_output="interpolate.png"
matrix_input1="matrix1.txt"
matrix_input2="matrix2.txt"
image_count=9

#Run a sanity check for those matrices
./SanityCheck $matrix_input1 $matrix_input2

#Run the interpolation code to get MatrixOutput.xml
./RunInterpolation2D $image_count $matrix_input1 $matrix_input2

#Run the python graphing code
python PlotInterpolation.py interpolation.xml $image_output $image_count

echo "Plotting..."

#display image
display $image_output

