import time
start_time = time.time()


def factorial(n):
    fact = 1
    for i in range (1, num+1):
        fact = fact*i

num = 100

for i in range(100000):
   factorial(num)
print("--- %s seconds ---" % (time.time() - start_time))