## A dynamic programming algorithm for the Robotic Cell Problem with a fixed job processing order

#### Alessandro Minoli, Giovanni Righini (2026)

### Abstract

The Robotic Cell Problem (RCP) is a flow-shop scheduling problem in which jobs must be transferred from each machine to the next one by a robot.
The robot movements require non-negligible time and must be optimized to minimize the makespan.
The problem is practically relevant in the context of manufacturing systems.
In this work, we study a variant of the RCP in which the processing order of the jobs is fixed.
We present a dynamic programming algorithm for the exact optimization of this variant and show how it can be transformed into an accurate heuristic.
Computational results are provided on instances with up to 30 jobs and 15 machines under different distributions of travel and processing times.
The results indicate that our algorithm can solve significantly larger instances than existing methods.
The proposed approach may also serve as a subroutine within future heuristic methods for the general RCP.

### Usage

Requirements: CMake >= 3.16 and a C++20 compiler.

Compile with:

```
mkdir build
cd build
cmake ..
make
cd ..
```

This produces the executable `./bin/DP4RCP`.

Run it as:

```
./bin/DP4RCP <instance_path> [mode] [verbose]
```

- `instance_path` (required): path to the instance file to solve.
- `mode` (optional, default `exact_dp`): the algorithm to run. One of:
  - `exact_dp`: the exact dynamic programming algorithm.
  - `heuristic_one_job_at_a_time`: the "*One job at a time*" heuristic.
  - `heuristic_one_machine_at_a_time`: the "*One machine at a time*" heuristic.
  - `heuristic_dp_rho1`: the heuristic DP algorithm with $\rho=1$.
  - `heuristic_dp_rho2`: the heuristic DP algorithm with $\rho=2$.
  - `test`: runs all of the above on the given instance and prints a single CSV line with their results (see [How to read the computational results](#how-to-read-the-computational-results)).
- `verbose` (optional, default `0`): set to `1` to print additional information about the solving process; `0` disables it. Ignored (always `0`) when `mode` is `test`.

For example, to solve `sample_instance.txt` with the exact algorithm and verbose output:

```
./bin/DP4RCP sample_instance.txt exact_dp 1
```

### Datasets

The directory [dataset_D1](https://github.com/alessandro-minoli/DP_for_RCP_with_a_fixed_job_processing_order/tree/main/dataset_D1) contains the 1680 instance files of Dataset D1.

The directory [dataset_D2](https://github.com/alessandro-minoli/DP_for_RCP_with_a_fixed_job_processing_order/tree/main/dataset_D2) contains the 3000 instance files of Dataset D2.
It is further divided into 20 subdirectories (one per instance class), each containing 150 instances.

### Format of the instance files

```
m                                   # number of machines
n                                   # number of jobs
p_1,1    p_1,2    ...  p_1,n        # processing times
p_2,1    p_2,2    ...  p_2,n
...
p_m,1    p_m,2    ...  p_m,n
t_0,0    t_0,1    ...  t_0,m+1      # travel times
t_1,0    t_1,1    ...  t_1,m+1
...
t_m+1,0  t_m+1,1  ...  t_m+1,m+1
```
### Python dependencies

Running the experiments and generating the tables and figures ([MILP_formulation.py](MILP_formulation.py) and the scripts in [scripts/](scripts)) requires Python 3 with the packages listed in [requirements.txt](requirements.txt). Install them with:

```
pip install -r requirements.txt
```

`MILP_formulation.py` also requires [Gurobi](https://www.gurobi.com) to be installed with a valid license (a free academic license is available). `pip install gurobipy` only installs the Python interface, not a license.

### How to run the experiments

These are the instructions to replicate the experiments we conducted.

The computational results related to the MILP formulation can be obtained by running this command:
```
python3 MILP_formulation.py > computational_results_MILP_formulation.csv
```

The computational results related to dataset D1 can be obtained by running these commands:
```
chmod +x run_experiments_dataset_D1.sh
./run_experiments_dataset_D1.sh > computational_results_dataset_D1.csv
```

The computational results related to dataset D2 can be obtained by running these commands:
```
chmod +x run_experiments_dataset_D2.sh
./run_experiments_dataset_D2.sh > computational_results_dataset_D2.csv
```

### How to read the computational results

The computational results are stored in the files:

- [computational_results_MILP_formulation.csv](https://github.com/alessandro-minoli/DP_for_RCP_with_a_fixed_job_processing_order/blob/main/computational_results_MILP_formulation.csv)
- [computational_results_dataset_D1.csv](https://github.com/alessandro-minoli/DP_for_RCP_with_a_fixed_job_processing_order/blob/main/computational_results_dataset_D1.csv)
- [computational_results_dataset_D2.csv](https://github.com/alessandro-minoli/DP_for_RCP_with_a_fixed_job_processing_order/blob/main/computational_results_dataset_D2.csv)

The meaning of the CSV fields is as follows:

| Field             | Meaning |
| :- | :-|
| instance_path | path of the solved instance
| m | number of machines of the solved instance
| n | number of jobs of the solved instance
| seed | seed of the solved instance
| tr | maximum travel time, i.e. travel times in [1,tr] |
| pr | maximum processing time, i.e. processing times in [1,pr] |
| milp_time | runtime [s] of the MILP formulation, or "TIME_LIMIT" |
| exact_sol | optimal completion time found by the exact DP algorithm |
| exact_time | runtime [s] of the exact DP algorithm |
| u1_sol | completion time found by the "*One job at a time*" heuristic |
| u2_sol | completion time found by the "*One machine at a time*" heuristic |
| h_rho1_sol | completion time found by the heuristic DP algorithm with $\rho=1$ |
| h_rho2_sol | completion time found by the heuristic DP algorithm with $\rho=2$ |
| h_rho2_time | runtime [s] of the heuristic DP algorithm with $\rho=2$ |

### How to create tables and figures

The tables and figures reported in the paper are related to the above computational results.
To create such tables (in .csv format) and figures (in .pdf format), run the following commands:

```
cd scripts
chmod +x run_create.sh
./run_create.sh
cd ..
```

You will find the output files in the [scripts](https://github.com/alessandro-minoli/DP_for_RCP_with_a_fixed_job_processing_order/blob/main/scripts) directory.

### License

This project is licensed under the [Apache License 2.0](LICENSE).
