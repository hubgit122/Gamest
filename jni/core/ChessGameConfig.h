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
                ���ϵͳ����
            **************************************************************************/
            bool checkConstrains();

            ChessGameConfig(GAME_TYPE id);

            virtual ~ChessGameConfig();
            virtual bool compileGUI();

            //��Ϸ�����������
            int INI_BOARD_WIDTH_LOG2;
            int INI_BOARD_HEIGHT_LOG2;
            OPERATIONS operationGraph[END][END + 1];
            bool **BOARD_RANGE;
            CHESSMAN_TYPES ** *INI_BOARD;

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

            //��Ϸ�����������
            static const int INI_CHESSMAN_GROUP_SIZE = 32;
            static const int INI_LATTICE_GROUP_SIZE = 32;
            static const int INT_BANNED_MOTION_SIZE = 16;
            static const int INT_MARKED_POINTS_SIZE = 32;
            static const int INT_BOARD_HISTORY_STACK_SIZE = 32;

            //�ض���Ϸ��������
            static int ROUND_LIMIT;
            static float TIME_LIMIT;
    };
}

#endif /*__CHESS_GAME_CONFIG_H__*/

