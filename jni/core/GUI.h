
#ifndef __GUI_H__
#define __GUI_H__

#include "utilities.h"
#include "ChessGameConfig.h"

//GUI�߳������߳��������, ���¿�ʼ.
#define WM_RESTART          (WM_USER+1)

//GUI�̸߳������߳���Ϣ, ���Ը�����һ����, �Һø�����Ľ����ͼ.
//�������̷߳��ֵ�ǰ�������, ֪ͨGUI�̶߳�ȡ�߷�, Ȼ�󴫸�������, �Һø��㽻��.
//������ƿ���չ, GUI����֪����һ�����˻��ǵ���.
#define WM_GET_MOVE         (WM_USER+2)
#define WM_MOVE_COMPLETE (WM_USER+3)
#define  WM_STATUS_TEXT (WM_USER+4)
#define WM_REGERT (WM_USER+5)

#define CIG_END         0
#define  CIG_UNDO       1
#define CIG_POINT       2

class CConfigurableIntelligenceGameView;
namespace CIG
{
    class Chessboard;
    class GUI
    {
        public:

            /*************************************************************************
                ����ͨ�Žӿ�, ��ƽ̨ʱ��Ҫ��д����.
            **************************************************************************/
            static CEvent drawComplete;
            static CEvent moveComplete;
            static CConfigurableIntelligenceGameView *cigView;
            static void drawBoard(Chessboard *cb = NULL, void *move = NULL);
            static void inform(const string &messsage, bool exit = false);
            static void exit();
            static UINT runThread(LPVOID pParam);
            static void postMessage(UINT msg, WPARAM wp, LPARAM  lp);

            /****************************
            askForMove ����ʹ��GUI������߷�������, ���߷��������ڵ��� getInput �����õ�����
            ��getInput����������, �ȴ������߼��̵Ĳ���.
             *****************************/
            static void askForMove(Chessboard *cb, void *op);
            static void GUI::getInput(PointOrVector &dist, UINT &msg);

            /*************************************************************************
                �������̻��Ʋ���
                ��ȷ�����Ӵ�С, �ڴ��ڳ�ʼ��ʱ�������̲������������ȷ���ͻ�����С.
                �涨����������:
                0----------------->x
                |
                |
                |
                ��
                y
            **************************************************************************/

            static void refreshBoardDisplayData();
            static PointOrVector_Float getGeometryCoordination(int x, int y);
            static PointOrVector_Float getGeometryCoordination(PointOrVector p);
            static PointOrVector getLogicalCoordination(PointOrVector_Float p);
            static PointOrVector getLogicalCoordination(float x, float y);
            static PointOrVector_Float boundsOfBoard;
            static PointOrVector_Float coordinateOf00;
            static int latticePenWidth;
            static PointOrVector guiPoint;
            static CEvent inputGot;
            static UINT msg;
            //�ж��������̵ı߽�Ƚ���, ������.
            //static int borderPenColor[3];
    };
    std::wstring s2ws(const std::string &s);
}

#endif /*__GUI_H_*/

