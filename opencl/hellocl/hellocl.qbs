import qbs
import qbs.Probes

CppApplication {
    files: ["main.cpp"]

    Probes.IncludeProbe {
        id: clIncludeProbe
        names: ["CL"]
    }
    Probes.PathProbe {
        id: clLibProbe

        property string versionString: "1"

        names: ["OpenCL"]

        platformPaths: [
            "/usr/lib",
            "/usr/local/lib",
            "/usr/lib/x86_64-linux-gnu"
        ]

        nameFilter: {
            return function(name) {
                var versionSuffix = ""
                if (clLibProbe.versionString)
                    versionSuffix = "." + clLibProbe.versionString

                return "lib" + name + ".so" + versionSuffix;
            }
        }
    }

    cpp.cxxLanguageVersion: "c++14"
    cpp.includePaths: [
        clIncludeProbe.path
    ]
    cpp.dynamicLibraries: [
        clLibProbe.filePath
    ]

    Group {
        name: "OpenCL"

        files: "*.cl"
        qbs.install: true
    }

    Group {
        fileTagsFilter: product.type
        qbs.install: true
    }

}
