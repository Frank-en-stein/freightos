import random
import string

ss = "A quick brownish fox jumps over a lazy dog erwin schrodinger\n"
chars = ''.join([ss for i in range(5000)])

for i in range(1000000):
    with open('sample/textfile' + str(i) + '.txt', 'w+') as f:
        f.write(chars)
    print(i)
