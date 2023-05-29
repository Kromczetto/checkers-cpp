#include "Counter.h"
#include <fstream>
#include <filesystem>
#include <iostream>

Counter::Counter() {
    countedMoveBlack = 0;
    countedMoveWhite = 0;
    topS = 0; 
}

void Counter::inBlack() {
    countedMoveBlack++;
}

void Counter::inWhite() {
    countedMoveWhite++;
}


int Counter::returnCountedMoveBlack() {
    return countedMoveBlack;
}

int Counter::returnCountedMoveWhite() {
    return countedMoveWhite;
}



void Counter::saveScore() {
    std::string sciezkaCzarne = "score/score_czarne.txt";
    std::string sciezkaBiale = "score/score_biale.txt";


    std::filesystem::path sciezkaPlikuCzarne(sciezkaCzarne);
    std::filesystem::path sciezkaPlikuBiale(sciezkaBiale);


    if (!std::filesystem::exists(sciezkaPlikuCzarne.parent_path())) {
        std::filesystem::create_directories(sciezkaPlikuCzarne.parent_path());
    }

    if (!std::filesystem::exists(sciezkaPlikuBiale.parent_path())) {
        std::filesystem::create_directories(sciezkaPlikuBiale.parent_path());
    }

 

    std::ofstream plikCzarne(sciezkaCzarne);
    std::ofstream plikBiale(sciezkaBiale);


    if (plikCzarne.is_open() && plikBiale.is_open() ) {
        plikCzarne << countedMoveBlack << "\n";
        plikBiale << countedMoveWhite << "\n";
    
        plikCzarne.close();
        plikBiale.close();
   
    }
    else {
        std::cout << "Nie udalo sie zapisac" << std::endl;
    }
}
