#uso: ./todos_testes.sh numero_repeticoes id nota
mkdir -p tempos
rm tempos/*

for j in 1 2 3 4 5 6
do
  if test $j -eq 1
  then
    for ((i = 0; i < $1; i++))
    do
      ./cliente.sh $j | tail -n 4 >> tempos/tempos$j
	  #~/Desktop/proj-mc823/client localhost $j | tail -n 2 >> tempos$j
    done
  elif test $j -eq 2
  then
    for ((i = 0; i < $1; i++))
    do
      ./cliente.sh $j $2 | tail -n 4 >> tempos/tempos$j
      #~/Desktop/proj-mc823/client localhost $j $2 | tail -n 2 >> tempos$j
    done
  elif test $j -eq 3
  then
    for ((i = 0; i < $1; i++))
    do
      ./cliente.sh $j | tail -n 4 >> tempos/tempos$j
      #~/Desktop/proj-mc823/client localhost $j | tail -n 2 >> tempos$j
    done
  elif test $j -eq 4
  then
    for ((i = 0; i < $1; i++))
    do
      ./cliente.sh $j $2 | tail -n 4 >> tempos/tempos$j
      #~/Desktop/proj-mc823/client localhost $j $2 | tail -n 2 >> tempos$j
    done
  elif test $j -eq 5
  then
    for ((i = 0; i < $1; i++))
    do
      ./cliente.sh $j $2 $3 | tail -n 4 >> tempos/tempos$j
      #~/Desktop/proj-mc823/client localhost $j $2 $3 | tail -n 2 >> tempos$j
    done
  elif test $j -eq 6
  then
    for ((i = 0; i < $1; i++))
    do
      ./cliente.sh $j $2 | tail -n 4 >> tempos/tempos$j
      #~/Desktop/proj-mc823/client localhost $j $2 | tail -n 2 >> tempos$j
    done
  fi
done

for ((i = 1; i <= 6; i++))
do
  cat tempos/tempos$i | grep SERVERTIME > tempos/stime$i
  cat tempos/tempos$i | grep TOTALTIME > tempos/ttime$i
done
