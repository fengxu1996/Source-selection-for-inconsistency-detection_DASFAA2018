goto EE
#source #hash #select_source p1_T p2_T #tuple/book SelectedSrcs/random_SelectedSrcs
100     100    10             80   40   10000 
--1.#records:10000--100000
--2.#top-k:5 10 20 40 60 80 100
--3.#src: 100-2000
--4.#hash:10-1000
:EE
book_Generator.exe 200 100 1 100 100 book SelectedSrcs

goto E1

mh_generator.exe 200 2 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 2 5 100 100 book SelectedSrcs
ComputeCov.exe 200 2 5 100 100 book SelectedSrcs
ComputeCov.exe 200 2 5 100 100 book random_SelectedSrcs
Greedy.exe 200 2 5 100 100 book random_SelectedSrcs

mh_generator.exe 200 3 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 3 5 100 100 book SelectedSrcs
ComputeCov.exe 200 3 5 100 100 book SelectedSrcs
ComputeCov.exe 200 3 5 100 100 book random_SelectedSrcs
Greedy.exe 200 3 5 100 100 book random_SelectedSrcs

mh_generator.exe 200 4 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 4 5 100 100 book SelectedSrcs
ComputeCov.exe 200 4 5 100 100 book SelectedSrcs
ComputeCov.exe 200 4 5 100 100 book random_SelectedSrcs
Greedy.exe 200 4 5 100 100 book random_SelectedSrcs

mh_generator.exe 200 5 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 5 5 100 100 book SelectedSrcs
ComputeCov.exe 200 5 5 100 100 book SelectedSrcs
ComputeCov.exe 200 5 5 100 100 book random_SelectedSrcs
Greedy.exe 200 5 5 100 100 book random_SelectedSrcs

mh_generator.exe 200 6 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 6 5 100 100 book SelectedSrcs
ComputeCov.exe 200 6 5 100 100 book SelectedSrcs
ComputeCov.exe 200 6 5 100 100 book random_SelectedSrcs
Greedy.exe 200 6 5 100 100 book random_SelectedSrcs

mh_generator.exe 200 7 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 7 5 100 100 book SelectedSrcs
ComputeCov.exe 200 7 5 100 100 book SelectedSrcs
ComputeCov.exe 200 7 5 100 100 book random_SelectedSrcs
Greedy.exe 200 7 5 100 100 book random_SelectedSrcs

mh_generator.exe 200 8 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 8 5 100 100 book SelectedSrcs
ComputeCov.exe 200 8 5 100 100 book SelectedSrcs
ComputeCov.exe 200 8 5 100 100 book random_SelectedSrcs
Greedy.exe 200 8 5 100 100 book random_SelectedSrcs

mh_generator.exe 200 9 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 9 5 100 100 book SelectedSrcs
ComputeCov.exe 200 9 5 100 100 book SelectedSrcs
ComputeCov.exe 200 9 5 100 100 book random_SelectedSrcs
Greedy.exe 200 9 5 100 100 book random_SelectedSrcs
:E1

mh_generator.exe 200 1 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 1 5 100 100 book SelectedSrcs
ComputeCov.exe 200 1 5 100 100 book SelectedSrcs
ComputeCov.exe 200 1 5 100 100 book random_SelectedSrcs
Greedy.exe 200 1 5 100 100 book random_SelectedSrcs

mh_generator.exe 200 10 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 10 5 100 100 book SelectedSrcs
ComputeCov.exe 200 10 5 100 100 book SelectedSrcs
ComputeCov.exe 200 10 5 100 100 book random_SelectedSrcs
Greedy.exe 200 10 5 100 100 book random_SelectedSrcs


mh_generator.exe 200 20 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 20 5 100 100 book SelectedSrcs
ComputeCov.exe 200 20 5 100 100 book SelectedSrcs
ComputeCov.exe 200 20 5 100 100 book random_SelectedSrcs
Greedy.exe 200 20 5 100 100 book random_SelectedSrcs


mh_generator.exe 200 30 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 30 5 100 100 book SelectedSrcs
ComputeCov.exe 200 30 5 100 100 book SelectedSrcs
ComputeCov.exe 200 30 5 100 100 book random_SelectedSrcs
Greedy.exe 200 30 5 100 100 book random_SelectedSrcs

mh_generator.exe 200 40 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 40 5 100 100 book SelectedSrcs
ComputeCov.exe 200 40 5 100 100 book SelectedSrcs
ComputeCov.exe 200 40 5 100 100 book random_SelectedSrcs
Greedy.exe 200 40 5 100 100 book random_SelectedSrcs

mh_generator.exe 200 50 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 50 5 100 100 book SelectedSrcs
ComputeCov.exe 200 50 5 100 100 book SelectedSrcs
ComputeCov.exe 200 50 5 100 100 book random_SelectedSrcs
Greedy.exe 200 50 5 100 100 book random_SelectedSrcs

mh_generator.exe 200 60 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 60 5 100 100 book SelectedSrcs
ComputeCov.exe 200 60 5 100 100 book SelectedSrcs
ComputeCov.exe 200 60 5 100 100 book random_SelectedSrcs
Greedy.exe 200 60 5 100 100 book random_SelectedSrcs

mh_generator.exe 200 70 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 70 5 100 100 book SelectedSrcs
ComputeCov.exe 200 70 5 100 100 book SelectedSrcs
ComputeCov.exe 200 70 5 100 100 book random_SelectedSrcs
Greedy.exe 200 70 5 100 100 book random_SelectedSrcs

mh_generator.exe 200 80 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 80 5 100 100 book SelectedSrcs
ComputeCov.exe 200 80 5 100 100 book SelectedSrcs
ComputeCov.exe 200 80 5 100 100 book random_SelectedSrcs
Greedy.exe 200 80 5 100 100 book random_SelectedSrcs

mh_generator.exe 200 90 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 90 5 100 100 book SelectedSrcs
ComputeCov.exe 200 90 5 100 100 book SelectedSrcs
ComputeCov.exe 200 90 5 100 100 book random_SelectedSrcs
Greedy.exe 200 90 5 100 100 book random_SelectedSrcs


mh_generator.exe 200 100 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 100 5 100 100 book SelectedSrcs
ComputeCov.exe 200 100 5 100 100 book SelectedSrcs
ComputeCov.exe 200 100 5 100 100 book random_SelectedSrcs
Greedy.exe 200 100 5 100 100 book random_SelectedSrcs



mh_generator.exe 200 200 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 200 5 100 100 book SelectedSrcs
ComputeCov.exe 200 200 5 100 100 book SelectedSrcs
ComputeCov.exe 200 200 5 100 100 book random_SelectedSrcs
Greedy.exe 200 200 5 100 100 book random_SelectedSrcs

mh_generator.exe 200 300 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 300 5 100 100 book SelectedSrcs
ComputeCov.exe 200 300 5 100 100 book SelectedSrcs
ComputeCov.exe 200 300 5 100 100 book random_SelectedSrcs
Greedy.exe 200 300 5 100 100 book random_SelectedSrcs

mh_generator.exe 200 400 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 400 5 100 100 book SelectedSrcs
ComputeCov.exe 200 400 5 100 100 book SelectedSrcs
ComputeCov.exe 200 400 5 100 100 book random_SelectedSrcs
Greedy.exe 200 400 5 100 100 book random_SelectedSrcs

mh_generator.exe 200 500 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 500 5 100 100 book SelectedSrcs
ComputeCov.exe 200 500 5 100 100 book SelectedSrcs
ComputeCov.exe 200 500 5 100 100 book random_SelectedSrcs
Greedy.exe 200 500 5 100 100 book random_SelectedSrcs

mh_generator.exe 200 600 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 600 5 100 100 book SelectedSrcs
ComputeCov.exe 200 600 5 100 100 book SelectedSrcs
ComputeCov.exe 200 600 5 100 100 book random_SelectedSrcs
Greedy.exe 200 600 5 100 100 book random_SelectedSrcs

mh_generator.exe 200 700 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 700 5 100 100 book SelectedSrcs
ComputeCov.exe 200 700 5 100 100 book SelectedSrcs
ComputeCov.exe 200 700 5 100 100 book random_SelectedSrcs
Greedy.exe 200 700 5 100 100 book random_SelectedSrcs


mh_generator.exe 200 800 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 800 5 100 100 book SelectedSrcs
ComputeCov.exe 200 800 5 100 100 book SelectedSrcs
ComputeCov.exe 200 800 5 100 100 book random_SelectedSrcs
Greedy.exe 200 800 5 100 100 book random_SelectedSrcs

mh_generator.exe 200 900 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 900 5 100 100 book SelectedSrcs
ComputeCov.exe 200 900 5 100 100 book SelectedSrcs
ComputeCov.exe 200 900 5 100 100 book random_SelectedSrcs
Greedy.exe 200 900 5 100 100 book random_SelectedSrcs

mh_generator.exe 200 1000 5 100 100 book SelectedSrcs
book_MH_Greedy.exe 200 1000 5 100 100 book SelectedSrcs
ComputeCov.exe 200 1000 5 100 100 book SelectedSrcs
ComputeCov.exe 200 1000 5 100 100 book random_SelectedSrcs
Greedy.exe 200 1000 5 100 100 book random_SelectedSrcs
