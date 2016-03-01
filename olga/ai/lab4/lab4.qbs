import qbs

CppApplication {
    type: "application"

    files: "main.cpp"

    cpp.cxxLanguageVersion: 'c++14'
    consoleApplication: true

    Group {
        name: "csv"

        prefix: "csv/"
        files: "*"
        qbs.install: true
        qbs.installDir: "csv"
    }

    Group {
        fileTagsFilter: product.type
        qbs.install: true
    }

    Depends { name: "Qt.core" }
}
