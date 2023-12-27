#ifndef FORMACTCIRCLE_H
#define FORMACTCIRCLE_H

#include <QWidget>

namespace Ui {
class FormActCircle;
}

class FormActCircle : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormActCircle(QWidget *parent = 0);
    ~FormActCircle();

    quint8 GetDir();
    void SetDir(quint8 dir);

    quint16 GetRadius();
    void SetRadius(quint16 radius);

    quint8 GetSpeed();
    void SetSpeed(quint8 speed);

    quint8 GetBegin();
    void SetBegin(quint8 begin);

    quint8 GetEnd();
    void SetEnd(quint8 end);

    quint32 GetZ();
    void SetZ(quint32 zpoint);

    quint32 GetY2();
    void SetY2(quint32 y2point);

    void retranslateUi(void);			// 设置界面字符串资源
    void UpdateWidgetState();

protected:
	void changeEvent(QEvent *e);

private:
    quint8 m_dir;
    quint16 m_radius;
    quint8 m_speed;
    quint8 m_begin;
    quint8 m_end;
    Ui::FormActCircle *ui;

private slots:
    void inputRadius(void);
    void inputSpeed(void);
    void setCirclePic(void);
    void inputZ(void);
    void inputY2(void);
    void SetZPoint(void);
    void SetY2Point(void);

};

#endif // FORMACTCIRCLE_H
