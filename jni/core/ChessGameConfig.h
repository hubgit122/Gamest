#ifndef __CHESS_GAME_CONFIG_H__
#define __CHESS_GAME_CONFIG_H__
using namespace std;
#include "utilities.h"
#include "Board.h"
#include "GraphWithNameAndID.h"
#include "Array.h"
#include "MapJSON.h"
#include "PointOrVector.h"
#include "Line.h"
#include "Operation.h"
#include "VectorJSON.h"
#include "DiaplayableDescription.h"

namespace CIG
{
    //��Ϸ�����������
    static const int INI_CHESSMAN_GROUP_SIZE = 32;
    static const int INI_LATTICE_GROUP_SIZE = 32;
    static const int INT_BANNED_MOTION_SIZE = 16;
    static const int INT_MARKED_POINTS_SIZE = 32;
    static const int INT_BOARD_HISTORY_STACK_SIZE = 32;
    static const int INI_PLAYER_ARRAY_SIZE = 6;

    class ChessGameConfig : public Object
    {
        public:
            /*************************************************************************
                ���ϵͳ����
            **************************************************************************/
            bool checkConstrains();

            ChessGameConfig(const MyJSONNode &json);
            virtual ~ChessGameConfig();
            virtual bool compileGUI();
            inline virtual string toJSON()const;

            //��Ϸ�����������
            Board<bool> boardRange;
            Array <Board<short>, INI_PLAYER_ARRAY_SIZE, 0> iniBoards;
            GraphWithNameAndID operationGraph;
            unsigned short INI_BOARD_WIDTH_LOG2;
            unsigned short INI_BOARD_HEIGHT_LOG2;
            unsigned short MAX_PLAYER_NUM;

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
            PointOrVector<float> chessmanRect;       //���Ӿ���. ���뱣֤������������û���ص�
            MapJSON<short, string> chessmanNames;

            VectorJSON<PointOrVectorS> LINE_DIRECTION;   // TO-DO �����ǳ�����, ������
            VectorJSON<Line> addtionalLines;
            VectorJSON<PointOrVectorS> additionalCircles;
            float additionalCircleRadias;
            VectorJSON<Line> addtionalRectangles;
            VectorJSON<DiaplayableDescription> additionalImages;

            //�ڲ����������
            PointOrVector<float> Vx;
            PointOrVector<float> Vy;
            float boundsOfBoardRelatively[4];
            enum
            {
                TOP, BOTTOM, LEFT, RIGHT
            };
            PointOrVector<float> getGeometryCoordination(int x, int y);
            PointOrVector<float> getGeometryCoordination(PointOrVectorS p);
            PointOrVectorS getLogicalCoordination(PointOrVector<float> p);
            PointOrVectorS getLogicalCoordination(float x, float y);
            PointOrVector<float> boundsOfBoard;
            PointOrVector<float> coordinateOf00;

            //�ض���Ϸ��������
            int ROUND_LIMIT;
            float TIME_LIMIT;
    };
}


//
//switch(id)
//{
//case CIG::ERRROR:
//    break;
//
//case CIG::DRAUGHTS:
//    break;
//
//case CIG::CHINESE_CHESS:
//    break;
//
//case CIG::GOBANG:
//    unsigned short operationGraph[END][END + 1] =
//    {
//        { NOMORE, NOMORE, NOMORE, NOMORE, NOMORE },
//        { ADD, NOMORE, NOMORE, NOMORE, NOMORE, },
//        { PUT, NOMORE, NOMORE, NOMORE, NOMORE, },
//        { NOMORE, NOMORE, NOMORE, NOMORE, NOMORE },
//        { END, NOMORE, NOMORE, NOMORE, NOMORE, },
//        { NOMORE, NOMORE, NOMORE, NOMORE, NOMORE },
//        { NOMORE, NOMORE, NOMORE, NOMORE, NOMORE },
//        { NOMORE, NOMORE, NOMORE, NOMORE, NOMORE },
//    };
//
//    memcpy(this->operationGraph, operationGraph, sizeof(operationGraph));
//
//    thetaOfXTop = 0;
//    thetaOfXY = 90;
//
//    lengthOfLattticeX = 40;
//    lengthOfLattticeY = lengthOfLattticeX;
//    borderWidth = lengthOfLattticeX;
//    latticePenWidth = 2;
//
//    markCrossByCircle = true;
//    markCircleRadias = 1;
//    drawLineWhenDrawDot = true;
//
//    roundChessman = true;
//    namedChessman = false;
//    chessmanRect = PointOrVector<float>(0.9 * lengthOfLattticeX, 0.9 * lengthOfLattticeY);
//    chessmanNames.insert(pair<short, string>(MONO_CHESS, " "));
//
//    LINE_DIRECTION.clear();
//    LINE_DIRECTION.push_back(PointOrVector(1, 0));
//    LINE_DIRECTION.push_back(PointOrVector(0, 1));
//
//    addtionalLines.clear();
//
//    additionalCircles.clear();
//    additionalCircles.push_back(PointOrVector(7, 7));         // ��Ԫ
//    additionalCircles.push_back(PointOrVector(3, 3));         // ��λ
//    additionalCircles.push_back(PointOrVector(3, 11));
//    additionalCircles.push_back(PointOrVector(11, 11));
//    additionalCircles.push_back(PointOrVector(11, 3));
//    additionalCircleRadias = 3;
//
//    addtionalRectangles.clear();
//    additionalImages.clear();
//
//    ROUND_LIMIT = 0;
//    TIME_LIMIT = 0;
//    break;
//
//case CIG::WESTEN_CHESS:
//    break;
//
//case CIG::GO:
//    break;
//
//case CIG::FLIGHT_CHESS:
//    break;
//
//case CIG::MILITARY_CHESS:
//    break;
//
//default:
//    break;
//}

#endif /*__CHESS_GAME_CONFIG_H__*/

