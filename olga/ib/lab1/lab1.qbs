import qbs

CppApplication {
    type: "application"

    files: "main.cpp"

    cpp.cxxLanguageVersion: 'c++14'

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

    Depends { name: "Qt.core" }
}
