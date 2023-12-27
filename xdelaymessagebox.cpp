#include <QtCore/QTimer>
#include "xdelaymessagebox.h"
#include "xmessagebox.h"

// 运行警告消息框
xDelayMessageBox::xDelayMessageBox(QObject *parent) : QObject(parent)
{
    m_pDelayShowTimer = new QTimer(this);
    connect(m_pDelayShowTimer, SIGNAL(timeout()), this, SLOT(DelayShow()));
}

xDelayMessageBox::~xDelayMessageBox()
{
    delete m_pDelayShowTimer;
}

qint32 xDelayMessageBox::DoWarning(const QString &title, const QString &msg)
{
    m_title = title;
    m_msg = msg;
    m_pDelayShowTimer->start(100);
    return XMSG_RET_YES;
}

void xDelayMessageBox::DelayShow(void)
{
    m_pDelayShowTimer->stop();
    if (xMessageBox::DoWarning(m_title, m_msg) == XMSG_HAS_SHOWED)
        m_pDelayShowTimer->start(100);
}
