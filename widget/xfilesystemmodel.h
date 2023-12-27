#ifndef XFILESYSTEMMODEL_H
#define XFILESYSTEMMODEL_H

#include <QFileSystemModel>
#include <QVariant>

class xFileSystemModel : public QFileSystemModel
{
	Q_OBJECT
public:
	explicit xFileSystemModel(QObject *parent = 0);
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	QVariant data(const QModelIndex &index, int role) const;
};

#endif // XFILESYSTEMMODEL_H
