import qbs;
import qbs.FileInfo;
import qbs.Probes;
import qbs.ModUtils;

Application {
    name: "App"
    type: "application"
    condition: yasmProbe.found

    property string yasmFormat: {
        if (qbs.targetOS.contains("osx"))
            return "macho32"
        if (qbs.targetOS.contains("linux"))
            return "elf32"
        if (qbs.targetOS.contains("windows"))
            return "win32"
        return "unknown"
    }
    property string yasmPath: {
        return yasmProbe.filePath
    }

    Probes.PathProbe {
        id: yasmProbe

        names: "yasm"
        pathSuffixes: ["/bin"]
    }

    Depends {
        name: "cpp"
    }

    files: [
        "main.cpp",
        "laba.asm",
    ]
    cpp.positionIndependentCode: false
    cpp.linkerFlags: "-Wl,-no_pie"

    FileTagger {
        patterns: ["*.asm"]
        fileTags: ["yasm"]
    }

    Rule {
        inputs: ["yasm"]
        multiplex: false

        Artifact {
            fileTags: ["obj"]
            filePath: ".obj/" + qbs.getHash(input.baseDir) + "/" + input.fileName + ".o"
        }

        prepare: {
            var args = [ "-o", output.filePath, "-f", product.yasmFormat,
                        input.filePath];
            //args = args.concat(["-g", "dwarf2"])
            var yasmPath = product.yasmPath;
            var cmd = new Command(yasmPath, args);
            cmd.description = "compiling " + FileInfo.fileName(input.filePath);
            cmd.highlight = "compile";
            return cmd;
        }
    }
}

