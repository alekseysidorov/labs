import qbs

Project {
    StaticLibrary {
        name: "figures"

        files: [
            "container.cpp",
            "container.h",
            "figures.cpp",
            "figures.h",
        ]

        Depends { name: "Qt.gui" }

        cpp.includePaths: [ "." ]
    }

    CppApplication {
        name: "editor"

        type: "application"
        files: [
            "main.cpp",
            "mainwindow.cpp",
            "mainwindow.h",
            "mainwindow.ui",
            "paintwidget.cpp",
            "paintwidget.h",
        ]

        Depends { name: "Qt.widgets" }
        Depends { name: "figures" }
    }
}
