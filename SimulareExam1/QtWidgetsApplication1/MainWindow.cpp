#include "MainWindow.h"

MainWindow::MainWindow(Service& srv, QWidget* parent) : QWidget(parent), srv{srv} {
    ui.setupUi(this);
    
    model = new ProdusModel{ srv, this };
    list_view = new QListView{ this };
    list_view->setModel(model);
    line = new QLineEdit{ this };
    btn_sort_tip = new QPushButton{ "Sortare Tip", this };
    btn_sort_ca = new QPushButton{ "Sortare ca", this };
    btn_refresh = new QPushButton{ "Refresh", this };

    init_state();
    connect_signals();

    layout = new QVBoxLayout{ this };
    layout->addWidget(list_view);
    layout->addWidget(line);
    layout->addWidget(btn_sort_tip);
    layout->addWidget(btn_sort_ca);
    layout->addWidget(btn_refresh);
    setLayout(layout);
}

void MainWindow::init_state() {
    line->setDisabled(true);
}

void MainWindow::connect_signals() {
    QObject::connect(btn_sort_tip, &QPushButton::clicked, this, [this]() {
        model->set_produse(srv.sort_tip());
    });

    QObject::connect(btn_sort_ca, &QPushButton::clicked, this, [this]() {
        model->set_produse(srv.sort_ca());
    });

    QObject::connect(btn_refresh, &QPushButton::clicked, this, [this]() {
        model->set_produse(srv.get_all());
    });

    QObject::connect(list_view->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this]() {
        const auto selected = list_view->selectionModel()->selectedIndexes().at(0);
        int id = model->data(selected, Qt::UserRole).toInt();
        line->setText(QString::number(srv.find(id).get_ca()));
    });
}
