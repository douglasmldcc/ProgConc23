import math

if __name__ == '__main__':
        # Recebe as dimensoes a trabalhar
        N = int(input("Entre com N para aproximação: "))
        Nt = int(input("Entre com o número de threads: "))
        apx=0.0

        for i in range(N,-1,-1):
            sg = int(math.pow(-1, i))
            cq = (2.0 * i) + 1.0
            res = sg * (1.0 / cq)
            apx += res

        Pi = 4 * apx
        #exibe o valor da variavel
        print("N =", N)
        print("Pi =", math.pi, ", Aproximação =", Pi )
        print("Diferença absoluta =", abs(math.pi - Pi ))
        print("Terminou")     