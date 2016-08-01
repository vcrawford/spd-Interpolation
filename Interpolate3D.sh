#! /bin/bash
# Interpolate 9 matrix1.txt matrix2.txt 

image_output="interpolate3D.png"
matrix_input1="matrix1-3D.txt"
matrix_input2="matrix2-3D.txt"
image_count=9

echo ""
echo "===GENERATING RANDOM MATRICES==="
#Generate random SPD matrices
python RandomSPD.py 3 $matrix_input1
python RandomSPD.py 3 $matrix_input2

#Run a sanity check for those matrices
./SanityCheck3D $matrix_input1 $matrix_input2

#Run the interpolation code to get MatrixOutput.xml
./RunInterpolation3D $image_count $matrix_input1 $matrix_input2

echo "Plotting..."

#Run the python graphing code
python PlotEllipsoidsFromMatrix.py

#display image
display $image_output

echo ""
