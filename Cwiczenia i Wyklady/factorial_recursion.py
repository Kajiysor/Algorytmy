import time
start_time = time.time()

def recur_factorial(n):
   if n == 1:
       return n
   else:
       return n*recur_factorial(n-1)

num = 100

for i in range(100000):
    recur_factorial(num)

print("--- %s seconds ---" % (time.time() - start_time))