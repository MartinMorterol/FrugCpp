nom=exe
rm ./build/$nom
rm $nom
mkdir build
cd build;
cmake ..;
make 2>&1 | less;
cp $nom ../$nom
cd ..
./$nom $@
