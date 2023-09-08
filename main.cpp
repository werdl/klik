#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include "deps/json.hpp"



using json=nlohmann::json;
using namespace std;
string exec(string command) {
    char buffer[128];
    string result = "";
    #if defined(__WIN)
        FILE* pipe = _popen(command.c_str(), "r");
    #else
        FILE* pipe = popen(command.c_str(), "r");
    #endif
    if (!pipe) {
        return "err";
    }
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    return result;
}
class klik {
    public:
        fstream ClassFile;
        json ClassData;
        string name;
        string filename;
    public: klik() {
        filename=name+".json";
        ClassFile(filename);
    }
    public: int NewKlik(string name) {
        
        json klik;
        fstream outfile(name+".klik.json");
        
        json desc;
        desc["name"]=name;
        const auto now=chrono::system_clock::now();
        
        desc["timestamp"]=chrono::duration_cast<std::chrono::seconds>(
                    now.time_since_epoch()).count();
        string whoami=exec("whoami");
        whoami.erase(whoami.end()-1,whoami.end());
        desc["creator"]=whoami;

        klik["desc"]=desc;

        json data;
        klik["data"]=data;
        cout << klik.dump(4);

        outfile << klik.dump(4);
        return 0;
    }
};


int main(int argc, char * argv[]) {
    klik x;
    x.NewKlik("test");
}