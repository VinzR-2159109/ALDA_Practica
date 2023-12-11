#ifndef LISTVIEWEDITVIEW_H
#define LISTVIEWEDITVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>

#include <Model/vertex.h>

template <typename T>
class ListViewEditView : public QWidget
{
public:
    ListViewEditView(QWidget *parent = nullptr);

    void clear();
    void updateValues(QVector<T> &editVector);

private:
    QPushButton *m_add;
    QPushButton *m_edit;
    QPushButton *m_delete;

    QListWidget *m_listView;

    QVector<T> m_editVector;
};

#endif // LISTVIEWEDITVIEW_H
