#ifndef CODELOOPFREE_H
#define CODELOOPFREE_H

#include "xconfig.h"
#include "xmlmodelitem.h"
#include "cmbprotocol.h"
class FormActLoopFree;

class CodeLoopFree : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodeLoopFree(QWidget *form);
    ~CodeLoopFree();
    virtual bool XmlRead(QXmlStreamReader &reader);
    virtual bool XmlWrite(QXmlStreamWriter &writer);

    virtual bool Update(bool bSaveAndValidate = true);

    virtual bool GenerateCode(quint16 *code, quint32 *para, quint8 other = 0);
//    virtual void GetExtData(void* ptr);
    virtual bool IsModified();

    void SetUserVar(quint16 var, int idx = 0);
    quint16 GetUserVar(int idx = 0);


private:
    int m_pos[MAX_LOOP_AXIS][MAX_LOOP_POINTS];
    quint8 m_speed;
    quint8 m_dspeed;
    quint16 m_dlen;
    bool m_rotate;
    bool m_xdec;
    quint8 m_poscount;
    bool m_isrunner;
    bool m_trvrot;
	quint16 m_counter;       // 计数器

    FormActLoopFree *m_form;
protected:
    virtual void UpdateBaseMember();
    bool XmlReadPara(QXmlStreamReader &reader);
};

#endif // CODELOOPFREE_H
