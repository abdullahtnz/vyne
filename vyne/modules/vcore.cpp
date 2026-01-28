#include "vcore.h"

void setupBuiltIns(SymbolContainer& env){
    env["global.vcore"] = SymbolTable(); 

    env["global.vcore"]["sub@now"] = Value([](std::vector<Value>& args) -> Value {
        return Value(static_cast<double>(time(0)));
    });

    env["global.vcore"]["sub@sleep"] = Value([](std::vector<Value>& args) -> Value {
        if (args.empty()) throw std::runtime_error("Argument Error : vcore.sleep expects 1 argument (ms)");

        long long ms = static_cast<long long>(args[0].asNumber());
        
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        
        return Value(true);
    });
}
