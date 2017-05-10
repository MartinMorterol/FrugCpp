nom=exe
rm ./build/$nom
rm $nom
mkdir build
cd build;
cmake ..;
make;
cp $nom ../$nom
cd ..
./$nom $@
