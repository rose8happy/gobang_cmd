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

    int boardSize = 15;        // ���̴�С (15x15)

    // �������飬0=�գ�1=���壬2=����
    std::vector<std::vector<int>> board;
    bool gameStarted = false;  // ���ڱ����Ϸ�Ƿ�ʼ
    bool isMyTurn = false; // �Ƿ��ֵ��Լ�����
    int chess = 1; // 1=���壬2=����
    GobangRuleChecker ruleChecker; // ���ֹ�������
    GobangAI ai;

    void mousePressEvent();
    void drawBoard();   // ��������
    void start();
    void boardReset();
    void winOrLose(bool win);
    void aiPlay();

};

#endif // GOBANGBOARD_H

