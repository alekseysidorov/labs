import qbs

CppApplication {
    type: "application"
    files: [
        "figures.cpp",
        "figures.h",
        "main.cpp",
        "mainwindow.cpp",
        "mainwindow.h",
        "mainwindow.ui",
        "paintwidget.cpp",
        "paintwidget.h",
    ]

    Depends { name: "Qt.widgets" }

    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
    }
}

