#ifndef XDELAYMESSAGEBOX_H
#define XDELAYMESSAGEBOX_H

#include <QObject>
#include <QtCore/QTimer>

class xDelayMessageBox : public QObject
{
    Q_OBJECT

public:
    explicit xDelayMessageBox(QObject *parent = 0);
    ~xDelayMessageBox();
    qint32 DoWarning(const QString &title, const QString &msg);

private:
    QTimer * m_pDelayShowTimer;
    QString m_title;
    QString m_msg;

private slots:
    void DelayShow(void);
};


#endif // XDELAYMESSAGEBOX_H
