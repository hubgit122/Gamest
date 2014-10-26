#include "ChessGameConfig.h"

namespace CIG
{


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
        Vx = PointOrVector<float>(lengthOfLattticeX * cos(theta1), lengthOfLattticeX * sin(theta1));
        Vy = PointOrVector<float>(lengthOfLattticeX * cos(theta1 + theta2), lengthOfLattticeX * sin(theta1 + theta2));
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
        coordinateOf00 = PointOrVector<float>(0, 0);         //先求相对位置

        for(int j = 0; j < (1 << INI_BOARD_HEIGHT_LOG2); ++j)
        {
            for(int i = 0; i < (1 << INI_BOARD_WIDTH_LOG2); ++i)
            {
                if(boardRange.at(j, i))
                {
                    PointOrVector<float> temp = getGeometryCoordination(i, j);

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
        coordinateOf00 = PointOrVector<float>(borderWidth - boundsOfBoardRelatively[LEFT], borderWidth - boundsOfBoardRelatively[TOP]);
    }

    std::string ChessGameConfig::toJSON() const
    {
        ostringstream oss;
        oss << JSON_OBJECT(JSON_KEYVALUE(boardRange) JSON_COMMA JSON_KEYVALUE(iniBoards)JSON_COMMA
                           JSON_KEYVALUE(operationGraph) JSON_COMMA JSON_KEYVALUE(INI_BOARD_WIDTH_LOG2)JSON_COMMA
                           JSON_KEYVALUE(INI_BOARD_HEIGHT_LOG2)JSON_COMMA JSON_KEYVALUE(MAX_PLAYER_NUM)JSON_COMMA
                           JSON_KEYVALUE(thetaOfXY)JSON_COMMA JSON_KEYVALUE(thetaOfXTop)JSON_COMMA
                           JSON_KEYVALUE(lengthOfLattticeX)JSON_COMMA JSON_KEYVALUE(lengthOfLattticeY)JSON_COMMA
                           JSON_KEYVALUE(borderWidth)JSON_COMMA JSON_KEYVALUE(latticePenWidth)JSON_COMMA
                           JSON_KEYVALUE(markCrossByCircle)JSON_COMMA JSON_KEYVALUE(markCircleRadias)JSON_COMMA
                           JSON_KEYVALUE(drawLineWhenDrawDot)JSON_COMMA JSON_KEYVALUE(roundChessman)JSON_COMMA
                           JSON_KEYVALUE(namedChessman)JSON_COMMA JSON_KEYVALUE(chessmanRect)JSON_COMMA
                           JSON_KEYVALUE(chessmanNames)JSON_COMMA JSON_KEYVALUE(LINE_DIRECTION)JSON_COMMA
                           JSON_KEYVALUE(addtionalLines)JSON_COMMA JSON_KEYVALUE(additionalCircles)JSON_COMMA
                           JSON_KEYVALUE(additionalCircleRadias)JSON_COMMA JSON_KEYVALUE(addtionalRectangles)JSON_COMMA
                           JSON_KEYVALUE(additionalImages)JSON_COMMA JSON_KEYVALUE(Vx)JSON_COMMA
                           JSON_KEYVALUE(Vy)JSON_COMMA JSON_KEYVALUE(boundsOfBoardRelatively) JSON_COMMA
                           JSON_KEYVALUE(boundsOfBoard)JSON_COMMA JSON_KEYVALUE(coordinateOf00) JSON_COMMA
                           JSON_KEYVALUE(ROUND_LIMIT) JSON_COMMA JSON_KEYVALUE(TIME_LIMIT));
        return oss.str();
    }

    ChessGameConfig::ChessGameConfig(const MyJSONNode &json) : JSON_INI(iniBoards), JSON_INI(boardRange), JSON_INI(chessmanRect), JSON_INI(thetaOfXTop), JSON_INI(thetaOfXY),
        JSON_INI(lengthOfLattticeX), JSON_INI(lengthOfLattticeY), JSON_INI(borderWidth), JSON_INI(latticePenWidth),
        JSON_INI(markCrossByCircle), JSON_INI(markCircleRadias), JSON_INI(drawLineWhenDrawDot), JSON_INI(roundChessman),
        JSON_INI(chessmanNames), JSON_INI(operationGraph), JSON_INI(LINE_DIRECTION), JSON_INI(namedChessman),
        JSON_INI(addtionalLines), JSON_INI(additionalCircleRadias), JSON_INI(addtionalRectangles), JSON_INI(additionalImages),
        JSON_INI(ROUND_LIMIT), JSON_INI(TIME_LIMIT)
    {
        this->assert(compileGUI());
    }

    bool CIG::ChessGameConfig::checkConstrains()
    {
        typedef unsigned long long U64;

        if(sizeof(U64) != 8)                      //检测过之后, 认为sizeof(U64)==8, 这样会化简一些除法.
        {
            ostringstream oss;
            oss << "系统字长与期望不同. \n" << "sizeof(U64) = " << sizeof(U64) << " != 8";
            informError(oss.str());
            return false;
        }

        return true;
    }
}

