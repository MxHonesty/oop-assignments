#include "Lab10.h"
#include "repo/RepoFile.h"

Lab10::Lab10(QWidget *parent) : QMainWindow(parent) {
    std::shared_ptr<RepoFile> repo = std::make_shared<RepoFile>("data.txt");
    srv = ServiceOferta{ repo };
    ui.setupUi(this);
    init();

}

void Lab10::init() {
    setLayout(main_layout);
    main_layout->addWidget(list_view);
}
