#include "headers/CommonLibs.hpp"

#include "headers/Interpreter.hpp"

const std::string versionInformation = R"(Canvas Alpha v0.1)";
const std::string helpInformation = 
R"(Usage: canvas [options] [-c <filename>]
                
options:
    -h | --help    : Display help
    -v | --version : Display version
    -e | --execute : Execute file)";

int executeFile(const std::string filename){
    std::ifstream file(filename);

    if(!file.is_open()){
        std::cout << "~Error~ Failed to open \'" << filename << "\'" << std::endl;
        return 1;
    }

    Interpreter mainInterpreter;
    std::string code, readLine;

    while(std::getline(file, readLine)){
        if (!readLine.empty() && readLine != "\n" && readLine[0] != '#') {
            code += readLine + "\n";
        }
    } file.close();

    auto startTime = std::chrono::high_resolution_clock::now();
    RET_CODE exitCode = mainInterpreter.execute(code);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto executionTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    
    if(exitCode == RET_CODE::OK){
        std::cout << "Exited in " << executionTime.count() << "ms" << std::endl;
    }else{
        std::cout << "Exited with errors." << std::endl;
    }

    return 0;
}

int main(int argc, char** argv){
    if(argc <= 1){
        std::cout << "~Error~ No arguments provided.\n~Try~ -h or --help for more information" << std::endl;
        
        return 1;
    }else{
        for(std::uint8_t argIndex = 1; argIndex < argc; argIndex++){
            const std::string argStr = argv[argIndex];
            
            if(argStr == "-h" || argStr == "--help"){
                std::cout << helpInformation << std::endl;
                return 0;
            }else if(argStr == "-v" || argStr == "--version"){
                std::cout << versionInformation << std::endl;
                return 0;
            }else if(argStr == "-e" || argStr == "--execute"){
                if(argIndex == argc - 1){
                    std::cout << "~Error~ Missing '<filename>' \n~Try~ -e <filename>" << std::endl;
                    return 1;
                }else{
                    return executeFile(argv[argIndex + 1]);
                }
            }else{
                std::cout << "~Error~ Invalid argument \'" << argStr << '\'' << std::endl;
            }
        }
    }

    return 0;
}