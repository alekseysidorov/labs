import qbs

Project {
    DynamicLibrary {
        name: "figures"

        files: [
            "container.cpp",
            "container.h",
            "figures.cpp",
            "figures.h",
        ]

        Depends { name: "Qt.core" }

        cpp.includePaths: [ "." ]

        Group {
            fileTagsFilter: product.type
            qbs.install: true
            qbs.installDir: "bin"
        }
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

        Depends { name: "Qt.core" }
        Depends { name: "Qt.gui" }
        Depends { name: "Qt.widgets" }
        Depends { name: "figures" }

        Group {
            fileTagsFilter: product.type
            qbs.install: true
            qbs.installDir: "bin"
        }
    }
}
