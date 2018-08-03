goto EE
#source #hash #select_source p1_T p2_T #tuple/book SelectedSrcs/random_SelectedSrcs
100     100    10             80   40   10000 
--1.#records:10000--100000
--2.#top-k:5 10 20 40 60 80 100
--3.#src: 100-2000
--4.#hash:10-1000
:EE
book_Generator.exe 200 null null 100 100 book


mh_generator.exe 200 100 1 100 100 book SelectedSrcs (ax+b)c
book_MH_Greedy.exe 200 100 1 100 100 book SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 100 1 100 100 book SelectedSrcs
ComputeCov.exe 200 100 1 100 100 book random_SelectedSrcs
Greedy.exe  200 100 1 100 100 book null null add_random_weight_NO
ComputeCov.exe 200 100 1 100 100 book greedy_SelectedSrcs 
book_BF_Greedy.exe 200 null 1 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 null 1 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO



mh_generator.exe 200 100 2 100 100 book SelectedSrcs (ax+b)c
book_MH_Greedy.exe 200 100 2 100 100 book SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 100 2 100 100 book SelectedSrcs
ComputeCov.exe 200 100 2 100 100 book random_SelectedSrcs
Greedy.exe  200 100 2 100 100 book null null add_random_weight_NO
ComputeCov.exe 200 100 2 100 100 book greedy_SelectedSrcs 
book_BF_Greedy.exe 200 null 2 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 null 2 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO



mh_generator.exe 200 100 3 100 100 book SelectedSrcs (ax+b)c
book_MH_Greedy.exe 200 100 3 100 100 book SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 100 3 100 100 book SelectedSrcs
ComputeCov.exe 200 100 3 100 100 book random_SelectedSrcs
Greedy.exe  200 100 3 100 100 book null null add_random_weight_NO
ComputeCov.exe 200 100 3 100 100 book greedy_SelectedSrcs 
book_BF_Greedy.exe 200 null 3 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 null 3 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO



mh_generator.exe 200 100 4 100 100 book SelectedSrcs (ax+b)c
book_MH_Greedy.exe 200 100 4 100 100 book SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 100 4 100 100 book SelectedSrcs
ComputeCov.exe 200 100 4 100 100 book random_SelectedSrcs
Greedy.exe  200 100 4 100 100 book null null add_random_weight_NO
ComputeCov.exe 200 100 4 100 100 book greedy_SelectedSrcs 
book_BF_Greedy.exe 200 null 4 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 null 4 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO


mh_generator.exe 200 100 5 100 100 book SelectedSrcs (ax+b)c
book_MH_Greedy.exe 200 100 5 100 100 book SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 100 5 100 100 book SelectedSrcs
ComputeCov.exe 200 100 5 100 100 book random_SelectedSrcs
Greedy.exe  200 100 5 100 100 book null null add_random_weight_NO
ComputeCov.exe 200 100 5 100 100 book greedy_SelectedSrcs 
book_BF_Greedy.exe 200 null 5 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 null 5 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO

mh_generator.exe 200 100 6 100 100 book SelectedSrcs (ax+b)c
book_MH_Greedy.exe 200 100 6 100 100 book SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 100 6 100 100 book SelectedSrcs
ComputeCov.exe 200 100 6 100 100 book random_SelectedSrcs
Greedy.exe  200 100 6 100 100 book null null add_random_weight_NO
ComputeCov.exe 200 100 6 100 100 book greedy_SelectedSrcs 
book_BF_Greedy.exe 200 null 6 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 null 6 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO


mh_generator.exe 200 100 7 100 100 book SelectedSrcs (ax+b)c
book_MH_Greedy.exe 200 100 7 100 100 book SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 100 7 100 100 book SelectedSrcs
ComputeCov.exe 200 100 7 100 100 book random_SelectedSrcs
Greedy.exe  200 100 7 100 100 book null null add_random_weight_NO
ComputeCov.exe 200 100 7 100 100 book greedy_SelectedSrcs 
book_BF_Greedy.exe 200 null 7 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 null 7 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO

mh_generator.exe 200 100 8 100 100 book SelectedSrcs (ax+b)c
book_MH_Greedy.exe 200 100 8 100 100 book SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 100 8 100 100 book SelectedSrcs
ComputeCov.exe 200 100 8 100 100 book random_SelectedSrcs
Greedy.exe  200 100 8 100 100 book null null add_random_weight_NO
ComputeCov.exe 200 100 8 100 100 book greedy_SelectedSrcs 
book_BF_Greedy.exe 200 null 8 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 null 8 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO


mh_generator.exe 200 100 9 100 100 book SelectedSrcs (ax+b)c
book_MH_Greedy.exe 200 100 9 100 100 book SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 100 9 100 100 book SelectedSrcs
ComputeCov.exe 200 100 9 100 100 book random_SelectedSrcs
Greedy.exe  200 100 9 100 100 book null null add_random_weight_NO
ComputeCov.exe 200 100 9 100 100 book greedy_SelectedSrcs 
book_BF_Greedy.exe 200 null 9 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 null 9 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO


mh_generator.exe 200 100 10 100 100 book SelectedSrcs (ax+b)c
book_MH_Greedy.exe 200 100 10 100 100 book SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 100 10 100 100 book SelectedSrcs
ComputeCov.exe 200 100 10 100 100 book random_SelectedSrcs
Greedy.exe  200 100 10 100 100 book null null add_random_weight_NO
ComputeCov.exe 200 100 10 100 100 book greedy_SelectedSrcs 
book_BF_Greedy.exe 200 null 10 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 null 10 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO
