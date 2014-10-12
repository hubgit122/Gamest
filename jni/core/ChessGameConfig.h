#ifndef __CHESS_GAME_CONFIG_H__
#define __CHESS_GAME_CONFIG_H__
using namespace std;
#include "utilities.h"
#include "Object.h"

namespace CIG
{
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

            //游戏种类相关配置
            static char *OPERATION_NAME[END];
            OPERATIONS operationGraph[END][END + 1];
            int INI_BOARD_WIDTH_LOG2;
            int INI_BOARD_HEIGHT_LOG2;
            bool **BOARD_RANGE;
            CHESSMAN_TYPES ** *INI_BOARD;

            //游戏界面配置
            bool roundChessman;                             //棋子圆或方
            bool namedChessman;                            //棋子拥有名字
            bool markCrossByCircle;                          //是否标记棋路交叉点
            bool drawLineWhenDrawDot;                  //是否画线(若画线, 则一定要画点, 否则点处会有空白)
            float markCircleRadias;
            degree thetaOfXY;                                  //棋盘线的夹角
            degree thetaOfXTop;                              //x轴的俯角
            PointOrVector_Float chessmanRect;       //棋子矩形. 必须保证棋子在棋盘上没有重叠
            float lengthOfLattticeX;
            float lengthOfLattticeY;
            int latticePenWidth;
            float additionalPointRadias;
            float borderWidth;
            PointOrVector_Float Vx;
            PointOrVector_Float Vy;
            string *chessmanName;
            vector<PointOrVector> LINE_DIRECTION;
            vector<Line> addtionalLines;
            vector<PointOrVector> addtionalCircles;
            vector<pair<PointOrVector, PointOrVector>> addtionalRectangles;
            vector<pair<PointOrVector, string>> addtionalImages;

            //内部管理的属性
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

            //游戏性能相关配置
            static const int INI_CHESSMAN_GROUP_SIZE = 32;
            static const int INI_LATTICE_GROUP_SIZE = 32;
            static const int INT_BANNED_MOTION_SIZE = 16;
            static const int INT_MARKED_POINTS_SIZE = 32;
            static const int INT_BOARD_HISTORY_STACK_SIZE = 32;

            //特定游戏规则配置
            static int ROUND_LIMIT;
            static float TIME_LIMIT;
    };
}

#endif /*__CHESS_GAME_CONFIG_H__*/

