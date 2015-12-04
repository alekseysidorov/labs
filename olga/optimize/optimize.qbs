import qbs

CppApplication {
    type: "application"

    files: "main.cpp"
    cpp.cxxLanguageVersion: "c++14"
    cpp.cxxStandardLibrary: "libc++"

    Depends {
        name: "Qt";
        submodules: [
            "widgets"
        ]
    }

    Group {
        fileTagsFilter: product.type
        qbs.install: true
    }
}

