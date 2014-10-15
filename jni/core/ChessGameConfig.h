#ifndef __CHESS_GAME_CONFIG_H__
#define __CHESS_GAME_CONFIG_H__
using namespace std;
#include "utilities.h"
#include "Object.h"

namespace CIG
{
    //��Ϸ�����������
    static const int INI_CHESSMAN_GROUP_SIZE = 32;
    static const int INI_LATTICE_GROUP_SIZE = 32;
    static const int INT_BANNED_MOTION_SIZE = 16;
    static const int INT_MARKED_POINTS_SIZE = 32;
    static const int INT_BOARD_HISTORY_STACK_SIZE = 32;
    static const int INI_PLAYER_ARRAY_SIZE = 6;

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    class ChessGameConfig : public Object
    {
        public:
            /*************************************************************************
                ���ϵͳ����
            **************************************************************************/
            bool checkConstrains();

            ChessGameConfig(GAME_TYPE id);

            virtual ~ChessGameConfig();
            virtual bool compileGUI();
            inline virtual string toJSON()const;

            //��Ϸ�����������
            Board<bool, INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2> boardRange;
            Array < Board<CHESSMAN_TYPES, INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2>, PLAYER_NUM, -1 > iniBoards;
            OPERATIONS operationGraph[END][END + 1];

            //��Ϸ��������
            degree thetaOfXTop;                              //x��ĸ���
            degree thetaOfXY;                                  //�����ߵļн�
            float lengthOfLattticeX;
            float lengthOfLattticeY;
            float borderWidth;
            int latticePenWidth;

            bool markCrossByCircle;                          //�Ƿ�����·�����
            float markCircleRadias;
            bool drawLineWhenDrawDot;                  //�Ƿ���(������, ��һ��Ҫ����, ����㴦���пհ�)

            bool roundChessman;                             //����Բ��
            bool namedChessman;                            //����ӵ������
            PointOrVector_Float chessmanRect;       //���Ӿ���. ���뱣֤������������û���ص�
            map<CHESSMAN_TYPES, string> chessmanNames;

            vector<PointOrVector> LINE_DIRECTION;   // TO-DO �����ǳ�����, ������
            vector<Line> addtionalLines;
            vector<PointOrVector> additionalCircles;
            float additionalCircleRadias;
            vector<pair<PointOrVector, PointOrVector>> addtionalRectangles;
            vector<pair<PointOrVector, string>> additionalImages;

            //�ڲ����������
            PointOrVector_Float Vx;
            PointOrVector_Float Vy;
            float boundsOfBoardRelatively[4];
            enum
            {
                TOP, BOTTOM, LEFT, RIGHT
            };
            static PointOrVector_Float getGeometryCoordination(int x, int y);
            static PointOrVector_Float getGeometryCoordination(PointOrVector p);
            static PointOrVector getLogicalCoordination(PointOrVector_Float p);
            static PointOrVector getLogicalCoordination(float x, float y);
            static PointOrVector_Float boundsOfBoard;
            static PointOrVector_Float coordinateOf00;

            //�ض���Ϸ��������
            int ROUND_LIMIT;
            float TIME_LIMIT;
    };

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    bool CIG::ChessGameConfig::checkConstrains()
    {
        typedef unsigned long long U64;

        if(sizeof(U64) != 8)                     //����֮��, ��Ϊsizeof(U64)==8, �����ữ��һЩ����.
        {
            ostringstream oss;
            oss << "ϵͳ�ֳ���������ͬ. \n" << "sizeof(U64) = " << sizeof(U64) << " != 8";
            GUI::inform(oss.str(), true);
            return false;
        }

        return true;
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
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

                thetaOfXTop = 0;
                thetaOfXY = 90;

                lengthOfLattticeX = 40;
                lengthOfLattticeY = lengthOfLattticeX;
                borderWidth = lengthOfLattticeX;
                latticePenWidth = 2;

                markCrossByCircle = true;
                markCircleRadias = 1;
                drawLineWhenDrawDot = true;

                roundChessman = true;
                namedChessman = false;
                chessmanRect = PointOrVector_Float(0.9 * lengthOfLattticeX, 0.9 * lengthOfLattticeY);
                chessmanNames.insert(pair<CHESSMAN_TYPES, string>(CHESS, " "));

                LINE_DIRECTION.clear();
                LINE_DIRECTION.push_back(PointOrVector(1, 0));
                LINE_DIRECTION.push_back(PointOrVector(0, 1));

                addtionalLines.clear();

                additionalCircles.clear();
                additionalCircles.push_back(PointOrVector(7, 7));         // ��Ԫ
                additionalCircles.push_back(PointOrVector(3, 3));         // ��λ
                additionalCircles.push_back(PointOrVector(3, 11));
                additionalCircles.push_back(PointOrVector(11, 11));
                additionalCircles.push_back(PointOrVector(11, 3));
                additionalCircleRadias = 3;

                addtionalRectangles.clear();
                additionalImages.clear();

                ROUND_LIMIT = 0;
                TIME_LIMIT = 0;
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

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    bool ChessGameConfig::compileGUI()
    {
        /*************************************************************************
        ����������ʾ����
        ��ȷ�����Ӵ�С, �ڴ��ڳ�ʼ��ʱ�������̲������������ȷ���ͻ�����С.
        **************************************************************************/
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
        //���ý��޳�ֵ, Ҳ�����̵����߽�
        boundsOfBoardRelatively[RIGHT] = -1E7;
        boundsOfBoardRelatively[LEFT] = 1E7;
        boundsOfBoardRelatively[TOP] = 1E7;
        boundsOfBoardRelatively[BOTTOM] = -1E7;
        coordinateOf00 = PointOrVector_Float(0, 0);         //�������λ��

        for(int i = 0; i < (1 << INI_BOARD_WIDTH_LOG2); ++i)
        {
            for(int j = 0; j < (1 << INI_BOARD_HEIGHT_LOG2); j++)
            {
                if(BOARD_RANGE[j][i])
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

#endif /*__CHESS_GAME_CONFIG_H__*/

