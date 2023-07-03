import time

#funcao que sera executada de forma sequencial
def task(x):
    for i in range(20000000):
        pass
    return x ** 2

if __name__ == '__main__':
    start = time.time()
    for aux in range(10):
        result = task(aux)
        print(result)
        
    print('work took {} seconds'.format(time.time() - start))

