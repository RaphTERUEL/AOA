#!/bin/bash

#
echo -e "[BEGIN]\n"

#
dir="data_runs_sujet5"
#mkdir -p $dir $dir"/logs"
rm -r $dir
#
#cp "plot_sujet5_all.gp" $dir


#Compiler optimizations
for opt in O2 O3
do
    #
    echo "Running with flag: "$opt

    #
    #mkdir -p $dir"/"$opt
    mkdir -p $dir"/"$opt""

    #
    #cp "plot_sujet5.gp" $dir"/"$opt

    #Going through sobel code variants

    #Compile variant
  	make "baseline" O=$opt

    for variant in `seq 88 4 92`;
    do
	#
    	echo -e "\tVariant: "$variant

      ./sujet5  $variant >> $dir"/"$opt"/sujet5_gcc.txt"
      ./sujet5_icc $variant >> $dir"/"$opt"/sujet5_icc.txt"

    done

    #
    #cd $dir"/"$opt

    #Generate the plot
    #gnuplot -c "plot_sujet5.gp" > "plot_"$opt".png"


done

mkdir -p $dir"/03_native"
mkdir -p $dir"/03_xHost"

make "baseline_xHost"

for variant in `seq 88 4 252`;
do
#
echo -e "\tVariant: "$variant

#Compile variant
./sujet5 $variant >> $dir"/03_native/sujet5_gcc.txt"
./sujet5_icc $variant >> $dir"/03_xHost/sujet5_icc.txt"

done
#
#cd $dir

#gnuplot -c "plot_sujet5_all.gp" > "plot_all.png"

#cd ..

#
make clean

#
echo -e "\n[DONE]"
