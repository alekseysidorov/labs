import qbs

Project {
    name: "Paint"

    DynamicLibrary {
        files: [
            "figures.cpp",
            "figures.h",
            "qpaintwidget.cpp",
            "qpaintwidget.h",
        ]
        name: "Figures"

        Depends { name: "cpp" }
        Depends { name: "Qt"; submodules: ["widgets", "gui"] }

        cpp.cxxLanguageVersion: "c++11"
        cpp.includePaths: [
            "."
        ]
    }

    Application {
        files: [
            "main.cpp",
            "mainwindow.cpp",
            "mainwindow.h",
            "mainwindow.ui",
            "thread.cpp",
            "thread.h",
        ]
        name: "Paint"

        Depends { name: "cpp" }
        Depends { name: "Figures" }
        Depends { name: "Qt"; submodules: ["widgets", "gui"] }

        cpp.cxxLanguageVersion: "c++11"
        cpp.includePaths: [
            "."
        ]
    }
}
