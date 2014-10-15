#ifndef __CHESS_GAME_CONFIG_H__
#define __CHESS_GAME_CONFIG_H__
using namespace std;
#include "utilities.h"
#include "Object.h"

namespace CIG
{
    //游戏性能相关配置
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
                检查系统环境
            **************************************************************************/
            bool checkConstrains();

            ChessGameConfig(GAME_TYPE id);

            virtual ~ChessGameConfig();
            virtual bool compileGUI();
            inline virtual string toJSON()const;

            //游戏种类相关配置
            Board<bool, INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2> boardRange;
            Array < Board<CHESSMAN_TYPES, INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2>, PLAYER_NUM, -1 > iniBoards;
            OPERATIONS operationGraph[END][END + 1];

            //游戏界面配置
            degree thetaOfXTop;                              //x轴的俯角
            degree thetaOfXY;                                  //棋盘线的夹角
            float lengthOfLattticeX;
            float lengthOfLattticeY;
            float borderWidth;
            int latticePenWidth;

            bool markCrossByCircle;                          //是否标记棋路交叉点
            float markCircleRadias;
            bool drawLineWhenDrawDot;                  //是否画线(若画线, 则一定要画点, 否则点处会有空白)

            bool roundChessman;                             //棋子圆或方
            bool namedChessman;                            //棋子拥有名字
            PointOrVector_Float chessmanRect;       //棋子矩形. 必须保证棋子在棋盘上没有重叠
            map<CHESSMAN_TYPES, string> chessmanNames;

            vector<PointOrVector> LINE_DIRECTION;   // TO-DO 不再是常量的, 改名字
            vector<Line> addtionalLines;
            vector<PointOrVector> additionalCircles;
            float additionalCircleRadias;
            vector<pair<PointOrVector, PointOrVector>> addtionalRectangles;
            vector<pair<PointOrVector, string>> additionalImages;

            //内部管理的属性
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

            //特定游戏规则配置
            int ROUND_LIMIT;
            float TIME_LIMIT;
    };

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    bool CIG::ChessGameConfig::checkConstrains()
    {
        typedef unsigned long long U64;

        if(sizeof(U64) != 8)                     //检测过之后, 认为sizeof(U64)==8, 这样会化简一些除法.
        {
            ostringstream oss;
            oss << "系统字长与期望不同. \n" << "sizeof(U64) = " << sizeof(U64) << " != 8";
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
                additionalCircles.push_back(PointOrVector(7, 7));         // 天元
                additionalCircles.push_back(PointOrVector(3, 3));         // 星位
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
        设置棋盘显示参数
        先确定棋子大小, 在窗口初始化时绘制棋盘并根据棋盘情况确定客户区大小.
        **************************************************************************/
        typedef float rad;
        rad theta1 = thetaOfXTop / 180.0 * PI,
            theta2 = thetaOfXY / 180.0 * PI;
        //支持动态调整棋盘, 所以不是常量, 可以调整.
        Vx = PointOrVector_Float(lengthOfLattticeX * cos(theta1), lengthOfLattticeX * sin(theta1));
        Vy = PointOrVector_Float(lengthOfLattticeX * cos(theta1 + theta2), lengthOfLattticeX * sin(theta1 + theta2));
        {
            /*************************************************************************
            检查棋子是否太大而导致棋盘放不下.
            检查边和对角线上的投影.
            **************************************************************************/
            if(roundInt(chessmanRect * Vx) > roundInt(Vx * Vx))
            {
                this->informError("棋子在X方向太大");
            }

            if(roundInt(chessmanRect * Vy) > roundInt(Vy * Vy))
            {
                informError("棋子在Y方向太大");
            }

            if(!roundChessman)
            {
                if(roundInt(chessmanRect * (Vx + Vy)) > roundInt((Vx + Vy) * (Vx + Vy)))
                {
                    informError("棋子在对角线方向太大");
                }

                if(roundInt(chessmanRect * (Vx - Vy)) > roundInt((Vx - Vy) * (Vx - Vy)))
                {
                    informError("棋子在副对角线方向太大");
                }
            }
            else
            {
                if(roundInt(chessmanRect * chessmanRect / 2) > roundInt((Vx + Vy) * (Vx + Vy)))
                {
                    informError("棋子在对角线方向太大");
                }

                if(roundInt(chessmanRect * chessmanRect / 2) > roundInt((Vx - Vy) * (Vx - Vy)))
                {
                    informError("棋子在副对角线方向太大");
                }
            }
        }
        //设置界限初值, 也是棋盘的最大边界
        boundsOfBoardRelatively[RIGHT] = -1E7;
        boundsOfBoardRelatively[LEFT] = 1E7;
        boundsOfBoardRelatively[TOP] = 1E7;
        boundsOfBoardRelatively[BOTTOM] = -1E7;
        coordinateOf00 = PointOrVector_Float(0, 0);         //先求相对位置

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

        //确定棋盘矩形的大小.
        boundsOfBoard.x[0] = borderWidth * 2 + boundsOfBoardRelatively[RIGHT] - boundsOfBoardRelatively[LEFT];
        boundsOfBoard.x[1] = borderWidth * 2 + boundsOfBoardRelatively[BOTTOM] - boundsOfBoardRelatively[TOP];
        //原点重新定位
        coordinateOf00 = PointOrVector_Float(borderWidth - boundsOfBoardRelatively[LEFT], borderWidth - boundsOfBoardRelatively[TOP]);
    }
}

#endif /*__CHESS_GAME_CONFIG_H__*/

