import threading
import math

class AproxPi(threading.Thread):
    def __init__(self, id, salto, N):
        threading.Thread.__init__(self)
        self.id = id
        self.salto = salto
        self.N = N

    def run(self):
        ap = 0
        for i in range(self.N - self.id, -1, -self.salto):
            sg = int(math.pow(-1, i))
            cq = (2 * i) + 1
            res = sg * (1.0 / cq)
            ap += res
        GeraPi.Api += ap

class GeraPi:
    Api = 0

    @staticmethod
    def main():
        N = int(input("Entre com N para aproximação: "))
        Nt = int(input("Entre com o número de threads: "))
        threads = []

        for i in range(Nt):
            salto = Nt
            thread = AproxPi(i, salto, N)
            threads.append(thread)

        for thread in threads:
            thread.start()

        for thread in threads:
            thread.join()

        pi = 4 * GeraPi.Api
        print("N =", N, ", Threads =", Nt)
        print("Pi =", math.pi, ", Aproximação =", pi)
        print("Diferença absoluta =", abs(math.pi - pi))
        print("Terminou")

if __name__ == "__main__":
    GeraPi.main()