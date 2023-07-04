import os
import sys
import subprocess
import random

ignore_cases = []
data_cases = [5,7,8,11]
cases = [i for i in range(1, 12) if i not in ignore_cases]

def main():
    compare = True
    if (len(sys.argv) == 2 and sys.argv[1] == "--no-compare"):
        compare = False

    for i in cases:
        inst_file = f"test/input/proj2_{i}_inst.bin"
        data_file = f"test/input/proj2_{i}_data.bin"
        ref_output_file = open(f"test/output/ref_{i}.txt", "w+")
        output_file = open(f"test/output/out_{i}.txt", "w+")
        inst_count = 0

        with open(inst_file, "rb") as f:
            inst_count = len(f.read()) // 4

        if i in data_cases:
            print(f"./riscv-sim {inst_file} {data_file} {inst_count}");
            subprocess.Popen(["./riscv-sim", inst_file, data_file, str(inst_count)],
                                   stdout=output_file, stderr=output_file).wait()
            if compare:
                subprocess.Popen(["./test/input/riscv-sim", inst_file, data_file, str(inst_count)],
                                   stdout=ref_output_file, stderr=ref_output_file).wait()
        else:
            print(f"./riscv-sim {inst_file} {inst_count}");
            subprocess.Popen(["./riscv-sim", inst_file, str(inst_count)],
                                   stdout=output_file, stderr=output_file).wait()
            if compare:
                subprocess.Popen(["./test/input/riscv-sim", inst_file, str(inst_count)],
                                   stdout=ref_output_file, stderr=ref_output_file).wait()

        ref_output_file.flush()
        output_file.flush()
        ref_output_file.close()
        output_file.close()

        if compare:
            print(f"file 1: {ref_output_file.name}");
            print(f"file 2: {output_file.name}");
            subprocess.Popen(["diff", "--color", ref_output_file.name, output_file.name]).wait()
        else:
            subprocess.Popen(["cat", output_file.name]).wait()

        print()

if __name__ == "__main__":
    main()
