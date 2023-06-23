#/* Disciplina: Programacao Concorrente */
#/* Prof.: Silvana Rossetto */
#/* Módulo 4 - Laboratório: 7 */
#/* Codigo: "Calcular a serie que gera o valor de Pi */

from threading import Thread
from threading import Lock
import math
import time

#classe variavel compartilhada
class Variavel():
    def __init__(self):
        self.valor = 0.0
        self.lock = Lock()

    def incrementa(self, i):
        self.lock.acquire()
        self.valor += i
        self.lock.release()

    def getValor(self):
        return self.valor

#classe da thread
class IncrementaThread(Thread):
    def __init__(self, id, variavel, n, salto):
        super().__init__()
        self.threadid = id
        self.variavel = variavel
        self.n = n
        self.salto = salto

    def run(self):
       ap = 0.0
       for pos in range(self.n-self.threadid, -1, -self.salto):
            #aproximação de pi  
            sg = int(math.pow(-1, pos))
            cq = (2.0 * pos) + 1.0
            res = sg * (1.0 / cq)
            ap += res
       self.variavel.incrementa(ap)

#fluxo principal
if __name__ == '__main__':
    
    # Recebe as dimensoes a trabalhar
    Ni = int(input("Entre com N para aproximação: "))
    Nt = int(input("Entre com o número de threads: "))



    #cria variavel compartilhada
    var = Variavel()
    #cria e dispara as threads
    threads = [IncrementaThread(i, var, Ni, Nt) for i in range(Nt)]

    #Marca o inicio do tempo de execução
    start = time.time()
    
    for thread in threads:
        thread.start()
    #aguarda as threads terminarem
    for thread in threads:
        thread.join()
    #Marca o fim do tempo de execução
    end = time.time()

    #exibe o valor da variavel
    print("N =", Ni, ", Threads =", Nt)
    print("Pi =", math.pi, ", Aproximação =", 4.0*var.getValor())
    print("Diferença absoluta =", abs(math.pi - 4.0*var.getValor()))
    print("Tempo de execução : ", end - start )
    print("Terminou")       
