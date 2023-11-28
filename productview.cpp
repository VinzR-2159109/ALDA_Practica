//Vinz Roosen & Lars Gielen
#include "productview.h"

#include <QGridLayout>
#include <QImage>
#include <QPixmap>

#include <QNetworkAccessManager>

ProductView::ProductView()
{
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::white);

    setAutoFillBackground(true);
    setPalette(pal);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QVBoxLayout *textLayout = new QVBoxLayout(this);

    m_titleLabel = new QLabel("Title");
    m_subTitleLabel = new QLabel("Subtitle");
    m_ratingLabel = new QLabel("Stars");
    m_priceLabel = new QLabel("Price");
    m_discountLabel = new QLabel("Discount");
    m_imageLabel = new QLabel();

    QFont titleFont;
    titleFont.setPointSize(15);
    titleFont.setBold(true);

    m_titleLabel->setFont(titleFont);
    m_titleLabel->setWordWrap(true);

    QFont discountFont;
    discountFont.setPointSize(13);
    discountFont.setBold(true);
    m_discountLabel->setStyleSheet("color: red;");

    m_discountLabel->setFont(discountFont);

    QFont font;
    titleFont.setPointSize(10);

    m_subTitleLabel->setFont(font);
    m_ratingLabel->setFont(font);
    m_priceLabel->setFont(font);
    m_imageLabel->setFont(font);

    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_subTitleLabel->setAlignment(Qt::AlignCenter);
    m_imageLabel->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);

    textLayout->addWidget(m_titleLabel);
    textLayout->addWidget(m_subTitleLabel);
    textLayout->addWidget(m_discountLabel);
    textLayout->addWidget(m_priceLabel);
    textLayout->addWidget(m_ratingLabel);
    textLayout->setAlignment(Qt::AlignTop);

    mainLayout->addLayout(textLayout);
    mainLayout->addWidget(m_imageLabel);

    setLayout(mainLayout);
}

void ProductView::setProduct(Product *product)
{
    // download image
    m_networkManager = new QNetworkAccessManager(this);
    connect(m_networkManager, &QNetworkAccessManager::finished, this, &ProductView::onImageDownloaded);

    QNetworkRequest request(product->getImageUrl());
    QNetworkReply *reply = m_networkManager->get(request);
    connect(reply, &QNetworkReply::finished, reply, &QNetworkReply::deleteLater);

    // set product data
    m_titleLabel->setText(product->getTitle());
    m_subTitleLabel->setText(product->getAsin());
    m_discountLabel->setText(QString("Now with with a %1% discount!").arg(product->getDiscount()));
    m_priceLabel->setText(QString("€ %1 -> € %2").arg(product->getListPrice()).arg(product->getPrice()));
    m_ratingLabel->setText(QString("%1/5 stars with %2 reviews").arg(product->getStars()).arg(product->getNumberOfReviews()));
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
        m_imageLabel->setPixmap(pixmap.scaled(m_imageLabel->width(), m_imageLabel->height(), Qt::KeepAspectRatio));
    }
    else
    {
        qDebug() << "Error downloading image:" << reply->errorString();
    }

    // Clean up
    reply->deleteLater();
    m_networkManager->deleteLater();
}
