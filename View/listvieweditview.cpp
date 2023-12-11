#include "listvieweditview.h"

#include <QVBoxLayout>

template <typename T>
ListViewEditView<T>::ListViewEditView(QWidget *parent)
    : QWidget(parent)
{
    m_add = new QPushButton("Add");
    m_edit = new QPushButton("Edit");
    m_delete = new QPushButton("Delete");

    m_listView = new QListWidget();

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    QVBoxLayout *vLayout = new QVBoxLayout();

    hLayout->addWidget(m_listView);
    hLayout->addLayout(vLayout);

    vLayout->addWidget(m_add);
    vLayout->addWidget(m_edit);
    vLayout->addWidget(m_delete);
}

template<typename T>
void ListViewEditView<T>::clear()
{
    m_listView->clear();
}

template <>
void ListViewEditView<QString>::updateValues(QVector<QString> &vector) {
    m_editVector = vector;

    m_listView->clear();
    QStringList stringList;
    for (const auto &value : vector) {
        stringList.append(value);
    }

    m_listView->addItems(stringList);
}

template <>
void ListViewEditView<Vertex*>::updateValues(QVector<Vertex*> &vector) {
    m_editVector = vector;

    m_listView->clear();
    QStringList stringList;
    for (const auto &value : vector) {
        stringList.append(value->getName());
    }

    m_listView->addItems(stringList);
}

template <>
void ListViewEditView<std::pair<Vertex*, Vertex*>>::updateValues(QVector<std::pair<Vertex*, Vertex*>> &vector) {
    m_editVector = vector;

    m_listView->clear();
    QStringList stringList;
    for (const auto &value : vector) {
        stringList.append(value.first->getName() + " -> " + value.second->getName());
    }

    m_listView->addItems(stringList);
}

template <>
void ListViewEditView<QVector<Vertex*>>::updateValues(QVector<QVector<Vertex*>> &vector) {
    m_editVector = vector;

    m_listView->clear();
    QStringList stringList;
    for (const auto &value : vector) {
        QStringList vertexNames;
        for (const auto &value : value) {
            vertexNames.append(value->getName());
        }
        stringList.append(vertexNames.join(", "));
    }

    m_listView->addItems(stringList);
}

template class ListViewEditView<QString>;
template class ListViewEditView<Vertex*>;
template class ListViewEditView<std::pair<Vertex*, Vertex*>>;
template class ListViewEditView<QVector<Vertex*>>;
