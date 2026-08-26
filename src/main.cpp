#include <assert.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <tuple>

#include "Instance.h"
#include "Solver.h"

int main(int argc, char *argv[])
{
    std::string usage = std::string("Usage: ") + argv[0] + " <instance_path> [mode] [verbose]\n\n"
        "  instance_path  path to the instance file (required)\n"
        "  mode           one of: exact_dp (default), heuristic_one_job_at_a_time,\n"
        "                 heuristic_one_machine_at_a_time, heuristic_dp_rho1,\n"
        "                 heuristic_dp_rho2, test\n"
        "  verbose        0 (default) or 1; ignored (forced to 0) when mode = test";

    if (argc < 2 || std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")
    {
        std::cerr << usage << std::endl;
        return (argc < 2) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    std::string filename = std::string(argv[1]);
    std::string mode = (argc > 2) ? std::string(argv[2]) : "exact_dp";

    bool verbose = false;
    if (argc > 3)
    {
        std::string verbose_arg = std::string(argv[3]);
        if (verbose_arg == "1")      verbose = true;
        else if (verbose_arg == "0") verbose = false;
        else
        {
            std::cerr << "ERROR, invalid verbose value '" << verbose_arg << "' (expected 0 or 1)" << std::endl;
            return EXIT_FAILURE;
        }
    }

    if (mode != "test" and mode != "exact_dp" and mode != "heuristic_one_job_at_a_time" and
        mode != "heuristic_one_machine_at_a_time" and mode != "heuristic_dp_rho1" and mode != "heuristic_dp_rho2")
    {
        std::cerr << "ERROR, invalid mode '" << mode << "'" << std::endl << std::endl;
        std::cerr << usage << std::endl;
        return EXIT_FAILURE;
    }

    if (mode != "test")
    {
        std::cout << "--- INPUT -------------------------------" << std::endl;
        std::cout << "filename: " << filename << std::endl;
        std::cout << "mode: " << mode << std::endl;
        std::cout << "verbose: " << verbose << std::endl;
    }

    Instance ins(filename);
    // std::cout << ins << std::endl;

    Solver solver;

    std::tuple<int,double> output;

    if (mode == "test")
    {
        verbose = false;

        std::cout << filename << ","; // instance_path

        if (filename.rfind("dataset_D1/", 0) == 0)
        {
            int m    = std::stoi(filename.substr(13, 2));
            int n    = std::stoi(filename.substr(18, 2));
            int seed = std::stoi(filename.substr(26, 2));
            std::cout << m << "," << n << "," << seed << ","; // m,n,seed
        }
        else if (filename.rfind("dataset_D2/", 0) == 0)
        {
            int tr = std::stoi(filename.substr(14, 2));
            int pr;
            int base; // index of the '/' right after pr
            if (filename[22] == '/') {
                // pr is 2 digits
                pr = std::stoi(filename.substr(20, 2));
                base = 22;
            } else {
                // pr is 3 digits
                pr = std::stoi(filename.substr(20, 3));
                base = 23;
            }
            int m    = std::stoi(filename.substr(base + 3, 2));
            int n    = std::stoi(filename.substr(base + 8, 2));
            int seed = std::stoi(filename.substr(base + 16, 2));
            std::cout << tr << "," << pr << "," << m << "," << n << "," << seed << ","; // tr,pr,m,n,seed
        }

        output = solver.run_exact_dp(ins, verbose);
        std::cout << std::get<0>(output) << ","; // exact_sol
        std::cout << std::get<1>(output) << ","; // exact_time

        output = solver.run_heuristic_one_job_at_a_time(ins, verbose);
        std::cout << std::get<0>(output) << ","; // u1_sol

        output = solver.run_heuristic_one_machine_at_a_time(ins, verbose);
        std::cout << std::get<0>(output) << ","; // u2_sol

        output = solver.run_heuristic_dp(ins, 1, verbose);
        std::cout << std::get<0>(output) << ","; // h_rho1_sol

        output = solver.run_heuristic_dp(ins, 2, verbose);
        std::cout << std::get<0>(output) << ",";       // h_rho2_sol
        std::cout << std::get<1>(output) << std::endl; // h_rho2_time
    }
    else if (mode == "exact_dp")                        output = solver.run_exact_dp                        (ins,    verbose);
    else if (mode == "heuristic_one_job_at_a_time")     output = solver.run_heuristic_one_job_at_a_time     (ins,    verbose);
    else if (mode == "heuristic_one_machine_at_a_time") output = solver.run_heuristic_one_machine_at_a_time (ins,    verbose);
    else if (mode == "heuristic_dp_rho1")               output = solver.run_heuristic_dp                    (ins, 1, verbose);
    else if (mode == "heuristic_dp_rho2")               output = solver.run_heuristic_dp                    (ins, 2, verbose);

    if (mode != "test")
    {
        std::cout << "--- OUTPUT ------------------------------" << std::endl;
        std::cout << "completion_time: " << std::get<0>(output) << std::endl;
        std::cout << "runtime[s]: " << std::get<1>(output) << std::endl;
    }

    return 0;
}
