/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   enemy.h
 * Author: rcc
 *
 * Created on March 9, 2020, 10:50 AM
 */

#ifndef ENEMY_H
#define ENEMY_H

class Enemy{
private:
    static const int length = 8;
    static const int height = 100; // any less than 100 and the code fails for some reason.
    char enemy[length][height] = {"{'$','$','$','$','$','$','$','$'}"
                                      "{'$','$','$','$','$','$','$','$'}"
                                      "{'$','$','$','$','$','$','$','$'}"};
    
public:
    Enemy(int l, int h){
//        length = l;
//        height = h;
//        char enemy[length][height] = {"{'$','$','$','$','$','$','$','$'}"
//                                      "{'$','$','$','$','$','$','$','$'}"
//                                      "{'$','$','$','$','$','$','$','$'}"};
    }
    ~Enemy();
//    void SetLength(int l){
//        length = l;
//    }
//    
//    void SetHeight(int h){
//        height = h;
//    }
//    
void ShowRows(char enemy[length][height]){
    for (int i = 0; i < length; i++){
     std::cout << enemy[i][height];
    }
    std::cout << '\n';
}

void ShowFull (char enemy[length][height]){
    for (int i = 0; i < height; i++){
        for(int j = 0; j < length; j++){
            ShowRows(enemy);        
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void ShiftRowsR(char enemy[length][height]){
    char last = enemy[length-1][height];
    for (int i = length; i > 0; i--){
        enemy[i][height] = enemy[i-1][height];
        enemy[0][height]=last;
    }
}
void ShiftRowsL(char enemy[length][height]){
    char first = enemy[0][height];
    for (int i = 0; i < length; i++){
        enemy[i-1][height] = enemy[i][height];
        enemy[length-1][height] = first;
    }
}
void ShiftRowsD (char enemy[length][height]){
    for (int i = 0; i < length; i++){
        for (int j = 0; j < height; i++){
            enemy[j][height] = enemy[j+1][height];
        }
    }
    std::cout << '\n' << '\n';
}
};

#endif /* ENEMY_H */

