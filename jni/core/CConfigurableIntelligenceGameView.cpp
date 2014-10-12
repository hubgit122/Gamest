
// CConfigurableIntelligenceGameView.cpp : CConfigurableIntelligenceGameView ���ʵ��
//


#include "ConfigurableIntelligenceGame.h"
#include "CConfigurableIntelligenceGameView.h"
#include "GUI.h"
#include "Player.h"
#include "Chessman.h"
#include "Chessboard.h"
#include "utilities.h"
#include "MotionGenerator.h"
#include "MainFrm.h"
#include "GraphSearchEngine.h"

//#define DEBUG_GENERATOR
using namespace CIG;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CConfigurableIntelligenceGameView::CConfigurableIntelligenceGameView(): nowBoard(), moveOfLastRound(), moveComplete()
{
    //����ĳ�ʼ�����ҵ�. ���Ի����ڱ��ٳ�ʼ��һ�ΰ�.

}

int CConfigurableIntelligenceGameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if(CWnd::OnCreate(lpCreateStruct) == -1)
    {
        return -1;
    }

    // TODO:  �ڴ������ר�õĴ�������CIG::GUI::cigView = this;
    m_GameThread = AfxBeginThread(CIG::GUI::runThread, this);
    workThreadOK.Lock();
    getMove = false;

    CClientDC memDC(this);
    boardBaseBitmap.LoadBitmap(IDB_BOARD_BASE);
    chessmanBaseBitmap.LoadBitmap((GUI::roundChessman) ? IDB_CHESSMAN_ROUND_NAMED : IDB_CHESSMAN_RECTANGLE);

    return 0;
}

CConfigurableIntelligenceGameView::~CConfigurableIntelligenceGameView()
{
    GUI::cigView = NULL;

    if(m_GameThread)
    {
        m_GameThread->PostThreadMessage(WM_QUIT, 0, 0);
    }
}


BEGIN_MESSAGE_MAP(CConfigurableIntelligenceGameView, CWnd)
    ON_WM_PAINT()
    ON_WM_CREATE()
    ON_COMMAND(ID_GAME_NEW, &CConfigurableIntelligenceGameView::OnGameNew)
    ON_MESSAGE(WM_MOVE_COMPLETE, &CConfigurableIntelligenceGameView::OnMoveComplete)
    ON_MESSAGE(WM_GET_MOVE, &CConfigurableIntelligenceGameView::OnGetMove)
    ON_WM_SIZE()
    ON_WM_CREATE()
    ON_WM_LBUTTONDOWN()
    ON_WM_RBUTTONDOWN()
    ON_WM_CHAR()
    ON_MESSAGE(WM_STATUS_TEXT, &CConfigurableIntelligenceGameView::OnOperationText)
    ON_COMMAND(ID_EDIT_UNDO, &CConfigurableIntelligenceGameView::OnEditUndo)
END_MESSAGE_MAP()

// CConfigurableIntelligenceGameView ��Ϣ�������

BOOL CConfigurableIntelligenceGameView::PreCreateWindow(CREATESTRUCT &cs)
{
    if(!CWnd::PreCreateWindow(cs))
    {
        return FALSE;
    }

    cs.dwExStyle |= WS_EX_CLIENTEDGE;
    cs.style &= ~WS_BORDER;
    cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
                                       ::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

    return TRUE;
}

void CConfigurableIntelligenceGameView::OnPaint()
{
    CPaintDC memClientDC(this); // ���ڻ��Ƶ��豸������
    // TODO: �ڴ˴������Ϣ����������

    DrawBoard();

    GUI::drawComplete.SetEvent();
}

void CConfigurableIntelligenceGameView::OnGameNew()
{
    // TODO: �ڴ���������������
    nowBoard = Chessboard();
    GraphSearchEngine::setTimeOut(20000);
    GraphSearchEngine::setLimitDepth(2);
    /*
        m_GameThread->PostThreadMessage(WM_RESTART, 0, 0);
        workThreadOK.Lock();
        */
    DrawBoard();
    m_GameThread->PostThreadMessage(WM_GET_MOVE, (WPARAM)&moveOfLastRound, (LPARAM)&nowBoard);
}

afx_msg LRESULT CConfigurableIntelligenceGameView::OnMoveComplete(WPARAM wParam, LPARAM lParam)
{
    history.push(moveOfLastRound);
    getMove = false;
    DrawBoard();

    if(nowBoard.gameOver())
    {
        MessageBox(_T("ʤ���ѷ�! "));
    }
    else
    {
        m_GameThread->PostThreadMessage(WM_GET_MOVE, 0, 0);
    }

    return 0;
}

afx_msg LRESULT CConfigurableIntelligenceGameView::OnGetMove(WPARAM wParam, LPARAM lParam)
{
    getMove = true;

    return 0;
}

void TransparentBlt2(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, UINT crTransparent)
{
    HDC hImageDC, hMaskDC;
    HBITMAP hOldImageBMP, hImageBMP, hOldMaskBMP, hMaskBMP;
    hImageBMP = CreateCompatibleBitmap(hdcDest, nWidthDest, nHeightDest);
    hMaskBMP = CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);
    hImageDC = CreateCompatibleDC(hdcDest);
    hMaskDC = CreateCompatibleDC(hdcDest);
    hOldImageBMP = (HBITMAP) SelectObject(hImageDC, hImageBMP);
    hOldMaskBMP = (HBITMAP) SelectObject(hMaskDC, hMaskBMP);

    SetStretchBltMode(hdcDest, COLORONCOLOR);
    SetStretchBltMode(hImageDC, COLORONCOLOR);
    SetStretchBltMode(hMaskDC, COLORONCOLOR);

    if(nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
    {
        BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest,
               hdcSrc, nXOriginSrc, nYOriginSrc, SRCCOPY);
    }
    else
    {
        StretchBlt(hImageDC, 0, 0, nWidthDest, nHeightDest,
                   hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, SRCCOPY);
    }

    SetBkColor(hImageDC, crTransparent);
    BitBlt(hMaskDC, 0, 0, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCCOPY);
    SetBkColor(hImageDC, RGB(0, 0, 0));
    SetTextColor(hImageDC, RGB(255, 255, 255));
    BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);
    SetBkColor(hdcDest, RGB(255, 255, 255));
    SetTextColor(hdcDest, RGB(0, 0, 0));
    BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest,
           hMaskDC, 0, 0, SRCAND);
    BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest,
           hImageDC, 0, 0, SRCPAINT);

    SelectObject(hImageDC, hOldImageBMP);
    DeleteDC(hImageDC);
    SelectObject(hMaskDC, hOldMaskBMP);
    DeleteDC(hMaskDC);
    DeleteObject(hImageBMP);
    DeleteObject(hMaskBMP);
}

bool yaheiInstalled()
{
    LONG   ires;
    HKEY   hMyKey;
    DWORD   Type   =   REG_SZ;
    DWORD   count =   256;
    byte   mstr[256] = "";
    ires = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                        _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts"),
                        0, KEY_READ, &hMyKey);

    if(ERROR_SUCCESS == ires)
    {
        ires = RegQueryValueEx(hMyKey, _T("΢���ź� Bold (TrueType)"), 0, &Type, mstr, &count);
    }

    return (mstr[0] != '\0');
}

void CConfigurableIntelligenceGameView::WrapChessWithFrame(CDC &dc, PointOrVector logicCoo, COLORREF color /*= RGB(255,0,0)*/, bool rectangleNotCircle/* = true*/, bool fill/* = false*/)
{
    PointOrVector_Float xy = GUI::getGeometryCoordination(logicCoo);
    CBrush *oldBrush = (CBrush *)dc.SelectStockObject(NULL_BRUSH);
    CPen pen(PS_SOLID, GUI::latticePenWidth, color);
    CPen *oldPen = dc.SelectObject(&pen);

    dc.Rectangle(roundInt(xy.x[0] - GUI::chessmanRect.x[0] / 2), roundInt(xy.x[1] - GUI::chessmanRect.x[1] / 2),  roundInt(xy.x[0] + GUI::chessmanRect.x[0] / 2), roundInt(xy.x[1] + GUI::chessmanRect.x[1] / 2));

    dc.SelectObject(oldBrush);
    dc.SelectObject(oldPen);
}

void CConfigurableIntelligenceGameView::DrawBoard()
{
    CClientDC dc(this);

    CRect rect;
    GetClientRect(&rect);
    Chessboard &boardToDraw = this->nowBoard;
    Move &moveToDraw = this->moveOfLastRound;

    CDC memClientDC;            //�ݴ�dc, ˫�����ͼ.
    memClientDC.CreateCompatibleDC(&dc);
    CBitmap memBitmap;
    memBitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
    CBitmap *oldMemBitmap = memClientDC.SelectObject(&memBitmap);

    //����״̬��
    {
        ostringstream oss;

        oss << "Round " << nowBoard.nowRound;

        for(int i = 0; i < ChessGameConfig::PLAYER_NUM; ++i)
        {
            oss << " " << nowBoard.getEvaluation((ChessGameConfig::PLAYER_NAMES)i);
        }

        oss << " ��ǰ���: " << GUI::playerName[boardToDraw.nowTurn] << ". ";

        if(boardToDraw.players[boardToDraw.nowTurn].makeBestMove == GUI::askForMove)
        {
            oss << "��ǰ����Ҳ����Ļغ�, ������: ";
        }
        else
        {
            oss << "��ȴ���������... ";
        }

        if(moveToDraw.size)
        {
            for(int i = 1; i < moveToDraw.size; ++i)            //����ʾbegin
            {
                oss << ChessGameConfig::OPERATION_NAME[moveToDraw[i].operation] << ' ';
                oss << moveToDraw[i].distination << "->";
            }
        }

#ifdef UNICODE
        std::wstring stemp = s2ws(oss.str()); // Temporary buffer is required
        LPCWSTR result = stemp.c_str();
#else
        LPCWSTR result = messsage.c_str();
#endif
        this->SendMessage(WM_STATUS_TEXT, (WPARAM)result);
    }

    //������
    {
        CDC boardBaseDC;
        CBitmap *pBoardBaseDCBmpOld = NULL;
        GenerateBoardBaseDC(boardBaseDC, pBoardBaseDCBmpOld);           //��ͼ����

        memClientDC.BitBlt(0, 0, rect.Width(), rect.Height(), &boardBaseDC, 0, 0, SRCCOPY) ; //��ԴDC��(0,0,20,20)���Ƶ�Ŀ��DC

        boardBaseDC.SelectObject(pBoardBaseDCBmpOld) ;//ѡ��ԭDDB
    }

    //������
    {
        CFont *pOldFont = NULL;
        CFont font;

        if(GUI::namedChessman)
        {
            font.CreatePointFont(roundInt(0.5 * 10 * min(GUI::chessmanRect.x[0], GUI::chessmanRect.x[1])), _T("�����п�"), NULL);
            pOldFont = memClientDC.SelectObject(&font);
            memClientDC.SetStretchBltMode(COLORONCOLOR);            // ��������ģʽ, ����ͼ�ÿ�һ��
        }

        memClientDC.SetBkMode(TRANSPARENT);

        for(int p = 0; p < ChessGameConfig::PLAYER_NUM; ++p)              //ÿ�����
        {
            for(int c = boardToDraw.players[p].ownedChessmans.size - 1; c >= 0; --c)        //ÿ������
            {
                if(boardToDraw.players[p].ownedChessmans[c].status == ChessGameConfig::CAPTURED)      //���Բ���
                {
                    continue;
                }

                CDC chessDC;
                chessDC.CreateCompatibleDC(&memClientDC);

                PointOrVector_Float xy = GUI::getGeometryCoordination(boardToDraw.players[p].ownedChessmans[c].coordinate);

                if(GUI::namedChessman)
                {
                    CBitmap *pBoardBaseDCBmpOld = chessDC.SelectObject(&chessmanBaseBitmap);
                    BITMAP bm;
                    chessmanBaseBitmap.GetBitmap(&bm);
                    TransparentBlt2(memClientDC.m_hDC, roundInt(xy.x[0] - GUI::chessmanRect.x[0] / 2), roundInt(xy.x[1] - GUI::chessmanRect.x[1] / 2), roundInt(GUI::chessmanRect.x[0]), roundInt(GUI::chessmanRect.x[1]), chessDC.m_hDC, 0, 0, bm.bmWidth, bm.bmHeight, RGB(0, 255, 0));

                    memClientDC.SetTextColor(GUI::playerColor[p]);
                    memClientDC.DrawText(CString(GUI::chessmanName[boardToDraw.players[p].ownedChessmans[c].chessmanType]), &CRect(xy.x[0] - roundInt(GUI::chessmanRect.x[0] / 2), roundInt(xy.x[1] - GUI::chessmanRect.x[1] / 2), roundInt(xy.x[0] + GUI::chessmanRect.x[0] / 2), xy.x[1] + GUI::chessmanRect.x[1] / 2), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
                    chessDC.SelectObject(pBoardBaseDCBmpOld);
                }
                else
                {
                    CBrush brush(GUI::playerColor[p]);
                    CBrush *pOldChessBrush = memClientDC.SelectObject(&brush);
                    memClientDC.Ellipse(&CRect(xy.x[0] - roundInt(GUI::chessmanRect.x[0] / 2), roundInt(xy.x[1] - GUI::chessmanRect.x[1] / 2), roundInt(xy.x[0] + GUI::chessmanRect.x[0] / 2), xy.x[1] + GUI::chessmanRect.x[1] / 2));
                    memClientDC.SelectObject(pOldChessBrush);
                }
            }
        }

        //����ϴ��߷�
        for(int i = moveToDraw.size - 1; i >= 0; --i)
        {
            if(moveToDraw[i].distination != PointOrVector(-1, -1))
            {
                WrapChessWithFrame(memClientDC, moveToDraw[i].distination);
            }
        }

        if(GUI::namedChessman)
        {
            memClientDC.SelectObject(pOldFont);
        }
    }// ������

    dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memClientDC, 0, 0, SRCCOPY);          //˫�����ͼ

    memClientDC.SelectObject(oldMemBitmap);
}

void CConfigurableIntelligenceGameView::GenerateBoardBaseDC(CDC &boardBaseDC, CBitmap *pBoardBaseDCBmpOld)
{
    boardBaseDC.CreateCompatibleDC(&CClientDC(this));       //����DC

    CRect rect;
    GetClientRect(&rect);

    CDC latticeDC, addtionalDC;
    latticeDC.CreateCompatibleDC(&boardBaseDC);
    addtionalDC.CreateCompatibleDC(&boardBaseDC);

    CBitmap latticeBitmap, addtionalBitmap;
    latticeBitmap.CreateCompatibleBitmap(&boardBaseDC, rect.Width(), rect.Height());
    addtionalBitmap.CreateCompatibleBitmap(&boardBaseDC, rect.Width(), rect.Height());
    CBitmap *oldLatticeBitmap = latticeDC.SelectObject(&latticeBitmap),
             *oldAdditionalBitmap = addtionalDC.SelectObject(&addtionalBitmap);

    latticeDC.StretchBlt(0, 0, rect.Width(), rect.Height(), NULL, 0, 0, 0, 0, BLACKNESS);       //����
    addtionalDC.StretchBlt(0, 0, rect.Width(), rect.Height(), NULL, 0, 0, 0, 0, BLACKNESS);     //����

    CPen pen(PS_SOLID, GUI::latticePenWidth, RGB(255, 255, 255));                   //���ڻ����Ļ���.
    CPen *oldLatticePen = latticeDC.SelectObject(&pen),
          *oldAdditionalPen = addtionalDC.SelectObject(&pen);

    latticeDC.SelectStockObject(NULL_BRUSH);
    addtionalDC.SelectStockObject(NULL_BRUSH);

    if(GUI::markCrossByCircle && GUI::drawLineWhenDrawDot)
    {
        for(int i = 0; i < (1 << ChessGameConfig::INI_BOARD_WIDTH_LOG2); ++i)
        {
            for(int j = 0; j < (1 << ChessGameConfig::INI_BOARD_HEIGHT_LOG2); ++j)
            {
                if(ChessGameConfig::BOARD_RANGE[j][i])            //�������
                {
                    int x = roundInt(GUI::getGeometryCoordination(i, j).x[0]);
                    int y = roundInt(GUI::getGeometryCoordination(i, j).x[1]);          //�õ���������

                    for(unsigned k = 0 ; k < GUI::LINE_DIRECTION.size(); ++k)           //������Ҫ���ߵķ�����
                    {
                        latticeDC.MoveTo(x, y);
                        int x_ = i + roundInt(GUI::LINE_DIRECTION[k].x[0]);
                        int y_ = j + roundInt(GUI::LINE_DIRECTION[k].x[1]);

                        if(ChessGameConfig::BOARD_RANGE[y_][x_])              //��Ӧ��ǰ���е�
                        {
                            PointOrVector_Float p = GUI::getGeometryCoordination(x_, y_);
                            latticeDC.LineTo(roundInt(p.x[0]), roundInt(p.x[1]));       //����
                        }
                    }
                }
            }
        }
    }

    // �ڸ���ƽ���ϻ�������
    for(unsigned i = 0; i < GUI::addtionalLines.size(); ++i)
    {
        int x = roundInt(GUI::getGeometryCoordination(GUI::addtionalLines[i].p0).x[0]);
        int y = roundInt(GUI::getGeometryCoordination(GUI::addtionalLines[i].p0).x[1]);         //�õ���������

        int x_ = roundInt(GUI::getGeometryCoordination(GUI::addtionalLines[i].p1).x[0]);
        int y_ = roundInt(GUI::getGeometryCoordination(GUI::addtionalLines[i].p1).x[1]);

        addtionalDC.MoveTo(x, y);
        addtionalDC.LineTo(x_, y_);
    }

    latticeDC.BitBlt(0, 0, rect.Width(), rect.Height(), &addtionalDC, 0, 0, SRCINVERT);     //���õ����������ߵ�����

    //���¸��ǵ�, ��ֹ����㱻���
    if(GUI::markCrossByCircle)
    {
        for(int i = 0; i < (1 << ChessGameConfig::INI_BOARD_WIDTH_LOG2); ++i)
        {
            for(int j = 0; j < (1 << ChessGameConfig::INI_BOARD_HEIGHT_LOG2); ++j)
            {
                if(ChessGameConfig::BOARD_RANGE[j][i])            //�������
                {
                    int x = roundInt(GUI::getGeometryCoordination(i, j).x[0]);
                    int y = roundInt(GUI::getGeometryCoordination(i, j).x[1]);          //�õ���������

                    latticeDC.Ellipse(roundInt(x - GUI::markCircleRadias), roundInt(y - GUI::markCircleRadias), roundInt(x + GUI::markCircleRadias), roundInt(y + GUI::markCircleRadias));          //����
                }
            }
        }
    }

    // ������ƽ���ϻ����ӵ�
    for(unsigned i = 0; i < GUI::addtionalPoints.size(); ++i)
    {
        int x = roundInt(GUI::getGeometryCoordination(GUI::addtionalPoints[i]).x[0]);
        int y = roundInt(GUI::getGeometryCoordination(GUI::addtionalPoints[i]).x[1]);           //�õ���������

        latticeDC.Ellipse(roundInt(x - GUI::additionalPointRadias), roundInt(y - GUI::additionalPointRadias), roundInt(x + GUI::additionalPointRadias), roundInt(y + GUI::additionalPointRadias));          //����
    }

    latticeDC.StretchBlt(0, 0, rect.Width(), rect.Height(), NULL, 0, 0, rect.Width(), rect.Height(), DSTINVERT);

    pBoardBaseDCBmpOld = boardBaseDC.SelectObject(&boardBaseBitmap) ;//����ԭ��DDB����ѡ����DDB��DC,

    boardBaseDC.StretchBlt(0, 0, rect.Width(), rect.Height(), &latticeDC, 0, 0, rect.Width(), rect.Height(), SRCAND);
    nBoardBaseDC = boardBaseDC.SaveDC();
    latticeDC.SelectObject(oldLatticePen);
    addtionalDC.SelectObject(oldAdditionalPen);
    latticeDC.SelectObject(oldLatticeBitmap);
    addtionalDC.SelectObject(oldAdditionalBitmap);
}


void CConfigurableIntelligenceGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    if(getMove)
    {
        PointOrVector lp = GUI::getLogicalCoordination(point.x, point.y);
        GUI::guiPoint = lp;
        GUI::msg = CIG_POINT;
        GUI::inputGot.SetEvent();
    }
    else
    {
#ifdef DEBUG_GENERATOR          //�����߷�������

        for(;;)
        {
            MotionGenerator mg(nowBoard);
            mg.generateMoves();

            for(int i = 0; i < mg.moveStack.size ; ++i)
            {
                nowBoard.onMoveIntent(mg.moveStack[i]);
                DrawBoard();
                nowBoard.undoMove(mg.moveStack[i]);
                MessageBox(_T("ok?"));
            }

            nowBoard.onChangeTurn();
        }

#endif // DEBUG_GENERATOR
    }

    CWnd::OnLButtonDown(nFlags, point);
}


void CConfigurableIntelligenceGameView::OnRButtonDown(UINT nFlags, CPoint point)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

    if(getMove)
    {
        GUI::guiPoint = PointOrVector();
        GUI::msg = CIG_UNDO;
        GUI::inputGot.SetEvent();
    }

    CWnd::OnRButtonDown(nFlags, point);
}


void CConfigurableIntelligenceGameView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

    if(getMove)
    {
        GUI::guiPoint = PointOrVector();
        GUI::msg = CIG_END;
        GUI::inputGot.SetEvent();
    }

    CWnd::OnChar(nChar, nRepCnt, nFlags);
}

afx_msg LRESULT CConfigurableIntelligenceGameView::OnOperationText(WPARAM wParam, LPARAM lParam)
{
    CMainFrame *w = (CMainFrame *)AfxGetMainWnd();
    CStatusBar &sb = w->m_wndOperationBar;
    sb.SetPaneText(0, (LPCTSTR)wParam);
    return 0;
}

void CConfigurableIntelligenceGameView::OnEditUndo()
{
    // TODO:  �ڴ���������������

    if(this->history.size)
    {
        while(nowBoard.players[history.top()[0].chessmanIndex.player].makeBestMove != GUI::askForMove)
        {
            nowBoard.undoWholeMove(history.top());
            history.popNoReturn();
        }

        DrawBoard();
        m_GameThread->PostThreadMessage(WM_GET_MOVE, (WPARAM)&moveOfLastRound, (LPARAM)&nowBoard);
    }
}
