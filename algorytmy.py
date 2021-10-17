def recursion(x, n):

    if n == 1:
        return 0
    if n < 0:
        return -1
    else:
        return (x * recursion(x, n-1))

recursion(5, 3)