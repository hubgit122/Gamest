#include "ChessGameConfig.h"

namespace CIG
{


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
        Vx = PointOrVector<float>(lengthOfLattticeX * cos(theta1), lengthOfLattticeX * sin(theta1));
        Vy = PointOrVector<float>(lengthOfLattticeX * cos(theta1 + theta2), lengthOfLattticeX * sin(theta1 + theta2));
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
        coordinateOf00 = PointOrVector<float>(0, 0);         //�������λ��

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

        //ȷ�����̾��εĴ�С.
        boundsOfBoard.x[0] = borderWidth * 2 + boundsOfBoardRelatively[RIGHT] - boundsOfBoardRelatively[LEFT];
        boundsOfBoard.x[1] = borderWidth * 2 + boundsOfBoardRelatively[BOTTOM] - boundsOfBoardRelatively[TOP];
        //ԭ�����¶�λ
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

        if(sizeof(U64) != 8)                      //����֮��, ��Ϊsizeof(U64)==8, �����ữ��һЩ����.
        {
            ostringstream oss;
            oss << "ϵͳ�ֳ���������ͬ. \n" << "sizeof(U64) = " << sizeof(U64) << " != 8";
            informError(oss.str());
            return false;
        }

        return true;
    }
}

