#!/usr/bin/env python

import random

print ("500")
f = open('output.txt','w')

for i in range(1,250):
	a = random.randint(1,1000000)
	b = random.randint(1,1000000)

	n1 = len(str(a))
	n2 = len(str(b))

	print ('{} {}' .format(n1,n2))
	
	print ('{} {}' .format(a,b))

	print ('3')
	
	
	c = a*b

	f.write(str(c))
	f.write('\n')
	
for i in range(1,250):
	a = random.randint(1,1000000)
	b = random.randint(1,1000000)

	n1 = len(str(a))
	n2 = len(str(b))

	print ('{} {}' .format(n1,n2))

	print ('{} {}' .format(a,b))
	
	print ('4')

	c = a/b
	
	f.write('{}\n'.format(c))

f.close

