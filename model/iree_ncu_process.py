from typing import Dict
import os
import subprocess
import pandas as pd
import logging

class NcuResult:
    def __init__(self,kname):
        self.name = kname
        self.gpu_time_duration = 0
        self.memory_throughput = 0
        self.compute_throughput = 0
        self.dram_read = 0
        self.dram_write = 0
        self.call_times = 0

def ncu_profile(cmd, out_file, gen_full = False)->Dict[str,Dict]:
 


    ncu_cmd = f'/usr/local/NVIDIA-Nsight-Compute/ncu  -f  --set full  -o {out_file}_full {cmd}'
    if gen_full:
        subprocess.run(ncu_cmd.split(), check=True)

    # gather metrics
    gpu_time_duration = "gpu__time_duration.sum"
    memory_throughput = "gpu__compute_memory_throughput.avg.pct_of_peak_sustained_elapsed"
    compute_throughput = "sm__throughput.avg.pct_of_peak_sustained_elapsed"
    dram_read = "dram__bytes_read.sum"
    dram_write = "dram__bytes_write.sum"
 

    metrics = [
        gpu_time_duration,
        memory_throughput,
        compute_throughput,
        dram_read,
        dram_write
    ]

    metrics_str = str.join(",",metrics)
    ncu_csv = f'/usr/local/NVIDIA-Nsight-Compute/ncu -f  --log-file {out_file}.csv --csv --metrics  {metrics_str} {cmd}'

    logging.info(f"{ncu_csv}")
    subprocess.run(ncu_csv.split(), check=True)
 
    df = pd.read_csv(f"{out_file}.csv", skiprows=2)
    
    result_dict:Dict[str,NcuResult] = {}
    # all
    all_time = 0
    all_memory_throughput = 0
    all_compute_throughput = 0
    all_dram_read = 0
    all_dram_write = 0

    for _, row in df.iterrows():
        kernel_name = row['Kernel Name'] 
        row_name = row['Metric Name']
        row_value = row["Metric Value"]
        # if "memcpy" in kernel_name:
        #     continue
        if kernel_name not in result_dict:
            result_dict[kernel_name] = NcuResult(kernel_name)
            result_dict[kernel_name].call_times = 1
        if  row_name == gpu_time_duration: 
            # us
            time = float(row_value) * 1e-3
            # has multi calls
            if result_dict[kernel_name].gpu_time_duration != 0:
                result_dict[kernel_name].call_times = result_dict[kernel_name].call_times + 1
            result_dict[kernel_name].gpu_time_duration = time
            all_time = all_time + time
        elif row_name == memory_throughput:
            temp_value = float(row_value)
            result_dict[kernel_name].memory_throughput = temp_value
            all_memory_throughput = all_memory_throughput + temp_value
        elif row_name == compute_throughput:
            temp_value = float(row_value)
            result_dict[kernel_name].compute_throughput = temp_value
            all_compute_throughput = all_compute_throughput + temp_value
        elif row_name == dram_read:
            temp_value = float(row_value)
            result_dict[kernel_name].dram_read =temp_value
            all_dram_read = all_dram_read + temp_value
        elif row_name == dram_write:
            temp_value = float(row_value)
            result_dict[kernel_name].dram_write = temp_value
            all_dram_write = all_dram_write + temp_value
    
    avg_memory_throughput = all_memory_throughput/ len(result_dict)
    avg_compute_throughput = all_compute_throughput/ len(result_dict)

    log_str = "\n|name |Time us |compute_throughput %| mem_throughput % | read MB| wite MB|calls| \n" \
    "|-|-|-|-|-|-|-|\n" \
    f"|sum | {all_time} | {avg_compute_throughput}| {avg_memory_throughput}| {all_dram_read/(1024 * 1024)}| {all_dram_write/(1024 * 1024)} | -|\n"
    

    for key,value in result_dict.items():
        if len(key) > 50 :
            key = key[:50]
        log_str = log_str + (f"|{key} | {value.gpu_time_duration }|  {value.compute_throughput }| {value.memory_throughput} |{value.dram_read/(1024 * 1024)} |{value.dram_write/(1024 * 1024)}| {value.call_times}|\n")
    logging.info(log_str)
   


