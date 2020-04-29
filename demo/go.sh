rm result.txt
g++ check.cpp -o check -std=c++11
mkdir output
rm -rf output/*
cd src
make clean
make
sudo dmesg -c
sudo ./scheduler < ../input/TIME_MEASUREMENT.txt > ../output/TIME_MEASUREMENT_stdout.txt
dmesg | grep Project > ../output/TIME_MEASUREMENT_dmesg.txt
../check ../output/TIME_MEASUREMENT_dmesg.txt ../input/TIME_MEASUREMENT.txt ../output/TIME_MEASUREMENT_stdout.txt ../output/TIME_MEASUREMENT_dmesg.txt >> ../result.txt

# FIFO

for i in $(seq 1 5);
do
    sudo dmesg -c
    sudo ./scheduler < ../input/FIFO_$i.txt > ../output/FIFO_$i\_stdout.txt
    dmesg | grep Project > ../output/FIFO_$i\_dmesg.txt
    ../check ../output/TIME_MEASUREMENT_dmesg.txt ../input/FIFO_$i.txt ../output/FIFO_$i\_stdout.txt ../output/FIFO_$i\_dmesg.txt >> ../result.txt
done

# SJF

for i in $(seq 1 5);
do
    sudo dmesg -c
    sudo ./scheduler < ../input/SJF_$i.txt > ../output/SJF_$i\_stdout.txt
    dmesg | grep Project > ../output/SJF_$i\_dmesg.txt
    ../check ../output/TIME_MEASUREMENT_dmesg.txt ../input/SJF_$i.txt ../output/SJF_$i\_stdout.txt ../output/SJF_$i\_dmesg.txt >> ../result.txt
done

# RR

for i in $(seq 1 5);
do
    sudo dmesg -c
    sudo ./scheduler < ../input/RR_$i.txt > ../output/RR_$i\_stdout.txt
    dmesg | grep Project > ../output/RR_$i\_dmesg.txt
    ../check ../output/TIME_MEASUREMENT_dmesg.txt ../input/RR_$i.txt ../output/RR_$i\_stdout.txt ../output/RR_$i\_dmesg.txt >> ../result.txt
done

# PSJF

for i in $(seq 1 5);
do
    sudo dmesg -c
    sudo ./scheduler < ../input/PSJF_$i.txt > ../output/PSJF_$i\_stdout.txt
    dmesg | grep Project > ../output/PSJF_$i\_dmesg.txt
    ../check ../output/TIME_MEASUREMENT_dmesg.txt ../input/PSJF_$i.txt ../output/PSJF_$i\_stdout.txt ../output/PSJF_$i\_dmesg.txt >> ../result.txt
done
