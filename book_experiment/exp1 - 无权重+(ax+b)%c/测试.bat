
book_Generator.exe 200 null null 100 100 book


mh_generator.exe 200 100 1 100 100 book SelectedSrcs (ax+b)%c
book_MH_Greedy.exe 200 100 1 100 100 book SelectedSrcs (ax+b)%c add_random_weight_NO
ComputeCov.exe 200 100 1 100 100 book SelectedSrcs
ComputeCov.exe 200 100 1 100 100 book random_SelectedSrcs
Greedy.exe  200 100 1 100 100 book null null add_random_weight_NO
ComputeCov.exe 200 100 1 100 100 book greedy_SelectedSrcs 
book_BF_Greedy.exe 200 null 1 100 100 book bf_greedy_SelectedSrcs (ax+b)%c add_random_weight_NO
ComputeCov.exe 200 null 1 100 100 book bf_greedy_SelectedSrcs (ax+b)%c add_random_weight_NO

pause