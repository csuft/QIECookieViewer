/********************************************************************************
** Form generated from reading UI file 'qiecookieviewer.ui'
**
** Created: Tue Jan 21 19:52:42 2014
**      by: Qt User Interface Compiler version 5.0.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QIECOOKIEVIEWER_H
#define UI_QIECOOKIEVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QIECookieViewerClass
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *filterExpLineEdit;
    QComboBox *colComboBox;
    QTableView *tableView;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *totalLabel;
    QLabel *label_2;
    QLabel *locationLabel;
    QCheckBox *caseCheckBox;
    QCheckBox *sortCheckBox;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *cleanBtn;
    QPushButton *prevBtn;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *openBtn;
    QPushButton *nextBtn;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *refreshBtn;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *closeBtn;
    QTableWidget *cookieDetailsView;

    void setupUi(QWidget *QIECookieViewerClass)
    {
        if (QIECookieViewerClass->objectName().isEmpty())
            QIECookieViewerClass->setObjectName(QStringLiteral("QIECookieViewerClass"));
        QIECookieViewerClass->resize(657, 451);
        verticalLayout_3 = new QVBoxLayout(QIECookieViewerClass);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        filterExpLineEdit = new QLineEdit(QIECookieViewerClass);
        filterExpLineEdit->setObjectName(QStringLiteral("filterExpLineEdit"));

        horizontalLayout->addWidget(filterExpLineEdit);

        colComboBox = new QComboBox(QIECookieViewerClass);
        colComboBox->setObjectName(QStringLiteral("colComboBox"));

        horizontalLayout->addWidget(colComboBox);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(QIECookieViewerClass);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableView->setGridStyle(Qt::DotLine);
        tableView->setSortingEnabled(true);
        tableView->setWordWrap(false);
        tableView->setCornerButtonEnabled(false);
        tableView->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(tableView);


        horizontalLayout_5->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(QIECookieViewerClass);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        totalLabel = new QLabel(groupBox);
        totalLabel->setObjectName(QStringLiteral("totalLabel"));
        totalLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(totalLabel, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        locationLabel = new QLabel(groupBox);
        locationLabel->setObjectName(QStringLiteral("locationLabel"));
        locationLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(locationLabel, 1, 1, 1, 1);

        caseCheckBox = new QCheckBox(groupBox);
        caseCheckBox->setObjectName(QStringLiteral("caseCheckBox"));

        gridLayout->addWidget(caseCheckBox, 2, 0, 1, 1);

        sortCheckBox = new QCheckBox(groupBox);
        sortCheckBox->setObjectName(QStringLiteral("sortCheckBox"));

        gridLayout->addWidget(sortCheckBox, 2, 1, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        cleanBtn = new QPushButton(QIECookieViewerClass);
        cleanBtn->setObjectName(QStringLiteral("cleanBtn"));

        horizontalLayout_2->addWidget(cleanBtn);

        prevBtn = new QPushButton(QIECookieViewerClass);
        prevBtn->setObjectName(QStringLiteral("prevBtn"));

        horizontalLayout_2->addWidget(prevBtn);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        openBtn = new QPushButton(QIECookieViewerClass);
        openBtn->setObjectName(QStringLiteral("openBtn"));

        horizontalLayout_3->addWidget(openBtn);

        nextBtn = new QPushButton(QIECookieViewerClass);
        nextBtn->setObjectName(QStringLiteral("nextBtn"));

        horizontalLayout_3->addWidget(nextBtn);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        refreshBtn = new QPushButton(QIECookieViewerClass);
        refreshBtn->setObjectName(QStringLiteral("refreshBtn"));

        horizontalLayout_4->addWidget(refreshBtn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_4);

        closeBtn = new QPushButton(QIECookieViewerClass);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));

        verticalLayout_2->addWidget(closeBtn);


        horizontalLayout_5->addLayout(verticalLayout_2);

        horizontalLayout_5->setStretch(0, 3);
        horizontalLayout_5->setStretch(1, 1);

        verticalLayout_3->addLayout(horizontalLayout_5);

        cookieDetailsView = new QTableWidget(QIECookieViewerClass);
        cookieDetailsView->setObjectName(QStringLiteral("cookieDetailsView"));
        cookieDetailsView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        cookieDetailsView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        cookieDetailsView->setGridStyle(Qt::DotLine);
        cookieDetailsView->setWordWrap(false);
        cookieDetailsView->horizontalHeader()->setStretchLastSection(true);
        cookieDetailsView->verticalHeader()->setVisible(false);

        verticalLayout_3->addWidget(cookieDetailsView);


        retranslateUi(QIECookieViewerClass);

        QMetaObject::connectSlotsByName(QIECookieViewerClass);
    } // setupUi

    void retranslateUi(QWidget *QIECookieViewerClass)
    {
        QIECookieViewerClass->setWindowTitle(QApplication::translate("QIECookieViewerClass", "QIECookieViewer", 0));
        groupBox->setTitle(QApplication::translate("QIECookieViewerClass", "Meta Information", 0));
        label->setText(QApplication::translate("QIECookieViewerClass", "Totoal:", 0));
        totalLabel->setText(QApplication::translate("QIECookieViewerClass", "TextLabel", 0));
        label_2->setText(QApplication::translate("QIECookieViewerClass", "Current Row:", 0));
        locationLabel->setText(QApplication::translate("QIECookieViewerClass", "TextLabel", 0));
        caseCheckBox->setText(QApplication::translate("QIECookieViewerClass", "Case", 0));
        sortCheckBox->setText(QApplication::translate("QIECookieViewerClass", "Sort", 0));
        cleanBtn->setText(QApplication::translate("QIECookieViewerClass", "Clean", 0));
        prevBtn->setText(QApplication::translate("QIECookieViewerClass", "Prev", 0));
        openBtn->setText(QApplication::translate("QIECookieViewerClass", "Open", 0));
        nextBtn->setText(QApplication::translate("QIECookieViewerClass", "Next", 0));
        refreshBtn->setText(QApplication::translate("QIECookieViewerClass", "Refresh", 0));
        closeBtn->setText(QApplication::translate("QIECookieViewerClass", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class QIECookieViewerClass: public Ui_QIECookieViewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QIECOOKIEVIEWER_H
