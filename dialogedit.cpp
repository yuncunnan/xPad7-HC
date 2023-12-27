#include <QDebug>
#include "dialogedit.h"
#include "teachtablemodel.h"

Dialogedit::Dialogedit(QObject *parent) :
	QItemDelegate(parent)
{
}

QWidget* Dialogedit::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QLineEdit *editor = new QLineEdit(parent);
	editor->setFrame(true);
	return editor;
}

void Dialogedit::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index,Qt::DisplayRole).toString();
	QLineEdit *lineedit = static_cast<QLineEdit*>(editor);
	lineedit->setText(value);
}

void Dialogedit::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    TeachTableModel *tmodel = static_cast<TeachTableModel*>(model);
    QLineEdit *lineedit = static_cast<QLineEdit*>(editor);
    QString value = lineedit->text();
    if (value != tmodel->GetItem(index.row())->GetName())
        model->setData(index, value, Qt::DisplayRole);
}
/*void Dialogedit::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}*/
