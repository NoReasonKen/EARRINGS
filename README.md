# EARRINGS

EARRINGS is an efficient and accurate adapter trimmer that entails no a priori adapter sequences for both single- and paired-end NGS reads.

## Information

EARRINGS is a more powerful and capable successor of [PEAT](https://github.com/jhhung/PEAT), which is now deprecated.

Like PEAT, EARRING adapts [skewer](https://github.com/relipmoc/skewer)for single-end read trimming.

## Requirement

- [g++-8](https://gcc.gnu.org/gcc-8/) and cmake [3.10.0](https://cmake.org/download/) or higher to build EARRINGS
- python3.7 or higher as well as numpy and pandas packages for the benchmarking

## Build

```sh
# In root directory of repository
> mkdir build
> cd build
# If default gcc or g++ version != 8.0
# -DCMAKE_C_COMPILER=/usr/bin/gcc-8 or -DCMAKE_CXX_COMPILER=/usr/bin/g++-8 is needed.
> cmake .. -DBUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../stage
> cmake --build . --target install
> ./EARRINGS -h
```

## Execution

There are 3 modes to execute EARRINGS: **build**, **single**, and **paired**.

Build mode generates an index for the source reference sequence (e.g., the entire genome, a chromosome, a collection of panel genes, etc.) of the **single-end** reads. The index is **not** used for trimming paired-end reads.

Single mode and paired mode are used for single-end reads and paired-end reads respectively.

### **Single-End**

### Build reference index

Before conducting single-end adapter trimming, **one has to prebuild the index** once for a specific reference
which is the source of the target reads.

```sh
# ./EARRINGS build -r [ref_path] -p [index_prefix]
> ./EARRINGS build -r hg38_chr1.fa -p earrings_hg38_chr1
> ./EARRINGS build -r 16S_rRNA_panel.fa -p 16S_rRNA_penel
```

Build parameters

- Required
  - -r [ --ref_path ] Path to the reference sequence, which is the source of reads.
  - -p [ --index_prefix ] A user-defined index prefix for index table.
- Optional
  - -h [ --help ] Display help message and exit.

### Execute Single-End trimming

EARRINGS first detects adapter then feeds the detected adapter to skewer.

```sh
# ./EARRINGS single -p [index_prefix] -1 [input_file]
> ./EARRINGS single -p path_to_index -1 ../test_data/has_adapter_1.fq
```

Single-End mode parameters

- Required
  - -1 [ --input1 ] The Single-End FastQ input file 1 (.fq).
  - -p [ --index_prefix ] The index prefix for pre-built index table.
- Optional
  - Utils
    - -h [ --help ] Display help message and exit.
  - Input / Output
    - -o [ --output ] The Single-End FastQ output file prefix. (default: EARRINGS_se)
    - -b [ --bam_input ] Transform reads in a BAM file into a FastA file, then trim off adapters from </br>
            the FastA file.</br>
            The file name of the untrimmed Fasta file is specified by the input file name for Skewer, </br>
            while the file name of the trimmed Fasta file is also specified by the output file name for Skewer.
    - -F [ --fasta ] Specify input file type as FastA. (Default input file format: FastQ)
  - Extract seeds / Alignment
    - -m [ --min_length ] Abort the read if the length of the read is less than m. (default: 0)
    - -d [ --seed_len ] The first ***seed_len*** bases at 5' portion is viewed as seed when conducting alignment.</br>
            EARRINGS allows at most one mismatch in the seed portion if enable_mismatch is set to true.</br>
            Reads will be aborted if more than one mismatch is found in the seed portion. If one mismatch </br>
            is found outside the seed region, the remainder (including mismatch) is reported as a tail.</br>
            It's recommended to set the seed_len to 18 for very short reads like miRNA, otherwise, it is </br>
            recommended to set it to 50. (default: 50)
    - -e [ --enable_mismatch ] Enable/disable mismatch toleration when conducting seed finding, </br>
            it can tolerate 1 error base at most if be set as true. (default: true)
    - -M [ --max_align ] Maximum number of candidates used in seed finding stage. (default: 0, not </br>
            limited)
  - Assemble adapter
    - -f [ --prune_factor ] Prune factor used when assembling adapters using the de-brujin graph. </br>
            Kmer frequency lower than the prune factor will be aborted. (default: 0.03)
    - --sensitive By default, minimum number of kmers must exceed 10 during assembly adapters.</br>
            However, if user have confidence that the dataset contains adapters, sensitive mode is </br>
            more suitable.
            Under sensitive mode, minimum number of kmers would not be restricted when assembly </br>
            adapters.
  - Adapter setting
    - -a [ --adapter1 ] Alternative adapter if auto-detect mechanism fails.</br>
            (default: AGATCGGAAGAGCACACGTCTGAACTCCAGTCAC)
    - -u [ --UMI ] Estimate the size of UMI sequences, results will be printed to console by default.

### **Paired-End**

### Execute Paired-End trimming

```sh
# ./EARRINGS paired -1 [input1] -2 [input2]
> ./EARRINGS paired -1 ../test_data/has_adapter_1.fq -2 ../test_data/has_adapter_2.fq
```

Paired-end mode parameters

- Required
  - -1 [ --input1 ] The PE FastQ input file 1 (.fq)
  - -2 [ --input2 ] The PE FastQ input file 2 (.fq)
- Optional
  - Utils
    - -h [ --help ] Display help message and exit.
    - -t [ --thread ] The number of threads used to run the program. (default: 1)
  - Input / Output
    - -F [ --fasta ] Specify input file type as FastA. (default input file format: FastQ)
    - -b [ --bam_input ] Transform reads in a BAM file into two FastA files. Then trim off adapters</br>
            from the FastA files. The file names of the untrimmed Fasta files are determined by input1 </br>
            and input2, while the file names of the trimmed Fasta files are determined by output1 and </br>
            output2.
    - -o [ --output ] The PE FastQ output file prefix. (default: EARRINGS_pe)
  - Extract seeds / Alignment
    - -m [ --min_length ] Abort the read if the length of the read is less than m. (default: 0)
  - Assemble adapter
    - -f [ --prune_factor ] Prune factor used when assembling adapters using the de Bruijn graph. kmer</br>
            frequency lower than the prune factor will be aborted. (default: 0.03)
    - --sensitive Sensitive mode can be used when the user is sure that the dataset contains adapters.</br>
            Under sensitive mode, we do not restrict the minimum number of occurrence of kmers when </br>
            assembly adapters.</br>
            By default, the minimum number of occurrence of kmers must exceed 10.
  - Trimming
    - -M [ --rc_thres ] Mismatch threshold applied in reverse complement scan. (default: 0.7)
    - -s [ --ss_thres ] Mismatch threshold applied in gene portion check. (default: 0.9)
    - -S [ --as_thres ] Mismatch threshold applied in adapter portion check. (default: 0.8)
  - Adapter setting
    - -a [ --adapter1 ] Default adapter 1 when auto-detect fails.</br>
            (default: AGATCGGAAGAGCACACGTCTGAACTCCAGTCAC)
    - -A [ --adapter2 ] Default adapter 2 when auto-detect fails.</br>
            (default: AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGTA)
    - -l [ --adapter_loc ] Specify the location of the adapter is at head side or tail side. </br>
            (default: tail)

## Run Simulation

The simulation is carried out using a modified version of [pIRS](https://github.com/galaxy001/pirs)
(profile based Illumina pair-end Reads Simulator).
Please build pIRS first before using it:

```sh
> cd simulator/pIRS
> make
```

pIRS simulates Illumina PE reads from a reference genome. In all the benchmarking except real data </br>
benchmarking, we use GRCh38 chr1 as reference genome to simulate reads.

One can run the simulation by:

```sh
# python3 script.py [seed] -r [ref_genome] -n [read_num] -m [insert_mean] -std [insert_td] -ad1 [ad1] -ad2 [ad1]
# To generate reads without adapters:
> python3 script.py 0 -r hg38_chr1.fa -n 10000 -m 150 -std 50 -ad1 "" -ad2 ""
# To generate reads with default adapters:
> python3 script.py 0 -r hg38_chr1.fa -n 10000 -m 150 -std 50
```

## Run Benchmarking

Before running benchmarking, please install all the prerequisites and set the locations of all the </br>
executions to $PATH:

1. AdapterRemoval ver. 2.3.0
2. skewer ver. 0.2.2
3. Cutadapt ver. 2.4
4. AKATrim ver. 1.3.3
5. Trimmomatic ver. 0.39
6. SeqPurge ver. 2019_11
7. fastp ver. 0.20.0 - commit 6ff0ffa
8. atropos ver. 1.1.21 - commit 2b15c77
9. PEAT ver. 1.2.5
10. python ver. 3.6
11. our modified version of pIRS (see Run Simulation part)
12. picard 2.23.0

For speed, memory, performance and adapter benchmarking, please download the first chromosome of GRCh38 from UCSC genome browser.
For running real data benchmarking, please download the following four datasets and their corresponding reference genome(.fa) from ncbi.

1. SRR529095: RNA IP-Seq of Argonaute proteins from Homo sapiens
2. SRR014866: miRNA of C.elegans
3. SRR330569: RNA-Seq of Gonads and Carcasses in D. simulans and D. pseudoobscura
4. SRR5000681: ATAC-Seq of Early Embryo replicate in C.elegans

Also, don't forget to install the aligners:

1. Bowtie2 v2.4.1
2. HISAT2 v2.2.0

After that, modify path-related variables in path&#46;py to the path where the downloaded datasets were placed.
Then prebuild indices for the aligners and EARRINGS by running:

```sh
> python3 build_index.py
```

Run real data benchmarking:

```sh
> python3 benchmark_real_data.py
```

Run speed benchmarking:

```sh
> python3 benchmark_speed.py
```

Run memory benchmarking:

```sh
> python3 benchmark_mem_usage.py
```

Run performance benchmarking:

```sh
> python3 benchmark_performance.py
```

Run adapter benchmarking:

```sh
> python3 benchmark_adapter.py
```

## Reference

1. Li, Y.-L., Weng, J.-C., Hsiao, C.-C., Chou, M.-T., Tseng, C.-W., & Hung, J.-H. (2015). PEAT: an intelligent and efficient paired-end sequencing adapter trimming algorithm. BMC Bioinformatics, 16(Suppl 1), S2. doi:10.1186/1471-2105-16-S1-S2</br>
[[paper](https://bmcbioinformatics.biomedcentral.com/articles/10.1186/1471-2105-16-S1-S2)]
[[github](https://github.com/jhhung/PEAT)]
2. Jiang, H., Lei, R., Ding, S.W. and Zhu, S. (2014) Skewer: a fast and accurate adapter trimmer for next-generation sequencing paired-end reads. BMC Bioinformatics, 15, 182.</br>
[[paper](https://bmcbioinformatics.biomedcentral.com/articles/10.1186/1471-2105-15-182)]
[[github](https://github.com/relipmoc/skewer)]
3. Hu, X., et al. (2012) pIRS: Profile-based Illumina pair-end reads simulator, Bioinformatics, 28, 1533-1535.</br>
[[paper](https://academic.oup.com/bioinformatics/article/28/11/1533/267409)]
[[github](https://github.com/galaxy001/pirs)]
4. Chou, M.-T., Han, B. W., Hsiao, C.-P., Zamore, P. D., Weng, Z., and Hung, J.-H. (2015). Tailor: a computational framework for detecting non-templated tailing of small silencing RNAs. Nucleic Acids Res. 43, e109.</br>
[[paper](https://academic.oup.com/nar/article/43/17/e109/2414301)]
[[github](https://github.com/jhhung/Tailor)]

## Citation

Wang et al. EARRINGS: An Efficient and Accurate Adapter Trimmer Entails No a Priori Adapter Sequences. Bioinformatics. Accepted.</br>
[[paper](https://academic.oup.com/bioinformatics/advance-article-abstract/doi/10.1093/bioinformatics/btab025/6103563)]
[[github](https://github.com/jhhung/EARRINGS)]

## Contact

```sh
Jui-Hung Hung <juihunghung@gmail.com>

Ting-Husan Wang <phoebewangintw@gmail.com>

Cheng-Ching Huang <ken5112840801@gmail.com>
```
