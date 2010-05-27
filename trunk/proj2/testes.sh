#uso: ./testes.sh opcao numero_repeticoes argumentos
rm tempos

if test $1 -eq 1
then
  for ((i = 0; i < $2; i++))
  do
    ./client localhost $1 | tail -n 2 >> tempos
  done
elif test $1 -eq 2
then
  for ((i = 0; i < $2; i++))
  do
    ./client localhost $1 $3 | tail -n 2 >> tempos
  done
elif test $1 -eq 3
then
  for ((i = 0; i < $2; i++))
  do
    ./client localhost $1 | tail -n 2 >> tempos
  done
elif test $1 -eq 4
then
  for ((i = 0; i < $2; i++))
  do
    ./client localhost $1 $3 | tail -n 2 >> tempos
  done
elif test $1 -eq 5
then
  for ((i = 0; i < $2; i++))
  do
    ./client localhost $1 $3 $4 | tail -n 2 >> tempos
  done
elif test $1 -eq 6
then
  for ((i = 0; i < $2; i++))
  do
    ./client localhost $1 $3 | tail -n 2 >> tempos
  done
fi
