#ifndef CODEPAPER_H
#define CODEPAPER_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActPaper;

class CodePaper : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodePaper(QWidget *form);
    ~CodePaper();

    virtual bool XmlRead(QXmlStreamReader &reader);
    virtual bool XmlWrite(QXmlStreamWriter &writer);

    virtual bool Update(bool bSaveAndValidate = true);

    virtual bool GenerateCode(quint16 *code, quint32 *para, quint8 other = 0);
    virtual bool IsModified();
    void UpdateBaseMember();
    int GetAxes(){return m_axes;}

private:
    int m_pos;
    int m_speed;
    int m_dspeed;
    int m_dvar;
    int m_invar;
    int m_outvar;
    quint8 m_axes;

    FormActPaper *m_form;
protected:
    bool XmlReadPara(QXmlStreamReader &reader);
};

#endif // CODEPAPER_H
