#include "xconfig.h"
#include <QFile>
#include <QXmlStreamReader>
#include "teachtablemodel.h"
#include "xmessagebox.h"
#include "xmlmodelitem.h"
#include "codedelay.h"
#include "codeparm.h"
#include "coderarm.h"
#include "codeend.h"
#include "codeendif.h"
#include "codeendfor.h"
#include "codeelse.h"
#include "codebreak.h"
#include "codeoperator.h"
#include "codeif.h"
#include "codefor.h"
#include "codewait.h"
#include "codevision.h"
#include "codeimm.h"
#include "codepos.h"
#include "codeextpos.h"
#include "codeextin.h"
#include "codeextout.h"
#include "vcodevacuum.h"
#include "codevacuum.h"
#include "codepaper.h"
#include "codeloopfree.h"
#include "codeloopmatrix.h"
#include "codespeed.h"
#include "codetbegin.h"
#include "codetend.h"
#include "codesingleloop.h"
#include "codesingleloopfree.h"
#include "codeinterp.h"
#include "codepower.h"
#include "codecircle.h"
#include "codemextout.h"
#include "qdebug.h"

#define COMBINE_ACT_MASK_PRO_HOR_VER    (1<<0)
#define COMBINE_ACT_MASK_RUN_ADV_RET    (1<<1)
#define COMBINE_ACT_MASK_RUN_ASC_DES    (1<<2)
#define COMBINE_ACT_MASK_IMM_EMC        (1<<3)
#define COMBINE_ACT_MASK_X_SERVO        (1<<4)
#define COMBINE_ACT_MASK_Y_SERVO        (1<<5)
#define COMBINE_ACT_MASK_Z_SERVO        (1<<6)
#define COMBINE_ACT_MASK_A_SERVO        (1<<7)
#define COMBINE_ACT_MASK_B_SERVO        (1<<8)
#define COMBINE_ACT_MASK_C_SERVO        (1<<9)
#define PATH_ACT_MASK_X_SERVO           (1<<10)
#define PATH_ACT_MASK_Y_SERVO           (1<<11)
#define PATH_ACT_MASK_Z_SERVO           (1<<12)
#define PATH_ACT_MASK_A_SERVO           (1<<13)
#define PATH_ACT_MASK_B_SERVO           (1<<14)
#define PATH_ACT_MASK_C_SERVO           (1<<15)

TeachTableModel::TeachTableModel(bool optedit, bool varedit, QObject *parent) : QAbstractTableModel(parent), m_err_string(" ")
{
	m_ismodifed = false;
    m_optedit = optedit;
    m_varedit = varedit;
    m_currentopt = -1;
    m_current_process = 0;
//	rowCheckState.clear();
}

TeachTableModel::~TeachTableModel()
{
    int proc = 0;
	int i;
    for (proc=0; proc<MAX_PROCESS; proc++)
    {
        for (i=0; i<m_codelist[proc].count(); i++)
        {
            delete m_codelist[proc].at(i);
        }
        for (i=0; i<m_optlist[proc].count(); i++)
        {
            delete m_optlist[proc].at(i);
        }
    }
    for (i=0; i<m_varlist.count(); i++)
    {
        delete m_varlist.at(i);
    }
}

int TeachTableModel::rowCount(const QModelIndex &parent) const
{
    if (m_varedit)
        return m_varlist.count();
    return m_codelist[m_current_process].count();
}
int TeachTableModel::columnCount(const QModelIndex &parent) const
{
    if (m_varedit)
        return 4;
    if (m_optedit)
        return 4;//4列  |行号|图标|指令名称参数|CheckBox
    return 3;
}

Qt::ItemFlags TeachTableModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;
    if (IsCodeDisable(index.row()))
    {
        return 0;
    }
    else
    {
        if ((index.column() == 2)&&(!m_optedit))
            return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        if ((index.column() == 3)&&m_optedit)
        {
            if ((index.row()+1)!=m_codelist[m_current_process].count())
                return Qt::ItemIsEnabled |Qt::ItemIsSelectable | Qt::ItemIsUserCheckable ;
        }
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
}

bool TeachTableModel::OptCheck(int code_pos, int current_opt, int check)
{
    int i;
    if (current_opt>=0)
    {
        if (current_opt<m_optlist[m_current_process].count())
        {
            //if (m_optlist.at(current_opt)->IsInclude(code_pos))
            if (check==Qt::Checked)
            {
                for (i=0; i<m_optlist[m_current_process].count(); i++)
                {
                    if (m_optlist[m_current_process].at(i)->IsInclude(code_pos))
                    {
                        quint8 ret = xMessageBox::DoQuestion(tr("一行代码只能对应一个选项！"), tr("此行代码已经被第")+QString::number(i+1)+tr("个选项包含，确定替换吗？"));
                        if (ret == XMSG_RET_YES)
                        {
                            m_optlist[m_current_process].at(i)->RemoveLine(code_pos);
                            //break;
                        }
                        else
                        {
                            return false;
                        }
                    }
                }
                m_optlist[m_current_process].at(current_opt)->InsertLine(code_pos);
            }
            else
                m_optlist[m_current_process].at(current_opt)->RemoveLine(code_pos);
            return true;
        }
    }
    return false;
}

bool TeachTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (!index.isValid())
		return false;
    if (role==Qt::DisplayRole&& index.column() == 2)
	{
        if (m_codelist[m_current_process].at(index.row())->SetNote(value.toString())==true)
			m_ismodifed = true;
		emit dataChanged(index, index);
	}
    else
    if ((role==Qt::CheckStateRole)&&(index.column()==3)&&m_optedit)
	{
        if ((index.row()+1)!=m_codelist[m_current_process].count())
        {
            if (OptCheck(index.row(), m_currentopt, value.toInt()))
            {
                m_ismodifed = true;
                emit dataChanged(index, index);
            }
        }
	}
	return true;
}

int TeachTableModel::IsOptCheck(int code_pos, int current_opt) const
{
    if (current_opt>=0)
    {
        if (current_opt<m_optlist[m_current_process].count())
        {
            if (m_optlist[m_current_process].at(current_opt)->IsInclude(code_pos))
                return Qt::Checked;
        }
    }
    return Qt::Unchecked;
}
QVariant TeachTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (m_varedit)
    {
        if (orientation == Qt::Horizontal)
        {
            if (role == Qt::DisplayRole)
            {
                switch (section)
                {
                case 0:
                    return tr("编号");
                case 1:
                    return tr("变量名");
                case 2:
                    return tr("初始值");
                case 3:
                    return tr("初始类型");
                }
            }
            else if (role == Qt::TextAlignmentRole)
                return int(Qt::AlignLeft | Qt::AlignVCenter);
            else if (role == Qt::SizeHintRole)
                return QSize(40, 40);
        }
        else if (orientation == Qt::Vertical)
        {
            if (role == Qt::TextAlignmentRole)
                return int(Qt::AlignRight | Qt::AlignVCenter);
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

void TeachTableModel::UpdateLineNum(void)
{
    int i;
    int line = 0;
    for (i=0; i<m_codelist[m_current_process].count(); i++)
    {
        m_codelist[m_current_process].at(i)->SetLineNum(line);
        if (!(m_codelist[m_current_process].at(i)->GetFlag()&FLAG_COMBINE))
            line ++;
    }
}

QVariant TeachTableModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
    if (m_varedit)
    {
        if (index.column()==0)
        {
            if (role==Qt::DisplayRole)
                return index.row();
        }
        else
        if (index.column()==1)
        {
            if (role==Qt::DisplayRole)
            {
                return m_varlist.at(index.row())->GetVarName();
            }
        }
        else
        if (index.column()==2)
        {
            if (role==Qt::DisplayRole)
            {
                return m_varlist.at(index.row())->GetVarValue();
            }
        }
        else
        if ((index.column()==3))
        {
            if (role==Qt::DisplayRole)
            {
                return m_varlist.at(index.row())->GetTypeName();
            }
        }
    }
    else
    {
        if (index.column()==0)
        {
            if (role==Qt::DisplayRole)
            {
                //if (m_codelist[m_current_process].at(index.row())->GetFlag()&FLAG_COMBINE) return QString::number(m_codelist[m_current_process].at(index.row())->GetLineNum())+" (";
                return m_codelist[m_current_process].at(index.row())->GetLineNum();
                //return index.row();
            }
            else
            if (role==Qt::BackgroundRole)
            {
                if (IsCodeDisable(index.row())) return Qt::lightGray;
                //if (m_codelist[m_current_process].at(index.row())->GetFlag()&FLAG_COMBINE)return Qt::yellow;
//                if (m_codelist[m_current_process].at(index.row())->GetLineNum() % 2 == 0) return QColor(QRgb(0xFFFF80));
//                return QColor(QRgb(0x80FF80));
            }
#if IS_XEDITOR
#else
            else
            if (role==Qt::ForegroundRole)
            {
                if (IsCodeDisable(index.row())) return Qt::gray;
            }
#endif
        }
        else
        if (index.column()==1)
        {
            if (role==Qt::DecorationRole)
            {
                return m_codelist[m_current_process].at(index.row())->GetIcon();
            }
            else
            if (role==Qt::BackgroundRole)
            {
                if (IsCodeDisable(index.row())) return Qt::lightGray;
//                if (m_codelist[m_current_process].at(index.row())->GetFlag()&FLAG_COMBINE)return Qt::yellow;
//                if (m_codelist[m_current_process].at(index.row())->GetLineNum() % 2 == 0) return QColor(QRgb(0xFFFF80));
//                return QColor(QRgb(0x80FF80));
            }
        }
        else
        if (index.column()==2)
        {
            if (role==Qt::DisplayRole)
            {
                if (m_codelist[m_current_process].at(index.row())->GetNote().length()>2)
                    return m_codelist[m_current_process].at(index.row())->GetNote();
                return m_codelist[m_current_process].at(index.row())->GetName();
            }
            else
            if (role==Qt::BackgroundRole)
            {
                if (IsCodeDisable(index.row())) return Qt::lightGray;
                //if (m_codelist[m_current_process].at(index.row())->GetFlag()&FLAG_COMBINE)return Qt::yellow;
//                if (m_codelist[m_current_process].at(index.row())->GetLineNum() % 2 == 0) return QColor(QRgb(0xFFFF80));
//                return QColor(QRgb(0x80FF80));
            }
#if IS_XEDITOR
#else
            else
            if (role==Qt::ForegroundRole)
            {
                if (IsCodeDisable(index.row())) return Qt::gray;
            }
#endif
        }
        else
        if ((index.column()==3)&&m_optedit)
        {
            if ((index.row()+1)!=m_codelist[m_current_process].count())
            {
                if (role==Qt::CheckStateRole)
                {
                    return IsOptCheck(index.row(), m_currentopt);
                }
            }
        }
    }

	return QVariant();
}

//XML读接口
void TeachTableModel::XmlSkipUnknownElement(QXmlStreamReader &reader)
{
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
			XmlSkipUnknownElement(reader);
		}
		else
		{
			reader.readNext();
		}
	}
}

bool TeachTableModel::XmlReadProgramElement(QXmlStreamReader &reader, int procid)
{
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
			if (reader.name()==XML_ELEMENT_CODE)
			{
                XmlReadCodeElement(reader, procid);
			}
			else
			{
				XmlSkipUnknownElement(reader);
				//reader.raiseError(QObject::tr("Not a program file!"));
			}
		}
		else
		{
			reader.readNext();
		}
	}
	return true;
}

void TeachTableModel::AddEndToProc(int procid)
{
    QWidget* widget = 0;
    XmlModelItem *pitem = 0;
    emit GetWidget(CODE_END, widget);
    pitem = new CodeEnd(widget);

    if (pitem)
    {
        m_codelist[procid].append(pitem);
    }
}

bool TeachTableModel::XmlReadVarInitElement(QXmlStreamReader &reader)
{
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
            if (reader.name()==XML_ELEMENT_VAR)
            {
                XmlModelVarInitItem *pitem = new XmlModelVarInitItem();
                if (pitem)
                {
                    pitem->XmlRead(reader);
                    m_varlist.append(pitem);
                }
                if (reader.isEndElement())
                    reader.readNext();
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

bool TeachTableModel::XmlReadCodeElement(QXmlStreamReader &reader, int procid)
{
	QWidget* widget = 0;
	XmlModelItem *pitem = 0;
	QString name = reader.attributes().value(XML_ATTR_NAME).toString();
	if (name==XML_CNAME_DELAY)
	{
		emit GetWidget(CODE_DELAY, widget);
		pitem = new CodeDelay(widget);
	}
	else
	if (name==XML_CNAME_BREAK)
	{
		emit GetWidget(CODE_BREAK, widget);
		pitem = new CodeBreak(widget);
	}
	else
	if (name==XML_CNAME_END)
	{
		emit GetWidget(CODE_END, widget);
		pitem = new CodeEnd(widget);
	}
	else
	if (name==XML_CNAME_ELSE)
	{
		emit GetWidget(CODE_ELSE, widget);
		pitem = new CodeElse(widget);
	}
	else
//	if (name==XML_CNAME_CEND)
//	{
//		emit GetWidget(CODE_CEND, widget);
//		pitem = new CodeCEnd(widget);
//	}
//    else
//    if (name==XML_CNAME_CBEGIN)
//    {
//        emit GetWidget(CODE_CBEGIN, widget);
//        pitem = new CodeCBegin(widget);
//    }
//    else
	if (name==XML_CNAME_TEND)
    {
		emit GetWidget(CODE_TEND, widget);
		pitem = new CodeTEnd(widget);
    }
    else
	if (name==XML_CNAME_TBEGIN)
    {
		emit GetWidget(CODE_TBEGIN, widget);
		pitem = new CodeTBegin(widget);
    }
    else
	if (name==XML_CNAME_ENDFOR)
	{
		emit GetWidget(CODE_ENDFOR, widget);
		pitem = new CodeEndFor(widget);
	}
	else
	if (name==XML_CNAME_ENDIF)
	{
		emit GetWidget(CODE_ENDIF, widget);
		pitem = new CodeEndIf(widget);
	}
	else
	if (name==XML_CNAME_SPEED)
	{
		emit GetWidget(CODE_SPEED, widget);
		pitem = new CodeSpeed(widget);
	}
	else
	if (name==XML_CNAME_IF)
	{
		int type = reader.attributes().value(XML_ATTR_TYPE).toString().toInt();
		emit GetWidget(CODE_IF, widget);
		pitem = new CodeIf(widget, type);
	}
	else
	if (name==XML_CNAME_OPR)
	{
		int type = reader.attributes().value(XML_ATTR_TYPE).toString().toInt();
        emit GetWidget(CODE_OPR, widget);
		pitem = new CodeOperator(widget, type);
	}
	else
	if (name==XML_CNAME_WAIT)
	{
		emit GetWidget(CODE_WAIT, widget);
		pitem = new CodeWait(widget);
	}
	else
	if (name==XML_CNAME_IMM)
	{
		emit GetWidget(CODE_IMM, widget);
		pitem = new CodeImm(widget);
	}
	else
	if (name==XML_CNAME_POS)
	{
		emit GetWidget(CODE_POS, widget);
		pitem = new CodePos(widget);
	}
    else
    if (name==XML_CNAME_EXTPOS)
    {
        emit GetWidget(CODE_EXTPOS, widget);
        pitem = new CodeExtPos(widget);
    }
    else
    if (name==XML_CNAME_INTERP)
    {
        emit GetWidget(CODE_INTERP, widget);
        pitem = new CodeInterp(widget);
    }
    else
    if (name==XML_CNAME_POWER)
    {
        emit GetWidget(CODE_POWER, widget);
        pitem = new CodePower(widget);
    }
    else
	if (name==XML_CNAME_PARM)
	{
		emit GetWidget(CODE_PROARM, widget);
		pitem = new CodePArm(widget);
	}
	else
	if (name==XML_CNAME_RARM)
	{
		emit GetWidget(CODE_RUNARM, widget);
		pitem = new CodeRArm(widget);
	}
	else
	if (name==XML_CNAME_EXTIN)
	{
		emit GetWidget(CODE_EXT_IN, widget);
		pitem = new CodeExtIn(widget);
	}
	else
	if (name==XML_CNAME_EXTOUT)
	{
		emit GetWidget(CODE_EXT_OUT, widget);
		pitem = new CodeExtOut(widget);
	}
    else
    if (name==XML_CNAME_MEXTOUT)
    {
        emit GetWidget(CODE_MEXTOUT, widget);
        pitem = new CodeMExtOut(widget);
    }
    else
    if (name==XML_CNAME_VACUUM)
    {
        emit GetWidget(VCODE_VACUUM, widget);
        pitem = new VCodeVacuum(widget);
    }
    else
    if (name==XML_CNAME_INVACUUM)
    {
        emit GetWidget(CODE_VACUUM, widget);
        pitem = new CodeVacuum(widget);
    }
    else
	if (name==XML_CNAME_PAPER)
	{
        emit GetWidget(CODE_PAPER, widget);
		pitem = new CodePaper(widget);
	}
	else
	if (name==XML_CNAME_MATRIX)
	{
        emit GetWidget(CODE_MATRIX, widget);
		pitem = new CodeLoopMatrix(widget);
	}
    else
    if (name==XML_CNAME_LOOP)
    {
        emit GetWidget(CODE_FREEPOS, widget);
        pitem = new CodeLoopFree(widget);
    }
    else
    if (name==XML_CNAME_CIRCLE)
    {
        emit GetWidget(CODE_CIRCLE, widget);
        pitem = new CodeCircle(widget);
    }
    else
    if (name==XML_CNAME_VISION)
    {
        emit GetWidget(CODE_VISION, widget);
        pitem = new CodeVision(widget);
    }
    else
    if (name==XML_CNAME_SINGLE_LOOP)
    {
        emit GetWidget(CODE_LOOP, widget);
        pitem = new CodeSingleLoop(widget);
    }
    else
    if (name==XML_CNAME_SINGLE_LOOP_FREE)
    {
        emit GetWidget(CODE_LOOPFREE, widget);
        pitem = new CodeSingleLoopFree(widget);
    }
    else
	if (name==XML_CNAME_FOR)
	{
		QString type = reader.attributes().value(XML_ATTR_TYPE).toString();
		if (type==XML_TYPE_CONST)
		{
			emit GetWidget(CODE_FOR_CONST, widget);
			pitem = new CodeFor(widget, CODE_FOR_CONST);
		}
		else
		{
			emit GetWidget(CODE_FOR_VAR, widget);
			pitem = new CodeFor(widget, CODE_FOR_VAR);
		}
	}

	if (pitem)
	{
		pitem->XmlRead(reader);
        m_codelist[procid].append(pitem);
	}
	else
	{
		XmlSkipUnknownElement(reader);
	}
	return true;
}

bool TeachTableModel::XmlReadOptionElement(QXmlStreamReader &reader, int procid)
{
    //QString version = reader.attributes().value(XML_ATTR_VERSION).toString();
    //if (version==XML_VERSION)
    //{
    //    qDebug("program file version error!");
    //    return false;
    //}
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
            if (reader.name()==XML_ELEMENT_ITEM)
            {
                XmlReadItemElement(reader);
            }
            else
            {
                XmlSkipUnknownElement(reader);
                //reader.raiseError(QObject::tr("Not a program file!"));
            }
        }
        else
        {
            reader.readNext();
        }
    }
    return true;
}

bool TeachTableModel::XmlReadItemElement(QXmlStreamReader &reader)
{
    XmlModelItemOption *pitem = new XmlModelItemOption();

	if (pitem)
	{
		pitem->XmlRead(reader);
        m_optlist[m_current_process].append(pitem);
	}
	else
	{
		XmlSkipUnknownElement(reader);
	}
	return true;
}

bool TeachTableModel::XmlReadSinRobotElement(QXmlStreamReader &reader)
{
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
            if (reader.name()==XML_ELEMENT_PROGRAM)
            {
                XmlReadProgramElement(reader, 0);
            }
            else
            if (reader.name()==XML_ELEMENT_PROGRAM1)
            {
                XmlReadProgramElement(reader, 0);
            }
            else
            if (reader.name()==XML_ELEMENT_PROGRAM2)
            {
                XmlReadProgramElement(reader, 1);
            }
            else
            if (reader.name()==XML_ELEMENT_PROGRAM3)
            {
                XmlReadProgramElement(reader, 2);
            }
            else
            if (reader.name()==XML_ELEMENT_OPTION)
            {
                XmlReadOptionElement(reader, 0);
            }
            else
            if (reader.name()==XML_ELEMENT_OPTION1)
            {
                XmlReadOptionElement(reader, 0);
            }
            else
            if (reader.name()==XML_ELEMENT_OPTION2)
            {
                XmlReadOptionElement(reader, 1);
            }
            else
            if (reader.name()==XML_ELEMENT_OPTION3)
            {
                XmlReadOptionElement(reader, 2);
            }
            else
            if (reader.name()==XML_ELEMENT_VAR_INIT)
            {
                XmlReadVarInitElement(reader);
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
#define EPS     0 // (1e-8)
bool TeachTableModel::LoadProgram(QString filename)
{
    m_lasterror = 0;
	QFile file(filename);
	if (!file.open(QFile::ReadOnly|QFile::Text))
	{
		return false;
	}
	ClearProgram();
	QXmlStreamReader reader;
	reader.setDevice(&file);
	{
		reader.readNext();
		while (!reader.atEnd())
		{
			if (reader.isStartElement())
			{
                if (reader.name()==XML_ELEMENT_SINROBOT)
				{
                    // 比较教导程序和系统中version大小
                    float xpgm_version, xml_version;
                    xpgm_version = reader.attributes().value(XML_ATTR_VERSION).toString().toFloat();
                    xml_version = CMBProtocol::XMLFileVersion().toFloat();

                    if (((xml_version - xpgm_version) >= EPS))
                    {
                        XmlReadSinRobotElement(reader);
                    }
                    else
                    {
                        m_lasterror = LOADERROR_VERSION;//?????
                        break;
                    }
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
	}
	file.close();
    if (m_lasterror)
        return false;
    if (reader.hasError())
	{
        m_lasterror = LOADERROR_FORMAT;//?????
        return false;
	}
	else
    if (file.error()!=QFile::NoError)
    {
        m_lasterror = LOADERROR_FILE;//?????
        return false;
    }
	m_ismodifed = false;
    m_current_process = 0;
    if (!m_codelist[1].count())
    {
        AddEndToProc(1);
    }
    if (!m_codelist[2].count())
    {
        AddEndToProc(2);
    }
    UpdateLineNum();
    reset();
    return true;
}

bool TeachTableModel::SaveProgram(QString filename)
{
    QList <quint16> varlist;
	int i;
	QFile file(filename);
	if (!file.open(QFile::WriteOnly|QFile::Text|QFile::Truncate))
	{
		return false;
	}
	QXmlStreamWriter writer(&file);
	writer.setAutoFormatting(true);
	writer.writeStartDocument();
    writer.writeStartElement(XML_ELEMENT_SINROBOT);
    writer.writeAttribute(XML_ATTR_VERSION, CMBProtocol::XMLFileVersion());

    writer.writeStartElement(XML_ELEMENT_PROGRAM1);
    for (i=0; i<m_codelist[0].count(); i++)
    {
        m_codelist[0].at(i)->XmlWrite(writer);
        AddUsrVar(m_codelist[0].at(i), varlist);
    }
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PROGRAM2);
    for (i=0; i<m_codelist[1].count(); i++)
    {
        m_codelist[1].at(i)->XmlWrite(writer);
        AddUsrVar(m_codelist[1].at(i), varlist);
    }
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PROGRAM3);
    for (i=0; i<m_codelist[2].count(); i++)
    {
        m_codelist[2].at(i)->XmlWrite(writer);
        AddUsrVar(m_codelist[2].at(i), varlist);
    }
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_OPTION1);
    for (i=0; i<m_optlist[0].count(); i++)
    {
        m_optlist[0].at(i)->XmlWrite(writer);
    }
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_OPTION2);
    for (i=0; i<m_optlist[1].count(); i++)
    {
        m_optlist[1].at(i)->XmlWrite(writer);
    }
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_OPTION3);
    for (i=0; i<m_optlist[2].count(); i++)
    {
        m_optlist[2].at(i)->XmlWrite(writer);
    }
    writer.writeEndElement();

    UpdateAllUsrVar(varlist);
    writer.writeStartElement(XML_ELEMENT_VAR_INIT);
    for (i=0; i<m_varlist.count(); i++)
    {
        m_varlist.at(i)->XmlWrite(writer);
    }
    writer.writeEndElement();

    writer.writeEndDocument();
	file.flush();
	file.close();
#if defined(Q_WS_QWS)
	sync();
#endif
	if (file.error()!=QFile::NoError)
	{
		return false;
	}
	m_ismodifed = false;
	return true;
}

void TeachTableModel::ClearProgram()
{
    int proc;
	int i;
    for (proc=0; proc<MAX_PROCESS; proc++)
    {
        for (i=0; i<m_codelist[proc].count(); i++)
        {
            delete m_codelist[proc].at(i);
        }
        m_codelist[proc].clear();
        for (i=0; i<m_optlist[proc].count(); i++)
        {
            delete m_optlist[proc].at(i);
        }
        m_optlist[proc].clear();
    }
    for (i=0; i<m_varlist.count(); i++)
    {
        delete m_varlist.at(i);
    }
    m_varlist.clear();
}

bool TeachTableModel::NewProgram(QWidget *form)
{
    int proc;
	int i;
    int flag = 1;   // 添加指令标志位
    for (i=0; i<m_varlist.count(); i++)
    {
        delete m_varlist.at(i);
    }
    m_varlist.clear();
    for (proc=0; proc<MAX_PROCESS; proc++)
    {
        for (i=0; i<m_codelist[proc].count(); i++)
        {
            delete m_codelist[proc].at(i);
        }
        m_codelist[proc].clear();
        for (i=0; i<m_optlist[proc].count(); i++)
        {
            delete m_optlist[proc].at(i);
        }
        m_optlist[proc].clear();
#if (FACTORY == FA_KEHUI)
        if (flag)
        {
            CodePos *pPos = new CodePos(NULL);
            pPos->SetParas(AXES_IDX_Y, 50, 0, 0);
            m_codelist[0].append(pPos);

			CodePArm *pPARM = new CodePArm(NULL);
			pPARM->SetParas(CMBProtocol::GetRotateAtOrigin() ? PRO_ACT_HOZIONTAL : PRO_ACT_VERTIACL, 0);
			m_codelist[0].append(pPARM);

			int pos[] = {0, 0, 0, 0, 0, 0};
			CodeInterp *pInterp = new CodeInterp(NULL);
			pInterp->SetParas(61, 50, pos); // 111101
			m_codelist[0].append(pInterp);

            CodeVacuum *pVacuum = new CodeVacuum(NULL);
            pVacuum->SetParas(false, 5, 63, 63, 0);
            m_codelist[0].append(pVacuum);

            flag = 0;
        }
#endif

#if (FACTORY == FA_KAIBOER)
        if (flag)
        {
            int type;
            if ((CMBProtocol::ReadRotateAtOrigin() == 0) || (CMBProtocol::ReadRotateAtOrigin() == 3))
                type = 0;
            else
                type =1;
            CodePArm *pPARM = new CodePArm(NULL);
            pPARM->SetParas(type, 0);
            m_codelist[0].append(pPARM);

            CodePos *pYPos = new CodePos(NULL);
            pYPos->SetParas(AXES_IDX_Y, 50, 0, 0);
            m_codelist[0].append(pYPos);

            CodePos *pXPos = new CodePos(NULL);
            pXPos->SetParas(AXES_IDX_X, 50, 0, 0);
            m_codelist[0].append(pXPos);

            CodePos *pZPos = new CodePos(NULL);
            pZPos->SetParas(AXES_IDX_Z, 50, 0, 0);
            m_codelist[0].append(pZPos);

            CodeImm *pIMM = new CodeImm(NULL);
            pIMM->SetParas(IMMOUT_EMO, 0);
            m_codelist[0].append(pIMM);

            flag = 0;
        }
#endif

#if ((FACTORY == FA_JINBOYUE) || (FACTORY == FA_JINBOYUE_SPECIAL))
        if (flag)
        {
            CodePos *pZPos1 = new CodePos(NULL);
            pZPos1->SetParas(AXES_IDX_Z, 50, 0, 0);
            m_codelist[0].append(pZPos1);

            CodePos *pXPos1 = new CodePos(NULL);
            pXPos1->SetParas(AXES_IDX_X, 50, 20000, 0);
            m_codelist[0].append(pXPos1);

            CodePArm *pPARM1 = new CodePArm(NULL);
            pPARM1->SetParas(0, 5);
            m_codelist[0].append(pPARM1);

            CodeImm *pIMM1 = new CodeImm(NULL);
            pIMM1->SetParas(IMMOUT_EMO, 0);
            m_codelist[0].append(pIMM1);

            CodePos *pYPos1 = new CodePos(NULL);
            pYPos1->SetParas(AXES_IDX_Y, 50, 30000, 0);
            m_codelist[0].append(pYPos1);

            CodePos *pXPos2 = new CodePos(NULL);
            pXPos2->SetParas(AXES_IDX_X, 50, 30000, 0);
            m_codelist[0].append(pXPos2);

            CodeVacuum *pVacuum1 = new CodeVacuum(NULL);
            pVacuum1->SetParas(true, 5, 1, 1, 0);
            m_codelist[0].append(pVacuum1);

            CodePos *pXPos3 = new CodePos(NULL);
            pXPos3->SetParas(AXES_IDX_X, 50, 20000, 0);
            m_codelist[0].append(pXPos3);

            CodePos *pYPos2 = new CodePos(NULL);
            pYPos2->SetParas(AXES_IDX_Y, 50, 0, 0);
            m_codelist[0].append(pYPos2);

            CodeImm *pIMM2 = new CodeImm(NULL);
            pIMM2->SetParas(IMMOUT_EMC, 0);
            m_codelist[0].append(pIMM2);

            CodePArm *pPARM2 = new CodePArm(NULL);
            pPARM2->SetParas(1, 5);
            m_codelist[0].append(pPARM2);

            CodePos *pZPos2 = new CodePos(NULL);
            pZPos2->SetParas(AXES_IDX_Z, 50, 50000, 0);
            m_codelist[0].append(pZPos2);

            CodePos *pXPos4 = new CodePos(NULL);
            pXPos4->SetParas(AXES_IDX_X, 50, 0, 0);
            m_codelist[0].append(pXPos4);

            CodePos *pYPos3 = new CodePos(NULL);
            pYPos3->SetParas(AXES_IDX_Y, 50, 30000, 0);
            m_codelist[0].append(pYPos3);

            CodeVacuum *pVacuum2 = new CodeVacuum(NULL);
            pVacuum2->SetParas(false, 5, 1, 1, 0);
            m_codelist[0].append(pVacuum2);

            CodePos *pYPos4 = new CodePos(NULL);
            pYPos4->SetParas(AXES_IDX_Y, 50, 0, 0);
            m_codelist[0].append(pYPos4);

            flag = 0;
        }
#endif
        m_codelist[proc].append(new CodeEnd(form));
    }
	return true;
}

void TeachTableModel::InsertCode(XmlModelItem *item, int insertpos)
{
    int i;
    int pos = insertpos;
    int code;
    quint16 var;
    code = item->GetCode();
    if ((code == CODE_MATRIX) || (code == CODE_FREEPOS) || (code == CODE_EXT_IN) || (code == CODE_EXT_OUT) || (code == CODE_LOOP) || (code == CODE_VACUUM) || (code == CODE_LOOPFREE)|| (code == CODE_MEXTOUT))
    {
        var = GetMinCounter();
        if (var == 0)
			xMessageBox::DoWarning(tr("系统提示"), tr("没有可用计数器!"));
        else
        {
            item->SetUserVar(var);
            InsertVar(var, 0, false);
        }
    }
    if (code == VCODE_VACUUM)
    {
        var = GetMinCounter();
        if (var == 0)
			xMessageBox::DoWarning(tr("系统提示"), tr("没有可用计数器!"));
        else
        {
            item->SetUserVar(var, 0);
            InsertVar(var, 0, false);
        }
        var = GetMinCounter();
        if (var == 0)
			xMessageBox::DoWarning(tr("系统提示"), tr("没有可用计数器!"));
        else
        {
            item->SetUserVar(var, 1);
            InsertVar(var, 0, false);
        }
    }
    if (insertpos==-1)
    {
        pos = m_codelist[m_current_process].count();
        m_codelist[m_current_process].append(item);
    }
	else
    {
        if (insertpos)
        {
            if ( m_codelist[m_current_process].at(insertpos-1)->GetFlag()&FLAG_COMBINE)
                item->SetFlag(FLAG_COMBINE);
        }
        m_codelist[m_current_process].insert(insertpos, item);
    }
    for (i=0; i<m_optlist[m_current_process].count(); i++)
	{
        m_optlist[m_current_process].at(i)->InsertCodeAdjust(pos);
	}
    UpdateLineNum();
    reset();
	m_ismodifed = true;
}

void TeachTableModel::RemoveCode(int pos)
{
    int i;
    int code;
    if (pos!=-1)
	{
        code = m_codelist[m_current_process].at(pos)->GetCode();
        if ((code == CODE_MATRIX) || (code == CODE_FREEPOS) || (code == CODE_FOR_VAR) || (code == CODE_OPR) || (code == CODE_MEXTOUT) ||
                (code == CODE_IF) || (code == CODE_EXT_IN) || (code == CODE_EXT_OUT) || (code == CODE_LOOP) || (code == CODE_VACUUM) || (code == CODE_LOOPFREE))
        {
            for (i=0; i<m_varlist.count(); i++)
            {
                if (m_varlist.at(i)->GetVar() == m_codelist[m_current_process].at(pos)->GetUserVar())
                {
                    RemoveVar(i);
                    break;
                }
            }
        }
        if (code == VCODE_VACUUM)
        {
            for (i=0; i<m_varlist.count(); i++)
            {
                if (m_varlist.at(i)->GetVar() == m_codelist[m_current_process].at(pos)->GetUserVar(0))
                {
                    RemoveVar(i);
                }
                if (m_varlist.at(i)->GetVar() == m_codelist[m_current_process].at(pos)->GetUserVar(1))
                {
                    RemoveVar(i);
                }
            }
        }
        if (pos >0)
        {
            if ((m_codelist[m_current_process].at(pos-1)->GetFlag()&FLAG_COMBINE)&&
                (!(m_codelist[m_current_process].at(pos)->GetFlag()&FLAG_COMBINE)))
            {
                m_codelist[m_current_process].at(pos-1)->ClrFlag(FLAG_COMBINE);
            }
        }
        delete m_codelist[m_current_process].at(pos);
        m_codelist[m_current_process].removeAt(pos);
        for (i=0; i<m_optlist[m_current_process].count(); i++)
        {
            m_optlist[m_current_process].at(i)->RemoveCodeAdjust(pos);
        }
        UpdateLineNum();
        reset();
        m_ismodifed = true;
    }
}

void TeachTableModel::ShowUI(int pos, bool show)
{
    if (pos<m_codelist[m_current_process].count())
	{
        if (show)
            m_codelist[m_current_process].at(pos)->Update(false);
        m_codelist[m_current_process].at(pos)->ShowUI(show);
    }
}

XmlModelItem* TeachTableModel::GetItem(int pos)
{
    if (pos<m_codelist[m_current_process].count())
        return m_codelist[m_current_process].at(pos);
    return 0;
}

bool TeachTableModel::IsCodeDisable(int pos) const                            // 判断指令是否有效
{
#if IS_XEDITOR
#else
    int i;
    if (pos<m_codelist[m_current_process].count())
    {
        for (i=0; i<m_optlist[m_current_process].count(); i++)
        {
            if (m_optlist[m_current_process].at(i)->IsInclude(pos))
                return !m_optlist[m_current_process].at(i)->IsEnable();
        }
    }
#endif
    return false;
}

XmlModelItemOption* TeachTableModel::GetItemOpt(int pos)
{
    if (pos<m_optlist[m_current_process].count())
        return m_optlist[m_current_process].at(pos);
    return 0;
}

bool TeachTableModel::IsInCombine(int pos)
{
    if (m_codelist[m_current_process].at(pos)->GetFlag()&FLAG_COMBINE)
        return true;
    if (pos)
    {
        if (m_codelist[m_current_process].at(pos-1)->GetFlag()&FLAG_COMBINE)
            return true;
    }
    return false;
}

void TeachTableModel::MoveUp(int pos)
{
    int i;
    if (IsInCombine(pos))
    {
        if (pos)
        {
            if ((m_codelist[m_current_process].at(pos)->GetFlag()&FLAG_COMBINE) &&
                (!(m_codelist[m_current_process].at(pos-1)->GetFlag()&FLAG_COMBINE)))
            {
                m_codelist[m_current_process].at(pos)->ClrFlag(FLAG_COMBINE);
            }
            else
            {
                if ((m_codelist[m_current_process].at(pos-1)->GetFlag()&FLAG_COMBINE) &&
                    (!(m_codelist[m_current_process].at(pos)->GetFlag()&FLAG_COMBINE)))
                {
                    m_codelist[m_current_process].at(pos-1)->ClrFlag(FLAG_COMBINE);
                    m_codelist[m_current_process].at(pos)->SetFlag(FLAG_COMBINE);
                }
            }
        }
        else
        {
            m_codelist[m_current_process].at(pos)->ClrFlag(FLAG_COMBINE);
        }
    }
    else
    {
        if (pos)
        {
            if (IsInCombine(pos-1))
            {
                m_codelist[m_current_process].at(pos)->SetFlag(FLAG_COMBINE);
            }
        }
    }
    m_codelist[m_current_process].move(pos, pos-1);
    for (i=0; i<m_optlist[m_current_process].count(); i++)
    {
        m_optlist[m_current_process].at(i)->MoveCodeAdjust(pos, pos-1);
    }
    UpdateLineNum();
    reset();
	m_ismodifed = true;
}

void TeachTableModel::MoveDown(int pos)
{
    int i;
    if (IsInCombine(pos))
    {
        if (pos)
        {
            if ((m_codelist[m_current_process].at(pos-1)->GetFlag()&FLAG_COMBINE) &&
                (!(m_codelist[m_current_process].at(pos)->GetFlag()&FLAG_COMBINE)))
            {
                m_codelist[m_current_process].at(pos-1)->ClrFlag(FLAG_COMBINE);
            }
            else
            {
                if (pos<m_codelist[m_current_process].count()-1)
                {
                    if ((m_codelist[m_current_process].at(pos)->GetFlag()&FLAG_COMBINE) &&
                        (!(m_codelist[m_current_process].at(pos+1)->GetFlag()&FLAG_COMBINE)))
                    {
                        m_codelist[m_current_process].at(pos+1)->SetFlag(FLAG_COMBINE);
                        m_codelist[m_current_process].at(pos)->ClrFlag(FLAG_COMBINE);
                    }
                }
            }
        }
    }
    else
    {
        if (pos<m_codelist[m_current_process].count()-1)
        {
            if (IsInCombine(pos+1))
            {
                m_codelist[m_current_process].at(pos)->SetFlag(FLAG_COMBINE);
            }
        }
    }


    m_codelist[m_current_process].move(pos, pos+1);
    for (i=0; i<m_optlist[m_current_process].count(); i++)
    {
        m_optlist[m_current_process].at(i)->MoveCodeAdjust(pos, pos+1);
    }
    UpdateLineNum();
    reset();
	m_ismodifed = true;
}

void TeachTableModel::CodeCombine(int pos)
{
    if (pos)
    {
        if (pos<m_codelist[m_current_process].count())
        {
            if (m_codelist[m_current_process].at(pos)->GetCode() != CODE_END)
            {
                if (!(m_codelist[m_current_process].at(pos-1)->GetFlag() & FLAG_COMBINE))
                {
                    m_codelist[m_current_process].at(pos-1)->SetFlag(FLAG_COMBINE);
                    UpdateLineNum();
                    reset();
                    m_ismodifed = true;
                }
            }
        }
    }
}

void TeachTableModel::CodeSeparate(int pos)
{
    if (pos>0)
    {
        if (m_codelist[m_current_process].at(pos-1)->GetFlag() & FLAG_COMBINE)
        {
            m_codelist[m_current_process].at(pos-1)->ClrFlag(FLAG_COMBINE);
        }
        else
        {
            m_codelist[m_current_process].at(pos)->ClrFlag(FLAG_COMBINE);
        }
        UpdateLineNum();
        reset();
        m_ismodifed = true;
    }
    if (pos == 0)
    {
        m_codelist[m_current_process].at(pos)->ClrFlag(FLAG_COMBINE);
        UpdateLineNum();
        reset();
        m_ismodifed = true;
    }
}

void TeachTableModel::InsertOpt(XmlModelItemOption *item, int insertpos)
{
    if (insertpos==-1)
        m_optlist[m_current_process].append(item);
    else
    {
        m_optlist[m_current_process].insert(insertpos, item);
    }
    //reset();
    m_ismodifed = true;
}

void TeachTableModel::RemoveOpt(int pos)
{
    if (pos!=-1)
    {
        delete m_optlist[m_current_process].at(pos);
        m_optlist[m_current_process].removeAt(pos);
        //reset();
        m_ismodifed = true;
    }
}

void TeachTableModel::EnableOption(int pos, bool enable)
{
    if (pos < m_optlist[m_current_process].count())
    {
        m_optlist[m_current_process].at(pos)->Enable(enable);
        m_ismodifed = true;
    }
}

void TeachTableModel::SetCurrentOpt(int pos)
{
    m_currentopt = pos;
	reset();
}

void TeachTableModel::SetOptNameEn(int pos, QString name)
{
    if (pos>=0)
    {
        if (pos < m_optlist[m_current_process].count())
        {
            if (m_optlist[m_current_process].at(pos)->GetNameEn()!=name)
            {
                m_optlist[m_current_process].at(pos)->SetNameEn(name);
                m_ismodifed = true;
            }
        }
    }
}

void TeachTableModel::SetOptNameDis(int pos, QString name)
{
    if (pos>=0)
    {
        if (pos < m_optlist[m_current_process].count())
        {
            if (m_optlist[m_current_process].at(pos)->GetNameDis()!=name)
            {
                m_optlist[m_current_process].at(pos)->SetNameDis(name);
                m_ismodifed = true;
            }
        }
    }
}

/*void TeachTableModel::MoveUpOpt(int pos)
{
    m_optlist.move(pos, pos-1);
    //reset();
	m_ismodifed = true;
}

void TeachTableModel::MoveDownOpt(int pos)
{
    m_optlist.move(pos, pos+1);
    //reset();
    m_ismodifed = true;
}
*/
/*bool TeachTableModel::SetGlobalSpeed(quint32 pos, quint8 speed)
{
	bool ret;
    ret =  m_codelist[m_current_process].at(pos)->SetParameters(PAR_SPEED, speed);
	if (ret)
	{
		reset();
		m_ismodifed = true;
	}
	return ret;
}*/

void TeachTableModel::SavePara(int pos, bool isReset)
{
    if (pos<m_codelist[m_current_process].count())
	{
        if (m_codelist[m_current_process].at(pos)->Update())
		{
			m_ismodifed = true;
			if (isReset)
            {
                UpdateLineNum();
                reset();
            }
		}
	}
}

// 生成当前程序所有的机器代码
int TeachTableModel::GenerateCodes(uint8_t procid, quint16 *code, quint32 *para)
{
	int i;
	int idx = 0;
    if (procid<MAX_PROCESS)
    {
        for (i=0; i<m_codelist[procid].count(); i++)
        {
            if (!IsCodeDisable(i))
            {
                int codes = m_codelist[procid].at(i)->GetCodes();
                if (idx+codes>4096) return -1;

                m_codelist[procid].at(i)->GenerateCode(code+idx, para+idx);
                idx += codes;
            }
        }
    }
    return idx;
}


bool TeachTableModel::IsModified(int pos)
{
    if (pos<m_codelist[m_current_process].count())
        return m_codelist[m_current_process].at(pos)->IsModified();
	return false;
}

/*int TeachTableModel::GetCombineBeginPos(int endpos)
{
	int i = endpos;
	for (; i>=0; i--)
	{
        if (m_codelist[m_current_process].at(i)->GetCode()==CODE_CBEGIN) break;
	}
	return i;
}*/
int TeachTableModel::GetCombineEndPos(int beginpos)
{
    int i = beginpos;
    for (; i<m_codelist[m_current_process].count(); i++)
    {
        //if (m_codelist[m_current_process].at(i)->GetCode()==CODE_CEND) break;
        if (!(m_codelist[m_current_process].at(i)->GetFlag()&FLAG_COMBINE)) break;
    }
    return i;
}
int TeachTableModel::GetPosByPcPointer(int pc)
{
	int i;
	int idx = 0;
    for (i=0; i<m_codelist[m_current_process].count(); i++)
	{
        if (IsCodeDisable(i)) continue;
        int codes = m_codelist[m_current_process].at(i)->GetCodes();
		if ((pc>=idx)&&(pc<idx+codes)) return i;
		idx += codes;
	}
	return idx;
}

int TeachTableModel::GetPcPointer(int pos)      //通过指令列表位置取得对应的主板PC指针
{
	int i;
	int idx = 0;
    for (i=0; i<m_codelist[m_current_process].count(); i++)
	{
		if (i==pos) break;
        if (!IsCodeDisable(i))
        idx += m_codelist[m_current_process].at(i)->GetCodes();
	}
	return idx;
}
// 生成指定指令的代码
int TeachTableModel::GenerateCode(int pos, quint16 *code, quint32* para)
{
    if (IsCodeDisable(pos)) return 0;
    m_codelist[m_current_process].at(pos)->GenerateCode(code, para, 0);
    return m_codelist[m_current_process].at(pos)->GetCodes();
}
// 检查程序是否有效
bool TeachTableModel::CheckProgram()
{
    m_infor = 0;
    int containAxesbmp[MAX_PROCESS];
    int i;
    for (i = 0; i < MAX_PROCESS; i++)
    {
        containAxesbmp[i] = 0;
        for (m_check_idx=0; m_check_idx<m_codelist[i].count(); m_check_idx++)
        {
            //if ((m_codelist[i].at(m_check_idx)->GetCode())==CODE_CBEGIN)
            if (m_codelist[i].at(m_check_idx)->GetFlag()&FLAG_COMBINE)
            {
                if (CheckCombine(i)==false) return false;
                continue;
            }
            if ((m_codelist[i].at(m_check_idx)->GetCode())==CODE_POS)
            {
                CodePos* ppos = (CodePos*)m_codelist[i].at(m_check_idx);
                containAxesbmp[i] |= ppos->GetAxesbmp();
            }
            if ((m_codelist[i].at(m_check_idx)->GetCode())==CODE_EXTPOS)
            {
                CodeExtPos* ppos = (CodeExtPos*)m_codelist[i].at(m_check_idx);
                containAxesbmp[i] |= ppos->GetAxesbmp();
            }
            if ((m_codelist[i].at(m_check_idx)->GetCode())==CODE_MATRIX)
            {
                if (((CodeLoopMatrix*)(m_codelist[i].at(m_check_idx)))->isrunner())
                    containAxesbmp[i] |= SRV_RAHOR|SRV_RAVER|SRV_TRV;
                else
                    containAxesbmp[i] |= SRV_PAHOR|SRV_PAVER|SRV_TRV;
            }
            if ((m_codelist[i].at(m_check_idx)->GetCode())==CODE_FREEPOS)
            {
                containAxesbmp[i] |= SRV_PAHOR|SRV_PAVER|SRV_TRV;
            }
            if ((m_codelist[i].at(m_check_idx)->GetCode())==CODE_LOOP)
            {
                CodeSingleLoop* psingleloop = (CodeSingleLoop*)m_codelist[i].at(m_check_idx);
                if (psingleloop->GetAxes() == AXIS_IDX_PHOR) containAxesbmp[i] |= SRV_PAHOR;
                if (psingleloop->GetAxes() == AXIS_IDX_PVER) containAxesbmp[i] |= SRV_PAVER;
                if (psingleloop->GetAxes() == AXIS_IDX_TRV) containAxesbmp[i] |= SRV_TRV;
                if (psingleloop->GetAxes() == AXIS_IDX_EXT) containAxesbmp[i] |= SRV_EXT;
                if (psingleloop->GetAxes() == AXIS_IDX_RHOR) containAxesbmp[i] |= SRV_RAHOR;
                if (psingleloop->GetAxes() == AXIS_IDX_RVER) containAxesbmp[i] |= SRV_RAVER;
            }
            if ((m_codelist[i].at(m_check_idx)->GetCode())==CODE_PAPER)
            {
                CodePaper* ppaper = (CodePaper*)m_codelist[i].at(m_check_idx);
                if (ppaper->GetAxes() == AXIS_IDX_PHOR) containAxesbmp[i] |= SRV_PAHOR;
                if (ppaper->GetAxes() == AXIS_IDX_PVER) containAxesbmp[i] |= SRV_PAVER;
                if (ppaper->GetAxes() == AXIS_IDX_TRV) containAxesbmp[i] |= SRV_TRV;
                if (ppaper->GetAxes() == AXIS_IDX_EXT) containAxesbmp[i] |= SRV_EXT;
                if (ppaper->GetAxes() == AXIS_IDX_RHOR) containAxesbmp[i] |= SRV_RAHOR;
                if (ppaper->GetAxes() == AXIS_IDX_RVER) containAxesbmp[i] |= SRV_RAVER;
            }
            if ((m_codelist[i].at(m_check_idx)->GetCode())==CODE_SPEED)
            {
                CodeSpeed* pspeed = (CodeSpeed*)m_codelist[i].at(m_check_idx);
                if (pspeed->GetAxes()&SRV_PAHOR) containAxesbmp[i] |= SRV_PAHOR;
                if (pspeed->GetAxes()&SRV_PAVER) containAxesbmp[i] |= SRV_PAVER;
                if (pspeed->GetAxes()&SRV_TRV) containAxesbmp[i] |= SRV_TRV;
                if (pspeed->GetAxes()&SRV_RAVER) containAxesbmp[i] |= SRV_RAVER;
                if (pspeed->GetAxes()&SRV_RAHOR) containAxesbmp[i] |= SRV_RAHOR;
                if (pspeed->GetAxes()&SRV_EXT) containAxesbmp[i] |= SRV_EXT;
            }
/*            if ((m_codelist[i].at(m_check_idx)->GetCode())==CODE_OPR)
            {
                CodeOperator* poperator = (CodeOperator*)m_codelist[i].at(m_check_idx);
                if (poperator->GetVar() > MAX_USER_VAR)
                m_cur_pos = m_check_idx;
                m_err_string = QString(tr("不能对计数器进行四则及赋值运算！"));
                return false;
            }*/

            if ((m_codelist[i].at(m_check_idx)->GetCode())==CODE_IF)
            {
                if (Checkif(i)==false) return false;
                continue;
            }
            if (((m_codelist[i].at(m_check_idx)->GetCode())==CODE_FOR_VAR)||
                ((m_codelist[i].at(m_check_idx)->GetCode())==CODE_FOR_CONST))
            {
                if (Checkfor(i)==false) return false;
                continue;
            }
            if ((m_codelist[i].at(m_check_idx)->GetCode())==CODE_TBEGIN)
            {
                if (CheckPath(i) == false) return false;
                continue;
            }

            if (((m_codelist[i].at(m_check_idx)->GetCode())==CODE_ENDIF)||
                ((m_codelist[i].at(m_check_idx)->GetCode())==CODE_ELSE))
            {
                m_cur_pos = m_check_idx;
                m_err_string = QString(tr("条件结束没有相应的条件开始！"));
                return false;
            }
            if ((m_codelist[i].at(m_check_idx)->GetCode())==CODE_ENDFOR)
            {
                m_cur_pos = m_check_idx;
                m_err_string = QString(tr("循环结束没有相应的循环开始！"));
                return false;
            }
            if ((m_codelist[i].at(m_check_idx)->GetCode())==CODE_BREAK)
            {
                m_cur_pos = m_check_idx;
                m_err_string = QString(tr("循环跳出只能在循环中！"));
                return false;
            }
/*            if ((m_codelist[i].at(m_check_idx)->GetCode())==CODE_CEND)
            {
                m_cur_pos = m_check_idx;
                m_err_string = QString(tr("组合结束没有相应的组合开始！"));
                return false;
            }*/
            if ((m_codelist[i].at(m_check_idx)->GetCode())==CODE_TEND)
            {
                m_cur_pos = m_check_idx;
                m_err_string = QString(tr("路径结束没有相应的路径开始！"));
                return false;
            }
        }
    }
#if (FACTORY != FA_WEILIHE)
	if (containAxesbmp[0]&containAxesbmp[1])
	{
		m_err_string = QString(tr("进程一和进程二不能同时包含同一个轴定位操作！"));
		return false;
	}

	if (containAxesbmp[1]&containAxesbmp[2])
	{
		m_err_string = QString(tr("进程二和进程三不能同时包含同一个轴定位操作！"));
		return false;
	}

	if (containAxesbmp[0]&containAxesbmp[2])
	{
		m_err_string = QString(tr("进程一和进程三不能同时包含同一个轴定位操作！"));
		return false;
	}
#endif

    return true;
}

bool TeachTableModel::Checkif(quint8 procid)
{
	m_cur_pos = m_check_idx++;
    for (; m_check_idx<m_codelist[procid].count(); m_check_idx++)
	{
        //if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_CBEGIN)
        if (m_codelist[procid].at(m_check_idx)->GetFlag()&FLAG_COMBINE)
        {
            if (CheckCombine(procid)==false) return false;
            continue;
        }
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_IF)
		{
            if (Checkif(procid)==false) return false;
			continue;
		}
        if (((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_FOR_VAR)||
            ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_FOR_CONST))
		{
            if (Checkfor(procid)==false) return false;
			continue;
		}
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_TBEGIN)
        {
            if (CheckPath(procid) == false) return false;
            continue;
        }

        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_ENDIF)
		{
			return true;
		}
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_BREAK)
		{
			if (m_infor==0)
			{
				m_cur_pos = m_check_idx;
				m_err_string = QString(tr("循环跳出只能在循环中！"));
				return false;
			}
		}
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_ENDFOR)
		{
			m_cur_pos = m_check_idx;
			m_err_string = QString(tr("条件语句中，循环结束没有相应的循环开始！"));
			return false;
		}
/*        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_CEND)
		{
			m_cur_pos = m_check_idx;
			m_err_string = QString(tr("条件语句中，组合结束没有相应的组合开始！"));
			return false;
        }*/
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_TEND)
        {
            m_cur_pos = m_check_idx;
            m_err_string = QString(tr("条件语句中，路径结束没有相应的路径开始！"));
            return false;
        }
    }
	m_err_string = QString(tr("没有相应的条件结束！"));
	return false;
}

bool TeachTableModel::Checkfor(quint8 procid)
{
	m_infor++;
	m_cur_pos = m_check_idx++;
    for (; m_check_idx<m_codelist[procid].count(); m_check_idx++)
	{
        //if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_CBEGIN)
        if (m_codelist[procid].at(m_check_idx)->GetFlag()&FLAG_COMBINE)
        {
            if (CheckCombine(procid)==false) return false;
            continue;
        }
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_IF)
		{
            if (Checkif(procid)==false) return false;
			continue;
		}
        if (((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_FOR_VAR)||
            ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_FOR_CONST))
		{
            if (Checkfor(procid)==false) return false;
			continue;
		}
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_TBEGIN)
        {
            if (CheckPath(procid) == false) return false;
            continue;
        }

        if (((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_ENDIF)||
            ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_ELSE))
		{
			m_cur_pos = m_check_idx;
			m_err_string = QString(tr("循环语句中，条件结束没有相应的条件开始！"));
			return false;
		}
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_END)
		{
			m_cur_pos = m_check_idx;
			m_err_string = QString(tr("循环语句中，不能使用程序结束语句！"));
			return false;
		}
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_ENDFOR)
		{
			//m_check_idx++;
			return true;
		}
/*        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_CEND)
		{
			m_cur_pos = m_check_idx;
			m_err_string = QString(tr("组合结束没有相应的组合开始！"));
			return false;
        }*/
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_TEND)
        {
            m_cur_pos = m_check_idx;
            m_err_string = QString(tr("循环语句中，路径结束没有相应的路径开始！"));
            return false;
        }
    }
	m_err_string = QString(tr("没有相应的循环结束！"));
	m_infor--;
	return false;
}

bool TeachTableModel::CheckCombine(quint8 procid)
{
	bool enterif = false;
	QMap<int, quint8> map;
	quint8 combine_count = 0;
    quint32 mask = 0;
//    m_cur_pos = m_check_idx++;
    m_cur_pos = m_check_idx;
    for (; m_check_idx<m_codelist[procid].count(); m_check_idx++)
	{
		combine_count++;
        if 	((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_ELSE)
		{
			m_cur_pos = m_check_idx;
			m_err_string = QString(tr("组合中不能使用条件否则语句！"));
			return false;
		}
        if 	((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_CIRCLE)
        {
            m_cur_pos = m_check_idx;
            m_err_string = QString(tr("组合中不能使用喷雾指令！"));
            return false;
        }
        if 	((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_IF)
		{
			if (enterif == true)
			{
				m_cur_pos = m_check_idx;
				m_err_string = QString(tr("组合中条件语句不能嵌套！"));
				return false;
			}
			else
				enterif = true;
			continue;
		}
        if 	((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_ENDIF)
		{
			if (enterif != true)
			{
				m_cur_pos = m_check_idx;
				m_err_string = QString(tr("组合中条件语句不配对，缺少条件开始！"));
				return false;
			}
			else
				enterif = false;
		}
        if (((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_FOR_VAR)||
            ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_FOR_CONST)||
            ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_BREAK)||
            ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_ENDFOR))
		{
            m_cur_pos = m_check_idx;
			m_err_string = QString(tr("组合中不能使用循环语句！"));
			return false;
		}
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_TEND)
		{
			m_cur_pos = m_check_idx;
			m_err_string = QString(tr("组合中不能使用路径语句！"));
			return false;
		}
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_TBEGIN)
		{
			m_cur_pos = m_check_idx;
			m_err_string = QString(tr("组合中不能使用路径语句！"));
			return false;
		}
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_END)
        {
            m_cur_pos = m_check_idx;
			m_err_string = QString(tr("组合中不能使用程序结束语句！"));
            return false;
        }
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_CUSTOMER)
		{
			m_cur_pos = m_check_idx;
            m_err_string = QString(tr("组合中不能调用原点归位指令！"));
			return false;
        }
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_FREEPOS)
        {
            m_cur_pos = m_check_idx;
            m_err_string = QString(tr("组合中不能使用循环定位指令！"));
            return false;
        }
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_MATRIX)
        {
            m_cur_pos = m_check_idx;
            m_err_string = QString(tr("组合中不能使用矩阵指令！"));
            return false;
        }
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_LOOP)
        {
            CodeSingleLoop* ploop = (CodeSingleLoop*)m_codelist[procid].at(m_check_idx);
            if (ploop->GetAxes() == AXES_IDX_Y)
            {
                if (mask&COMBINE_ACT_MASK_Y_SERVO)
            {
                m_cur_pos = m_check_idx;
                m_err_string = QString(tr("组合中只能有一条Y轴循环定位！"));
                return false;
            }
                mask |= COMBINE_ACT_MASK_Y_SERVO;
            }
            else
            if (ploop->GetAxes() == AXES_IDX_Z)
            {
                if (mask&COMBINE_ACT_MASK_Z_SERVO)
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("组合中只能有一条Z轴循环定位！"));
                    return false;
                }
                mask |= COMBINE_ACT_MASK_Z_SERVO;
            }
            else
            if (ploop->GetAxes() == AXES_IDX_X)
            {
                if (mask&COMBINE_ACT_MASK_X_SERVO)
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("组合中只能有一条X轴循环定位！"));
                    return false;
                }
                mask |= COMBINE_ACT_MASK_X_SERVO;
            }
            else
            if (ploop->GetAxes() == AXES_IDX_A)
            {
                if (mask&COMBINE_ACT_MASK_A_SERVO)
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("组合中只能有一条A轴循环定位！"));
                    return false;
                }
                mask |= COMBINE_ACT_MASK_A_SERVO;
            }
            else
            if (ploop->GetAxes() == AXES_IDX_B)
            {
                if (mask&COMBINE_ACT_MASK_B_SERVO)
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("组合中只能有一条B轴循环定位！"));
                    return false;
                }
                mask |= COMBINE_ACT_MASK_B_SERVO;
            }
            else
            {
                if (mask&COMBINE_ACT_MASK_C_SERVO)
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("组合中只能有一条C轴循环定位！"));
                    return false;
                }
                mask |= COMBINE_ACT_MASK_C_SERVO;
            }
        }
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_PAPER)
        {
            m_cur_pos = m_check_idx;
            m_err_string = QString(tr("组合中不能使用搜索指令！"));
            return false;
        }
       if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_WAIT)
		{
			m_cur_pos = m_check_idx;
			m_err_string = QString(tr("组合中不能使用等待语句！"));
			return false;
		}
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_DELAY)
		{
			m_cur_pos = m_check_idx;
			m_err_string = QString(tr("组合中不能使用延时语句！"));
			return false;
		}
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_EXTPOS)
        {
            CodeExtPos* ppos = (CodeExtPos*)m_codelist[procid].at(m_check_idx);
            if (ppos->GetAxesbmp()&(1<<AXES_IDX_Y))
            {
                if (mask&COMBINE_ACT_MASK_Y_SERVO)
            {
                m_cur_pos = m_check_idx;
                m_err_string = QString(tr("组合中只能有一条Y定位！"));
                return false;
            }
                mask |= COMBINE_ACT_MASK_Y_SERVO;
            }
            else
            if (ppos->GetAxesbmp()&(1<<AXES_IDX_Z))
            {
                if (mask&COMBINE_ACT_MASK_Z_SERVO)
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("组合中只能有一条Z轴定位！"));
                    return false;
                }
                mask |= COMBINE_ACT_MASK_Z_SERVO;
            }
            else
            if (ppos->GetAxesbmp()&(1<<AXES_IDX_X))
            {
                if (mask&COMBINE_ACT_MASK_X_SERVO)
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("组合中只能有一条X轴定位！"));
                    return false;
                }
                mask |= COMBINE_ACT_MASK_X_SERVO;
            }
            else
            if (ppos->GetAxesbmp()&(1<<AXES_IDX_A))
            {
                if (mask&COMBINE_ACT_MASK_A_SERVO)
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("组合中只能有一条A轴定位！"));
                    return false;
                }
                mask |= COMBINE_ACT_MASK_A_SERVO;
            }
            else
            if (ppos->GetAxesbmp()&(1<<AXES_IDX_B))
            {
                if (mask&COMBINE_ACT_MASK_B_SERVO)
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("组合中只能有一条B轴定位！"));
                    return false;
                }
                mask |= COMBINE_ACT_MASK_B_SERVO;
            }
            else
            {
                if (mask&COMBINE_ACT_MASK_C_SERVO)
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("组合中只能有一条C轴定位！"));
                    return false;
                }
                mask |= COMBINE_ACT_MASK_C_SERVO;
            }
        }
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_POS)
		{
            CodePos* ppos = (CodePos*)m_codelist[procid].at(m_check_idx);
            if (ppos->GetAxesbmp()&(1<<AXES_IDX_Y))
            {
                if (mask&COMBINE_ACT_MASK_Y_SERVO)
			{
				m_cur_pos = m_check_idx;
                m_err_string = QString(tr("组合中只能有一条Y定位！"));
				return false;
			}
                mask |= COMBINE_ACT_MASK_Y_SERVO;
            }
            else
            if (ppos->GetAxesbmp()&(1<<AXES_IDX_Z))
            {
                if (mask&COMBINE_ACT_MASK_Z_SERVO)
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("组合中只能有一条Z轴定位！"));
                    return false;
                }
                mask |= COMBINE_ACT_MASK_Z_SERVO;
            }
            else
            if (ppos->GetAxesbmp()&(1<<AXES_IDX_X))
            {
                if (mask&COMBINE_ACT_MASK_X_SERVO)
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("组合中只能有一条X轴定位！"));
                    return false;
                }
                mask |= COMBINE_ACT_MASK_X_SERVO;
            }
            else
            if (ppos->GetAxesbmp()&(1<<AXES_IDX_A))
            {
                if (mask&COMBINE_ACT_MASK_A_SERVO)
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("组合中只能有一条A轴定位！"));
                    return false;
                }
                mask |= COMBINE_ACT_MASK_A_SERVO;
            }
            else
            if (ppos->GetAxesbmp()&(1<<AXES_IDX_B))
            {
                if (mask&COMBINE_ACT_MASK_B_SERVO)
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("组合中只能有一条B轴定位！"));
                    return false;
                }
                mask |= COMBINE_ACT_MASK_B_SERVO;
            }
            else
            {
                if (mask&COMBINE_ACT_MASK_C_SERVO)
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("组合中只能有一条C轴定位！"));
                    return false;
                }
                mask |= COMBINE_ACT_MASK_C_SERVO;
            }
		}
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_INTERP)
        {
            CodeInterp* pinterp = (CodeInterp*)m_codelist[procid].at(m_check_idx);
            if (pinterp->GetAxesbmp()&(1<<AXES_IDX_Y))
            {
                if (mask&COMBINE_ACT_MASK_Y_SERVO)
            {
                m_cur_pos = m_check_idx;
                m_err_string = QString(tr("组合中只能有一条Y轴插补定位！"));
                return false;
            }
                mask |= COMBINE_ACT_MASK_Y_SERVO;
            }
//            else
            if (pinterp->GetAxesbmp()&(1<<AXES_IDX_Z))
            {
                if (mask&COMBINE_ACT_MASK_Z_SERVO)
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("组合中只能有一条Z轴插补定位！"));
                    return false;
                }
                mask |= COMBINE_ACT_MASK_Z_SERVO;
            }
//            else
            if (pinterp->GetAxesbmp()&(1<<AXES_IDX_X))
            {
                if (mask&COMBINE_ACT_MASK_X_SERVO)
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("组合中只能有一条X轴插补定位！"));
                    return false;
                }
                mask |= COMBINE_ACT_MASK_X_SERVO;
            }
//            else
            if (pinterp->GetAxesbmp()&(1<<AXES_IDX_A))
            {
                if (mask&COMBINE_ACT_MASK_A_SERVO)
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("组合中只能有一条A轴插补定位！"));
                    return false;
                }
                mask |= COMBINE_ACT_MASK_A_SERVO;
            }
//            else
            if (pinterp->GetAxesbmp()&(1<<AXES_IDX_B))
            {
                if (mask&COMBINE_ACT_MASK_B_SERVO)
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("组合中只能有一条B轴插补定位！"));
                    return false;
                }
                mask |= COMBINE_ACT_MASK_B_SERVO;
            }
//            else
            if (pinterp->GetAxesbmp()&(1<<AXES_IDX_C))
            {
                if (mask&COMBINE_ACT_MASK_C_SERVO)
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("组合中只能有一条C轴插补定位！"));
                    return false;
                }
                mask |= COMBINE_ACT_MASK_C_SERVO;
            }
        }
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_PROARM)
		{
            if (mask&COMBINE_ACT_MASK_PRO_HOR_VER)
			{
				m_cur_pos = m_check_idx;
				m_err_string = QString(tr("组合中不能有两个正臂倒角动作！"));
				return false;
			}
            mask |= COMBINE_ACT_MASK_PRO_HOR_VER;
		}
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_RUNARM)
		{
            int type = ((CodeRArm*)m_codelist[procid].at(m_check_idx))->GetType();
            if ((type==RUN_ACT_ADVANCE)||
                (type==RUN_ACT_RETURN))
			{
                if (mask&COMBINE_ACT_MASK_RUN_ADV_RET)
				{
					m_cur_pos = m_check_idx;
					m_err_string = QString(tr("组合中不能有两个副臂引拔动作！"));
					return false;
				}
                mask |= COMBINE_ACT_MASK_RUN_ADV_RET;
			}
            if ((type==RUN_ACT_DESCENT)||
                (type==RUN_ACT_ASCENT))
			{
                if (mask&COMBINE_ACT_MASK_RUN_ASC_DES)
				{
					m_cur_pos = m_check_idx;
					m_err_string = QString(tr("组合中不能有两个副臂上下动作！"));
					return false;
				}
                mask |= COMBINE_ACT_MASK_RUN_ASC_DES;
			}
		}
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_EXT_OUT)
		{
            CodeExtOut* ext = (CodeExtOut*)m_codelist[procid].at(m_check_idx);
            if (map.contains(ext->GetVar()))
			{
				m_cur_pos = m_check_idx;
				m_err_string = QString(tr("组合中两个扩展输出动作不能控制同一个输出！"));
				return false;
			}
            map[ext->GetVar()] = 1;
		}
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_EXT_IN)
        {
            CodeExtIn* ext = (CodeExtIn*)m_codelist[procid].at(m_check_idx);
            if (map.contains(ext->GetVar()))
            {
                m_cur_pos = m_check_idx;
                m_err_string = QString(tr("组合中两个扩展输入动作不能控制同一个输入！"));
                return false;
            }
            map[ext->GetVar()] = 1;
        }
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==VCODE_VACUUM)
        {
            VCodeVacuum* vac = (VCodeVacuum*)m_codelist[procid].at(m_check_idx);
            if (map.contains(vac->GetVar(0))||map.contains(vac->GetVar(1)))
            {
                m_cur_pos = m_check_idx;
                m_err_string = QString(tr("组合中扩展(或治具)动作不能控制同一个输入/输出！"));
                return false;
            }
            map[vac->GetVar(0)] = 1;
            map[vac->GetVar(1)] = 1;
        }
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_VACUUM)
        {
            CodeVacuum* vac = (CodeVacuum*)m_codelist[procid].at(m_check_idx);
            if (map.contains(0xFFFF0000))
            {
                if (map[0xFFFF0000]&vac->GetOutBmp())
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("组合中治具动作不能控制相同输出！"));
                    return false;
                }
            }
            if (map.contains(0xFFFF0001))
            {
                if (map[0xFFFF0001]&vac->GetInBmp())
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("组合中治具动作不能控制相同输入！"));
                    return false;
                }
            }
            map[0xFFFF0000] |= vac->GetOutBmp();
            map[0xFFFF0001] |= vac->GetInBmp();
        }
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_OPR)
		{
			m_cur_pos = m_check_idx;
            m_err_string = QString(tr("组合中不能使用变量运算语句！"));
			return false;
		}
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_IMM)
		{
            CodeImm* imm = (CodeImm*)m_codelist[procid].at(m_check_idx);
            if (imm->GetType()!=IMMOUT_EMC)
            {
				m_cur_pos = m_check_idx;
				m_err_string = QString(tr("只有允许关模动作能在组合中！"));
				return false;
			}
            if (mask&COMBINE_ACT_MASK_IMM_EMC)
            {
                m_cur_pos = m_check_idx;
                m_err_string = QString(tr("组合中不能有两个允许关模动作！"));
                return false;
            }
            mask |= COMBINE_ACT_MASK_IMM_EMC;
		}
		if (combine_count>=MAX_COMBINE)
		{
			m_cur_pos = m_check_idx;
			m_err_string = QString(tr("不能多于30个动作同时执行！"));
			return false;
		}
        //if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_CEND)
        if (!(m_codelist[procid].at(m_check_idx)->GetFlag()&FLAG_COMBINE))
        {
            if (enterif == true)
            {
                m_cur_pos = m_check_idx;
                m_err_string = QString(tr("组合中条件语句不配对，缺少条件结束！"));
                return false;
            }
            return true;
        }
    }
	m_err_string = QString(tr("没有相应的组合结束！"));
	return false;
}

bool TeachTableModel::CheckPath(quint8 procid)
{
    quint8 path_count = 0;
    quint32 mask = 0;
    m_cur_pos = m_check_idx++;
    for (; m_check_idx<m_codelist[procid].count(); m_check_idx++)
    {
        path_count++;
        //if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_CBEGIN)
        if (m_codelist[procid].at(m_check_idx)->GetFlag()&FLAG_COMBINE)
        {
            m_cur_pos = m_check_idx;
            m_err_string = QString(tr("路径中不能使用组合！"));
            return false;
        }
/*        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_CEND)
        {
            m_cur_pos = m_check_idx;
            m_err_string = QString(tr("路径中不能使用组合结束语句！"));
            return false;
        }*/
        if 	((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_IF)
        {
            m_cur_pos = m_check_idx;
            m_err_string = QString(tr("路径中不能使用条件语句！"));
            return false;
        }
        if 	((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_ELSE)
        {
            m_cur_pos = m_check_idx;
            m_err_string = QString(tr("路径中不能使用条件否则语句！"));
            return false;
        }
        if 	((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_ENDIF)
        {
            m_cur_pos = m_check_idx;
            m_err_string = QString(tr("路径中不能使用条件结束语句！"));
            return false;
        }
        if (((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_FOR_VAR)||
            ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_FOR_CONST))
		{
			m_cur_pos = m_check_idx;
			m_err_string = QString(tr("路径中不能使用循环语句！"));
			return false;
		}
        if 	((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_BREAK)
		{
			m_cur_pos = m_check_idx;
			m_err_string = QString(tr("路径中不能使用循环跳出语句！"));
			return false;
		}
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_INTERP)
        {
            CodeInterp* pinterp = (CodeInterp*)m_codelist[procid].at(m_check_idx);
            if (pinterp->GetAxesbmp()&(1<<AXES_IDX_Y))
            {
                if (mask&PATH_ACT_MASK_Y_SERVO)
            {
                m_cur_pos = m_check_idx;
                m_err_string = QString(tr("连续路径中只能有一条Y轴插补定位！"));
                return false;
            }
                mask |= PATH_ACT_MASK_Y_SERVO;
            }
//            else
            if (pinterp->GetAxesbmp()&(1<<AXES_IDX_Z))
            {
                if (mask&PATH_ACT_MASK_Z_SERVO)
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("连续路径中只能有一条Z轴插补定位！"));
                    return false;
                }
                mask |= PATH_ACT_MASK_Z_SERVO;
            }
//            else
            if (pinterp->GetAxesbmp()&(1<<AXES_IDX_X))
            {
                if (mask&PATH_ACT_MASK_X_SERVO)
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("连续路径中只能有一条X轴插补定位！"));
                    return false;
                }
                mask |= PATH_ACT_MASK_X_SERVO;
            }
//            else
            if (pinterp->GetAxesbmp()&(1<<AXES_IDX_A))
            {
                if (mask&PATH_ACT_MASK_A_SERVO)
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("连续路径中只能有一条A轴插补定位！"));
                    return false;
                }
                mask |= PATH_ACT_MASK_A_SERVO;
            }
//            else
            if (pinterp->GetAxesbmp()&(1<<AXES_IDX_B))
            {
                if (mask&PATH_ACT_MASK_B_SERVO)
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("连续路径中只能有一条B轴插补定位！"));
                    return false;
                }
                mask |= PATH_ACT_MASK_B_SERVO;
            }
//            else
            if (pinterp->GetAxesbmp()&(1<<AXES_IDX_C))
            {
                if (mask&PATH_ACT_MASK_C_SERVO)
                {
                    m_cur_pos = m_check_idx;
                    m_err_string = QString(tr("连续路径中只能有一条C轴插补定位！"));
                    return false;
                }
                mask |= PATH_ACT_MASK_C_SERVO;
            }
        }
        if 	((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_ENDFOR)
		{
			m_cur_pos = m_check_idx;
			m_err_string = QString(tr("路径中不能使用循环结束语句！"));
			return false;
		}
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_IMM)
        {
            CodeImm* imm = (CodeImm*)m_codelist[procid].at(m_check_idx);
            if (imm->GetType()==IMMOUT_EMO)
            {
                m_cur_pos = m_check_idx;
                m_err_string = QString(tr("路径中不能使用等待开模语句！"));
                return false;
            }
        }
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_TBEGIN)
        {
            m_cur_pos = m_check_idx;
            m_err_string = QString(tr("路径中不能使用路径开始语句！"));
            return false;
        }
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_TEND)
        {
            return true;
        }
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_END)
        {
            m_cur_pos = m_check_idx;
            m_err_string = QString(tr("路径中不能使用程序结束语句！"));
            return false;
        }
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_CUSTOMER)
		{
			m_cur_pos = m_check_idx;
            m_err_string = QString(tr("路径中不能调用归位指令！"));
			return false;
		}
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_FREEPOS)
        {
            m_cur_pos = m_check_idx;
            m_err_string = QString(tr("路径中不能使用循环定位指令！"));
            return false;
        }
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_MATRIX)
        {
            m_cur_pos = m_check_idx;
            m_err_string = QString(tr("路径中不能使用矩阵指令！"));
            return false;
        }
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_LOOP)
        {
            m_cur_pos = m_check_idx;
            m_err_string = QString(tr("路径中不能使用单轴循环定位指令！"));
            return false;
        }
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_LOOPFREE)
        {
            m_cur_pos = m_check_idx;
            m_err_string = QString(tr("路径中不能使用单轴循环自由定位指令！"));
            return false;
        }
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_PAPER)
        {
            m_cur_pos = m_check_idx;
            m_err_string = QString(tr("路径中不能使用搜索指令！"));
            return false;
        }
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_WAIT)
        {
            m_cur_pos = m_check_idx;
            m_err_string = QString(tr("路径中不能使用等待语句！"));
            return false;
        }
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_DELAY)
		{
			m_cur_pos = m_check_idx;
			m_err_string = QString(tr("路径中不能使用延时语句！"));
			return false;
		}
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_SPEED)
		{
			m_cur_pos = m_check_idx;
            m_err_string = QString(tr("路径中不能使用速度调整语句！"));
			return false;
		}
        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_OPR)
		{
			m_cur_pos = m_check_idx;
            m_err_string = QString(tr("路径中不能使用变量运算语句！"));
			return false;
		}
/*        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_PROARM)
		{
			m_cur_pos = m_check_idx;
			m_err_string = QString(tr("路径中不能有正臂倒角动作！"));
			return false;
        }*/
/*		if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_EXT_OUT)
		{
			m_cur_pos = m_check_idx;
			m_err_string = QString(tr("路径中不能使用扩展输出动作！"));
			return false;
        }*/
/*        if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_EXT_IN)
		{
			m_cur_pos = m_check_idx;
			m_err_string = QString(tr("路径中不能使用扩展输入动作！"));
			return false;
        }*/
/*		if ((m_codelist[procid].at(m_check_idx)->GetCode())==CODE_RUNARM)
        {
            m_cur_pos = m_check_idx;
            m_err_string = QString(tr("路径中不能有副臂动作！"));
            return false;
        }*/
		if (path_count>=MAX_TRAJ)
        {
            m_cur_pos = m_check_idx;
            m_err_string = QString(tr("不能多于100条指令！"));
            return false;
        }
    }
    m_err_string = QString(tr("没有相应的路径结束！"));
    return false;
}

int TeachTableModel::GetCode(int pos)   //返回指令码
{
    if (pos<m_codelist[m_current_process].count())
	{
        return m_codelist[m_current_process].at(pos)->GetCode();
	}
	return -1;
}
int TeachTableModel::GetFlag(int pos)   //返回指令控制字
{
    if (pos<m_codelist[m_current_process].count())
    {
        return m_codelist[m_current_process].at(pos)->GetFlag();
    }
    return -1;
}
int TeachTableModel::SetFlag(int flag, int pos)   //设置指令控制字
{
    if (pos<m_codelist[m_current_process].count())
    {
        if (pos==-1)
        {
            pos = m_codelist[m_current_process].count() - 1;
        }
        if (pos>-1)
        {
            m_codelist[m_current_process].at(pos)->SetFlag(flag);
        }
        return 0;
    }
    return -1;
}

void TeachTableModel::SetCurProcess(int procid)
{
    if (procid<MAX_PROCESS)
    {
        if (m_current_process != procid)
        {
            m_current_process = procid;
            UpdateLineNum();
            reset();
        }
    }
}

bool TeachTableModel::GetVarItem(int pos, quint16 &var, quint32 &value, quint8 &type)
{
    if (pos<m_varlist.count()&&(pos>=0))
    {
        var = m_varlist.at(pos)->GetVar();
        value = m_varlist.at(pos)->GetVarValue();
        type = m_varlist.at(pos)->GetType();
        return true;
    }
    return false;
}

bool TeachTableModel::InsertVar(quint16 var, quint32 value, quint8 type, int insertpos)
{ 
    if (IshaveValue(var))
    {
        return false;
    }
    XmlModelVarInitItem *pitem = new XmlModelVarInitItem();
    if (pitem)
    {
        pitem->SetVar(var);
        pitem->SetValue(value);
        pitem->SetType(type);
        if (insertpos==-1)
            m_varlist.append(pitem);
        else
            m_varlist.insert(insertpos, pitem);
        UpdateLineNum();
        reset();
        m_ismodifed = true;
        return true;
    }
    return false;
}

void TeachTableModel::RemoveVar(int pos)
{
    if (pos<m_varlist.count()&&(pos>=0))
    {
        delete m_varlist.at(pos);
        m_varlist.removeAt(pos);
        UpdateLineNum();
        reset();
        m_ismodifed = true;
    }
}

bool TeachTableModel::IshaveValue(quint16 var, QList <quint16> varlist)
{
    int i;
    for (i = 0; i < varlist.count(); i++)
    {
        if (var == varlist.at(i))
            return true;
    }
    return false;
}

void TeachTableModel::UpdateAllUsrVar(QList<quint16> varlist)
{
    // 如果varlist中有，m_varlist中没有，将varlist中数据插入m_varlist中
    int i;
    for (i = 0; i < varlist.count(); i++)
    {
        if (!IshaveValue(varlist.at(i)))
        {
            XmlModelVarInitItem *pitem = new XmlModelVarInitItem();
            if (pitem)
            {
                pitem->SetVar(varlist.at(i));
                pitem->SetValue(0);
                pitem->SetType(TYPE_AUTO);
                m_varlist.append(pitem);
            }
        }
    }
    // 如果m_varlist中有，varlist中没有，将m_varlist中删除
    for (i = 0; i < m_varlist.count(); i++)
    {
        if (!IshaveValue(m_varlist.at(i)->GetVar(), varlist))
        {
            delete m_varlist.at(i);
            m_varlist.removeAt(i);
        }
        else
        {
            i++;
        }
    }
}

void TeachTableModel::AddUsrVar(XmlModelItem *pitem, QList<quint16> &varlist)
{
    if (((pitem->GetCode()) == CODE_FOR_VAR) ||
        ((pitem->GetCode()) == CODE_OPR) ||
        ((pitem->GetCode()) == CODE_EXT_IN) ||
        ((pitem->GetCode()) == CODE_EXT_OUT) ||
        ((pitem->GetCode()) == CODE_MEXTOUT) ||
        ((pitem->GetCode()) == CODE_MATRIX) ||
        ((pitem->GetCode()) == CODE_LOOP) ||
        ((pitem->GetCode()) == CODE_LOOPFREE) ||
        ((pitem->GetCode()) == CODE_VACUUM) ||
        ((pitem->GetCode()) == CODE_FREEPOS))
    {
        if (pitem->GetUserVar() != 0)
        {
            varlist.append(pitem->GetUserVar());
        }
    }
    if (((pitem->GetCode()) == CODE_IF) || ((pitem->GetCode()) == VCODE_VACUUM))
    {
        if (pitem->GetUserVar() != 0)
        {
            varlist.append(pitem->GetUserVar());
        }
        if (pitem->GetUserVar(1) != 0)
        {
            varlist.append(pitem->GetUserVar(1));
        }
    }
}

bool TeachTableModel::SetVar(int pos , quint16 var, quint32 value, quint8 type)
{
    if (pos<m_varlist.count()&&(pos>=0))
    {
        if ((m_varlist.at(pos)->GetVar() != var)||
            (m_varlist.at(pos)->GetVarValue() != value)||
            (m_varlist.at(pos)->GetType() != type))
        {
            m_varlist.at(pos)->SetType(type);
            m_varlist.at(pos)->SetVar(var);
            m_varlist.at(pos)->SetValue(value);
            UpdateLineNum();
            reset();
            m_ismodifed = true;
            return true;
        }
    }
    return false;
}

bool TeachTableModel::Inquire(void)
{
    int i;
    for (i=0; i<m_varlist.count(); i++)
    {
        if (m_varlist.at(i)->GetType() == TYPE_INQUIRE)
            return true;
    }
    return false;
}

int TeachTableModel::GenerateVar(int &firstidx, quint32 * para, bool ClearInq)
{
    int count = 0;
    int i, j;
    int min = 0xFFFF;
    for (i=0; i<m_varlist.count(); i++)
    {
        if ((m_varlist.at(i)->GetVar()&MASK_VAR_VAL) >= firstidx)
        {
            if ((m_varlist.at(i)->GetVar()&MASK_VAR_VAL) < min)
            {
                if ((m_varlist.at(i)->GetType()==TYPE_AUTO) ||
                    ((m_varlist.at(i)->GetType()==TYPE_INQUIRE)&&ClearInq))
                min = m_varlist.at(i)->GetVar()&MASK_VAR_VAL;
            }
        }
    }
    if (min!=0xFFFF)
    {
        firstidx = min;
        for (j=0; j<m_varlist.count(); j++)
        {
            for (i=0; i<m_varlist.count(); i++)
            {
                if ((m_varlist.at(i)->GetVar()&MASK_VAR_VAL) == min)
                {
                    if ((m_varlist.at(i)->GetType()==TYPE_AUTO) ||
                       ((m_varlist.at(i)->GetType()==TYPE_INQUIRE)&&ClearInq))
                    {
                        para[count] = m_varlist.at(i)->GetVarValue();
                        count ++;
                        min ++;
                        break;
                    }
                }
            }
            if (i==m_varlist.count()) break;
        }
    }

    return count;
}
bool TeachTableModel::IshaveValue(quint16 var)
{
    int i;
    for (i = 0; i < m_varlist.count(); i++)
    {
        if (var == m_varlist.at(i)->GetVar())
            return true;
    }
    return false;
}
quint16 TeachTableModel::GetMinCounter()
{
    int i;
    for (i = MAX_USER_VAR+1; i <= MAX_COUNTER_VAR; i++)
    {
        if (!IshaveValue(i|VAR_TYPE_USR))
            return i|VAR_TYPE_USR;
    }
    return 0;
}
