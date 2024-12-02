//
// Created by i1i on 11/8/24.
//

#ifndef GOBANGBOARD_H
#define GOBANGBOARD_H

#include <random>
#include "GobangRuleChecker.h"
#include "GobangAI.h"
#include <vector>
#include <utility>
#include <iostream>

class GobangBoard {

public:
    GobangBoard();
    [[noreturn]] void run();
    std::pair<int, int> pre_black;
    std::pair<int, int> pre_white;

private:

    int boardSize = 15;        // 棋盘大小 (15x15)

    // 棋盘数组，0=空，1=黑棋，2=白棋
    std::vector<std::vector<int>> board;
    bool gameStarted = false;  // 用于标记游戏是否开始
    bool isMyTurn = false; // 是否轮到自己落子
    int chess = 1; // 1=黑棋，2=白棋
    GobangRuleChecker ruleChecker; // 禁手规则检查类
    GobangAI ai;

    void mousePressEvent();
    void drawBoard();   // 绘制棋盘
    void start();
    void boardReset();
    void winOrLose(bool win);
    void aiPlay();

};

#endif // GOBANGBOARD_H

