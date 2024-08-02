for((i=1; i<21; i=i+1))
do ./a.out <ins/$i.in> $i.meu;
diff $i.meu ins/$i.out
