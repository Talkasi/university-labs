n = int(input("Enter n of the list: "))
l = [0] * n

for i in range(n):
    l[i] = int(input("Enter element #{:g}: ".format(i + 1)))

m_l = -1
m_st = -1
c_st = 0
c_l = 0
for i in range(1, n - 1):
    if l[i - 1] < l[i] > l[i + 1] or l[i - 1] > l[i] < l[i + 1]:
        if c_l == 0:
            c_st = i
        c_l += 1
    else:
        if m_l < c_l:
            m_l = c_l
            m_st = c_st
        c_l = 0
        c_s = -1

if m_l < c_l:
    m_l = c_l
    m_st = c_st

print("\nThe longest sequence is:")
for i in range(m_st, m_st + m_l):
    print("#{:g}: {:g}".format(i + 1, l[i]))
