**Laboratório 4**

Comunicação entre threads via memória compartilhada

**Programação Concorrente (ICP-361) 2023-1**

Prof. Silvana Rossetto

Aluno Douglas de Morais Lima - 117227656

#

# Atividade 1

1. A saída esperada é de 20000, dada a soma de cada thread.
2. Os valores foram, por algumas vezes, diferentes, isso ocorreu muito provavelmente porque as duas threads incrementaram ao mesmo tempo a mesma variável compartilhada, incrementando juntas mas computando apenas uma.
3. Sim, o programa apresenta condição de corrida, visto que além de entrar nas seções críticas, também incrementa a mesma variável.
4. Não, as threads separadamente incrementam até 10000, o valor que seria incrementado fica perdido após a thread perder a cpu.

doug@DESKTOP-LRESFVL:/mnt/c/Users/dougl/Documents/GitHub/ProgConc23/Lab4/Exemplos$ ./ex1

Thread : 0 esta executando...

Thread : 0 terminou!

Thread : 1 esta executando...

Thread : 1 terminou!

Valor de 'soma' = 20000

doug@DESKTOP-LRESFVL:/mnt/c/Users/dougl/Documents/GitHub/ProgConc23/Lab4/Exemplos$ ./ex1

Thread : 0 esta executando...

Thread : 1 esta executando...

Thread : 0 terminou!

Thread : 1 terminou!

Valor de 'soma' = 19682

# Atividade 2

1. Os valores impressos serão sempre os mesmos, pois,a sincronização por exclusão mútua garante que cada thread incremente a variável compartilhada com segurança, mesmo que ela perca a CPU outra thread não pode acessar aquela mesma variável.

doug@DESKTOP-LRESFVL:/mnt/c/Users/dougl/Documents/GitHub/ProgConc23/Lab4/Exemplos$ ./ex1a

Thread : 0 esta executando...

Thread : 1 esta executando...

Thread : 1 terminou!

Thread : 0 terminou!

Valor de soma = 200000

doug@DESKTOP-LRESFVL:/mnt/c/Users/dougl/Documents/GitHub/ProgConc23/Lab4/Exemplos$ ./ex1a

Thread : 0 esta executando...

Thread : 1 esta executando...

Thread : 0 terminou!

Thread : 1 terminou!

Valor de soma = 200000

doug@DESKTOP-LRESFVL:/mnt/c/Users/dougl/Documents/GitHub/ProgConc23/Lab4/Exemplos$ ./ex1a

Thread : 0 esta executando...

Thread : 1 esta executando...

Thread : 0 terminou!

Thread : 1 terminou!

Valor de soma = 200000

doug@DESKTOP-LRESFVL:/mnt/c/Users/dougl/Documents/GitHub/ProgConc23/Lab4/Exemplos$ ./ex1a

Thread : 0 esta executando...

Thread : 1 esta executando...

Thread : 0 terminou!

Thread : 1 terminou!

Valor de soma = 200000

# Atividade 3

1. A seção crítica do código se encontra no _public void inc() ,_ sabendo que é a função que incrementa a variável compartilhada. O valor final esperado de s, similar aos exemplos anteriores, seria de 20000.
2. Os valores impressos não tiveram consistência com o valor esperado, assim como nos exemplos anteriores em c, as threads estão acessando a mesma variável compartilhada sem nenhum tipo de exclusão mútua, ou seja, os valores estão sendo perdidos quando a thread perde CPU.

doug@DESKTOP-LRESFVL:/mnt/c/Users/dougl/Documents/GitHub/ProgConc23/Lab4/Exemplos$ java TIncrementoBase

Thread 0 iniciou!

Thread 1 iniciou!

Thread 1 terminou!

Thread 0 terminou!

Valor de s = 127465

doug@DESKTOP-LRESFVL:/mnt/c/Users/dougl/Documents/GitHub/ProgConc23/Lab4/Exemplos$ java TIncrementoBase

Thread 0 iniciou!

Thread 1 iniciou!

Thread 1 terminou!

Thread 0 terminou!

Valor de s = 126093

doug@DESKTOP-LRESFVL:/mnt/c/Users/dougl/Documents/GitHub/ProgConc23/Lab4/Exemplos$ java TIncrementoBase

Thread 1 iniciou!

Thread 0 iniciou!

Thread 0 terminou!

Thread 1 terminou!

Valor de s = 121455

## Atividade 4

1. Nesta rotina os valores impressos foram sempre os mesmo, além disso, foram sempre o valor esperado. Os valores foram incrementados corretamente nesta rotina por meio do _synchronized_ que, no java, faz o papel da exclusão mútua do lock mutex da linguagem C, sanando o problema da condição de corrida na criação da função que incrementa.

doug@DESKTOP-LRESFVL:/mnt/c/Users/dougl/Documents/GitHub/ProgConc23/Lab4/Exemplos$ java TIncrementoBase

Thread 0 iniciou!

Thread 1 iniciou!

Thread 0 terminou!

Thread 1 terminou!

Valor de s = 200000

doug@DESKTOP-LRESFVL:/mnt/c/Users/dougl/Documents/GitHub/ProgConc23/Lab4/Exemplos$ java TIncrementoBase

Thread 1 iniciou!

Thread 0 iniciou!

Thread 1 terminou!

Thread 0 terminou!

Valor de s = 200000

doug@DESKTOP-LRESFVL:/mnt/c/Users/dougl/Documents/GitHub/ProgConc23/Lab4/Exemplos$ java TIncrementoBase

Thread 1 iniciou!

Thread 0 iniciou!

Thread 1 terminou!

Thread 0 terminou!

Valor de s = 200000

doug@DESKTOP-LRESFVL:/mnt/c/Users/dougl/Documents/GitHub/ProgConc23/Lab4/Exemplos$ java TIncrementoBase

Thread 0 iniciou!

Thread 1 iniciou!

Thread 0 terminou!

Thread 1 terminou!

Valor de s = 200000
