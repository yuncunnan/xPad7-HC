#ifndef XTRANSLATOR_H
#define XTRANSLATOR_H

#include <QObject>
#include <QTranslator>

class CMBProtocol;

class xTranslator : public QObject
{
	Q_OBJECT
public:
	explicit xTranslator(QObject *parent = 0);
	~xTranslator(void);
	void SetLanguage(quint8 lan);
	
signals:
	
public slots:
	
private:
	CMBProtocol *pModbus;
	QTranslator appTranslator;
};

extern xTranslator *xLan;

#endif // XTRANSLATOR_H
