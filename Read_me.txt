# MultiThread_sort
--Creates an array with random numbers and sorts it,
--dividing the array into subarrays and have each thread sort a subarray.

Takes arguments: -numbers=X -threads=Y -seed=Z -mode=I
where: 
  -numbers=X is the numbers of random numbers to be sorted
  -threads=Y is the number of threads used (1,2,4 or 8)
  -seed=Z    is the random number generator seed 
  -mode=I    is the mode(1,2 or 3):
                  1-> Absolute synchronization sort (only 1 thread reads and writes each time)
                  2-> Medium synchronization sort (All threads can read but only 1 thread writes each time)
                  3-> No synchronization sort (No synchronization between threads)
Example Run:
Initial array = { 83 86 77 15 93 35 86 92 49 21 62 27 90 59 63 26 40 26 72 36 11 68 67 29 82 30 62 23 67 35 29 2 22 58 69 67 93 56 11 42 29 73 21 19 84 37 98 24 15 70 }
Division array = { 0 6 12 18 24 30 36 42 }

--ABSOLUTE SYNCHRONIZATION SORT--
Thread[1] : sort[ 6 to 11 ]
Thread[3] : sort[ 18 to 23 ]
Thread[2] : sort[ 12 to 17 ]
Thread[0] : sort[ 0 to 5 ]
Thread[4] : sort[ 24 to 29 ]
Thread[5] : sort[ 30 to 35 ]
Thread[6] : sort[ 36 to 41 ]
Thread[7] : sort[ 42 to 49 ]

Successfully waited for all threads to finish...
Inital Array before Merge = { 15 35 77 83 86 93 21 27 49 62 86 92 26 26 40 59 63 90 11 29 36 67 68 72 23 30 35 62 67 82 2 22 29 58 67 69 11 29 42 56 73 93 15 19 21 24 37 70 84 98 }
Merging initial array...

Sorted array = { 2 11 11 15 15 19 21 21 22 23 24 26 26 27 29 29 29 30 35 35 36 37 40 42 49 56 58 59 62 62 63 67 67 67 68 69 70 72 73 77 82 83 84 86 86 90 92 93 93 98 }
Time elapsed = 1871000 ns
Program Terminated!

-------------------------------------------
Initial array = { 83 86 77 15 93 35 86 92 49 21 62 27 90 59 63 26 40 26 72 36 11 68 67 29 82 30 62 23 67 35 29 2 22 58 69 67 93 56 11 42 29 73 21 19 84 37 98 24 15 70 }
Division array = { 0 6 12 18 24 30 36 42 }

--MEDIUM SYNCHRONIZATION SORT--
Thread[0] : sort[ 0 to 5 ]
Thread[1] : sort[ 6 to 11 ]
Thread[2] : sort[ 12 to 17 ]
Thread[3] : sort[ 18 to 23 ]
Thread[5] : sort[ 30 to 35 ]
Thread[4] : sort[ 24 to 29 ]
Thread[6] : sort[ 36 to 41 ]
Thread[7] : sort[ 42 to 49 ]

Successfully waited for all threads to finish...
Inital Array before Merge = { 15 35 77 83 86 93 21 27 49 62 86 92 26 26 40 59 63 90 11 29 36 67 68 72 23 30 35 62 67 82 2 22 29 58 67 69 11 29 42 56 73 93 15 19 21 24 37 70 84 98 }
Merging initial array...

Sorted array = { 2 11 11 15 15 19 21 21 22 23 24 26 26 27 29 29 29 30 35 35 36 37 40 42 49 56 58 59 62 62 63 67 67 67 68 69 70 72 73 77 82 83 84 86 86 90 92 93 93 98 }
Time elapsed = 725000 ns
Program Terminated!

-------------------------------------------
Initial array = { 83 86 77 15 93 35 86 92 49 21 62 27 90 59 63 26 40 26 72 36 11 68 67 29 82 30 62 23 67 35 29 2 22 58 69 67 93 56 11 42 29 73 21 19 84 37 98 24 15 70 }
Division array = { 0 6 12 18 24 30 36 42 }

--NO SYNCHRONIZATION SORT--
Thread[0] : sort[ 0 to 5 ]
Thread[1] : sort[ 6 to 11 ]
Thread[3] : sort[ 18 to 23 ]
Thread[2] : sort[ 12 to 17 ]
Thread[4] : sort[ 24 to 29 ]
Thread[5] : sort[ 30 to 35 ]
Thread[6] : sort[ 36 to 41 ]
Thread[7] : sort[ 42 to 49 ]

Successfully waited for all threads to finish...
Inital Array before Merge = { 15 35 77 83 86 93 21 27 49 62 86 92 26 26 40 59 63 90 11 29 36 67 68 72 23 30 35 62 67 82 2 22 29 58 67 69 11 29 42 56 73 93 15 19 21 24 37 70 84 98 }
Merging initial array...

Sorted array = { 2 11 11 15 15 19 21 21 22 23 24 26 26 27 29 29 29 30 35 35 36 37 40 42 49 56 58 59 62 62 63 67 67 67 68 69 70 72 73 77 82 83 84 86 86 90 92 93 93 98 }
Time elapsed = 677000 ns
Program Terminated!

-------------------------------------------Initial array = { 83 86 77 15 93 35 86 92 49 21 62 27 90 59 63 26 40 26 72 36 11 68 67 29 82 30 62 23 67 35 29 2 22 58 69 67 93 56 11 42 29 73 21 19 84 37 98 24 15 70 }
Division array = { 0 6 12 18 24 30 36 42 }

--ABSOLUTE SYNCHRONIZATION SORT--
Thread[1] : sort[ 6 to 11 ]
Thread[3] : sort[ 18 to 23 ]
Thread[2] : sort[ 12 to 17 ]
Thread[0] : sort[ 0 to 5 ]
Thread[4] : sort[ 24 to 29 ]
Thread[5] : sort[ 30 to 35 ]
Thread[6] : sort[ 36 to 41 ]
Thread[7] : sort[ 42 to 49 ]

Successfully waited for all threads to finish...
Inital Array before Merge = { 15 35 77 83 86 93 21 27 49 62 86 92 26 26 40 59 63 90 11 29 36 67 68 72 23 30 35 62 67 82 2 22 29 58 67 69 11 29 42 56 73 93 15 19 21 24 37 70 84 98 }
Merging initial array...

Sorted array = { 2 11 11 15 15 19 21 21 22 23 24 26 26 27 29 29 29 30 35 35 36 37 40 42 49 56 58 59 62 62 63 67 67 67 68 69 70 72 73 77 82 83 84 86 86 90 92 93 93 98 }
Time elapsed = 1871000 ns
Program Terminated!

-------------------------------------------
Initial array = { 83 86 77 15 93 35 86 92 49 21 62 27 90 59 63 26 40 26 72 36 11 68 67 29 82 30 62 23 67 35 29 2 22 58 69 67 93 56 11 42 29 73 21 19 84 37 98 24 15 70 }
Division array = { 0 6 12 18 24 30 36 42 }

--MEDIUM SYNCHRONIZATION SORT--
Thread[0] : sort[ 0 to 5 ]
Thread[1] : sort[ 6 to 11 ]
Thread[2] : sort[ 12 to 17 ]
Thread[3] : sort[ 18 to 23 ]
Thread[5] : sort[ 30 to 35 ]
Thread[4] : sort[ 24 to 29 ]
Thread[6] : sort[ 36 to 41 ]
Thread[7] : sort[ 42 to 49 ]

Successfully waited for all threads to finish...
Inital Array before Merge = { 15 35 77 83 86 93 21 27 49 62 86 92 26 26 40 59 63 90 11 29 36 67 68 72 23 30 35 62 67 82 2 22 29 58 67 69 11 29 42 56 73 93 15 19 21 24 37 70 84 98 }
Merging initial array...

Sorted array = { 2 11 11 15 15 19 21 21 22 23 24 26 26 27 29 29 29 30 35 35 36 37 40 42 49 56 58 59 62 62 63 67 67 67 68 69 70 72 73 77 82 83 84 86 86 90 92 93 93 98 }
Time elapsed = 725000 ns
Program Terminated!

-------------------------------------------
Initial array = { 83 86 77 15 93 35 86 92 49 21 62 27 90 59 63 26 40 26 72 36 11 68 67 29 82 30 62 23 67 35 29 2 22 58 69 67 93 56 11 42 29 73 21 19 84 37 98 24 15 70 }
Division array = { 0 6 12 18 24 30 36 42 }

--NO SYNCHRONIZATION SORT--
Thread[0] : sort[ 0 to 5 ]
Thread[1] : sort[ 6 to 11 ]
Thread[3] : sort[ 18 to 23 ]
Thread[2] : sort[ 12 to 17 ]
Thread[4] : sort[ 24 to 29 ]
Thread[5] : sort[ 30 to 35 ]
Thread[6] : sort[ 36 to 41 ]
Thread[7] : sort[ 42 to 49 ]

Successfully waited for all threads to finish...
Inital Array before Merge = { 15 35 77 83 86 93 21 27 49 62 86 92 26 26 40 59 63 90 11 29 36 67 68 72 23 30 35 62 67 82 2 22 29 58 67 69 11 29 42 56 73 93 15 19 21 24 37 70 84 98 }
Merging initial array...

Sorted array = { 2 11 11 15 15 19 21 21 22 23 24 26 26 27 29 29 29 30 35 35 36 37 40 42 49 56 58 59 62 62 63 67 67 67 68 69 70 72 73 77 82 83 84 86 86 90 92 93 93 98 }
Time elapsed = 677000 ns
Program Terminated!

-------------------------------------------
