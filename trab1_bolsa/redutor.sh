#!/bin/bash
companias=(ULTRAPAR WEGE3 LREN3 GRND3 SBSP3 JSLG3 CIEL3 NATU3 VIVT4 LEVE3)

echo "Headerzao daora" >dados.txt

for i in ${companias[*]}
do
	grep -i "$i" COTAHIST_A2015.TXT >>dados.txt
done

echo "Fim" >>dados.txt