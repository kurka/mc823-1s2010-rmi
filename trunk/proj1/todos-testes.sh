#uso: ./testes.sh numero_repeticoes id nota
rm tempos*

for j in 1 2 3 4 5 6
do
  if test $j -eq 1
  then
    for ((i = 0; i < $1; i++))
    do
      ./client localhost $j | tail -n 2 >> tempos$j
    done
  elif test $j -eq 2
  then
    for ((i = 0; i < $1; i++))
    do
      ./client localhost $j $2 | tail -n 2 >> tempos$j
    done
  elif test $j -eq 3
  then
    for ((i = 0; i < $1; i++))
    do
      ./client localhost $j | tail -n 2 >> tempos$j
    done
  elif test $j -eq 4
  then
    for ((i = 0; i < $1; i++))
    do
      ./client localhost $j $2 | tail -n 2 >> tempos$j
    done
  elif test $j -eq 5
  then
    for ((i = 0; i < $1; i++))
    do
      ./client localhost $j $2 $3 | tail -n 2 >> tempos$j
    done
  elif test $j -eq 6
  then
    for ((i = 0; i < $1; i++))
    do
      ./client localhost $j $2 | tail -n 2 >> tempos$j
    done
  fi
done

for ((i = 1; i <= 6; i++))
do
  cat tempos$i | grep SERVERTIME > stime$i
  cat tempos$i | grep TOTALTIME > ttime$i
done
