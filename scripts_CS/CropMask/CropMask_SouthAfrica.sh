#!/bin/bash

source /home/achenebert/src/S5T5-scripts/CropMask/set_build_folder.sh

/home/achenebert/src/scripts/CropMask.py -refp /data/s2agri/input/InSituData/2015/SouthAfrica/ZA_FST_LC_FO_2015_SummerCrop.shp -ratio 0.75 -input \
/data/s2agri/input/EOData/2015/SouthAfrica/SouthAfrica/SPOT5_HRG2_XS_20150414_N2A_SouthAfricaD0000B0000/SPOT5_HRG2_XS_20150414_N2A_SouthAfricaD0000B0000.xml \
/data/s2agri/input/EOData/2015/SouthAfrica/SouthAfrica/SPOT5_HRG2_XS_20150429_N2A_SouthAfricaD0000B0000/SPOT5_HRG2_XS_20150429_N2A_SouthAfricaD0000B0000.xml \
/data/s2agri/input/EOData/2015/SouthAfrica/SouthAfrica/SPOT5_HRG2_XS_20150504_N2A_SouthAfricaD0000B0000/SPOT5_HRG2_XS_20150504_N2A_SouthAfricaD0000B0000.xml \
/data/s2agri/input/EOData/2015/SouthAfrica/SouthAfrica/SPOT5_HRG2_XS_20150509_N2A_SouthAfricaD0000B0000/SPOT5_HRG2_XS_20150509_N2A_SouthAfricaD0000B0000.xml \
/data/s2agri/input/EOData/2015/SouthAfrica/SouthAfrica/SPOT5_HRG2_XS_20150514_N2A_SouthAfricaD0000B0000/SPOT5_HRG2_XS_20150514_N2A_SouthAfricaD0000B0000.xml \
/data/s2agri/input/EOData/2015/SouthAfrica/SouthAfrica/SPOT5_HRG2_XS_20150519_N2A_SouthAfricaD0000B0000/SPOT5_HRG2_XS_20150519_N2A_SouthAfricaD0000B0000.xml \
/data/s2agri/input/EOData/2015/SouthAfrica/SouthAfrica/SPOT5_HRG2_XS_20150524_N2A_SouthAfricaD0000B0000/SPOT5_HRG2_XS_20150524_N2A_SouthAfricaD0000B0000.xml \
/data/s2agri/input/EOData/2015/SouthAfrica/SouthAfrica/SPOT5_HRG2_XS_20150608_N2A_SouthAfricaD0000B0000/SPOT5_HRG2_XS_20150608_N2A_SouthAfricaD0000B0000.xml \
/data/s2agri/input/EOData/2015/SouthAfrica/SouthAfrica/SPOT5_HRG2_XS_20150613_N2A_SouthAfricaD0000B0000/SPOT5_HRG2_XS_20150613_N2A_SouthAfricaD0000B0000.xml \
/data/s2agri/input/EOData/2015/SouthAfrica/SouthAfrica/SPOT5_HRG2_XS_20150618_N2A_SouthAfricaD0000B0000/SPOT5_HRG2_XS_20150618_N2A_SouthAfricaD0000B0000.xml \
/data/s2agri/input/EOData/2015/SouthAfrica/SouthAfrica/SPOT5_HRG2_XS_20150623_N2A_SouthAfricaD0000B0000/SPOT5_HRG2_XS_20150623_N2A_SouthAfricaD0000B0000.xml \
/data/s2agri/input/EOData/2015/SouthAfrica/SouthAfrica/SPOT5_HRG2_XS_20150628_N2A_SouthAfricaD0000B0000/SPOT5_HRG2_XS_20150628_N2A_SouthAfricaD0000B0000.xml \
/data/s2agri/input/EOData/2015/SouthAfrica/SouthAfrica/SPOT5_HRG2_XS_20150703_N2A_SouthAfricaD0000B0000/SPOT5_HRG2_XS_20150703_N2A_SouthAfricaD0000B0000.xml \
/data/s2agri/input/EOData/2015/SouthAfrica/SouthAfrica/SPOT5_HRG2_XS_20150708_N2A_SouthAfricaD0000B0000/SPOT5_HRG2_XS_20150708_N2A_SouthAfricaD0000B0000.xml \
/data/s2agri/input/EOData/2015/SouthAfrica/SouthAfrica/SPOT5_HRG2_XS_20150718_N2A_SouthAfricaD0000B0000/SPOT5_HRG2_XS_20150718_N2A_SouthAfricaD0000B0000.xml \
/data/s2agri/input/EOData/2015/SouthAfrica/SouthAfrica/SPOT5_HRG2_XS_20150728_N2A_SouthAfricaD0000B0000/SPOT5_HRG2_XS_20150728_N2A_SouthAfricaD0000B0000.xml \
/data/s2agri/input/EOData/2015/SouthAfrica/SouthAfrica/SPOT5_HRG2_XS_20150807_N2A_SouthAfricaD0000B0000/SPOT5_HRG2_XS_20150807_N2A_SouthAfricaD0000B0000.xml \
/data/s2agri/input/EOData/2015/SouthAfrica/SouthAfrica/SPOT5_HRG2_XS_20150817_N2A_SouthAfricaD0000B0000/SPOT5_HRG2_XS_20150817_N2A_SouthAfricaD0000B0000.xml \
/data/s2agri/input/EOData/2015/SouthAfrica/SouthAfrica/SPOT5_HRG2_XS_20150822_N2A_SouthAfricaD0000B0000/SPOT5_HRG2_XS_20150822_N2A_SouthAfricaD0000B0000.xml \
/data/s2agri/input/EOData/2015/SouthAfrica/SouthAfrica/SPOT5_HRG2_XS_20150827_N2A_SouthAfricaD0000B0000/SPOT5_HRG2_XS_20150827_N2A_SouthAfricaD0000B0000.xml \
/data/s2agri/input/EOData/2015/SouthAfrica/SouthAfrica/SPOT5_HRG2_XS_20150901_N2A_SouthAfricaD0000B0000/SPOT5_HRG2_XS_20150901_N2A_SouthAfricaD0000B0000.xml \
/data/s2agri/input/EOData/2015/SouthAfrica/SouthAfrica/SPOT5_HRG2_XS_20150911_N2A_SouthAfricaD0000B0000/SPOT5_HRG2_XS_20150911_N2A_SouthAfricaD0000B0000.xml \
-t0 20150414 -tend 20150911 -rate 5 -radius 100 -nbtrsample 4000 -rseed 0 -window 6 -lmbd 2 -weight 1 -nbcomp 6 -spatialr 10 -ranger 0.65 -minsize 10 -rfnbtrees 100 -rfmax 25 -rfmin 25 -tilename T15SVC -pixsize 10 \
-outdir /data/s2agri/output/SouthAfrica/SouthAfrica/cropMask -targetfolder /data/s2agri/output/SouthAfrica/SouthAfrica/cropMask-product -buildfolder /data/s2agri/sen2agri-processors-build/
