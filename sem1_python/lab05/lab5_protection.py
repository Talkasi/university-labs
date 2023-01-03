eps = float(input("Enter eps: "))
x = float(input("Enter x: "))

n = 1
t_current = -x
s = t_current
while abs(t_current) > eps:
    n += 1
    t_current = -t_current * x / n
    s += t_current

print("\nSum is {:.7g}, it was computed by {:g} iteration(s).".format(s, n))
