#!bin/bash

a=(1 2 4 8 16 2 1 1 1 8)
b=(2 2 2 2 4 1 1 1 4 4)
c=(0 0 0 0 0 1 1 1 0 0)
d=(0 0 0 0 0 0 0 1 1 8)
e=(1 1 1 1 1 1 1 1 2 2)
f=(0 0 0 0 0 0 0 2 0 0)
n=(50 100 200 400 800 1000 2000 4000 8000 16000 32000 64000 128000)

gcc -Wall -o calcula_recorrencia_14_0026363 calcula_recorrencia_14_0026363.c

for i in {0..9} 
do
	for j in {0..3}
	do
		for k in {0..12} 
		do
			for l in {0..9}
			do
				./calcula_recorrencia_14_0026363 ${a[$i]} ${b[$i]} ${c[$i]} ${d[$i]} ${e[$i]} ${f[$i]} $j ${n[$k]}
			done
		done
	done
done

python plot.py