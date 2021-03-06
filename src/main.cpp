#include<string.h>
#include<fstream>
#include"graph/graph.cpp"


//Defining a method to clear the terminal while in the program
#ifdef linux
#define clear() std::system("clear")
#else
#define clear() system("CLS")
#endif

void test(int argc, char *argv[]);

int main(int argc, char *argv[]) {

    clear();

    if(argc <= 2) {
        std::cerr << "[ERROR]: Not enough paramaters!\n"<< std::endl;
        return 0;
    }

    if(strcmp(argv[1],"test") == 0) {
        test(argc,argv);
        return 0;
    }

    if(argc <= 3) {
        std::cerr << "[ERROR]: Not enough paramaters!\n"<< std::endl;
        return 0;
    }

    int n = std::atoi(argv[1]);
    
    std::ofstream results("results.txt");

    for(int i = 3; i < argc; i++) {

        clock_t sum;

        for (int j = 0 ; j < n ; j++ ) {

            if(strstr(argv[i],".txt") == NULL) {
                std::cerr << "[ERROR]: \"" << argv[2] << "\" is not a text file path \n"<< std::endl;
                return 0;
            }

            Graph* teste = new Graph(argv[i]);
            
            clock_t time = clock();
            if(strcmp(argv[2],"kruskal") == 0) 
                teste->kruskal();
            else if(strcmp(argv[2],"dfs") == 0)
                teste->depth_first_search();
            time = clock() - time;

            sum += time;
        }

        double total_time = ((double)sum)/((CLOCKS_PER_SEC/1000));

        results << "Graph[" << i - 3 << "]" << std::endl;
        results << "path: " << argv[i] << std::endl;
        results << "Total time: " << total_time << "s" << std::endl;
        results << "Average time : " << total_time/n << "s" << std::endl;

    }

    return 0;
}

//Function only used for outside testing 
void test(int argc, char *argv[]) {

    Graph* teste = new Graph(argv[2]);
    teste->print();

    counter n;

    if(strcmp(argv[3],"kruskal") == 0) 
        n = teste->kruskal();
    else 
        n = teste->depth_first_search();
    

    std::cout << "\nnum_cycles = " << n << std::endl;
}

