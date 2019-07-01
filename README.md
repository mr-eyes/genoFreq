# genoFreq

Generate frequency matrix for all samples genotypes

## Dependencies

### Google sparsehash

`sudo apt-get install libsparsehash-dev`

### Boost

`sudo apt-get install libboost-all-dev`

## Build

```shell
mkdir build && cd build/
cmake ..
make
```

## Execute

```shell
./genoFreq <vcf.gz>
```
