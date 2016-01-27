import qbs

Project {
    name: "Paint"

    Product {
        files: [
            "figlibrary.cpp",
            "figlibrary.h",
            "figures.cpp",
            "figures.h",
        ]
        name: "Figures"
        type: "staticlibrary"

        Depends { name: "cpp" }
        Depends { name: "Qt"; submodules: ["gui"] }

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

    Product {
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
        type: "application"

        Depends { name: "cpp" }
        Depends { name: "Figures" }
        Depends { name: "Qt"; submodules: ["widgets"] }

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

    Product {
        files: [
            "figurist.cpp",
        ]
        name: "Figurist"
        type: "application"

        Depends { name: "cpp" }
        Depends { name: "Figures" }
        Depends { name: "Qt"; submodules: ["core", "gui"] }

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
