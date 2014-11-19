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
    //游戏性能相关配置
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
                检查系统环境
            **************************************************************************/
            bool checkConstrains();

            ChessGameConfig(const MyJSONNode &json);
            virtual ~ChessGameConfig();
            virtual bool compileGUI();
            inline virtual string toJSON()const;

            //游戏种类相关配置
            Board<bool> boardRange;
            Array <Board<short>, INI_PLAYER_ARRAY_SIZE, 0> iniBoards;
            GraphWithNameAndID operationGraph;
            unsigned short INI_BOARD_WIDTH_LOG2;
            unsigned short INI_BOARD_HEIGHT_LOG2;
            unsigned short MAX_PLAYER_NUM;

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
            PointOrVector<float> chessmanRect;       //棋子矩形. 必须保证棋子在棋盘上没有重叠
            MapJSON<short, string> chessmanNames;

            VectorJSON<PointOrVectorS> LINE_DIRECTION;   // TO-DO 不再是常量的, 改名字
            VectorJSON<Line> addtionalLines;
            VectorJSON<PointOrVectorS> additionalCircles;
            float additionalCircleRadias;
            VectorJSON<Line> addtionalRectangles;
            VectorJSON<DiaplayableDescription> additionalImages;

            //内部管理的属性
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

            //特定游戏规则配置
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
//    additionalCircles.push_back(PointOrVector(7, 7));         // 天元
//    additionalCircles.push_back(PointOrVector(3, 3));         // 星位
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

