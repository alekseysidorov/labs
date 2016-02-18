import qbs

CppApplication {
    type: "application"

    files: [
        "main.cpp",
        "mainwindow.cpp",
        "mainwindow.h",
        "mainwindow.ui",
    ]

    cpp.cxxLanguageVersion: 'c++14'
    cpp.cxxStandardLibrary: "libc++"

    Group {
        name: "txt"

        prefix: "txt/"
        files: "*"
        qbs.install: true
        qbs.installDir: "txt"
    }

    Group {
        fileTagsFilter: product.type
        qbs.install: true
    }

    Depends { name: "Qt.widgets" }
}
