# Kuracheva Ksenia, ИУ7-13Б
# V14: Пятиугольная правильная призма, вписанная в цилиндр (даны параметры цилиндра R, h, найти V, Sполн, Sбок).
import math

print('\tInput area <-> Data\n')
r_cylinder = float(input("The radius of the cylinder is: "))
while r_cylinder <= 0:
    print('\nError occurred. Parameter must be greater than 0.')
    r_cylinder = float(input("The radius of the cylinder is: "))

h_cylinder = float(input("The height of the cylinder is: "))
while h_cylinder <= 0:
    print('\nError occurred. Parameter must be greater than 0.')
    h_cylinder = float(input("The height of the cylinder is: "))

s_prism_base = math.sin(360 / 5 * math.pi / 180) * r_cylinder * 5  # Square of the prism base
v_prism = h_cylinder * s_prism_base  # Valume of the prism

a_prism = math.sqrt(2 * r_cylinder ** 2 - 2 * r_cylinder ** 2 * math.cos(72 * math.pi / 180))  # Side of the prism base
s_prism_side_area = a_prism * h_cylinder * 5  # Square of the prism side area

s_prism = s_prism_side_area + s_prism_base  # Square of the prism

print('\n\tOutput area <-> Result\n')
print('The volume of the prism is {:.5g}.'.format(v_prism))
print('The square of the prism is {:.5g}.'.format(s_prism))
print('The square of the side area of the prism is {:.5g}.'.format(s_prism_side_area))
