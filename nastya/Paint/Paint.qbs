import qbs

Project {
    name: "Paint"

    DynamicLibrary {
        files: [
            "figlibrary.cpp",
            "figlibrary.h",
            "figures.cpp",
            "figures.h",
        ]
        name: "Figures"

        Depends { name: "cpp" }
        Depends { name: "Qt"; submodules: ["widgets", "gui"] }

        cpp.cxxLanguageVersion: "c++11"
        cpp.includePaths: [
            "."
        ]

        Group {
            fileTagsFilter: product.type
            qbs.install: true
            qbs.installDir: "bin"
        }
    }

    Application {
        files: [
            "main.cpp",
            "mainwindow.cpp",
            "mainwindow.h",
            "mainwindow.ui",
            "thread.cpp",
            "thread.h",
            "qpaintwidget.cpp",
            "qpaintwidget.h",
        ]
        name: "Paint"

        Depends { name: "cpp" }
        Depends { name: "Figures" }
        Depends { name: "Qt"; submodules: ["widgets", "gui"] }

        cpp.cxxLanguageVersion: "c++11"
        cpp.includePaths: [
            "."
        ]

        Group {
            fileTagsFilter: product.type
            qbs.install: true
            qbs.installDir: "bin"
        }
    }
}
