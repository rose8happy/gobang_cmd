//
// Created by i1i on 11/8/24.
//
#include "GobangBoard.h"

GobangBoard::GobangBoard() : ruleChecker(board, chess), ai(board,chess)
{
    // ��ʼ����������Ϊ 0���գ�
    board = std::vector<std::vector<int>>(boardSize, std::vector<int>(boardSize, 0));
}

[[noreturn]] void GobangBoard::run() {
    while (true) {
        // ��ʼ��Ϸ
        start();
        // һ����Ϸ�У������̣�����ָ��
        while (gameStarted) {
            drawBoard();
            mousePressEvent();
        }
        printf("Do you want to play again? (y/n): ");
        char choice;
        std::cin >> choice;
        if (choice == 'n' || choice == 'N') break;
    }
}

void GobangBoard::start()
{
    boardReset();
    // ʹ������豸��ȡ�������
    std::random_device rd;
    std::mt19937 gen(rd());  // ʹ�� Mersenne Twister ����
    std::uniform_int_distribution<> dis(1, 2);  // ���� 1 �� 2 �ķֲ�
    // ���� 1 �� 2 �������
    chess = dis(gen);
    ai.chess = 3-chess;
    if (chess == 1) {
        isMyTurn = true;
        printf("��ʾ You play black and go first\n");
    } else if (chess==2)
    {
        isMyTurn = false;
        printf("��ʾ You play white and go second\n");
        aiPlay();
    }
    printf("�������⽡��ʼ��Ϸ\n");
    getchar();
}

// void GobangBoard::onSurrenderButtonClicked()
// {
//     if (gameStarted) winOrLose(false);
// }

void GobangBoard::boardReset()
{
    for (int i=0;i<boardSize;i++)
    {
        std::fill(board[i].begin(), board[i].end(), 0);
    }
    drawBoard();
}

void GobangBoard::winOrLose(bool win)
{
    if (win)
    {
        printf("��ʾYou win!\n");
    } else
    {
        printf("��ʾYou lose!\n");
    }
    gameStarted = false;
    isMyTurn = false;
    printf("�������⽡���¿�ʼ\n");
    getchar();
}

void GobangBoard::drawBoard() {
    system("cls");   //����
    printf("  ");
    for (int i=0;i<boardSize;i++) {
        printf("%d ", i+1);
    }
    printf("\n");
    for (int i=0;i<boardSize;i++) {
        printf("%c ", 'A'+i);
        for (int j=0;j<boardSize;j++) {
            if (i==pre_white.first && j==pre_white.second) {
                printf("��");
            } else if (i==pre_black.first && j==pre_black.second) {
                printf("��");
            }else if (board[i][j] == 1) {
                printf("��");
            } else if (board[i][j] == 2) {
                printf("��");
            } else if (board[i][j] == 0) {
                if (i==0 && j==0) printf("��");
                else if (i==boardSize-1 && j==boardSize-1) printf("��");
                else if (i==0 && j==boardSize-1) printf("��");
                else if (i==boardSize-1 && j==0) printf("��");
                else if (i==0) printf("��");
                else if (j==0) printf("��");
                else if (i==boardSize-1) printf("��");
                else if (j==boardSize-1) printf("��");
                else printf("��");
            }
        }
        printf("\n");
    }
    // ��ʾִ��
    printf("����Ҫ�µ�λ��������(A,1)\n");
}

void GobangBoard::mousePressEvent() {
    std::string input;
    std::getline(std::cin, input);

    if (input.size() < 3 || input[0] < 'A' || input[0] >= 'A' + boardSize || input[2] < '1' || input[2] > '9') {
        printf("��ʾ Invalid input. Please enter in format (A,1).\n");
        return;
    }

    int row = input[0] - 'A';
    int col = input[2] - '1';

    if (!isMyTurn) return;

    // ���Լ��Ļغϲ�������
    if (col >= 0 && col < boardSize && row >= 0 && row < boardSize && board[row][col] == 0) {
        // �����֣���ֹ����
        ruleChecker.chess = chess;
        if (ruleChecker.isForbiddenMove(row, col))
        {
            printf( "��ʾYou can not put a piece here!\n");
            return;
        }
        isMyTurn = false; // ��AI��������û�true
        board[row][col] = chess;  // ʾ�����������
        if (chess == 1) pre_black = {row, col};
        else pre_white = {row, col};
        drawBoard();  // ���½�����ʾ
        int res = ruleChecker.judge();
        if (res)
        {
            winOrLose(res==chess);
            return;
        }

        aiPlay();
    }
}

void GobangBoard::aiPlay()
{
    ai.chess=chess;
    auto bestMove = ai.getBestMove();
    if (chess == 1) pre_white = bestMove;
    else pre_black = bestMove;
    int ai_chess = 3-chess;
    board[bestMove.first][bestMove.second] = ai_chess;
    drawBoard();
    int res = ruleChecker.judge();
    if (res)
    {
        winOrLose(res==chess);
        return;
    }
    isMyTurn = true;
}

