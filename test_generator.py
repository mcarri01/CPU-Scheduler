import random

def generate_test(num):
	for i in range(num):
		rand = random.randint(1,100)
		print("%d %d %d %d" % (rand, rand, rand, rand))




generate_test(20);