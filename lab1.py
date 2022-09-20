# Kuracheva Ksenia, ИУ7-13Б
# V14: Пятиугольная правильная призма, вписанная в цилиндр (даны параметры цилиндра R, h, найти V, Sполн, Sбок).
import math as m

print('\tInput area <-> Data\n')
r_cylinder = float(input("The radius of the cylinder is: "))
h_cylinder = float(input("The height of the cylinder is: "))

if r_cylinder <= 0 or h_cylinder <= 0:
	print('\nError occurred. Parameters must be greater than 0.')
else:
	s_prism_base = m.sin(360/5 * m.pi / 180) * r_cylinder * 5 							# Square of the prism base
	v_prism = h_cylinder * s_prism_base													# Valume of the prism

	a_prism = m.sqrt(2 * r_cylinder**2 - 2 * r_cylinder**2 * m.cos(72 * m.pi / 180))	# Side of the prism base
	s_prism_sdarea = a_prism * h_cylinder * 5											# Square of the prism side area

	s_prism = s_prism_sdarea + s_prism_base												# Square of the prism

	print('\n\tOutput area <-> Result\n')
	print('The volume of the prism is {:.5g}.'.format(v_prism))
	print('The square of the prism is {:.5g}.'.format(s_prism))
	print('The square of the side area of the prism is {:.5g}.'.format(s_prism_sdarea))
