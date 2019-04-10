# RangeSim
GEANT4 range simulator

## Installation
```
mkdir build
cd build
cmake $SOURCE_DIR
make
```

## Run
Edit config.cfg. Then,
```
./rangesim
```

## Scripts
### TrackVis.C
Track visualization. Following is an example of the script output.
![track_vis_ex](./scripts/trackVisExample.gif)

### DrawHist.C
Histogram drawing. Following is an example of the script output.
![hist_draw_ex](./scripts/histExample.png "DrawHist.C Example result")

## Known issues
* Linker prints error with geant-4.10.04.p01 version. It seems HepRandom library cannot be found. Please use the latest version of GEANT4.
