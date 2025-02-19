#include <fmt/format.h>
#include "LOG/easylogging++.h"
#include "ConfigParams.h"
#include "Instance.h"
#include "Utils/GetOpt.h"
#include "Cvrp_cplex_interface.h"

INITIALIZE_EASYLOGGINGPP

using namespace fmt;
int main(int argc, char **argv) {
    // Load configuration from file
    el::Configurations conf("easylogger_conf.conf");
    // Init loggers
    el::Loggers::getLogger("main");
    el::Loggers::getLogger("instance");
    el::Loggers::getLogger("config");
    el::Loggers::getLogger("Cvrp_bc");
    el::Loggers::getLogger("optimizer");
    el::Loggers::getLogger("callback");
    el::Loggers::reconfigureAllLoggers(conf);
    LOG(INFO) << "Logger Initialized";

    // Parse arguments
    GetOpt opt {argc,argv};
    CLOG(INFO,"main") << "Arguments Parsed";

    ConfigParams cp {opt.getConfig()};
    // Parse instance file
    Instance is {opt.getInstance()};
    if (!is.isValid())
        exit(EXIT_FAILURE);
    CLOG(INFO,"main") << "Instance initialized";

    Cvrp_cplex_interface cci {is,cp};
    cci.solveModel();
    cci.writeSolution();
    return 0;
}
