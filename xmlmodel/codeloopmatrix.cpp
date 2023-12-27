#include "xconfig.h"
#include "formactloopmatrix.h"
#include "codeloopmatrix.h"
#include "cmbprotocol.h"
#include "QDebug"

CodeLoopMatrix::CodeLoopMatrix(QWidget *form) :	XmlModelItem(QIcon(":/img/action/Matrix.png"), form, QString(tr("调用矩阵子程序")))
{
	m_form = (FormActLoopMatrix*)form;
	m_speed = 50;
    m_horspeed = 50;
    m_trvspeed = 50;
	m_dspeed = 10;
	m_dlen = 0;
    m_rel_posx = false;
    m_rel_posy = false;
    m_rel_posz = false;
    m_counter = 0;
    m_isrunner = false;
    m_trvrot = false;
    m_dec_axes = false;
    m_horizontal = false;
    m_dec_axes_prior = ORDER_MODE_XYZ;

    m_xs = 1;
    m_x_interval = 0;

    m_ys = 1;
    m_y_interval = 0;

    m_zs = 1;
    m_z_interval = 0;

    m_posx = 0;
    m_posy = 0;
    m_posz = 0;

    m_conveyor_delay = 0;	//输送带延时
    m_conveyor_out = 0;		//输送带端口
    ConveyorUse = 0;			//使用输送带

    m_code = CODE_MATRIX;
    m_codes = 8;
    if (CMBProtocol::GetFunctions(SUB_FUN2_LOOP_MATRIX))
        m_codes++;

    if (CMBProtocol::GetFunctions(SUB_FUN2_LOOP_MATRIX_EXT))
        m_codes++;

}

CodeLoopMatrix::~CodeLoopMatrix()
{
}

bool CodeLoopMatrix::XmlReadPara(QXmlStreamReader &reader)
{
	QString name = reader.attributes().value(XML_ATTR_NAME).toString();
	if ((name==XML_PNAME_PARA1)||
		(name==XML_PNAME_PARA2)||
		(name==XML_PNAME_PARA3)||
		(name==XML_PNAME_PARA4)||
		(name==XML_PNAME_PARA5)||
        (name==XML_PNAME_PARA6)||
        (name==XML_PNAME_PARA7)||
        (name==XML_PNAME_PARA8)||
        (name==XML_PNAME_PARA9)||
        (name==XML_PNAME_PARA10)||
        (name==XML_PNAME_PARA11)||
        (name==XML_PNAME_PARA12)||
        (name==XML_PNAME_PARA13)||
        (name==XML_PNAME_PARA14)||
        (name==XML_PNAME_PARA15)||
        (name==XML_PNAME_PARA16)||
        (name==XML_PNAME_PARA17)||
        (name==XML_PNAME_PARA18)||
        (name==XML_PNAME_PARA19)||
        (name==XML_PNAME_PARA20)||
        (name==XML_PNAME_PARA21)||
        (name==XML_PNAME_PARA22)||
        (name==XML_PNAME_PARA23)||
        (name==XML_PNAME_PARA24)||
        (name==XML_PNAME_PARA25)||
        (name==XML_PNAME_PARA26))
    {
		QString val = reader.readElementText();
		if (name==XML_PNAME_PARA1) m_speed = val.toInt();
		if (name==XML_PNAME_PARA2) m_dspeed = val.toInt();
		if (name==XML_PNAME_PARA3) m_dlen = val.toInt();
        if (name==XML_PNAME_PARA4) m_isrunner = val.toInt();
        if (name==XML_PNAME_PARA5) m_dec_axes = val.toInt();
        if (name==XML_PNAME_PARA6) m_counter = val.toInt();
        if (name==XML_PNAME_PARA7) m_rel_posx = val.toInt();
        if (name==XML_PNAME_PARA8) m_rel_posy = val.toInt();
        if (name==XML_PNAME_PARA9) m_rel_posz = val.toInt();
        if (name==XML_PNAME_PARA10) m_horizontal = val.toInt();
        if (name==XML_PNAME_PARA11) m_dec_axes_prior = val.toInt();
        if (name==XML_PNAME_PARA12) m_xs = val.toInt();
        if (name==XML_PNAME_PARA13) m_x_interval = val.toInt();
        if (name==XML_PNAME_PARA14) m_ys = val.toInt();
        if (name==XML_PNAME_PARA15) m_y_interval = val.toInt();
        if (name==XML_PNAME_PARA16) m_zs = val.toInt();
        if (name==XML_PNAME_PARA17) m_z_interval = val.toInt();
        if (name==XML_PNAME_PARA18) m_posx = val.toInt();
        if (name==XML_PNAME_PARA19) m_posy = val.toInt();
        if (name==XML_PNAME_PARA20) m_posz = val.toInt();
        if (name==XML_PNAME_PARA21) m_trvrot = val.toInt();
        if (name==XML_PNAME_PARA22) m_conveyor_delay = val.toInt();
        if (name==XML_PNAME_PARA23) m_conveyor_out = val.toInt();
        if (name==XML_PNAME_PARA24) ConveyorUse = val.toInt();
        if (name==XML_PNAME_PARA25) m_horspeed = val.toInt();
        if (name==XML_PNAME_PARA26) m_trvspeed = val.toInt();
        UpdateBaseMember();
		if (reader.isEndElement())
			reader.readNext();
	}
	else
		XmlSkipUnknownElement(reader);
	return true;
}
bool CodeLoopMatrix::XmlRead(QXmlStreamReader &reader)
{
    m_note = reader.attributes().value(XML_ATTR_NOTE).toString();
    m_flag = reader.attributes().value(XML_ATTR_FLAG).toString().toUShort();
	reader.readNext();
	while (!reader.atEnd())
	{
		if (reader.isEndElement())
		{
			reader.readNext();
			break;
		}
		if (reader.isStartElement())
		{
			if (reader.name()==XML_ELEMENT_PARA)
			{
				XmlReadPara(reader);
			}
			else
			{
				XmlSkipUnknownElement(reader);
			}
		}
		else
		{
			reader.readNext();
		}
	}
	return true;
}
bool CodeLoopMatrix::XmlWrite(QXmlStreamWriter &writer)
{
    writer.writeStartElement(XML_ELEMENT_CODE);
	writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_MATRIX);
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));


	writer.writeStartElement(XML_ELEMENT_PARA);
	writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA1);
	writer.writeCharacters(QString("%1").arg(m_speed));
	writer.writeEndElement();

	writer.writeStartElement(XML_ELEMENT_PARA);
	writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA2);
	writer.writeCharacters(QString("%1").arg(m_dspeed));
	writer.writeEndElement();

	writer.writeStartElement(XML_ELEMENT_PARA);
	writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA3);
	writer.writeCharacters(QString("%1").arg(m_dlen));
	writer.writeEndElement();

	writer.writeStartElement(XML_ELEMENT_PARA);
	writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA4);
    writer.writeCharacters(QString("%1").arg(m_isrunner));
	writer.writeEndElement();

	writer.writeStartElement(XML_ELEMENT_PARA);
	writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA5);
    writer.writeCharacters(QString("%1").arg(m_dec_axes));
	writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA6);
    writer.writeCharacters(QString("%1").arg(m_counter));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA7);
    writer.writeCharacters(QString("%1").arg(m_rel_posx));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA8);
    writer.writeCharacters(QString("%1").arg(m_rel_posy));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA9);
    writer.writeCharacters(QString("%1").arg(m_rel_posz));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA10);
    writer.writeCharacters(QString("%1").arg(m_horizontal));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA11);
    writer.writeCharacters(QString("%1").arg(m_dec_axes_prior));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA12);
    writer.writeCharacters(QString("%1").arg(m_xs));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA13);
    writer.writeCharacters(QString("%1").arg(m_x_interval));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA14);
    writer.writeCharacters(QString("%1").arg(m_ys));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA15);
    writer.writeCharacters(QString("%1").arg(m_y_interval));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA16);
    writer.writeCharacters(QString("%1").arg(m_zs));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA17);
    writer.writeCharacters(QString("%1").arg(m_z_interval));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA18);
    writer.writeCharacters(QString("%1").arg(m_posx));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA19);
    writer.writeCharacters(QString("%1").arg(m_posy));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA20);
    writer.writeCharacters(QString("%1").arg(m_posz));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA21);
    writer.writeCharacters(QString("%1").arg(m_trvrot));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA22);
    writer.writeCharacters(QString("%1").arg(m_conveyor_delay));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA23);
    writer.writeCharacters(QString("%1").arg(m_conveyor_out));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA24);
    writer.writeCharacters(QString("%1").arg(ConveyorUse));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA25);
    writer.writeCharacters(QString("%1").arg(m_horspeed));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA26);
    writer.writeCharacters(QString("%1").arg(m_trvspeed));
    writer.writeEndElement();

    writer.writeEndElement();
	return true;
}
bool CodeLoopMatrix::Update(bool bSaveAndValidate)
{
    if (m_form)
	{
		if (bSaveAndValidate)
		{
			bool change=false;
			if (m_speed != m_form->GetSpeed())
			{
				m_speed = m_form->GetSpeed();
				change=true;
			}
            if (m_horspeed != m_form->GetHorSpeed())
            {
                m_horspeed = m_form->GetHorSpeed();
                change=true;
            }
            if (m_trvspeed != m_form->GetTrvSpeed())
            {
                m_trvspeed = m_form->GetTrvSpeed();
                change=true;
            }
			if (m_dspeed != m_form->GetDSpeed())
			{
				m_dspeed = m_form->GetDSpeed();
				change=true;
			}
            if (m_counter != m_form->GetVar())
			{
                m_counter = m_form->GetVar();
				change=true;
			}
            if (m_dlen != m_form->GetDLen())
            {
                m_dlen = m_form->GetDLen();
                change=true;
            }
            if (m_isrunner != m_form->GetIsRunner())
            {
                m_isrunner = m_form->GetIsRunner();
                change=true;
            }
            if (m_trvrot != m_form->GetTrvRot())
            {
                m_trvrot = m_form->GetTrvRot();
                change=true;
            }
            if (m_dec_axes != m_form->GetXDec())
            {
                m_dec_axes = m_form->GetXDec();
                change=true;
            }
            if (m_horizontal != m_form->GetRotate())
            {
                m_horizontal = m_form->GetRotate();
                change=true;
            }
            if (m_dec_axes_prior != m_form->GetFirstDec())
            {
                m_dec_axes_prior = m_form->GetFirstDec();
                change=true;
            }
            if (m_posx != m_form->GetX(0))
            {
                m_posx = m_form->GetX(0);
                change=true;
            }
            if (m_x_interval != m_form->GetX(1))
            {
                m_x_interval = m_form->GetX(1);
                change=true;
            }
            if (m_xs != m_form->GetX(2))
            {
                m_xs = m_form->GetX(2);
                change=true;
            }
            if (m_posy != m_form->GetY(0))
            {
                m_posy = m_form->GetY(0);
                change=true;
            }
            if (m_y_interval != m_form->GetY(1))
            {
                m_y_interval = m_form->GetY(1);
                change=true;
            }
            if (m_ys != m_form->GetY(2))
            {
                m_ys = m_form->GetY(2);
                change=true;
            }
            if (m_posz != m_form->GetZ(0))
            {
                m_posz = m_form->GetZ(0);
                change=true;
            }
            if (m_z_interval != m_form->GetZ(1))
            {
                m_z_interval = m_form->GetZ(1);
                change=true;
            }
            if (m_zs != m_form->GetZ(2))
            {
                m_zs = m_form->GetZ(2);
                change=true;
            }
            if (m_conveyor_delay != m_form->GetConveyor_delay())
            {
                m_conveyor_delay = m_form->GetConveyor_delay();
                change=true;
            }
            if (m_conveyor_out != m_form->GetConveyor_out())
            {
                m_conveyor_out = m_form->GetConveyor_out();
                change=true;
            }
            if (ConveyorUse != m_form->GetConveyor_use())
            {
                ConveyorUse = m_form->GetConveyor_use();
                change=true;
            }
            if (change) UpdateBaseMember();
			return change;
		}
		else
		{
			m_form->SetSpeed(m_speed);
            m_form->SetHorSpeed(m_horspeed);
            m_form->SetTrvSpeed(m_trvspeed);
			m_form->SetDSpeed(m_dspeed);
            m_form->SetDLen(m_dlen);
            m_form->SetRotate(m_horizontal);
            m_form->SetXDec(m_dec_axes);
            m_form->SetFirstDec(m_dec_axes_prior);
            m_form->SetIsRunner(m_isrunner);
            m_form->SetVar(m_counter);
            m_form->SetX(0, m_posx);
            m_form->SetX(1, m_x_interval);
            m_form->SetX(2, m_xs);
            m_form->SetY(0, m_posy);
            m_form->SetY(1, m_y_interval);
            m_form->SetY(2, m_ys);
            m_form->SetZ(0, m_posz);
            m_form->SetZ(1, m_z_interval);
            m_form->SetZ(2, m_zs);
            m_form->SetTrvRot(m_trvrot);
            m_form->SetConveyor_delay(m_conveyor_delay);
            m_form->SetConveyor_out(m_conveyor_out);
            m_form->SetConveyor_use(ConveyorUse);
            m_form->UpdateWidgetState();
         }
	}
	return false;
}

bool CodeLoopMatrix::GenerateCode(quint16* code, quint32 *para, quint8 other)
{
    int codeidx = 0;
    quint32 relSpd = CMBProtocol::GetSrvSpeed();
    relSpd = qRound((double)(m_speed * relSpd) / 100.0);
    relSpd = (relSpd == 0 ? 1 : relSpd);

    quint32 horSpd  = CMBProtocol::GetSrvSpeed();;
    horSpd = qRound((double)(m_horspeed * horSpd) / 100.0);
    horSpd = (horSpd == 0 ? 1 : horSpd);

    quint32 trvSpd = CMBProtocol::GetSrvSpeed();
    trvSpd = qRound((double)(m_trvspeed * trvSpd) / 100.0);
    trvSpd = (trvSpd == 0 ? 1 : trvSpd);

    quint32 decSpd = CMBProtocol::GetSrvSpeed();
    decSpd = qRound((double)(m_dspeed * decSpd) / 100.0);
    decSpd = (decSpd == 0 ? 1 : decSpd);

    code[0] = CODE_MATRIX | (((quint16)m_flag) << 8);
    para[0] = 0;
    if (m_isrunner) para[0] = 0x1;
    if (m_dec_axes) para[0] |= 0x2;
    if (m_horizontal) para[0] |= 0x4;
    if (m_dec_axes_prior&1) para[0] |= 0x8;
    if (m_rel_posx) para[0] |= 0x10;
    if (m_rel_posy) para[0] |= 0x20;
    if (m_rel_posz) para[0] |= 0x40;
    if (m_dec_axes_prior&2) para[0] |= 0x80;
    if (m_trvrot) para[0] |= 0x100;
    if (CMBProtocol::GetFunctions(SUB_FUN2_LOOP_MATRIX))
        para[codeidx] |= 0x200;      // 主板支持矩阵指令控制传送带，则置1；
    if (CMBProtocol::GetFunctions(SUB_FUN2_LOOP_MATRIX_EXT))
        para[codeidx] |= 0x400;
    para[codeidx] |= ((m_counter&0xFFFF)<<16);
    codeidx++;

    code[codeidx] = CODE_CONST | (((quint16)m_flag) << 8);
    para[codeidx] = relSpd&0x7F;
    if (m_dec_axes_prior&4) para[1] |= 0x80;
    para[codeidx] |= (decSpd&0x7F)<<8;
    para[codeidx] |= 0x8000;

    para[codeidx] |= m_dlen<<16;
    codeidx++;

    code[codeidx] = CODE_CONST | (((quint16)m_flag) << 8);
    para[codeidx] = m_xs;
    para[codeidx] |= m_x_interval <<16;
    codeidx++;
    code[codeidx] = CODE_CONST | (((quint16)m_flag) << 8);
    para[codeidx] = m_ys;
    para[codeidx] |= m_y_interval <<16;
    codeidx++;
    code[codeidx] = CODE_CONST | (((quint16)m_flag) << 8);
    para[codeidx] = m_zs;
    para[codeidx] |= m_z_interval <<16;
    codeidx++;
    code[codeidx] = CODE_CONST | (((quint16)m_flag) << 8);
    para[codeidx] = m_posx;
    codeidx++;
    code[codeidx] = CODE_CONST | (((quint16)m_flag) << 8);
    para[codeidx] = m_posy;
    codeidx++;
    code[codeidx] = CODE_CONST | (((quint16)m_flag) << 8);
    para[codeidx] = m_posz;
    codeidx++;
    if ((CMBProtocol::GetFunctions(SUB_FUN2_LOOP_MATRIX)))
    {
        if (ConveyorUse)
        {
            code[codeidx] = CODE_CONST | (((quint16)m_flag) << 8);
            para[codeidx] = m_conveyor_delay << 16;
            para[codeidx] |= m_conveyor_out;
        }
        else
        {
            code[codeidx] = CODE_CONST | (((quint16)m_flag) << 8);
            para[codeidx] = 0;
        }
        codeidx++;
    }
    if (CMBProtocol::GetFunctions(SUB_FUN2_LOOP_MATRIX_EXT))
    {
        code[codeidx] = CODE_CONST | (((quint16)m_flag) << 8);
        para[codeidx] =  (trvSpd & 0xFF)<< 8;
        para[codeidx] |= (horSpd & 0xFF);
    }
    return true;
}

bool CodeLoopMatrix::IsModified()
{
	if (m_form)
	{
        if ((m_speed != m_form->GetSpeed())||
            (m_horspeed != m_form->GetHorSpeed())||
            (m_trvspeed != m_form->GetTrvSpeed())||
            (m_dspeed != m_form->GetDSpeed())||
            (m_horizontal != m_form->GetRotate())||
            (m_dec_axes != m_form->GetXDec())||
            (m_dlen != m_form->GetDLen())||
            (m_dec_axes_prior != m_form->GetFirstDec()) ||
            (m_isrunner != m_form->GetIsRunner()) ||
            (m_trvrot != m_form->GetTrvRot()) ||
            (m_counter != m_form->GetVar())||
            (m_posx != m_form->GetX(0))||
            (m_x_interval != m_form->GetX(1))||
            (m_xs != m_form->GetX(2))||
            (m_posy != m_form->GetY(0))||
            (m_y_interval != m_form->GetY(1))||
            (m_ys != m_form->GetY(2))||
            (m_posz != m_form->GetZ(0))||
            (m_z_interval != m_form->GetZ(1))||
            (m_zs != m_form->GetZ(2))||
            (m_conveyor_delay != m_form->GetConveyor_delay())||
            (m_conveyor_out != m_form->GetConveyor_out())||
            (ConveyorUse != m_form->GetConveyor_use()))
             return true;
	}
	return XmlModelItem::IsModified();
}

void CodeLoopMatrix::SetUserVar(quint16 var, int idx)
{
    m_counter = var;
}

quint16 CodeLoopMatrix::GetUserVar(int idx)
{
    if ((m_counter &MASK_VAR_TYPE) == VAR_TYPE_USR)
        return m_counter;
    return 0;
}
