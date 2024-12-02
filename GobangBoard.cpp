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

        // һ����Ϸ�У������̣�����ָ��
        while (true) {
            drawBoard();
            mousePressEvent();
        }
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
    ai.chess = chess;
    if (chess == 1) {
        isMyTurn = true;
        printf("��ʾ You play black and go first\n");
    } else if (chess==2)
    {
        isMyTurn = false;
        printf("��ʾ You play white and go second\n");
        aiPlay();
    } else
    {
        printf("��ʾError");
    }
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
        printf("��ʾYou win!");
    } else
    {
        printf("��ʾYou lose!");
    }
    gameStarted = false;
    isMyTurn = false;
}

void GobangBoard::drawBoard() {
    system("cls");   //����
    for (int i=0;i<boardSize;i++) {
        printf("%d ", i+1);
    }
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
}

void GobangBoard::mousePressEvent() {
    char row_c = 0; int col_i = 0;
    scanf("%c %d", &row_c, &col_i);
    getchar();

    int col = col_i;
    int row = row_c - 'A';

    if (!isMyTurn) return;

    // ���Լ��Ļغϲ�������
    if (col >= 0 && col < boardSize && row >= 0 && row < boardSize && board[row][col] == 0) {
        // �����֣���ֹ����
        //ruleChecker.board = board;
        ruleChecker.chess = chess;
        if (ruleChecker.isForbiddenMove(row, col))
        {
            printf( "��ʾYou can not put a piece here!");
            return;
        }
        isMyTurn = false; // ��AI��������û�true
        board[row][col] = chess;  // ʾ�����������
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
    // ʹ��C++11�����������һ��1��2��֮�������ӳ�
    std::random_device rd;
    std::mt19937 gen(rd()); // ʹ���������������
    std::uniform_int_distribution<> dis(0, 1000); // ����1000��2000����������
    int delay = dis(gen); // ��ȡ����ӳ�
    // ʹ��QTimer�����ӳٵ���

    ai.chess=chess;
    auto bestMove = ai.getBestMove();
    int ai_chess = 3-chess;
    board[bestMove.first()][bestMove.second()] = ai_chess;
    drawBoard();
    int res = ruleChecker.judge();
    if (res)
    {
        winOrLose(res==chess);
        return;
    }
    isMyTurn = true;


}

