
#include "GUI.h"
#include "ChessGameConfig.h"
#include "ChessBoard.h"

namespace CIG
{
    bool CIG::ChessGameConfig::checkConstrains()
    {
        typedef unsigned long long U64;

        if(sizeof(U64) != 8)                    //����֮��, ��Ϊsizeof(U64)==8, �����ữ��һЩ����.
        {
            ostringstream oss;
            oss << "ϵͳ�ֳ���������ͬ. \n" << "sizeof(U64) = " << sizeof(U64) << " != 8";
            GUI::inform(oss.str(), true);
            return false;
        }

        return true;
    }

    float ChessGameConfig::TIME_LIMIT = -1;

    ChessGameConfig::ChessGameConfig(GAME_TYPE id)
    {
        switch(id)
        {
            case CIG::ERRROR:
                break;

            case CIG::DRAUGHTS:
                break;

            case CIG::CHINESE_CHESS:
                break;

            case CIG::GOBANG:
                INI_BOARD_WIDTH_LOG2 = 4;
                INI_BOARD_HEIGHT_LOG2 = 4;

                roundChessman = true;     // TO-DO
                namedChessman = false;

                markCrossByCircle = true; // TO-DO
                markCircleRadias = 1;// TO-DO

                additionalPointRadias = 3;       // TO-DO

                drawLineWhenDrawDot = true;       // TO-DO

                thetaOfXTop = 0;     // TO-DO
                thetaOfXY = 90;

                lengthOfLattticeX = 40;          // TO-DO
                lengthOfLattticeY = lengthOfLattticeX;
                borderWidth = lengthOfLattticeX;
                latticePenWidth = 2;

                OPERATIONS operationGraph[END][END + 1] =
                {
                    { NOMORE, NOMORE, NOMORE, NOMORE, NOMORE },
                    { ADD, NOMORE, NOMORE, NOMORE, NOMORE, },
                    { PUT, NOMORE, NOMORE, NOMORE, NOMORE, },
                    { NOMORE, NOMORE, NOMORE, NOMORE, NOMORE },
                    { END, NOMORE, NOMORE, NOMORE, NOMORE, },
                    { NOMORE, NOMORE, NOMORE, NOMORE, NOMORE },
                    { NOMORE, NOMORE, NOMORE, NOMORE, NOMORE },
                    { NOMORE, NOMORE, NOMORE, NOMORE, NOMORE },
                };

                memcpy(this->operationGraph, operationGraph, sizeof(operationGraph));

                bool BOARD_RANGE[1 << 4][1 << 4] =
                {
                    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
                    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
                    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
                    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
                    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
                    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
                    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
                    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
                    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
                    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
                    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
                    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
                    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
                    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
                    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
                };

                this->BOARD_RANGE = (bool **)memoryAlloc(sizeof(bool) * (1 << INI_BOARD_HEIGHT_LOG2) * (1 << INI_BOARD_HEIGHT_LOG2));
                memcpy(this->BOARD_RANGE, BOARD_RANGE, sizeof(BOARD_RANGE));

                CHESSMAN_TYPES INI_BOARD[2][1 << 4][1 << 4] =
                {
                    {
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN,  /*NOCHESSMAN*/CHESS, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                    },
                    {
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN,  /*NOCHESSMAN*/CHESS, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN,  /*NOCHESSMAN*/CHESS, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                        { NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, NOCHESSMAN, },
                    }
                };

                this->INI_BOARD = (CHESSMAN_TYPES ** *)memoryAlloc(sizeof(CHESSMAN_TYPES) * (PLAYER_NUMS[GOBANG]) * (1 << INI_BOARD_HEIGHT_LOG2) * (1 << INI_BOARD_HEIGHT_LOG2));
                memcpy(this->INI_BOARD, INI_BOARD, sizeof(INI_BOARD));

                break;

            case CIG::WESTEN_CHESS:
                break;

            case CIG::GO:
                break;

            case CIG::FLIGHT_CHESS:
                break;

            case CIG::MILITARY_CHESS:
                break;

            default:
                break;
        }

        this->assert(compileGUI());
    }

    bool ChessGameConfig::compileGUI()
    {
        /*************************************************************************
        ����������ʾ����
        ��ȷ�����Ӵ�С, �ڴ��ڳ�ʼ��ʱ�������̲������������ȷ���ͻ�����С.
        **************************************************************************/
        const long double PI = acos((long double) - 1.0);
        typedef float rad;
        rad theta1 = thetaOfXTop / 180.0 * PI,
            theta2 = thetaOfXY / 180.0 * PI;
        //֧�ֶ�̬��������, ���Բ��ǳ���, ���Ե���.
        Vx = PointOrVector_Float(lengthOfLattticeX * cos(theta1), lengthOfLattticeX * sin(theta1));
        Vy = PointOrVector_Float(lengthOfLattticeX * cos(theta1 + theta2), lengthOfLattticeX * sin(theta1 + theta2));
        {
            /*************************************************************************
            ��������Ƿ�̫����������̷Ų���.
            ���ߺͶԽ����ϵ�ͶӰ.
            **************************************************************************/
            if(roundInt(chessmanRect * Vx) > roundInt(Vx * Vx))
            {
                this->informError("������X����̫��");
            }

            if(roundInt(chessmanRect * Vy) > roundInt(Vy * Vy))
            {
                informError("������Y����̫��");
            }

            if(!roundChessman)
            {
                if(roundInt(chessmanRect * (Vx + Vy)) > roundInt((Vx + Vy) * (Vx + Vy)))
                {
                    informError("�����ڶԽ��߷���̫��");
                }

                if(roundInt(chessmanRect * (Vx - Vy)) > roundInt((Vx - Vy) * (Vx - Vy)))
                {
                    informError("�����ڸ��Խ��߷���̫��");
                }
            }
            else
            {
                if(roundInt(chessmanRect * chessmanRect / 2) > roundInt((Vx + Vy) * (Vx + Vy)))
                {
                    informError("�����ڶԽ��߷���̫��");
                }

                if(roundInt(chessmanRect * chessmanRect / 2) > roundInt((Vx - Vy) * (Vx - Vy)))
                {
                    informError("�����ڸ��Խ��߷���̫��");
                }
            }
        }
        LINE_DIRECTION.clear();
        LINE_DIRECTION.push_back(PointOrVector(1, 0));
        LINE_DIRECTION.push_back(PointOrVector(0, 1));
        //���ý��޳�ֵ
        boundsOfBoardRelatively[RIGHT] = -1E7;
        boundsOfBoardRelatively[LEFT] = 1E7;
        boundsOfBoardRelatively[TOP] = 1E7;
        boundsOfBoardRelatively[BOTTOM] = -1E7;
        coordinateOf00 = PointOrVector_Float(0, 0);         //�������λ��

        for(int i = 0; i < (1 << CIGRuleConfig::INI_BOARD_WIDTH_LOG2); ++i)
        {
            for(int j = 0; j < (1 << CIGRuleConfig::INI_BOARD_HEIGHT_LOG2); j++)
            {
                if(CIGRuleConfig::BOARD_RANGE[j][i])
                {
                    PointOrVector_Float temp = getGeometryCoordination(i, j);

                    if(temp.x[0] > boundsOfBoardRelatively[RIGHT])
                    {
                        boundsOfBoardRelatively[RIGHT] = temp.x[0];
                    }

                    if(temp.x[0] < boundsOfBoardRelatively[LEFT])
                    {
                        boundsOfBoardRelatively[LEFT] = temp.x[0];
                    }

                    if(temp.x[1] < boundsOfBoardRelatively[TOP])
                    {
                        boundsOfBoardRelatively[TOP] = temp.x[1];
                    }

                    if(temp.x[1] > boundsOfBoardRelatively[BOTTOM])
                    {
                        boundsOfBoardRelatively[BOTTOM] = temp.x[1];
                    }
                }
            }
        }

        //ȷ�����̾��εĴ�С.
        boundsOfBoard.x[0] = borderWidth * 2 + boundsOfBoardRelatively[RIGHT] - boundsOfBoardRelatively[LEFT];
        boundsOfBoard.x[1] = borderWidth * 2 + boundsOfBoardRelatively[BOTTOM] - boundsOfBoardRelatively[TOP];
        //ԭ�����¶�λ
        coordinateOf00 = PointOrVector_Float(borderWidth - boundsOfBoardRelatively[LEFT], borderWidth - boundsOfBoardRelatively[TOP]);
    }

}
