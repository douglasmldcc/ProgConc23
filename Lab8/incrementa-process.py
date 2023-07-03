#/* Prof.: Silvana Rossetto */
#/* Módulo 4 - Laboratório: 8 */
#/* Codigo: exemplo de uso de variavel compartilhada em Python */ 

from multiprocessing import Process
from threading import Lock

#classe variavel compartilhada
class Variavel():
    def __init__(self):
        self.valor = 0
        self.lock = Lock()

    def incrementa(self):
        self.lock.acquire()
        self.valor += 1
        self.lock.release()

    def getValor(self):
        return self.valor

#classe do processo
class Incrementa(Process):
    def __init__(self, id, variavel):
        super().__init__()
        self.procid = id
        self.variavel = variavel

    def run(self):
        print("Thread", self.procid)
        for _ in range(100000):
            self.variavel.incrementa()
        print("processo: ",  self.procid)
        print("variavel = ", var.getValor())        

#fluxo principal
if __name__ == '__main__':
    #cria variavel compartilhada
    var = Variavel()
    #cria e dispara os processos
    procs = [Incrementa(i, var) for i in range(2)]
    for p in procs:
        p.start()
    #aguarda os procs terminarem
    for p in procs:
        p.join()
    #exibe o valor da variavel
    print("main")
    print("variavel = ", var.getValor())        
