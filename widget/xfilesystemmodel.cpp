#include <QDateTime>
#include "xfilesystemmodel.h"

xFileSystemModel::xFileSystemModel(QObject * parent) : QFileSystemModel(parent)
{
}

QVariant xFileSystemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal)
	{
		if (role == Qt::DisplayRole)
		{
			switch (section)
			{
			case 0:
				return tr("文件名称");
			case 1:
				return tr("尺寸");
			case 2:
				return tr("类型");
			case 3:
				return tr("修改时间");
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
	return QFileSystemModel::headerData(section, orientation, role);
}

QVariant xFileSystemModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
	if ((role == Qt::DisplayRole) && (index.column() == 3))
	{
        return lastModified(index).toString("yyyy-MM-dd hh:mm");
	}
	else if (role == Qt::TextAlignmentRole)
	{
		if (index.column() == 1)
			return int(Qt::AlignRight | Qt::AlignVCenter);
		else
			return int(Qt::AlignLeft | Qt::AlignVCenter);
	}
	return QFileSystemModel::data(index, role);
}
