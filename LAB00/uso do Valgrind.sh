valgrind ./a.out <1.in> 1.meu // apenas um arquivo

//  varios arquivos
for((i=1; i<21; i=i+1))
do valgrind ./a.out <ins/$i.in> $i.meu;
done;
