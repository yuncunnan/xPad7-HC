#ifndef CODECIRCLE_H
#define CODECIRCLE_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActCircle;

class CodeCircle : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodeCircle(QWidget* form);
    virtual bool XmlRead(QXmlStreamReader &reader);
    virtual bool XmlWrite(QXmlStreamWriter &writer);

    virtual bool Update(bool bSaveAndValidate = true);

    virtual bool GenerateCode(quint16 *code, quint32 *para, quint8 other = 0);
    virtual bool IsModified();

private:
    quint8 m_dir;
    quint16 m_radius;
    quint8 m_speed;
    quint8 m_begin;
    quint8 m_end;
    quint32 m_z;
    quint32 m_y2;
    FormActCircle *m_form;
protected:
    virtual void UpdateBaseMember();
    bool XmlReadPara(QXmlStreamReader &reader);
};

#endif // CODECIRCLE_H
