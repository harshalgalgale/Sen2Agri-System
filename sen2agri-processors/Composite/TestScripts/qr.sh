#! /bin/bash

#USER modif
#add directories where SPOT products are to be found
inputXML="/mnt/Satellite_Imagery/S2-QR/SouthAfrica/SPOT4_HRVIR1_XS_20130131_N2A_ESouthAfricaD0000B0000/SPOT4_HRVIR1_XS_20130131_N2A_ESouthAfricaD0000B0000.xml "
inputXML+="/mnt/Satellite_Imagery/S2-QR/SouthAfrica/SPOT4_HRVIR1_XS_20130205_N2A_ESouthAfricaD0000B0000/SPOT4_HRVIR1_XS_20130205_N2A_ESouthAfricaD0000B0000.xml "
inputXML+="/mnt/Satellite_Imagery/S2-QR/SouthAfrica/SPOT4_HRVIR1_XS_20130220_N2A_ESouthAfricaD0000B0000/SPOT4_HRVIR1_XS_20130220_N2A_ESouthAfricaD0000B0000.xml "
inputXML+="/mnt/Satellite_Imagery/S2-QR/SouthAfrica/SPOT4_HRVIR1_XS_20130225_N2A_ESouthAfricaD0000B0000/SPOT4_HRVIR1_XS_20130225_N2A_ESouthAfricaD0000B0000.xml "
inputXML+="/mnt/Satellite_Imagery/S2-QR/SouthAfrica/SPOT4_HRVIR1_XS_20130302_N2A_ESouthAfricaD0000B0000/SPOT4_HRVIR1_XS_20130302_N2A_ESouthAfricaD0000B0000.xml "
inputXML+="/mnt/Satellite_Imagery/S2-QR/SouthAfrica/SPOT4_HRVIR1_XS_20130312_N2A_ESouthAfricaD0000B0000/SPOT4_HRVIR1_XS_20130312_N2A_ESouthAfricaD0000B0000.xml "
inputXML+="/mnt/Satellite_Imagery/S2-QR/SouthAfrica/SPOT4_HRVIR1_XS_20130317_N2A_ESouthAfricaD0000B0000/SPOT4_HRVIR1_XS_20130317_N2A_ESouthAfricaD0000B0000.xml "
inputXML+="/mnt/Satellite_Imagery/S2-QR/SouthAfrica/SPOT4_HRVIR1_XS_20130322_N2A_ESouthAfricaD0000B0000/SPOT4_HRVIR1_XS_20130322_N2A_ESouthAfricaD0000B0000.xml "
inputXML+="/mnt/Satellite_Imagery/S2-QR/SouthAfrica/SPOT4_HRVIR1_XS_20130401_N2A_ESouthAfricaD0000B0000/SPOT4_HRVIR1_XS_20130401_N2A_ESouthAfricaD0000B0000.xml "
inputXML+="/mnt/Satellite_Imagery/S2-QR/SouthAfrica/SPOT4_HRVIR1_XS_20130406_N2A_ESouthAfricaD0000B0000/SPOT4_HRVIR1_XS_20130406_N2A_ESouthAfricaD0000B0000.xml "
inputXML+="/mnt/Satellite_Imagery/S2-QR/SouthAfrica/SPOT4_HRVIR1_XS_20130416_N2A_ESouthAfricaD0000B0000/SPOT4_HRVIR1_XS_20130416_N2A_ESouthAfricaD0000B0000.xml "
inputXML+="/mnt/Satellite_Imagery/S2-QR/SouthAfrica/SPOT4_HRVIR1_XS_20130421_N2A_ESouthAfricaD0000B0000/SPOT4_HRVIR1_XS_20130421_N2A_ESouthAfricaD0000B0000.xml "
inputXML+="/mnt/Satellite_Imagery/S2-QR/SouthAfrica/SPOT4_HRVIR1_XS_20130426_N2A_ESouthAfricaD0000B0000/SPOT4_HRVIR1_XS_20130426_N2A_ESouthAfricaD0000B0000.xml "
inputXML+="/mnt/Satellite_Imagery/S2-QR/SouthAfrica/SPOT4_HRVIR1_XS_20130501_N2A_ESouthAfricaD0000B0000/SPOT4_HRVIR1_XS_20130501_N2A_ESouthAfricaD0000B0000.xml "
inputXML+="/mnt/Satellite_Imagery/S2-QR/SouthAfrica/SPOT4_HRVIR1_XS_20130506_N2A_ESouthAfricaD0000B0000/SPOT4_HRVIR1_XS_20130506_N2A_ESouthAfricaD0000B0000.xml "
inputXML+="/mnt/Satellite_Imagery/S2-QR/SouthAfrica/SPOT4_HRVIR1_XS_20130511_N2A_ESouthAfricaD0000B0000/SPOT4_HRVIR1_XS_20130511_N2A_ESouthAfricaD0000B0000.xml "
inputXML+="/mnt/Satellite_Imagery/S2-QR/SouthAfrica/SPOT4_HRVIR1_XS_20130516_N2A_ESouthAfricaD0000B0000/SPOT4_HRVIR1_XS_20130516_N2A_ESouthAfricaD0000B0000.xml "
inputXML+="/mnt/Satellite_Imagery/S2-QR/SouthAfrica/SPOT4_HRVIR1_XS_20130521_N2A_ESouthAfricaD0000B0000/SPOT4_HRVIR1_XS_20130521_N2A_ESouthAfricaD0000B0000.xml "
inputXML+="/mnt/Satellite_Imagery/S2-QR/SouthAfrica/SPOT4_HRVIR1_XS_20130526_N2A_ESouthAfricaD0000B0000/SPOT4_HRVIR1_XS_20130526_N2A_ESouthAfricaD0000B0000.xml "
inputXML+="/mnt/Satellite_Imagery/S2-QR/SouthAfrica/SPOT4_HRVIR1_XS_20130531_N2A_ESouthAfricaD0000B0000/SPOT4_HRVIR1_XS_20130531_N2A_ESouthAfricaD0000B0000.xml "
inputXML+="/mnt/Satellite_Imagery/S2-QR/SouthAfrica/SPOT4_HRVIR1_XS_20130605_N2A_ESouthAfricaD0000B0000/SPOT4_HRVIR1_XS_20130605_N2A_ESouthAfricaD0000B0000.xml "
inputXML+="/mnt/Satellite_Imagery/S2-QR/SouthAfrica/SPOT4_HRVIR1_XS_20130610_N2A_ESouthAfricaD0000B0000/SPOT4_HRVIR1_XS_20130610_N2A_ESouthAfricaD0000B0000.xml "
inputXML+="/mnt/Satellite_Imagery/S2-QR/SouthAfrica/SPOT4_HRVIR1_XS_20130615_N2A_ESouthAfricaD0000B0000/SPOT4_HRVIR1_XS_20130615_N2A_ESouthAfricaD0000B0000.xml "


L3A_DATE="20130501"
HALF_SYNTHESIS="50"
#end of USER modif

if [ $# -lt 3 ]
then
  echo "Usage: $0 <resolution> <out folder name> <bands mapping file> [scattering coefficient file - S2 case only]"
  echo "The file with input xmls should be given. The resolution for which the computations will be performed should be given. The output directory should be given" 1>&2  
  exit
fi

SCAT_COEF=""
if [ $# == 4 ] ; then    
    ./run_composite.sh "$inputXML" "$1" "$2" "$L3A_DATE" "$HALF_SYNTHESIS" "$3" "$4"
else
    ./run_composite.sh "$inputXML" "$1" "$2" "$L3A_DATE" "$HALF_SYNTHESIS" "$3"
fi


