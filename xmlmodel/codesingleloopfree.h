#ifndef CODESINGLELOOPFREE_H
#define CODESINGLELOOPFREE_H

#include "xconfig.h"
#include "xmlmodelitem.h"
#include "cmbprotocol.h"
class FormActSingleLoopFree;

class CodeSingleLoopFree : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodeSingleLoopFree(QWidget *form);
    ~CodeSingleLoopFree();
    virtual bool XmlRead(QXmlStreamReader &reader);
    virtual bool XmlWrite(QXmlStreamWriter &writer);

    virtual bool Update(bool bSaveAndValidate = true);

    virtual bool GenerateCode(quint16 *code, quint32 *para, quint8 other = 0);
//    virtual void GetExtData(void* ptr);
    virtual bool IsModified();

    void SetUserVar(quint16 var, int idx = 0);
    quint16 GetUserVar(int idx = 0);
    int GetAxes(){return m_axes;}

private:
    int m_pos[MAX_SINGLELOOPFREE_POINTS];
    quint8 m_speed;
    quint8 m_axes;
	quint16 m_counter;       // 计数器
    quint16 m_poscount;
    quint8 m_times;
    quint8 m_dspeed;        // 减速速度
    quint16 m_dlen;         // 减速距离

    FormActSingleLoopFree *m_form;
protected:
    virtual void UpdateBaseMember();
    bool XmlReadPara(QXmlStreamReader &reader);
};

#endif // CODESINGLELOOPFREE_H
