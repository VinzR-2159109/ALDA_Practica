#include "productview.h"

#include <QHBoxLayout>
#include <QImage>
#include <QPixmap>

#include <QNetworkAccessManager>

ProductView::ProductView()
{
    QHBoxLayout *layout = new QHBoxLayout();

    QStringList headers;
    headers << "ASIN" << "Title" << "Stars" << "Price" << "List price" << "Discount";

    m_table = new QTableWidget();
    m_table->setColumnCount(6);
    m_table->setHorizontalHeaderLabels(headers);

    m_imageLabel = new QLabel();

    layout->addWidget(m_table);
    layout->addWidget(m_imageLabel);

    setLayout(layout);
}

void ProductView::setProduct(Product *product)
{
    // create image label
    m_imageLabel->setText("Test text");

    // Create a network manager to handle the download
    m_networkManager = new QNetworkAccessManager(this);
    connect(m_networkManager, &QNetworkAccessManager::finished, this, &ProductView::onImageDownloaded);

    QNetworkRequest request(product->getImageUrl());
    QNetworkReply *reply = m_networkManager->get(request);
    connect(reply, &QNetworkReply::finished, reply, &QNetworkReply::deleteLater);

    // set table
    m_table->removeRow(0);
    m_table->insertRow(0);

    m_table->setItem(0, 0, new QTableWidgetItem(product->getAsin()));
    m_table->setItem(0, 1, new QTableWidgetItem(product->getTitle()));
    m_table->setItem(0, 2, new QTableWidgetItem(QString::number(product->getStars())));
    m_table->setItem(0, 3, new QTableWidgetItem(QString::number(product->getPrice())));
    m_table->setItem(0, 4, new QTableWidgetItem(QString::number(product->getListPrice())));
    m_table->setItem(0, 5, new QTableWidgetItem(QString::number(product->getDiscount()) + "%"));
}

void ProductView::onImageDownloaded(QNetworkReply *reply)
{
    // set image
    if (reply->error() == QNetworkReply::NoError)
    {
        // Read the data from the reply and set it as a pixmap for the QLabel
        QByteArray imageData = reply->readAll();
        QPixmap pixmap;
        pixmap.loadFromData(imageData);
        m_imageLabel->setPixmap(pixmap);
    }
    else
    {
        qDebug() << "Error downloading image:" << reply->errorString();
    }

    // Clean up
    reply->deleteLater();
    m_networkManager->deleteLater();
}
