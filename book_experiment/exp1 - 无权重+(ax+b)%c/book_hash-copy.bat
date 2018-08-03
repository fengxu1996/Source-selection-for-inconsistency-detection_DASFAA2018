goto EE
#source #hash #select_source p1_T p2_T #tuple/book SelectedSrcs/random_SelectedSrcs
100     100    10             80   40   10000 
--1.#records:10000--100000
--2.#top-k:3 10 20 40 60 80 100
--3.#src: 100-2000
--4.#hash:10-1000
:EE
book_Generator.exe 200 null null 100 100 book


mh_generator.exe 200 1 3 100 100 book SelectedSrcs (ax+b)c
book_MH_Greedy.exe 200 1 3 100 100 book SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 1 3 100 100 book SelectedSrcs
ComputeCov.exe 200 1 3 100 100 book random_SelectedSrcs
Greedy.exe 200 1 3 100 100 book null null add_random_weight_NO
ComputeCov.exe 200 1 3 100 100 book greedy_SelectedSrcs
book_BF_Greedy.exe 200 null 3 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 null 3 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO


mh_generator.exe 200 10 3 100 100 book SelectedSrcs (ax+b)c
book_MH_Greedy.exe 200 10 3 100 100 book SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 10 3 100 100 book SelectedSrcs
ComputeCov.exe 200 10 3 100 100 book random_SelectedSrcs
Greedy.exe 200 10 3 100 100 book null null add_random_weight_NO
ComputeCov.exe 200 10 3 100 100 book greedy_SelectedSrcs
book_BF_Greedy.exe 200 null 3 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 null 3 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO


mh_generator.exe 200 20 3 100 100 book SelectedSrcs (ax+b)c
book_MH_Greedy.exe 200 20 3 100 100 book SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 20 3 100 100 book SelectedSrcs
ComputeCov.exe 200 20 3 100 100 book random_SelectedSrcs
Greedy.exe 200 20 3 100 100 book null null add_random_weight_NO
ComputeCov.exe 200 20 3 100 100 book greedy_SelectedSrcs
book_BF_Greedy.exe 200 null 3 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 null 3 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO


mh_generator.exe 200 30 3 100 100 book SelectedSrcs (ax+b)c
book_MH_Greedy.exe 200 30 3 100 100 book SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 30 3 100 100 book SelectedSrcs
ComputeCov.exe 200 30 3 100 100 book random_SelectedSrcs
Greedy.exe 200 30 3 100 100 book null null add_random_weight_NO
ComputeCov.exe 200 30 3 100 100 book greedy_SelectedSrcs
book_BF_Greedy.exe 200 null 3 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 null 3 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO



mh_generator.exe 200 40 3 100 100 book SelectedSrcs (ax+b)c
book_MH_Greedy.exe 200 40 3 100 100 book SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 40 3 100 100 book SelectedSrcs
ComputeCov.exe 200 40 3 100 100 book random_SelectedSrcs
Greedy.exe 200 40 3 100 100 book null null add_random_weight_NO
ComputeCov.exe 200 40 3 100 100 book greedy_SelectedSrcs
book_BF_Greedy.exe 200 null 3 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 null 3 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO


mh_generator.exe 200 50 3 100 100 book SelectedSrcs (ax+b)c
book_MH_Greedy.exe 200 50 3 100 100 book SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 50 3 100 100 book SelectedSrcs
ComputeCov.exe 200 50 3 100 100 book random_SelectedSrcs
Greedy.exe 200 50 3 100 100 book null null add_random_weight_NO
ComputeCov.exe 200 50 3 100 100 book greedy_SelectedSrcs
book_BF_Greedy.exe 200 null 3 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 null 3 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO


mh_generator.exe 200 60 3 100 100 book SelectedSrcs (ax+b)c
book_MH_Greedy.exe 200 60 3 100 100 book SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 60 3 100 100 book SelectedSrcs
ComputeCov.exe 200 60 3 100 100 book random_SelectedSrcs
Greedy.exe 200 60 3 100 100 book null null add_random_weight_NO
ComputeCov.exe 200 60 3 100 100 book greedy_SelectedSrcs
book_BF_Greedy.exe 200 null 3 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 null 3 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO



mh_generator.exe 200 70 3 100 100 book SelectedSrcs (ax+b)c
book_MH_Greedy.exe 200 70 3 100 100 book SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 70 3 100 100 book SelectedSrcs
ComputeCov.exe 200 70 3 100 100 book random_SelectedSrcs
Greedy.exe 200 70 3 100 100 book null null add_random_weight_NO
ComputeCov.exe 200 70 3 100 100 book greedy_SelectedSrcs
book_BF_Greedy.exe 200 null 3 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 null 3 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO


mh_generator.exe 200 80 3 100 100 book SelectedSrcs (ax+b)c
book_MH_Greedy.exe 200 80 3 100 100 book SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 80 3 100 100 book SelectedSrcs
ComputeCov.exe 200 80 3 100 100 book random_SelectedSrcs
Greedy.exe 200 80 3 100 100 book null null add_random_weight_NO
ComputeCov.exe 200 80 3 100 100 book greedy_SelectedSrcs
book_BF_Greedy.exe 200 null 3 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 null 3 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO



mh_generator.exe 200 90 3 100 100 book SelectedSrcs (ax+b)c
book_MH_Greedy.exe 200 90 3 100 100 book SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 90 3 100 100 book SelectedSrcs
ComputeCov.exe 200 90 3 100 100 book random_SelectedSrcs
Greedy.exe 200 90 3 100 100 book null null add_random_weight_NO
ComputeCov.exe 200 90 3 100 100 book greedy_SelectedSrcs
book_BF_Greedy.exe 200 null 3 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 null 3 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO



mh_generator.exe 200 100 3 100 100 book SelectedSrcs (ax+b)c
book_MH_Greedy.exe 200 100 3 100 100 book SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 100 3 100 100 book SelectedSrcs
ComputeCov.exe 200 100 3 100 100 book random_SelectedSrcs
Greedy.exe 200 100 3 100 100 book null null add_random_weight_NO
ComputeCov.exe 200 100 3 100 100 book greedy_SelectedSrcs
book_BF_Greedy.exe 200 null 3 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO
ComputeCov.exe 200 null 3 100 100 book bf_greedy_SelectedSrcs (ax+b)c add_random_weight_NO

