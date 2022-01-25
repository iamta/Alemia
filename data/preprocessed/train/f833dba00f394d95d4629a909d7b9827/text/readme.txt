Exercitiul2/
sanity check:
rulare: ./oets-par 10 2 2
output: 
  0  0  1  1  1  2  3  5  6  8
  0  0  1  1  1  2  3  5  6  8
Sorted correctly

stress test:
Output correct on intensive test

timp rulare pt N=100000:
1 thread: real    0m24.259s
2 threaduri: real    0m16.983s
4 threaduri:  real    0m9.709s


Exercitiul4/
sanity check:
rulare: ./mergeSort-par 16 2 1
output: 
  0  1  2  2  4  4  5  6  6  7  7  8  9 12 13 15
  0  1  2  2  4  4  5  6  6  7  7  8  9 12 13 15
Sorted correctly

stress test:
Output correct on intensive test

timp rulare pt N=33554432:
1 thread: real    0m14.977s
2 threaduri: real    0m10.438s
4 threaduri: real    0m8.883s

